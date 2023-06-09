;
; ���� ��� ࠡ��� � ��ப��묨 �㭪�ﬨ
;

; str_len (str1)
;   ����� ��ப� (�����頥��� � eax)

; str_cat (str1, str2)
;   ���������� � ��ப� st1 ��ப� str2

; str_n_cat (str1, str2, n_len)
;   ���������� � ��ப� st1 ��ப� str2. �᫨ ��ப� str2 ������� 祬 n_len, � ����������� ���� n_len ᨬ�����.

; conv_str_to_int (buf)
;   �८�ࠧ������ ��ப� buf � �᫮ (�����頥��� � eax)

; convert_int_to_str (len)
;   �८�ࠧ������ �᫠ (eax) � ��ப� (edi). len - ������ ��ப� edi, ������ ����� �ᯮ�짮���� ��� �८�ࠧ������.


;output:
; eax = strlen
align 4
proc str_len, str1:dword
	mov eax,[str1]
	@@:
		cmp byte[eax],0
		je @f
		inc eax
		jmp @b
	@@:
	sub eax,[str1]
	ret
endp

align 4
proc str_cat uses eax ecx edi esi, str1:dword, str2:dword
	mov esi,[str2]
	stdcall str_len,esi
	mov ecx,eax
	inc ecx
	mov edi,[str1]
	stdcall str_len,edi
	add edi,eax
	cld
	repne movsb
	ret
endp

align 4
proc str_n_cat uses eax ecx edi esi, str1:dword, str2:dword, n_len:dword
	mov esi,[str2]
	mov ecx,[n_len]
	mov edi,[str1]
	stdcall str_len,edi
	add edi,eax
	cld
	repne movsb
	mov byte[edi],0
	ret
endp

;input:
; buf - 㪠��⥫� �� ��ப�, �᫮ ������ ���� � 10 ��� 16 �筮� ����
;output:
; eax - �᫮
align 4
proc conv_str_to_int uses ebx ecx esi, buf:dword
	xor eax,eax
	xor ebx,ebx
	mov esi,[buf]
	;��।������ ����⥫��� �ᥫ
	xor ecx,ecx
	inc ecx
	cmp byte[esi],'-'
	jne @f
		dec ecx
		inc esi
	@@:

	cmp word[esi],'0x'
	je .load_digit_16

	.load_digit_10: ;���뢠��� 10-���� ���
		mov bl,byte[esi]
		cmp bl,'0'
		jl @f
		cmp bl,'9'
		jg @f
			sub bl,'0'
			imul eax,10
			add eax,ebx
			inc esi
			jmp .load_digit_10
	jmp @f

	.load_digit_16: ;���뢠��� 16-���� ���
		add esi,2
	.cycle_16:
		mov bl,byte[esi]
		cmp bl,'0'
		jl @f
		cmp bl,'f'
		jg @f
		cmp bl,'9'
		jle .us1
			cmp bl,'A'
			jl @f ;��ᥨ���� ᨬ���� >'9' � <'A'
		.us1: ;��⠢��� �᫮���
		cmp bl,'F'
		jle .us2
			cmp bl,'a'
			jl @f ;��ᥨ���� ᨬ���� >'F' � <'a'
			sub bl,32 ;��ॢ���� ᨬ���� � ���孨� ॣ����, ��� ��饭�� �� ��᫥��饩 ��ࠡ�⪨
		.us2: ;��⠢��� �᫮���
			sub bl,'0'
			cmp bl,9
			jle .cor1
				sub bl,7 ;convert 'A' to '10'
			.cor1:
			shl eax,4
			add eax,ebx
			inc esi
			jmp .cycle_16
	@@:
	or ecx,ecx ;�᫨ �᫮ ����⥫쭮�
	jnz @f
		neg eax
		inc eax
	@@:
	ret
endp

;input:
; eax - �᫮
; edi - ���� ��� ��ப�
; len - ������ ����
;output:
align 4
proc convert_int_to_str, len:dword
pushad
	mov esi,[len]
	add esi,edi
	dec esi
	bt eax,31
	jae @f
		;�᫨ �᫮ ����⥫쭮�
		neg eax
		;inc eax ;???
		mov byte[edi],'-'
		inc edi
	@@:
	call .str
popad
	ret
endp

align 4
.str:
	mov ecx,0x0a ;�������� ��⥬� ��᫥��� ���������� ॣ����� ebx,eax,ecx,edx �室�� ��ࠬ���� eax - �᫮
	;��ॢ�� �᫠ � ASCII ��ப� ������ ����� ecx=��⥬� ��᫥�� edi ���� �㤠 �����뢠��, �㤥� ��ப�, ��祬 ����� ��६����� 
	cmp eax,ecx ;�ࠢ���� �᫨ � eax ����� 祬 � ecx � ��३� �� @@-1 �.�. �� pop eax
	jb @f
		xor edx,edx ;������ edx
		div ecx   ;ࠧ������ - ���⮪ � edx
		push edx  ;�������� � �⥪
		;dec edi  ;ᬥ饭�� ����室���� ��� ����� � ���� ��ப�
		call .str ;��३� �� ᠬ� ᥡ� �.�. �맢��� ᠬ� ᥡ� � ⠪ �� ⮣� ������ ���� � eax �� �⠭�� ����� 祬 � ecx
		pop eax
	@@: ;cmp al,10 ;�஢���� �� ����� �� ���祭�� � al 祬 10 (��� ��⥬� ��᫥�� 10 ������ ������� - ��譠�))
	cmp edi,esi
	jge @f
		or al,0x30 ;������ ������� ����  祬 ��� ���
		stosb      ;������� ������� �� ॣ���� al � �祪� ����� es:edi
		mov byte[edi],0 ;� ����� ��ப� �⠢�� 0, ��-�� �� �뫠��� ����
	@@:
	ret	   ;���� � �⥪� �࠭����� ���-�� �맮��� � �⮫쪮 ࠧ �� � �㤥� ��뢠����
