TILE_LEN	  equ 256
TILE_LEN_W	  equ TILE_LEN
TILE_LEN_H	  equ TILE_LEN
RGB_TILE_SIZE_1N4 equ (TILE_LEN*TILE_LEN*3/4) ;1/4 ���� ����� ���⨭��
RGB_TILE_SIZE_1N2 equ (TILE_LEN*TILE_LEN*3/2) ;1/2 ���� ����� ���⨭��
RGB_TILE_SIZE	  equ TILE_LEN*TILE_LEN*3     ;ࠧ��� 1-� ���⨭��
TREE_ICON_SYS16_BMP_SIZE equ 256*3*11+54 ;ࠧ��� bmp 䠩�� � ��⥬�묨 ��������
TREE_ICON_NOD16_BMP_SIZE equ 256*3* 1+54
TILE_TEXT_MAX_LEN equ 40 ;���ᨬ��쭠� ������ ⥪�� ��� �뢮�� ����� 䠩��

FRACT_TILE_00 equ 1 ;�஡�� 䠩�, 1/4 - ���孨� ���� 㣮�
FRACT_TILE_01 equ 2 ;�஡�� 䠩�, 1/4 - ������ ���� 㣮�
FRACT_TILE_10 equ 4 ;�஡�� 䠩�, 1/4 - ���孨� �ࠢ� 㣮�
FRACT_TILE_11 equ 8 ;�஡�� 䠩�, 1/4 - ������ �ࠢ� 㣮�
FRACT_TILE_ALL equ 15 ;15=1+2+4+8
FRACT_TILE_BIT00 equ 0
FRACT_TILE_BIT01 equ 1
FRACT_TILE_BIT10 equ 2
FRACT_TILE_BIT11 equ 3

;䫠��, �㦭� �� ��������:
SCALE_0BIT_USE equ 8
SCALE_1BIT_USE equ 9
SCALE_0_USE equ 0x100 ;䫠� ������ ���⨭�� ⥪�饣� �஢��
SCALE_1_USE equ 0x200 ;䫠� ������ ���⨭�� ���襣� �஢�� (�㤥� �������� � �ய�ᮢ��)

met_fr_opn db 0 ;䫠� ������ 䠩�� � ��⪠��

size_tile_struc equ 32 ;ࠧ��� �������� ⠩��
max_tiles_cols	equ 4 ;���ᨬ��쭮� �᫮ ⠩��� �� �ਭ� ����
max_tiles_rows	equ 3 ;���ᨬ��쭮� �᫮ ⠩��� �� ���� ����
max_tiles_count equ (max_tiles_cols*max_tiles_rows) ;���ᨬ��쭮� �᫮ ⠩��� � �ணࠬ��

tile_coord_x	equ dword[edi] ;���न��� x (��� ��ࠬ��� ��� ����㧪�)
tile_coord_y	equ dword[edi+ 4] ;���न��� y (��� ��ࠬ��� ��� ����㧪�)
tile_zoom	equ  byte[edi+ 8] ;����⠡ ����㦠����� ⠩��
tile_err_f	equ  byte[edi+ 9] ;��� �訡�� �� ����⨨ ����ࠦ����
tile_drobn	equ  word[edi+10] ;���� ��� ��࠭���� १���⮢ ������ �஡��� ���⨭��
tile_offs_l_load  equ 12 ;offset params last load tile
tile_key_coord_x  equ dword[edi+12] ;���न��� x (��� ���� ��᫥���� ����㧪�)
tile_key_coord_y  equ dword[edi+16] ;���न��� y (��� ���� ��᫥���� ����㧪�)
tile_key_path_len equ  byte[edi+21] ;������ ⥪�� � ���� Cache
tile_rgb_icon	equ dword[edi+22] ;㪠��⥫� �� ���� ��� �࠭���� �᭮���� ��� �����⮩ ���⨭��
tile_drobn_icon equ dword[edi+26] ;㪠��⥫� �� ���� ��� �࠭���� 4-� �஡��� ���⨭��
tile_delta_x	equ  byte[edi+30] ;ᤢ�� ⠩�� �⭮�⥫쭮 ����� �� �� x
tile_delta_y	equ  byte[edi+31] ;ᤢ�� ⠩�� �⭮�⥫쭮 ����� �� �� y


; *** ���冷� �맮�� �㭪権 �� ����㧪� ⠩��� ***
;load_tile
;       get_tile_path
;       load_new_tile (⥪��� ���⨭��)
;       get_tile_path
;       load_new_tile (������ ���⨭��)
;       get_tile_path
;       load_new_tile (������ ���⨭��)
;       get_tile_path
;       load_new_tile (������ ���⨭��)
;       get_tile_path
;       load_new_tile (������ ���⨭��)
;       get_parent_tiles (横���᪨� ��ᬮ�� த�⥫�᪨� ⠩���)
;               get_tile_path
;               load_new_tile (������ ���⨭��)


;��।������ ���न���� ����� ��ࠢ�
align 4
CursorMoveRight:
push ebx ecx
	xor ebx,ebx
	xor ecx,ecx
	mov cl,byte[map.zoom]
	dec ecx
	cmp cx,0
	jle .no_move ;�� 0-� ����⠡� �� ���������
	@@:
		rol ebx,1
		or ebx,1 ;����������� ���ᨬ����� ���न����, �� ����� ����⠡�
		loop @b
	cmp dword[map.coord_x],ebx
	jge .no_move ;�᫨ ���न��� �ࠩ���, �� ���������
		inc dword[map.coord_x]
		;ᤢ����� ��� ⠩��� �����, ��-�� ���� ⠩��� ᮢ���� � ��諮�� ����� ����㦠�� �����
		stdcall tiles_grid_move_left, tile_00,max_tiles_count,max_tiles_cols
		call but_Refresh
	.no_move:
pop ecx ebx
	ret

;��।������ ���न���� ����� ����
align 4
CursorMoveDown:
push ebx ecx
	xor ebx,ebx
	xor ecx,ecx
	mov cl,byte[map.zoom]
	dec ecx
	cmp cx,0
	jle .no_move ;�� 0-� ����⠡� �� ���������
	@@:
		rol ebx,1
		or ebx,1 ;����������� ���ᨬ����� ���न����, �� ����� ����⠡�
		loop @b
	cmp dword[map.coord_y],ebx
	jge .no_move ;�᫨ ���न��� �ࠩ���, �� ���������
		inc dword[map.coord_y]
		;ᤢ����� ��� ⠩��� �����
		stdcall tiles_grid_move_up, tile_00,max_tiles_count,max_tiles_rows
		call but_Refresh
	.no_move:
pop ecx ebx
	ret

;��६�饭�� ��⪨ �����, �� ᯨ��
align 4
but_met_up:
	stdcall dword[tl_node_move_up], tree2
	ret

;��६�饭�� ��⪨ ����, �� ᯨ��?
align 4
but_met_dn:
	stdcall dword[tl_node_move_down], tree2
	ret

;���塞 ���७�� ��� �����
align 4
fun_new_map_type:
push eax
	stdcall dword[tl_node_get_data], tree1
	cmp eax,0
	je @f
		mov dword[txt_tile_type],eax
	@@:
pop eax
	ret

;������ �ᯮ������� ⠩��� �� �⪥
align 4
proc tiles_init_grid uses eax ebx ecx edx edi, beg_tiles:dword, count:dword, cols:dword
	xor eax,eax
	xor ebx,ebx
	mov edi,[beg_tiles]
	mov ecx,[count]
	mov edx,[cols]
	@@:
		mov tile_delta_x,al
		mov tile_delta_y,bl
		add edi,size_tile_struc
		inc ax
		cmp eax,edx
		jl .old_lin
			xor eax,eax
			inc bx
		.old_lin:
		loop @b
	ret
endp

;ᤢ����� ��� �����, �뫥�訥 �⮫��� ���� ��४����� �� �ࠢ�� ��஭�
;�㭪�� �㦭� ��� ��⨬���樨 ���饭�� � ����, �� �������� ����� �� �������
;⠩�� � ��⨢��������� ��஭�, � १���� ���न���� ����設�⢠ ⠩��� �� ��������
;� ����� �ணࠬ�� �� �㤥� �����뢠�� �� ������, 祬 � ���⨣����� ��⨬�����
align 4
proc tiles_grid_move_left uses eax ebx ecx edx edi, beg_tiles:dword, count:dword, cols:dword
	xor eax,eax
	xor ebx,ebx
	mov edi,[beg_tiles]
	mov ecx,[count]
	mov edx,[cols]
	@@:
		cmp tile_delta_x,0
		jne .no_jump
			add tile_delta_x,dl ;�᫨ �⮫��� = 0, � ������塞 'cols' ��-�� �� �뫠��� �����
		.no_jump:
		dec tile_delta_x
		add edi,size_tile_struc
		loop @b
	ret
endp

;ᤢ����� ��� ��ࠢ�, �뫥�訥 �⮫��� ���� ��४����� �� ����� ��஭�
;������ ⮦� �� � tiles_grid_move_left ⮫쪮 ������� ���न���� � ����� ��஭�
align 4
proc tiles_grid_move_right uses eax ebx ecx edx edi, beg_tiles:dword, count:dword, cols:dword
	xor eax,eax
	xor ebx,ebx
	mov edi,[beg_tiles]
	mov ecx,[count]
	mov edx,[cols]
	@@:
		inc tile_delta_x
		cmp tile_delta_x,dl
		jl .no_jump
			mov tile_delta_x,0 ;�᫨ �⮫��� = 'cols', � �⠢�� ��� 0 ��-�� �� �뫠��� ��ࠢ�
		.no_jump:
		add edi,size_tile_struc
		loop @b
	ret
endp

align 4
proc tiles_grid_move_up uses eax ebx ecx edx edi, beg_tiles:dword, count:dword, rows:dword
	xor eax,eax
	xor ebx,ebx
	mov edi,[beg_tiles]
	mov ecx,[count]
	mov edx,[rows]
	@@:
		cmp tile_delta_y,0
		jne .no_jump
			add tile_delta_y,dl ;�᫨ ��ப� = 0, � ������塞 'rows' ��-�� �� �뫠���� ����
		.no_jump:
		dec tile_delta_y
		add edi,size_tile_struc
		loop @b
	ret
endp

align 4
proc tiles_grid_move_down uses eax ebx ecx edx edi, beg_tiles:dword, count:dword, rows:dword
	xor eax,eax
	xor ebx,ebx
	mov edi,[beg_tiles]
	mov ecx,[count]
	mov edx,[rows]
	@@:
		inc tile_delta_y
		cmp tile_delta_y,dl
		jl .no_jump
			mov tile_delta_y,0 ;�᫨ ��ப� = 'rows', � �⠢�� �� 0 ��-�� �� �뫠���� �����
		.no_jump:
		add edi,size_tile_struc
		loop @b
	ret
endp

align 4
proc array_tile_function uses ecx edi, beg_tiles:dword, count:dword, funct:dword
	mov edi,[beg_tiles]
	mov ecx,[count]
	@@:
		stdcall [funct],edi
		add edi,size_tile_struc
		loop @b
	ret
endp

align 4
draw_tiles:
pushad
	movzx ecx,byte[map.zoom]
	mov esi,[sc.work_text]
	or  esi,0x40000000
	mov edi,[sc.work]
	mcall SF_DRAW_NUMBER,0x20000,, (128 shl 16)+13

	stdcall array_tile_function, tile_00,max_tiles_count,draw_tile
popad
	ret

; edi - pointer tile struct
;output:
; eax - 7
; edx - coordinates to tile draw

align 4
proc tile_clear_area, height:dword
pushad
	mov cx,dx
	shl ecx,16
	mov cx,word[height]

	shr edx,16
	mov bx,dx
	shl ebx,16
	mov bx,TILE_LEN_W

	mov edx,0xffffd0
	mcall SF_DRAW_RECT
popad
	ret
endp

;���ᮢ��� ���� tile
align 4
proc draw_tile, tile:dword
pushad
	mov edi,[tile]

;*** set base point ***
	mov edx,5*65536+35
	movzx eax,tile_delta_y
	shl ax,8 ;*256
	add edx,eax
	movzx eax,tile_delta_x
	shl eax,8+16
	add edx,eax
