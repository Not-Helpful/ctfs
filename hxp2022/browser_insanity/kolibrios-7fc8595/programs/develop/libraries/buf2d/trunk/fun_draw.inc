;
;*** �㭪樨 �ᮢ���� � ���� ***
;

align 16
proc buf_draw_buf, buf_struc:dword
	pushad
	mov edi,[buf_struc]
	cmp buf2d_bits,24
	jne .error
		mov eax,7
		mov ebx,buf2d_data

		mov ecx,buf2d_w
		ror ecx,16
		mov edx,buf2d_h
		mov cx,dx

		mov edx,buf2d_size_lt
		ror edx,16
		int 0x40
		jmp .end_draw_24
	.error:
		stdcall print_err,sz_buf2d_draw,txt_err_n24b
	.end_draw_24:
	popad
	ret
endp

align 4
txt_err_size_w16 db 'image width < 16 pixels',13,10,0

;input:
; ebx = coord x
; ecx = coord y
; edx = pixel color
; edi = pointer to buffer struct
align 4
draw_pixel:
	;cmp buf2d_bits,24
	;jne @f
	bt ebx,31
	jc @f
	bt ecx,31
	jc @f
	cmp ebx,buf2d_w
	jge @f
	cmp ecx,buf2d_h
	jge @f
	push esi
		mov esi,buf2d_w ;size x
		imul esi,ecx ;size_x*y
		add esi,ebx	 ;size_x*y+x
		cmp buf2d_bits,8
		je .beg8
		cmp buf2d_bits,32
		je .beg32
			lea esi,[esi+esi*2] ;(size_x*y+x)*3
			add esi,buf2d_data  ;ptr+(size_x*y+x)*3
			mov word[esi],dx ;copy pixel color
			ror edx,16
			mov byte[esi+2],dl
			ror edx,16
			jmp .end_draw
		.beg8: ;�ᮢ���� �窨 � 8 ��⭮� ����
			add esi,buf2d_data  ;ptr+(size_x*y+x)
			mov byte[esi],dl
			jmp .end_draw
		.beg32: ;�ᮢ���� �窨 � 32 ��⭮� ����
			shl esi,2
			add esi,buf2d_data  ;ptr+(size_x*y+x)
			mov dword[esi],edx
		.end_draw:
	pop esi
	@@:
	ret

;input:
; ebx = coord x
; ecx = coord y
; edi = pointer to buffer struct
;output:
; eax = 梥� �窨
; � ��砥 �訡�� eax = 0xffffffff
align 4
get_pixel_8:
	mov eax,0xffffffff

	bt ebx,31
	jc @f
	bt ecx,31
	jc @f
	cmp ebx,buf2d_w
	jge @f
	cmp ecx,buf2d_h
	jge @f
	push esi
		mov esi,buf2d_w ;size x
		imul esi,ecx ;size_x*y
		add esi,ebx	 ;size_x*y+x
		add esi,buf2d_data  ;ptr+(size_x*y+x)

		movzx eax,byte[esi] ;copy pixel color
	pop esi
	@@:
	ret

;input:
; ebx = coord x
; ecx = coord y
; edi = pointer to buffer struct
;output:
; eax = 梥� �窨
; � ��砥 �訡�� eax = 0xffffffff
align 4
get_pixel_24:
	mov eax,0xffffffff

	bt ebx,31
	jc @f
	bt ecx,31
	jc @f
	cmp ebx,buf2d_w
	jge @f
	cmp ecx,buf2d_h
	jge @f
	push esi
		mov esi,buf2d_w ;size x
		imul esi,ecx ;size_x*y
		add esi,ebx	 ;size_x*y+x
		lea esi,[esi+esi*2] ;(size_x*y+x)*3
		add esi,buf2d_data  ;ptr+(size_x*y+x)*3

		xor eax,eax
		mov ax,word[esi] ;copy pixel color
		ror eax,16
		mov al,byte[esi+2]
		ror eax,16
	pop esi
	@@:
	ret

;input:
; ebx = coord x
; ecx = coord y
; edi = pointer to buffer struct
;output:
; eax = 梥� �窨
; � ��砥 �訡�� eax = 0xffffffff
align 4
get_pixel_32:
	mov eax,0xffffffff

	bt ebx,31
	jc @f
	bt ecx,31
	jc @f
	cmp ebx,buf2d_w
	jge @f
	cmp ecx,buf2d_h
	jge @f
	push esi
		mov esi,buf2d_w ;size x
		imul esi,ecx ;size_x*y
		add esi,ebx	 ;size_x*y+x
		shl esi,2
		add esi,buf2d_data  ;ptr+(size_x*y+x)*4

		mov eax,dword[esi] ;copy pixel color
	pop esi
	@@:
	ret

