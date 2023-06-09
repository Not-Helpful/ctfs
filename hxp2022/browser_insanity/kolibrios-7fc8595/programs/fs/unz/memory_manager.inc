;MM_ = MemoryManager
;��� ����� �������� �뤥���� ������ �����쪨�� ���窠��, ��⨬��쭮 �ᯮ����
;��࠭��� �����
;����� - �� ���� ��� ��᪮�쪮 ��࠭��, ����� ����� ������
;� MM_BlockInfo � ����� � ���� ����� �⥪���ࠧ��� ��������(� ��᫥
;����� � ����訬 ���ᠬ), �����稢��饩�� dword 0. � ��砫� �����
;��室���� �����. � ������� ��室���� ���� dword'��: ��砫�
;���⪮�, �� �����(���. ����+1). �� ���� �ᥣ�� ��������� ��
;�ᯮ������� ����뢠����
;���⪮� � ���⭮� ���浪�, �.�. � ᠬ�� ���� ����� �㤥� ��� ������
;�� ᠬ� ���� ���⮪. ��� �뤥����� ����� �㦭� ���� ����, � ���஬
;�����筮 ���� (���� ����室���� ���� = ����訢���� ���� + ����
;��� ���� � ����묨 � ���� �����) � ��⠢��� ���� � �㦭묨 ����묨.
;��� 㤠����� ���⪠ �㦭� ⮫쪮 ���� �� ��� ���� � �㦭� ���⪮�
;� ���ࠢ��� �ᯮ������� ��⠫��� ���.
;begData1.....endData1,begData2...endData2,.......0,beg2,end2,beg1,end1


;�뤥��� ������
;return eax = 㪠��⥫� �� �뤥���� ����
;proc MM_AllocMem stdcall,Size:DWORD

;��� � �뤥����� ��㯭�� ��᪮�: �ᥣ�� �뤥��� ����� ��࠭���



align 4
MM_AllocMem:
	Size equ ebp+8
	begFree equ ebp-8 ;��砫�
	endFree equ ebp-4 ;� ����� ᢮������� ���� �� ���� ���� ��
	endArea equ ebp-12
	push	ebp
	mov	ebp,esp
	add	esp,-4*3
	push	ebx edi esi
;dps 'MEM: '
;dph [Size]
;dps ' '
				;��砫� ��� ����ᥩ
	mov	edx,[MM_NBlocks]
	cmp	edx,0
	jne	.BegTestBlocks	       ;�᫨ ������ ���, � �������� ����
	mov	ecx,[Size]
	call	AddBlock
	jmp	.return
align 4
 .BegTestBlocks:


	xor	ebx,ebx
	mov	ecx,edx
align 4
  .TestBlock:	 ;�஢�ઠ �����
		   ;�஢�ઠ: ���� �� ���� ��� ��� ����� ����
	mov	edi,[MM_BlocksInfo+ebx]
	add	edi,[MM_BlocksInfo+ebx+4]
	mov	[endArea], edi
	sub	edi,4

	cmp	dword[edi],0	 ;�᫨ � ����� ��� �� ����� �����
	jne	.NoEmptyBlock
	mov	eax,[MM_BlocksInfo+ebx]
	mov	dword[edi-4],eax
	mov	dword[edi],eax
	mov	edx,[Size]
	add	dword[edi],edx
	mov	dword[edi-8],0
	jmp	.return
align 4
 .NoEmptyBlock:
	xor	eax,eax
	push	ecx
	or	ecx,-1
	std
	repne	scasd
	cld
	pop	ecx
	mov	eax,[edi+12] ;����� ��� ���⪠
	add	eax,4
	cmp	eax,edi
	jb	@f

	add	ebx,8
	dec	ecx
	jnz	.TestBlock

	mov	ecx,[Size]
	call	AddBlock
	jmp	.return
     @@:


	mov	[begFree],eax  ;eax = ����� ���. ���⪠ + 4
	mov	[endFree],edi  ;edi = 㪠��⥫� �� ����� ��� ���⪠ - 12
	sub	dword[begFree],4
	add	dword[endFree],12

   ;�஢�ઠ ��। �ᥬ� ���⪠��
	mov	edi,[MM_BlocksInfo+ebx]
	mov	eax,[endArea]
	mov	eax,[eax-8]
	sub	eax,[MM_BlocksInfo+ebx]
	cmp	eax,[Size]
	ja	.AddInBegBlock

   ;�஢�ઠ ����� ���⪠��
	mov	eax,[endArea]
	cmp	dword[eax-12],0
	je	.EndTest ;�᫨ � ����� ⮫쪮 1 ���⮪

	sub	eax,4
     @@:
	mov	edi,[eax-12]
	sub	edi,[eax]
	cmp	edi,[Size]
	jae	.AddInMiddle
	sub	eax,8
	cmp	dword[eax-8],0
	jne	@b

   .EndTest:

   ;�஢�ઠ ��᫥ ��� ������
	mov	eax,[begFree]
	mov	edi,[endFree]
	lea	esi,[edi-8]    ;8 - ���� ��� ������
	sub	esi,eax

	cmp	esi,[Size]
	ja	.AddInEnd

	add	ebx,8
	dec	ecx
	jnz	.TestBlock

	mov	ecx,[Size]
	call	AddBlock

	jmp	.return