;*** set base point ***

	mov ebx,dword[procinfo.box.width] ;�஢��塞 ������ �� ���⨭�� �� �� x
	sub ebx,min_window_w-5 ;5 - ����� ᫥�� ��� 1-� ���⨭��
	shl ebx,16
	mov bx,dx ;������ ���न��� ���� �� ���뢠����, ��⮬� ������ �� ࠢ�묨
	cmp edx,ebx
	jg .end_f

	;�஢��塞 ������ �� ���⨭�� �� �� y
	mcall SF_STYLE_SETTINGS,SSF_GET_SKIN_HEIGHT ;eax = ���� ᪨��
	mov ecx,dword[procinfo.box.height]
	mov ebx,edx
	and ebx,0xffff ;ebx = ���न��� 'y' ��� �뢮�� ⠩��
	add eax,ebx
	add eax,5+5 ;5-ࠬ��

	cmp ecx,eax
	jle .end_f

	sub ecx,eax
	cmp ecx,TILE_LEN_H
	jle @f
		mov ecx,TILE_LEN_H
	@@:

	mov eax,SF_PUT_IMAGE
	bt tile_drobn,SCALE_0BIT_USE
	jc .draw
	bt tile_drobn,SCALE_1BIT_USE
	jc .draw
	jmp @f
		.draw:
		mov ebx,tile_rgb_icon
		or ecx,TILE_LEN_W*65536 ;������� �ਭ� ��� 楫�� ���⨭��
		int 0x40 ;�뢮� �� ��࠭ 楫�� ��� 㢥��稭�� ���⨭��
		jmp .end_clear_tile
	@@:
		cmp tile_drobn,FRACT_TILE_ALL
		je .end_clear_tile
			stdcall tile_clear_area, ecx ;��⪠ ������ ⠩��
	.end_clear_tile:

	cmp tile_drobn,0
	je .info ;�᫨ ��� �� ����� �஡��� ���⨭��

	mov si,cx ;si - ���� ������ �஡��� ���⨭��
	sub si,TILE_LEN_H/2 ;si - ���� ������ �஡��� ���⨭��
	cmp cx,TILE_LEN_H/2
	jl @f
		mov cx,TILE_LEN_H/2 ;������� ����� ��� ���孥� �஡��� ���⨭��
	@@:

	and ecx,0xffff ;��࠭�� ��ன �ਭ�
	or ecx,(TILE_LEN_W/2)*65536 ;������� �ਭ� ��� �஡��� ���⨭��
	mov ebx,tile_drobn_icon
	bt tile_drobn,FRACT_TILE_BIT00
	jae @f
		int 0x40
	@@:
	add dx,TILE_LEN_H/2
	add ebx,RGB_TILE_SIZE_1N4
	bt tile_drobn,FRACT_TILE_BIT01
	jae @f
		xchg cx,si
		int 0x40
		xchg cx,si
	@@:

	sub dx,TILE_LEN_H/2
	ror edx,16
	add dx,TILE_LEN_W/2
	ror edx,16
	add ebx,RGB_TILE_SIZE_1N4
	bt tile_drobn,FRACT_TILE_BIT10
	jae @f
		int 0x40
	@@:

	add dx,TILE_LEN_H/2
	add ebx,RGB_TILE_SIZE_1N4
	bt tile_drobn,FRACT_TILE_BIT11
	jae @f
		xchg cx,si
		int 0x40
	@@:
	jmp .end_f

	.info: ;�뢮� ���ଠ樨, �� �� 㤠筮� ����⨨ ���⨭��
	bt tile_drobn,SCALE_0BIT_USE
	jc .end_f
	bt tile_drobn,SCALE_1BIT_USE
	jc .end_f
		mov ebx,edx
		add ebx,0x30003
		mov edx,tile_rgb_icon ;�� ��㤠筮� ����⨨ � tile_rgb_icon ���� � 䠩��
;;;    mov dword[edx+RGB_TILE_SIZE_1N4],0 ;�⠢�� �㫨, �� ��砩 �᫨ � ��ப� � ������ 䠩�� ����
		stdcall [str_len],tile_rgb_icon,RGB_TILE_SIZE_1N4
		mov edi,eax

		mov eax,SF_DRAW_TEXT
		mov ecx,0xff
;or ecx,0x80000000
		mov esi,TILE_TEXT_MAX_LEN

	@@:
		cmp edi,TILE_TEXT_MAX_LEN
		jg .no_line_last
			mov esi,edi
			int 0x40
			jmp .end_f
		.no_line_last:
		int 0x40
		add edx,esi
		sub edi,esi
		add ebx,10 ;���᪠���� �� ������ ��ப�
		jmp @b
	.end_f:
popad
	ret
endp

;㢥��祭�� ����⠡�
align 4
but_ZoomP:
	cmp byte[map.zoom],24
	jge @f
		inc byte[map.zoom]
		shl dword[map.coord_x],1
		shl dword[map.coord_y],1
		call but_Refresh
	@@:
	ret

;㬥��襭�� ����⠡�
align 4
but_ZoomM:
	cmp byte[map.zoom],1
	jle @f
		dec byte[map.zoom]
		shr dword[map.coord_x],1
		shr dword[map.coord_y],1
		call but_Refresh
	@@:
	ret