;input:
; ebx = coord x
; ecx = coord y
; edx = pixel color + transparent
; edi = pointer to buffer struct
; t_prop, m_prop - ����樥��� ����室��� ��� ���᫥��� �⥯��� �஧�筮��
align 16
proc draw_pixel_transp, t_prop:dword, m_prop:dword
locals
	transp_32 dd 0 ;梥� ��㥬�� �窨 + �஧�筮���
endl
	;cmp buf2d_bits,24
	;jne @f
	bt ebx,31
	jc @f
	bt ecx,31
	jc @f
	cmp ebx,buf2d_w
	jge @f
	cmp ecx,buf2d_h
	jge @f
	push eax ebx edx edi esi
		mov esi,buf2d_w ;size x
		imul esi,ecx ;size_x*y
		add esi,ebx	 ;size_x*y+x
		lea esi,[esi+esi*2] ;(size_x*y+x)*3
		add esi,buf2d_data  ;ptr+(size_x*y+x)*3

		mov edi,esi ;㪠��⥫� �� 梥� 䮭�
		mov [transp_32],edx ;梥� ��㥬�� �窨

		xor edx,edx
		mov eax,[t_prop]
		shl eax,8 ;*=256
		mov ebx,[m_prop]
		div ebx ;����塞 ����. �஧�筮�� (������ ���� �� 0 �� 255)
		bt ax,8
		jnc .over_255
			;�᫨ ����. �஧�筮�� >=256 � 㬥��蠥� ��� �� 255
			mov al,0xff
		.over_255:

		mov esi,ebp
		sub esi,4 ;㪠��⥫� �� transp_32
		mov byte[esi+3],al ;�஧�筮��� ��㥬�� �窨

		call combine_colors_0
	pop esi edi edx ebx eax
	@@:
	ret
endp

align 4
proc buf_clear, buf_struc:dword, color:dword ;���⪠ ���� ������ 梥⮬
	pushad
	mov edi,[buf_struc]

	mov ecx,buf2d_w
	mov ebx,buf2d_h
	imul ecx,ebx

	cld

	cmp buf2d_bits,8
	jne .end_clear_8
		mov edi,buf2d_data
		mov al,byte[color]
		rep stosb
		jmp .end_clear_32
	.end_clear_8:

	cmp buf2d_bits,24
	jne .end_clear_24
		mov edi,buf2d_data
		mov eax,dword[color]
		mov ebx,eax
		shr ebx,16
		@@:
			stosw
			mov byte[edi],bl
			inc edi
			loop @b
		jmp .end_clear_32
	.end_clear_24:

	cmp buf2d_bits,32
	jne .end_clear_32
		mov edi,buf2d_data
		mov eax,dword[color]
		rep stosd
		;jmp .end_clear_32
	.end_clear_32:
	popad
	ret
endp

align 4
proc buf_line_brs, buf_struc:dword, coord_x0:dword, coord_y0:dword, coord_x1:dword, coord_y1:dword, color:dword
locals
	loc_1 dd ?
	loc_2 dd ?
	napravl db ?
endl
	pushad
		mov eax,[coord_x1]
		sub eax,[coord_x0]
		bt eax,31
		jae @f
			neg eax
		@@:
		mov ebx,[coord_y1]
		sub ebx,[coord_y0]
		jnz @f
			;�᫨ ������ ��ਧ��⠫쭠� ����� y0=y1
			stdcall buf_line_h, [buf_struc], [coord_x0], [coord_y0], [coord_x1], [color]
			jmp .coord_end
		@@:
		bt ebx,31
		jae @f
			neg ebx
		@@:
		mov edx,[color]

		mov [napravl],byte 0 ;bool steep=false
		cmp eax,ebx
		jle @f
			mov [napravl],byte 1 ;bool steep=true
			swap dword[coord_x0],dword[coord_y0] ;swap(x0, y0);
			swap dword[coord_x1],dword[coord_y1] ;swap(x1, y1);
		@@:
		mov eax,dword[coord_y0] ;x0
		cmp eax,dword[coord_y1] ;if(x0>x1)
		jle @f
			swap dword[coord_y0],dword[coord_y1] ;swap(x0, x1);
			swap dword[coord_x0],dword[coord_x1] ;swap(y0, y1);
		@@:

; int deltax esi
; int deltay edi
; int error  ebp-6
; int ystep  ebp-8

		mov eax,[coord_y0]
		mov esi,[coord_y1]
		sub esi,eax ;deltax = y1-y0
		mov ebx,esi
		shr ebx,1
		mov [loc_1],ebx ;error = deltax/2

		mov eax,dword[coord_x0]
		mov edi,[coord_x1]
		mov [loc_2],dword -1 ;ystep = -1
		cmp eax,edi ;if (x0<x1) ystep = 1;
		jge @f
			mov [loc_2],dword 1 ;ystep = 1
		@@:
		sub edi,eax ;x1-x0

		bts edi,31
		jae @f
			neg edi
		@@:
		and edi,0x7fffffff ;deltay = abs(x1-x0)

		mov eax,edi
		mov edi,[buf_struc]
		cmp buf2d_bits,8
		je @f
		cmp buf2d_bits,24
		je @f
			jmp .coord_end
		@@:

		cmp [napravl],0
		jne .coord_yx
			mov ebx,dword[coord_x0]
			mov ecx,dword[coord_y0]

			@@: ;for (x=x0 ; x<x1; x++) ;------------------------------------
				cmp ecx,dword[coord_y1]
				jg @f ;jge ???
				call draw_pixel

				sub dword[loc_1],eax ;error -= deltay
				cmp dword[loc_1],0 ;if(error<0)
				jge .if0
					add ebx,[loc_2] ;y += ystep
					add [loc_1],esi ;error += deltax
				.if0:
				inc ecx
				jmp @b
			@@:
			jmp .coord_end
		.coord_yx:
			mov ebx,dword[coord_y0]
			mov ecx,dword[coord_x0]

			@@: ;for (x=x0 ; x<x1; x++) ;------------------------------------
				cmp ebx,dword[coord_y1]
				jg @f ;jge ???
				call draw_pixel

				sub dword[loc_1],eax ;error -= deltay
				cmp dword[loc_1],0 ;if(error<0)
				jge .if1
					add ecx,[loc_2] ;y += ystep
					add [loc_1],esi ;error += deltax
				.if1:
				inc ebx
				jmp @b
			@@:
	.coord_end:
	popad
	ret
endp

;�ᮢ���� ᣫ������� �����
align 4
proc buf_line_brs_sm, buf_struc:dword, coord_x0:dword, coord_y0:dword, coord_x1:dword, coord_y1:dword, color:dword
locals
	loc_1 dd ?
	loc_2 dd ?
	napravl db ?
endl
	pushad
		mov eax,[coord_x1]
		sub eax,[coord_x0]
		jnz @f
			stdcall buf_line_brs, [buf_struc], [coord_x0], [coord_y0], [coord_x1], [coord_y1], [color] ;����� |
			jmp .coord_end
		@@:
		bt eax,31
		jae @f
			neg eax
		@@:
		mov ebx,[coord_y1]
		sub ebx,[coord_y0]
		jnz @f
			;�᫨ ������ ��ਧ��⠫쭠� ����� y0=y1
			stdcall buf_line_h, [buf_struc], [coord_x0], [coord_y0], [coord_x1], [color]
			jmp .coord_end
		@@:
		bt ebx,31
		jae @f
			neg ebx
		@@:
		mov edx,[color]

		mov [napravl],byte 0 ;bool steep=false
		cmp eax,ebx
		jle @f
			mov [napravl],byte 1 ;bool steep=true
			swap dword[coord_x0],dword[coord_y0] ;swap(x0, y0);
			swap dword[coord_x1],dword[coord_y1] ;swap(x1, y1);
		@@:
		mov eax,[coord_y0] ;x0
		cmp eax,[coord_y1] ;if(x0>x1)
		jle @f
			swap dword[coord_y0],dword[coord_y1] ;swap(x0, x1);
			swap dword[coord_x0],dword[coord_x1] ;swap(y0, y1);
		@@:

; int deltax esi
; int deltay edi
; int error  ebp-6
; int ystep  ebp-8

		mov eax,[coord_y0]
		mov esi,[coord_y1]
		sub esi,eax ;deltax = y1-y0
		mov ebx,esi
		shr ebx,1
		mov [loc_1],ebx ;error = deltax/2

		mov eax,[coord_x0]
		mov edi,[coord_x1]
		mov [loc_2],dword -1 ;ystep = -1
		cmp eax,edi ;if (x0<x1) ystep = 1;
		jge @f
			mov [loc_2],dword 1 ;ystep = 1
		@@:
		sub edi,eax ;x1-x0

		bts edi,31
		jae @f
			neg edi
		@@:
		and edi,0x7fffffff ;deltay = abs(x1-x0)

		mov eax,edi
		mov edi,[buf_struc]
		cmp buf2d_bits,24
		jne .coord_end

		cmp [napravl],0
		jne .coord_yx
			mov ebx,[coord_x0]
			mov ecx,[coord_y0]

			@@: ;for (x=x0 ; x<x1; x++) ;------------------------------------
				cmp ecx,[coord_y1]
				jg @f ;jge ???
				push eax
					mov eax,esi
					sub eax,[loc_1]
					stdcall draw_pixel_transp, eax,esi
				pop eax
				add ebx,[loc_2]
				stdcall draw_pixel_transp, [loc_1],esi
				sub ebx,[loc_2]

				sub [loc_1],eax ;error -= deltay
				cmp dword[loc_1],0 ;if(error<0)
				jge .if0
					add ebx,[loc_2] ;y += ystep
					add [loc_1],esi ;error += deltax
				.if0:
				inc ecx
				jmp @b
			@@:
			jmp .coord_end
		.coord_yx:
			mov ebx,[coord_y0]
			mov ecx,[coord_x0]

			@@: ;for (x=x0 ; x<x1; x++) ;------------------------------------
				cmp ebx,[coord_y1]
				jg @f ;jge ???
				push eax
					mov eax,esi
					sub eax,[loc_1]
					stdcall draw_pixel_transp, eax,esi
				pop eax
				add ecx,[loc_2]
				stdcall draw_pixel_transp, [loc_1],esi
				sub ecx,[loc_2]

				sub [loc_1],eax ;error -= deltay
				cmp dword[loc_1],0 ;if(error<0)
				jge .if1
					add ecx,[loc_2] ;y += ystep
					add [loc_1],esi ;error += deltax
				.if1:
				inc ebx
				jmp @b
			@@:
	.coord_end:
	popad
	ret
endp

;�ᮢ���� ��ਧ��⠫쭮� �����, ��⮬� ��� ��ࠬ��� coord_y1
align 4
proc buf_line_h, buf_struc:dword, coord_x0:dword, coord_y0:dword, coord_x1:dword, color:dword
	pushad
	pushfd
		mov edi,[buf_struc]
		cmp buf2d_bits,8
		je @f
		cmp buf2d_bits,24
		je @f
			jmp .end24
		@@: ;��।������ ���न��� ����� �⭮�⥫쭮 ����

		mov ecx,dword[coord_y0]
		bt ecx,31
		jc .end24 ;�᫨ ���न��� y0 ����⥫쭠�
		cmp ecx,buf2d_h
		jge .end24 ;�᫨ ���न��� y0 ����� ����� ����

		mov ebx,dword[coord_x0]
		mov esi,dword[coord_x1]
		cmp ebx,esi
		jle @f
			xchg ebx,esi ;�᫨ x0 > x1 � ���塞 ���⠬� x0 � x1
		@@:
		bt ebx,31
		jae @f
			;�᫨ ���न��� x0 ����⥫쭠�
			xor ebx,ebx
		@@:
		cmp esi,buf2d_w
		jl @f
			;�᫨ ���न��� x0 ����� �ਭ� ����
			mov esi,buf2d_w
			dec esi
		@@:
		cmp ebx,esi
		jg .end24 ;�᫨ x0 > x1 ����� ���������� ����� ��� ���न���� x0, x1 ��室����� �� ����� �� �।���� ����

		cmp buf2d_bits,24
		je .beg24
			;�ᮢ���� � 8 ��⭮� ����
			;� edx ����塞 ��砫� 1-� �窨 ����� � ���� ����ࠦ����
			mov edx,buf2d_w ;size x
			imul edx,ecx ;size_x*y
			add edx,ebx	 ;size_x*y+x
			add edx,buf2d_data ;ptr+(size_x*y+x)
			mov edi,edx ;⥯��� ����� ������ 㪠��⥫� �� ����

			mov ecx,esi
			sub ecx,ebx ;� ecx �������⢮ �祪 ����� �뢮����� � ����
			inc ecx ;��-�� ��᫥���� �窠 ����� ⠪�� �⮡ࠦ�����
			mov eax,dword[color] ;�㤥� �ᯮ�짮���� ⮫쪮 ���祭�� � al
			cld
			rep stosb ;横� �� �� x �� x0 �� x1 (������ x1)
			jmp .end24

		.beg24: ;�ᮢ���� � 24 ��⭮� ����
		;� eax ����塞 ��砫� 1-� �窨 ����� � ���� ����ࠦ����
		mov eax,buf2d_w ;size x
		imul eax,ecx ;size_x*y
		add eax,ebx	 ;size_x*y+x
		lea eax,[eax+eax*2] ;(size_x*y+x)*3
		add eax,buf2d_data  ;ptr+(size_x*y+x)*3

		mov ecx,esi
		sub ecx,ebx ;� ecx �������⢮ �祪 ����� �뢮����� � ����
		inc ecx ;��-�� ��᫥���� �窠 ����� ⠪�� �⮡ࠦ�����
		mov edx,dword[color]
		mov ebx,edx ;���न��� x0 � ebx 㦥 �� �㦭�
		ror edx,16 ;�����稢��� ॣ���� �� �� 3-� ���� ����� � dl
		cld
		@@: ;横� �� �� x �� x0 �� x1 (������ x1)
			mov word[eax],bx ;copy pixel color
			mov byte[eax+2],dl
			add eax,3
			loop @b
		.end24:
	popfd
	popad
	ret
