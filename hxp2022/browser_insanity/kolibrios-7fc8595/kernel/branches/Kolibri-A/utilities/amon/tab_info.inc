;
; Ghost Monitor - ������� (������) ������������ � ����������� �������
; Copyright (C) 2005, 2006, 2007 Mihailov Ilia (ghost.nsk@mail.ru)
; All Right Reserved

;
;
; ������� ���������� � �������
;
; �������� ��� ������ (�������� �����)
;
;

	; ����� ���������
	mov	edx, lab_info_tab
	mov	ebx, 17 * 65536 + 285
	call	show_text

	; ����� ������������� ����������
	mov	edx, Vendor
	mov	esi, 12
	mov	ebx, 160 * 65536 + 285
	int	0x40
	; ��������� MMX
	mov	ebx, 160 * 65536 + 305
	mov	esi, 3
	mov	edx, msg_yes
	cmp	byte[CPU_mmx], 1
	je	mmx_en
	mov	edx, msg_no
mmx_en:	int	0x40
	; ��� �����������
	mov	edx, [hwm_chip_name]
	or	ecx, 0x80000000
	mov	ebx, 160 * 65536 + 325
	mov	al, 4
	int	0x40
	; ������� ����������
	mov	eax, 18
	mov	ebx, 5
	int	0x40

	xor	edx, edx
	mov	ebx, 1000000
	div	ebx
	mov	ecx, eax
	call	digit_len
	mov	eax, 47
	mov	edx, 160 * 65536 + 295
	xor	esi, esi
	int	0x40
	
	; push	eax			; ������� ��� ����� ����������� ftoa
	; fild	dword[esp]
	; push	1000;000
	; fidiv	dword[esp]
	; fidiv	dword[esp]
	; fstp	dword[esp]
	; mov	esi, esp
	; call	ftoa
	; mov	ebx, 160 * 65536 + 295
	; mov	edx, Data_String
	; mov	eax, 4
	; mov	esi, 7
	; xor	ecx, ecx
	; int	0x40
	; pop	eax
	; pop	eax
	
	; ��������� � ������ ����������
	mov	eax, 47
	mov	ebx, 0x10100
	xor	ecx, ecx
	mov	cl, [CPU_fam]
	mov	edx, 250 * 65536 + 285
	xor	esi, esi
	int	0x40
	mov	cl, [CPU_mod]
	add	edx, 10 * 65536
	int	0x40
	
	; ����������� ���������
	call	multiplier
	test	ecx, ecx
	jz	@f
	movzx	ecx, cl
	push	ecx
	fild	dword[esp]
	push	10
	fidiv	dword[esp]
	fstp	dword[esp]
	mov	esi, esp
	call	ftoa
	mov	ebx, 160 * 65536 + 315
	mov	edx, Data_String
	mov	eax, 4
	mov	esi, eax
	xor	ecx, ecx
	int	0x40
	pop	eax
	pop	eax
@@:
	; ��������� ������
if (OS_version >= 0x0530)
	mov	eax, 18
	mov	ebx, 16
	int	0x40
	mov	ecx, eax
	call	digit_len
	mov	eax, 47
	mov	edx, 160 * 65536 + 335
	xor	esi, esi
	int	0x40
end if
	
	; ����������� ���������
	mov	eax, 4
	mov	ebx, 152 * 65536 + 285
	mov	edx, dub_p
	mov	esi, 1
	mov	ecx, 6		; <- ���������� �����
nxt_dp:	push	ecx
	mov	ecx, 0x10000000
	int	0x40
	add	ebx, 10
	pop	ecx
	loop	nxt_dp
;---------------------------------------------------------------------	
	jmp	end_drow_tab
dub_p	db	':'

lab_info_tab mls \
	'CPU Vendor',\
	'CPU frequency (MHz)',\
	'MMX tehnology',\
	'Multiplier',\
	'Monitoring chip',\
	'Free memory (Kb)'