;��࠭���� 䠩�� � ��⪠��
align 4
but_MetSave:
	stdcall dword[tl_save_mem], tree2,0,[bmp_icon],TREE_ICON_SYS16_BMP_SIZE

	copy_path fn_metki,sys_path,file_name,0
	push eax ebx ecx edi
		stdcall dword[tl_get_mem_size], tree2,[bmp_icon]
		inc eax ;��� ����� � 䠩� �������饣� ���

		m2m [run_file_70.Buffer], [bmp_icon]
		mov [run_file_70.Function], SSF_CREATE_FILE
		mov [run_file_70.Position], 0
		mov [run_file_70.Flags], 0
		mov [run_file_70.Count], eax
		mov byte[run_file_70+20], 0
		mov [run_file_70.FileName], file_name
		mcall SF_FILE,run_file_70
	pop edi ecx ebx eax
	jmp still

;���뢠�� 䠩� � ��⪠��
align 4
but_MetLoad:
	cmp byte[met_fr_opn],0
	jne .end_f
	copy_path fn_metki,sys_path,file_name,0
	pushad
		mov byte[met_fr_opn],1
		mov [run_file_70.Function], SSF_READ_FILE
		mov [run_file_70.Position], 0
		mov [run_file_70.Flags], 0
		mov [run_file_70.Count], TREE_ICON_SYS16_BMP_SIZE
		mov byte[run_file_70+20], 0
		mov [run_file_70.FileName], file_name
		m2m [run_file_70.Buffer], [bmp_icon]
		mcall SF_FILE,run_file_70
		cmp ebx,0xffffffff
		je @f
			stdcall [tl_load_mem], tree2,0,[bmp_icon],TREE_ICON_SYS16_BMP_SIZE
			stdcall [tl_cur_beg], tree2
			stdcall [tl_draw], tree2
		@@:
		mov byte[file_name],0 ;clear file name
	popad
	.end_f:
	ret

;���������� ��⪨
align 4
but_MetAdd:
push eax
	mov eax,dword[bmp_icon]
	m2m dword[eax],  dword[map.coord_x]
	m2m dword[eax+4],dword[map.coord_y]
	m2m  word[eax+8], word[map.zoom]
	add eax,12
	stdcall dword[str_copy], eax,30,dword[edit2.text],30
	stdcall dword[tl_node_add], tree2, 0, dword[bmp_icon] 
	stdcall dword[tl_draw], tree2
pop eax
	jmp still

;���室 � ��࠭��� ��⪥
align 4
fun_goto_met:
	push eax
	stdcall dword[tl_node_get_data], tree2
	cmp eax,0
	je @f ;����� �� �⮨� �� ��⪥
		m2m dword[map.coord_x],dword[eax]
		m2m dword[map.coord_y],dword[eax+4]
		m2m word[map.zoom],word[eax+8]
		call but_Refresh
	@@:
	pop eax
	ret

;�������� �����
align 4
but_Refresh:
	call fun_new_map_type ;�஢��塞 �� �������� �� ⨯ ��ᬠ�ਢ����� 䠩���

	stdcall array_tile_function, tile_00,max_tiles_count,load_tile
	stdcall draw_tiles
	ret

align 4
proc tile_init uses eax edi, tile:dword
	mov edi,[tile]
	stdcall mem.Alloc, RGB_TILE_SIZE+300
	mov tile_rgb_icon,eax
	stdcall mem.Alloc, RGB_TILE_SIZE
	mov tile_drobn_icon,eax
	ret
endp

align 4
proc tile_destroy uses edi, tile:dword
	mov edi,[tile]
	stdcall mem.Free,tile_rgb_icon
	stdcall mem.Free,tile_drobn_icon
	ret
endp


;����㦠�� ⠩��, � ��।������� ������
align 4
proc load_tile uses eax ebx ecx edi, tile:dword
  mov edi,dword[tile] ;�����㥬 㪠��⥫� �� �������� ⠩��, ��-�� ࠡ�⠫� ����⠭��

  stdcall mem_copy, map,edi, 9 ;�����㥬 ���न���� ����� � �������� ⠩��
  movzx eax,tile_delta_x
  add tile_coord_x,eax ;ᤢ����� ���न���� ⠩��, �⭮�⥫쭮 �����
  mov al,tile_delta_y
  add tile_coord_y,eax
  stdcall get_tile_path,edi    ;��६ ���� � ⠩��

;***
  ; �஢�ઠ ���न��� ��᫥���� ����㦥���� ���⨭��
  mov eax,edi
  mov ecx,9
  @@:
    mov bl,byte[eax+tile_offs_l_load]
    cmp byte[eax],bl
    jne .st_load
    inc eax
    loop @b
  mov ebx,dword[edit1.size];�஢��塞 ⠪�� ⨯ ����, ����� �� ࠭�� ����㦥�
  cmp tile_key_path_len,bl ;�� ��������� ⨯� ����� �㦭� ⠪�� �����뢠�� 䠩��
  jne .st_load

  jmp @f    ;�᫨ ���न���� ᮢ���� � 㦥 �� ����㦠��
  .st_load: ;start load tile

  ; ��⠭���� ����� ���न��� ��� ��᫥���� ����㦥���� ���⨭��
  mov eax,edi
  add eax,tile_offs_l_load
  stdcall mem_copy, edi,eax,9
  mov ebx,dword[edit1.size]
  mov tile_key_path_len,bl
;***

  ;mov tile_drobn,0
  mov tile_drobn,SCALE_0_USE ;�⠢�� 䫠� ������ ���⨭�� ⥪�饣� �஢��
  stdcall load_new_tile,edi
  cmp tile_err_f,0
  je @f ;�᫨ 㤠筮 ���뫨 ⥪�騩 䠩� � ��⠫�� ����⢨� �ய�᪠��
;  cmp tile_err_f,6
;  je @f
    mov tile_drobn,0
    bt dword[ch2.flags],1 ;�஢��塞 ���� '���� ᭨��'
    jae .opt_drobn_false

    ;�᫨ 䠩� �� ������, �������� �
    inc tile_zoom
    shl tile_coord_y,1
    shl tile_coord_x,1
    stdcall get_tile_path,edi
    stdcall load_new_tile,edi

    cmp tile_err_f,0
    jne .no_tile_00 ;�᫨ ��㤠筮 ���뫨 � �� 㬥��蠥� ����ࠦ����
      or tile_drobn,FRACT_TILE_00
; 1 ᦠ⨥ ���⨭�� �� ����
      stdcall img_rgb_hdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN, TILE_LEN
; 2 ᦠ⨥ ���⨭�� �� �ਭ�
      stdcall img_rgb_wdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN/2
; 3 ����஢���� 1-� ���⨭�� � १�ࢭ� ����
      stdcall mem_copy, tile_rgb_icon, tile_drobn_icon, RGB_TILE_SIZE_1N4
    .no_tile_00:

    ;�᫨ 䠩� �� ������, �������� �
    inc tile_coord_y
    stdcall get_tile_path,edi
    stdcall load_new_tile,edi

    cmp tile_err_f,0
    jne .no_tile_01 ;�᫨ ��㤠筮 ���뫨 � �� 㬥��蠥� ����ࠦ����
;      mov byte[map.drobn],0
      or tile_drobn,FRACT_TILE_01
; 1 ᦠ⨥ ���⨭�� �� ����
      stdcall img_rgb_hdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN, TILE_LEN
; 2 ᦠ⨥ ���⨭�� �� �ਭ�
      stdcall img_rgb_wdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN/2
; 3 ����஢���� 2-� ���⨭�� � १�ࢭ� ����
      mov eax,tile_drobn_icon
      add eax,RGB_TILE_SIZE_1N4 ; ᤢ�� ���⨭�� ���� (�. �. ��� ������)
      stdcall mem_copy, tile_rgb_icon, eax, RGB_TILE_SIZE_1N4
    .no_tile_01:

    ;�᫨ 䠩� �� ������, �������� �
    dec tile_coord_y
    inc tile_coord_x
    stdcall get_tile_path,edi
    stdcall load_new_tile,edi

    cmp tile_err_f,0
    jne .no_tile_10 ;�᫨ ��㤠筮 ���뫨 � �� 㬥��蠥� ����ࠦ����
;      mov byte[map.drobn],0
      or tile_drobn,FRACT_TILE_10
; 1 ᦠ⨥ ���⨭�� �� ����
      stdcall img_rgb_hdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN, TILE_LEN
; 2 ᦠ⨥ ���⨭�� �� �ਭ�
      stdcall img_rgb_wdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN/2
; 3 ����஢���� 3-� ���⨭�� � १�ࢭ� ����
      mov eax,tile_drobn_icon
      add eax,RGB_TILE_SIZE_1N2 ; ᤢ�� ���⨭�� ���� (�. �. ��� ������)
      stdcall mem_copy, tile_rgb_icon, eax, RGB_TILE_SIZE_1N4
    .no_tile_10:

    ;�᫨ 䠩� �� ������, �������� �
    inc tile_coord_y
    stdcall get_tile_path,edi
    stdcall load_new_tile,edi

    cmp tile_err_f,0
    jne .no_tile_11 ;�᫨ ��㤠筮 ���뫨 � �� 㬥��蠥� ����ࠦ����
;      mov byte[map.drobn],0
      or tile_drobn,FRACT_TILE_11
; 1 ᦠ⨥ ���⨭�� �� ����
      stdcall img_rgb_hdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN, TILE_LEN
; 2 ᦠ⨥ ���⨭�� �� �ਭ�
      stdcall img_rgb_wdiv2, tile_rgb_icon, TILE_LEN*TILE_LEN/2
; 3 ᤢ�� ���⨭�� ���� ��� ����஢���� (�. �. ��� ������)
      stdcall img_rgb_hoffs, tile_rgb_icon, TILE_LEN*TILE_LEN/4, TILE_LEN/2, TILE_LEN*3/2

      ;�����㥬 ��᫥���� �஡��� ���⨭�� � ���� drobn_icon
      ;� ���஬ 㦥 �뫨 ��ନ஢��� 3 ��㣨�
      mov eax,tile_drobn_icon
      add eax,RGB_TILE_SIZE_1N4*3
      stdcall mem_copy, tile_rgb_icon, eax, RGB_TILE_SIZE_1N4
    .no_tile_11:
  .opt_drobn_false:


	bt dword[ch1.flags],1 ;�஢��塞 ���� '���� ᢥ���'
	jae @f
	cmp tile_drobn,FRACT_TILE_ALL ;�᫨ ᮡ࠭� ��� ���⨭��, � ᢥ��� 㦥 �� ��६
	je @f
		;�� ����� �뫠-�� ����祭� ���� '���� ᭨��', ��� ���ன �����﫨�� ���न����
		;��⮬� ����� �����㥬 ���न���� ����� � �������� ⠩��
		stdcall mem_copy, map,edi, 9
		movzx eax,tile_delta_x
		add tile_coord_x,eax ;ᤢ����� ���न���� ⠩��, �⭮�⥫쭮 �����
		mov al,tile_delta_y
		add tile_coord_y,eax

		xor ecx,ecx
		.zoom:
		cmp tile_zoom,0
		je @f ;��ᬠ�ਢ����� ᠬ�� ������ ���⨭��, ��室��
		call get_parent_tiles ;横���᪨� ��ᬮ�� த�⥫�᪨� ⠩���
		bt tile_drobn,SCALE_1BIT_USE
		jc @f
		cmp ecx,5 ;5 - ��࠭�祭�� �� �⥯��� �������� ���⨭��
		je @f
		jmp .zoom
	@@:

	ret
endp

;output:
;ecx - if not file = count parent levels else = 0
align 4
proc get_parent_tiles
  dec tile_zoom
  shr tile_coord_y,1
  shr tile_coord_x,1
  inc ecx

  stdcall get_tile_path,edi ;��६ ���� � ⠩��
  stdcall load_new_tile,edi
  cmp tile_err_f,0
  jne @f ;�᫨ ��㤠筮 ���뫨 � �� ������� ����ࠦ����
    or tile_drobn,SCALE_1_USE
    mov ebx,ecx
  .zoom_cycle:
    xor eax,eax
    dec ebx
    bt tile_key_coord_y,ebx
    jae .scale_bot_l
      add eax,RGB_TILE_SIZE_1N2
    .scale_bot_l:
    bt tile_key_coord_x,ebx
    jae .scale_rig_l
      add eax,TILE_LEN_W*3/2
    .scale_rig_l:
    cmp eax,0
    je .scale_top_left
      add eax,tile_rgb_icon
      stdcall mem_copy, eax, tile_rgb_icon, RGB_TILE_SIZE_1N2
    .scale_top_left:

    ;�������� ���孥� ���⨭��
    stdcall img_rgb_wcrop, tile_rgb_icon,TILE_LEN_W,TILE_LEN_W/2,TILE_LEN_H ;��१��� ��譥�
    stdcall img_rgb_wmul2, tile_rgb_icon,RGB_TILE_SIZE_1N4/3 ;��⨣����� �� �ਭ�
    stdcall img_rgb_hmul2, tile_rgb_icon,RGB_TILE_SIZE_1N2/3,TILE_LEN_W ;������� �� ����
  loop .zoom_cycle
  @@:
  ret
endp