endp

align 4
proc buf_rect_by_size, buf_struc:dword, coord_x:dword,coord_y:dword,w:dword,h:dword, color:dword
pushad
	mov edi,[buf_struc]
	cmp buf2d_bits,8
	je @f
	cmp buf2d_bits,24
	je @f
		jmp .coord_end
	@@:

		mov eax,[coord_x]
		mov ebx,[coord_y]
		mov ecx,[w]
		;cmp ecx,1
		;jl .coord_end
		or ecx,ecx
		jz .coord_end
		jg @f
			add eax,ecx
			inc eax
			neg ecx
		@@:
		add ecx,eax
		dec ecx
		mov edx,[h]
		;cmp edx,1
		;jl .coord_end
		or edx,edx
		jz .coord_end
		jg @f
			add ebx,edx
			inc ebx
			neg edx
		@@:

		add edx,ebx
		dec edx
		mov esi,[color]
		stdcall buf_line_h, edi, eax, ebx, ecx, esi ;����� -
		stdcall buf_line_brs, edi, eax, ebx, eax, edx, esi ;����� |
		stdcall buf_line_h, edi, eax, edx, ecx, esi ;����� -
		stdcall buf_line_brs, edi, ecx, ebx, ecx, edx, esi ;����� |
	.coord_end:
popad
	ret
endp

align 4
proc buf_filled_rect_by_size, buf_struc:dword, coord_x:dword,coord_y:dword,w:dword,h:dword, color:dword
pushad
	mov edi,[buf_struc]
	cmp buf2d_bits,8
	je @f
	cmp buf2d_bits,24
	je @f
		jmp .coord_end
	@@:
		mov eax,[coord_x]
		mov ebx,[coord_y]
		mov edx,[w]
		or edx,edx
		jz .coord_end ;�᫨ ���� 0 ���ᥫ��
		jg @f ;�᫨ ���� ������⥫쭠�
			add eax,edx
			inc eax
			neg edx ;�ਭ� ������ ������⥫쭮�
		@@:
		add edx,eax
		dec edx
		mov ecx,[h]
		or ecx,ecx
		jz .coord_end ;�᫨ ���� 0 ���ᥫ��
		jg @f ;�᫨ ���� ������⥫쭠�
			add ebx,ecx ;ᤢ����� ������ ���न���� ��אַ㣮�쭨��
			inc ebx
			neg ecx ;����� ������ ������⥫쭮�
		@@:
		mov esi,[color]
		cld
		@@:
			stdcall buf_line_h, edi, eax, ebx, edx, esi ;����� -
			inc ebx
			loop @b
	.coord_end:
popad
	ret
endp

align 4
proc buf_circle, buf_struc:dword, coord_x:dword, coord_y:dword, r:dword, color:dword
locals
	po_x dd ?
	po_y dd ?
endl
	pushad
	mov edi,[buf_struc]
	cmp buf2d_bits,8
	je @f
	cmp buf2d_bits,24
	je @f
		jmp .error
	@@:
		mov edx,dword[color]

		finit
		fild dword[coord_x]
		fild dword[coord_y]
		fild dword[r]
		fldz ;px=0
		fld st1 ;py=r

		fldpi
		fmul st0,st3
		fistp dword[po_x]
		mov esi,dword[po_x] ;esi=pi*r
		shl esi,1 ;esi=2*pi*r

		;st0 = py
		;st1 = px
		;st2 = r
		;st3 = y
		;st4 = x

		@@:
			;Point(px + x, y - py)
			fld st1 ;st0=px
			fadd st0,st5 ;st0=px+x
			fistp dword[po_x]
			mov ebx,dword[po_x]
			fld st3 ;st0=y
			fsub st0,st1 ;st0=y-py
			fistp dword[po_y]
			mov ecx,dword[po_y]
			call draw_pixel
			;px += py/r
			fld st0 ;st0=py
			fdiv st0,st3 ;st0=py/r
			faddp st2,st0 ;st3+=st0
			;py -= px/r
			fld st1 ;st0=px
			fdiv st0,st3 ;st0=px/r
			fsubp st1,st0 ;st2-=st0

			dec esi
			cmp esi,0
			jge @b
		jmp .exit_fun
	.error:
		stdcall print_err,sz_buf2d_circle,txt_err_n8_24b
	.exit_fun:

	popad
	ret
endp

;�㭪�� ��� ������� ������ ��࠭�� 梥⮬
align 4
proc buf_flood_fill, buf_struc:dword, coord_x:dword, coord_y:dword, mode:dword, color_f:dword, color_b:dword
	pushad
		mov edi,[buf_struc]
		cmp buf2d_bits,24
		jne .end24

			mov ebx,[coord_x]
			mov ecx,[coord_y]
			mov edx,[color_f]
			mov esi,[color_b]

			cmp dword[mode],1 ;� ����ᨬ��� �� 'mode' ��।��塞 ����� �����⬮� �㤥� ���짮������
			je @f
				call buf_flood_fill_recurs_0 ;�������� �� ���ᥫ�� 梥� esi
				jmp .end24
			@@:
				call buf_flood_fill_recurs_1 ;�������� ���ᥫ� ����騥 梥� esi

		.end24:
	popad
	ret
endp

;input:
; ebx = coord_x
; ecx = coord_y
; edx = 梥� �������
; esi = 梥� �࠭���, �� ���ன �㤥� �� �������
; edi = buf_struc
;output:
; eax = �������
align 4
buf_flood_fill_recurs_0:
	call get_pixel_24
	cmp eax,0xffffffff ;if error coords
	je .end_fun
	cmp eax,edx ;�᫨ 梥� ���ᥫ� ᮢ��� � 梥⮬ �������, ����� ������� � �⮩ ������ 㦥 �뫠 ᤥ����
	je .end_fun

		call draw_pixel

		dec ebx
		call get_pixel_24
		cmp eax,esi
		je @f
			call buf_flood_fill_recurs_0
		@@:
		inc ebx


		inc ebx
		call get_pixel_24
		cmp eax,esi
		je @f
			call buf_flood_fill_recurs_0
		@@:
		dec ebx

		dec ecx
		call get_pixel_24
		cmp eax,esi
		je @f
			call buf_flood_fill_recurs_0
		@@:
		inc ecx

		inc ecx
		call get_pixel_24
		cmp eax,esi
		je @f
			call buf_flood_fill_recurs_0
		@@:
		dec ecx

	.end_fun:
	ret

;input:
; ebx = coord_x
; ecx = coord_y
; edx = 梥� �������
; esi = 梥� ���ᥫ��, �� ����� �㤥� �� �������
; edi = buf_struc
;output:
; eax = �������
align 4
buf_flood_fill_recurs_1:
	call get_pixel_24
	cmp eax,0xffffffff ;if error coords
	je .end_fun
	cmp eax,edx ;�᫨ 梥� ���ᥫ� ᮢ��� � 梥⮬ �������, ����� ������� � �⮩ ������ 㦥 �뫠 ᤥ����
	je .end_fun
	cmp eax,esi ;�᫨ 梥� ���ᥫ� �� ᮢ��� � ��������� 梥⮬ �������, � �४�頥� �������
	jne .end_fun

		call draw_pixel

		dec ebx
		call get_pixel_24
		cmp eax,esi
		jne @f
			call buf_flood_fill_recurs_1
		@@:
		inc ebx


		inc ebx
		call get_pixel_24
		cmp eax,esi
		jne @f
			call buf_flood_fill_recurs_1
		@@:
		dec ebx

		dec ecx
		call get_pixel_24
		cmp eax,esi
		jne @f
			call buf_flood_fill_recurs_1
		@@:
		inc ecx

		inc ecx
		call get_pixel_24
		cmp eax,esi
		jne @f
			call buf_flood_fill_recurs_1
		@@:
		dec ecx

	.end_fun:
	ret

;�㭪�� ��� �ᮢ���� �窨
align 4
proc buf_set_pixel uses ebx ecx edx edi, buf_struc:dword, coord_x:dword, coord_y:dword, color:dword
	mov edi,[buf_struc]
	mov ebx,[coord_x]
	mov ecx,[coord_y]
	mov edx,[color]
	call draw_pixel
	ret
endp

;output:
; eax = 梥� �窨
; � ��砥 �訡�� eax = 0xffffffff
align 4
proc buf_get_pixel uses ebx ecx edi, buf_struc:dword, coord_x:dword, coord_y:dword
	mov edi,[buf_struc]
	mov ebx,[coord_x]
	mov ecx,[coord_y]

	cmp buf2d_bits,8
	jne @f
		call get_pixel_8
		jmp .end_fun
	@@:
	cmp buf2d_bits,24
	jne @f
		call get_pixel_24
		jmp .end_fun
	@@:
	cmp buf2d_bits,32
	jne @f
		call get_pixel_32
		;jmp .end_fun
	@@:
	.end_fun:
	ret
endp