align 4
  .AddInBegBlock: ;�������� � ��砫�. � edi ��砫� �����
	;pop     eax

	mov	eax,edi
	add	eax,[MM_BlocksInfo+ebx+4]
	sub	eax,4
	push	eax
	call	MoveRecordsLeft
	pop	eax
	mov	[eax-4],edi
	push	edi
	add	edi,[Size]
	mov	[eax],edi
	pop	eax

	jmp	.return
align 4
  .AddInMiddle:  ;�������� ����� ���⪠��, ���=����� ���⪠ ��। ᢮����� ���⮬

	;pop     ecx   ;add     esp,4
	push	eax
	sub	eax,8
	call	MoveRecordsLeft
	pop	eax

	mov	edx,[eax]
	mov	[eax-12],edx
	add	edx,[Size]
	mov	[eax-8],edx
	mov	eax,[eax]
	jmp	.return
align 4
  .AddInEnd:  ;�������� ��᫥ ���⪮�. �di=㪠��⥫� �� 2�� ���� ���� � ��䮩 � ��� ���⪥

	;add     esp,4
	mov	eax,[edi]
	mov	[edi-12],eax
	push	eax
	add	eax,[Size]
	mov	[edi-8],eax
	pop	eax

.return:

	pop	esi edi ebx
	leave
	ret 4

restore Xren
restore Size
restore begFree
restore endFree



;eax - ���� ᤢ������ dword
;ᤢ����� ���� dword'�� �� 8B ����� ������ dword 0
align 4
proc MoveRecordsLeft
local	var1:DWORD,\
	var2:DWORD

	p2p	[var1],[eax]
	p2p	[var2],[eax-4]

     @@:
	sub	eax,8
	cmp	dword[var1],0
	je	@f

	push	dword[eax]
	p2p	[eax],[var1]
	pop	dword[var1]

	push	dword[eax-4]
	p2p	[eax-4],[var2]
	pop	dword[var2]
	jmp	@b
      @@:

	mov	dword[eax],0
	ret
endp

;ecx = ࠧ��� �ॡ㥬��� ���⪠
;�������� ���� � ᮧ���� � �� ���⮪ ࠧ��஬ ecx
align 4
proc AddBlock
	mov	edx,[MM_NBlocks]
	inc	edx
	cmp	edx,MM_MAX_BLOCKS
	ja	.ErrAlloc

	push	ecx
	add	ecx,12

	test	ecx,0FFFh	   ;���㣫塞 �� ����襩 �࠭��� ��࠭���
	jz	@f
	add	ecx,1000h
	and	ecx,0FFFFF000h
      @@:

	mcall	68,12,ecx
	mov	[MM_NBlocks],edx     ;���������� ������ � �����
	mov	[edx*4*2-4*2+MM_BlocksInfo],eax  ;begin
	mov	[edx*4*2-4+MM_BlocksInfo],ecx	 ;size
;dps 'Block '
;dph eax
;dps ' '
;dph ecx
;dnl
	mov	edx,eax
	add	edx,ecx
	mov	[edx-8],eax
	pop	dword[edx-4]
	add	[edx-4],eax
	mov	dword[edx-12],0
	ret

 .ErrAlloc:
	pop	ecx
	xor	eax,eax
	ret
endp
;-------------------------------------------------------------------------------


;㤠���  ������
;proc MM_DelMem Pointer:DWORD
align 4
MM_DelMem:
	Pointer equ ebp+8
	push	ebp
	mov	ebp,esp
; int3
	push	ebx
	mov	ecx,[MM_NBlocks]
	test	ecx,ecx
	jnz	@f
	xor	eax,eax
	pop	ebx
	leave
	ret 4
      @@:

	mov	eax,[Pointer]
	xor	ebx,ebx ;ebx - (����� �����)*8
   .TestBlocks:
	mov	edx,[MM_BlocksInfo+ebx]
	add	edx,[MM_BlocksInfo+ebx+4]
	sub	edx,8	      ;edx - 㪠��⥫� �� 1�� ����

     .TestMems:
	cmp	[edx],eax
	je	.FoundMem

	sub	edx,8
	cmp	dword[edx+4],0
	jne	.TestMems

	add	ebx,4
	loop	.TestBlocks

	xor	eax,eax
	pop	ebx
	leave
	ret 4

   .FoundMem:
	cmp	dword[edx-4],0
	jz	.EndDelMem

   .NextMoveMem:
	p2p    [edx+4],[edx-4]
	p2p    [edx],[edx-8]
	sub	edx,8
	cmp	dword[edx-4],0
	jnz	.NextMoveMem

    .EndDelMem:
	mov	dword[edx+4],0
	mov	dword[edx],0

	mov	eax,1
	pop	ebx
	leave
	ret 4

restore Pointer