;tile - 㪠��⥫� �� �������� ⠩��
align 4 ;����㦠�� ��।������ ⠩�
proc load_new_tile, tile:dword
  pushad

  mov [run_file_70.Function], SSF_READ_FILE
  mov [run_file_70.Position], 0
  mov [run_file_70.Flags], 0
  mov [run_file_70.Count], RGB_TILE_SIZE+300 ;+54
  m2m [run_file_70.Buffer], [bmp_icon]
  mov byte[run_file_70+20], 0
  mov [run_file_70.FileName], file_name
  mcall SF_FILE,run_file_70
  mov edi,[tile]
;  cmp ebx,0xffffffff
;  je .no_load
  cmp al,6 ;�訡�� 6 - ����� 䠩� �����稫�� ࠭�� 祬 ����
  jne @f
    xor al,al ;��� �� �訡�� �� ���譠, ��⮬� �⠢�� ��� ࠢ�� 0, ��� �� ���筮� ����⨨
  @@:
  mov tile_err_f,al
  cmp al,0
  jne .no_load

  stdcall dword[img_decode], dword[bmp_icon],ebx,0
  mov dword[data_icon],eax
  stdcall dword[img_to_rgb2], dword[data_icon],tile_rgb_icon
  stdcall dword[img_destroy], dword[data_icon]
    jmp @f
  .no_load:

  mov al,byte[map.zoom]
  cmp tile_zoom,al
  jne @f
    mov eax,tile_rgb_icon
    mov bl,tile_err_f
    add bl,'0' ;bl - ��� �訡�� ������
    mov byte[eax],bl
    inc eax
    mov byte[eax],' '
    inc eax
    stdcall mem_copy, file_name,eax,250 ;�����㥬 ���� � 䠩�� �� �訡�筮� ����⨨
  @@:
  popad
  ret
endp

;�㭪�� �������� ���� ��� � 䠩�� � ����: \z?\?\x?\?\y?
align 4
proc get_tile_path uses eax ecx edi esi, tile:dword
	mov ecx,300
	mov edi,txt_tile_path
	@@:
		mov byte[edi],0 ;��⨬ ��ப�
		inc edi
		loop @b

	mov esi,[tile] ;��६ 㪠��⥫�

	mov ecx,0x80000000 ;rol 0x80000000,1 = 1
	movzx eax,byte[esi+8] ;+8 = zoom
	.calc_coord:
		rol ecx,1 ;ecx = maximum coord
		dec ax
		cmp ax,0
		jg .calc_coord

	mov byte[txt_tile_path],'z'
	mov edi,txt_tile_path
	inc edi
	movzx eax,byte[esi+8] ;+8 = zoom
	stdcall convert_int_to_str, 300

	inc edi
	cmp byte[esi+8],9 ;+8 = zoom
	jle @f
		inc edi
	@@:
	mov byte[edi],'/'
	inc edi

	mov eax,[esi] ;coord_x
cmp eax,ecx
jge .out_of_rang ;coord_x ����� �����⨬��� ���祭�� �� �������� ����⠡�
	shr eax,10
	stdcall convert_int_to_str, 300

	@@:
		inc edi
		cmp byte[edi],'0'
		jge @b
	mov byte[edi],'/'
	inc edi
	mov byte[edi],'x'
	inc edi

	mov eax,[esi] ;coord_x
	stdcall convert_int_to_str, 300

	@@:
		inc edi
		cmp byte[edi],'0'
		jl @f
		cmp byte[edi],'9'
		jg @f
		jmp @b
	@@:

	;coord y
	mov byte[edi],'/'
	inc edi

	mov eax,[esi+4] ;coord_y
cmp eax,ecx
jge .out_of_rang ;coord_y ����� �����⨬��� ���祭�� �� �������� ����⠡�
	shr eax,10
	stdcall convert_int_to_str, 300

	@@:
		inc edi
		cmp byte[edi],'0'
		jge @b
	mov byte[edi],'/'
	inc edi
	mov byte[edi],'y'
	inc edi

	mov eax,[esi+4] ;coord_y]
	stdcall convert_int_to_str, 300

.out_of_rang:
	call get_all_path
	ret
endp

align 4
get_all_path: ;�㭪�� ��� ᮡ�࠭�� ������� ��� �� ��� ��᪮�
	mov ecx,[edit1.text]
	add ecx,[edit1.size]
	dec ecx

	stdcall [str_copy], file_name,4096-1, [edit1.text],[edit1.max]

	cmp byte[ecx],'/'
	je @f
		stdcall [str_catchar],file_name,4096-1, dword '/'
	@@:

	stdcall [str_cat], file_name,4096-1, txt_tile_path,300
	stdcall [str_cat], file_name,4096-1, [txt_tile_type],10
	ret