;�८�ࠧ������ 8-��⭮�� ���� ࠧ��஬ 16*16 � ࠧ��� 1*256 ᨬ�����
align 4
proc buf_convert_text_matrix, buf_struc:dword
	locals
		tmp_mem dd ?
		c1 dw ?
		c2 dd ?
		c3 dw ?
	endl
	pushad
	mov edi,[buf_struc]
	cmp buf2d_bits,8
	jne .error0
		mov ecx,buf2d_h
		mov ebx,ecx
		shr ebx,4 ;�।�������� �� � ���� 16 ��ப � ᨬ������, ��⮬� ����� �� 2^4
		or ebx,ebx
		jz .error1
		mov edx,buf2d_w
		imul ecx,edx ;ecx = size  8 b
		invoke mem.alloc,ecx ;�뤥�塞 �६����� ������
		mov [tmp_mem],eax ;eax - new memory

		shr edx,4 ;�।�������� �� � ���� 16 ������� � ᨬ������, ��⮬� ����� �� 2^4
		mov eax,ebx
		imul ebx,edx ;����塞 �������⢮ ���ᥫ�� �� 1 ᨬ���
		;eax = bhe - ���� �㪢�
		;ebx = bwi*bhe - �������⢮ ���ᥫ�� � 1-� �㪢�
		;edx = bwi - �ਭ� �㪢�
		;ecx,esi,edi - �ᯮ������� � 横�� .c_0
		shr buf2d_w,4
		shl buf2d_h,4 ;�८�ࠧ��뢠�� ࠧ���� ����

		cld
		mov esi,buf2d_data
		mov edi,[tmp_mem]
		mov word[c3],16
		.c_3:
			mov dword[c2],eax
			.c_2:
				mov word[c1],16
				.c_1:
					mov ecx,edx ;.c_0:
					rep movsb
					add edi,ebx
					sub edi,edx ;edi+=(bwi*bhe-bwi)
					dec word[c1]
					cmp word[c1],0
					jg .c_1
				add edi,edx
				shl ebx,4
				sub edi,ebx ;edi-=(16*bwi*bhe-bwi)
				shr ebx,4
				dec dword[c2]
				cmp dword[c2],0
				jg .c_2
			sub edi,ebx
			shl ebx,4
			add edi,ebx ;edi+=(15*bwi*bhe)
			shr ebx,4
			dec word[c3]
			cmp word[c3],0
			jg .c_3

		mov edi,[buf_struc] ;����஢���� ����� ������ � �᭮���� ����
		mov edi,buf2d_data
		mov esi,[tmp_mem]
		mov ecx,ebx
		shl ecx,8
		rep movsb
		invoke mem.free,[tmp_mem] ;��⨬ �६����� ������
		jmp .end_conv
	.error0:
		stdcall print_err,sz_buf2d_convert_text_matrix,txt_err_n8b
		jmp .end_conv
	.error1:
		stdcall print_err,sz_buf2d_convert_text_matrix,txt_err_size_w16
	.end_conv:
	popad
	ret
endp

align 4
proc buf_draw_text, buf_struc:dword, buf_t_matr:dword, text:dword, coord_x:dword, coord_y:dword, color:dword
	locals
		buf_t_matr_offs dd ?
		buf_s_matr buf_2d_header ? ;ebp-BUF_STRUCT_SIZE �����쭠� ����� ᨬ����
	endl
	pushad
	mov edi,[buf_struc]
	cmp buf2d_bits,24
	jne .error2
	mov edi,[buf_t_matr]
	cmp buf2d_bits,8
	jne .error1
		mov edx,buf2d_data
		mov [buf_t_matr_offs],edx
		mov ecx,BUF_STRUCT_SIZE ;�����㥬 �������� ⥪�⮢�� ������
		mov esi,edi
		mov edi,ebp
		sub edi,BUF_STRUCT_SIZE ;&buf_s_matr
		cld
		rep movsb
		sub edi,BUF_STRUCT_SIZE ;&buf_s_matr
		shr buf2d_h,8 ;����� ����� ᨬ���쭮�� ���� �� 256, ��� ��宦����� ����� 1-�� ᨬ����
		mov ebx,buf2d_h ;��६ ����� ᨬ����
		mov ecx,buf2d_w ;��६ �ਭ� ᨬ����

		mov eax,[coord_x]
		mov esi,[text]
		cmp byte[esi],0
		je .end_draw ;�᫨ ����� ��ப�
		@@:
			xor edx,edx
			mov dl,byte[esi] ;��६ ��� ᨬ����
			imul edx,ebx ;㬭����� ��� �� ����� ᨬ����
			imul edx,ecx ;㬭����� �� �ਭ� ᨬ����
			add edx,[buf_t_matr_offs] ;�ਡ���塞 ᬥ饭�� 0-�� ᨬ����, �. �. ����砥��� ᬥ饭�� �뢮������ ᨬ����
			mov buf2d_data,edx ;� ������� ���� ᨬ����, �⠢�� 㪠��⥫� �� �㦭� ᨬ��� �� ���� buf_t_matr
			stdcall buf_bit_blt_alpha, [buf_struc], eax,[coord_y], edi,[color]
			add eax,ecx
			.new_s:
				inc esi
				cmp byte[esi],13
				jne .no_13
					mov eax,[coord_x]
					add [coord_y],ebx
					jmp .new_s
				.no_13:
			cmp byte[esi],0
			jne @b
		jmp .end_draw
	.error1:
		stdcall print_err,sz_buf2d_draw_text,txt_err_n8b
		jmp .end_draw
	.error2:
		stdcall print_err,sz_buf2d_draw_text,txt_err_n24b
	.end_draw:
	popad
	ret
endp

;input:
; ebp+8  = p0
; ebp+12 = p1
align 4
line_len4i:
	push ebp
	mov ebp,esp
		fild word [ebp+8]
		fisub word [ebp+12]
		fmul st0,st0 ;st0=x^2
		fild word [ebp+10]
		fisub word [ebp+14]
		fmul st0,st0 ;st0=y^2
		faddp
		fsqrt
		fstp dword [ebp+12]
	pop ebp
	ret 4 ;8

align 4
proc buf_curve_bezier, buffer:dword, coord_p0:dword,coord_p1:dword,coord_p2:dword, color:dword
	locals
		delt_t dd ?
		opr_param dd ?
		v_poi_0 dd ?
	endl
	pushad

;float t, xt,yt;
;for(t=.0;t<1.;t+=.005){
;  xt=pow(1.-t,2)*x0+2*t*(1.-t)*x1+pow(t,2)*x2;
;  yt=pow(1.-t,2)*y0+2*t*(1.-t)*y1+pow(t,2)*y2;
;  dc.SetPixel(xt,yt,255L);
;}

	mov edx,[color] ;set curve color
	mov edi,[buffer]
	xor ebx,ebx
	xor ecx,ecx

	finit
	fldz

	; calculate delta t
	stdcall line_len4i, dword[coord_p1],dword[coord_p0]
	fadd dword[esp]
	add esp,4 ;pop ...

	stdcall line_len4i, dword[coord_p2],dword[coord_p1]
	fadd dword[esp]
	add esp,4 ;pop ...

	fadd st0,st0 ; len*=2
	ftst
	fstsw ax

	fld1
	sahf
	jle @f ;�������� ������� �� 0
		fdiv st0,st1
	@@:
	fstp dword[delt_t]

	ffree st0 ;1.0
	fincstp

	;fild word[coord_p2+2] ;y2
	fild word[coord_p1+2] ;y1
	fild word[coord_p0+2] ;y0
	fild word[coord_p2] ;x2
	fild word[coord_p1] ;x1
	fild word[coord_p0] ;x0
	fld dword[delt_t]
	fldz ;t=.0

	@@:
		fld1
		fsub st0,st1 ;1.-t
		fmul st0,st0 ;pow(1.-t,2)
		fmul st0,st3 ;...*x0
		fstp dword[opr_param]

		fld1
		fsub st0,st1 ;1.-t
		fmul st0,st1 ;(1.-t)*t
		fadd st0,st0
		fmul st0,st4 ;...*x1
		mov esi,dword[opr_param]
		fstp dword[opr_param]

		fld st0 ;st0=t
		fmul st0,st0 ;t^2
		fmul st0,st5 ;(t^2)*x2

		fadd dword[opr_param]
		mov dword[opr_param],esi
		fadd dword[opr_param]
		fistp word[v_poi_0] ;x

		fld1
		fsub st0,st1 ;1.-t
		fmul st0,st0 ;pow(1.-t,2)
		fmul st0,st6 ;...*y0
		fstp dword[opr_param]

		fld1
		fsub st0,st1 ;1.-t
		fmul st0,st1 ;(1.-t)*t
		fadd st0,st0
		fmul st0,st7 ;...*y1
		mov esi,dword[opr_param]
		fstp dword[opr_param]

		fld st0 ;st0=t
		fmul st0,st0 ;t^2
		fimul word[coord_p2+2] ;(t^2)*y2

		fadd dword[opr_param]
		mov dword[opr_param],esi
		fadd dword[opr_param]
		fistp word[v_poi_0+2] ;y

		mov eax,1
		mov bx,word[v_poi_0+2]
		mov cx,word[v_poi_0]
		call draw_pixel

		fadd st0,st1 ;t+dt

		fld1
		fcomp
		fstsw ax
		sahf
	jae @b

	popad
	ret
endp
