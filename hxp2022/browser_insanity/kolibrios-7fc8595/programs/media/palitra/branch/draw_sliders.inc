draw_result:
    ;.................................................................................................
    ; ������ ࠬ�� �뢮�� १����
    ;.................................................................................................
    mcall   SF_DRAW_RECT, <4,110>,   <9, 197>, [sc.work_graph]
    mcall               , <5,110-2>, <10,195>, [sc.work_light]

    ;.................................................................................................
    ; ���ᮢ�� १���� 梥� � hex color2
    ;.................................................................................................
    CURCOLX = 11
    CURCOLY = 17
    mcall   , <CURCOLX+5,15>, <CURCOLY+4,15>, 0x222222
    ; color 2 - draw color
    mcall   , <CURCOLX+6,13>, <CURCOLY+5,13>, [color2]
    ; color 1 - draw fringle
    mcall   , <CURCOLX+0,15>, <CURCOLY+0,15>, 0x222222
    ; color 2 - draw color
    mcall   , <CURCOLX+1,13>, <CURCOLY+1,13>, [color]

    ; value - draw fringle
    mcall   , <CURCOLX+23,72>, <CURCOLY+0,19>, 0x222222
    ; value - draw background
    mcall   , <CURCOLX+24,70>, <CURCOLY+1,17>, 0xFFFFFF

    ; �㭪�� 47 - �뢮� �᫠ � ����
    ; ebx - ��ࠬ���� �८�ࠧ������ �᫠ � ⥪�� (HEX)
    mcall   SF_DRAW_NUMBER, 256+8 shl 16, [color], <CURCOLX+27,CURCOLY+2>, 0x10000000, 0

    ; �㭪�� 4: ������� ⥪�� � ����
    ; edx - ��㥬 '#'
    ; esi - ����� ⥪�� � �����
    ; mcall   SF_DRAW_TEXT, <38,20>, 0, hex, 1

    ;.................................................................................................
    ; ���ᮢ�� r g b ���祭��
    ;.................................................................................................
    call    get_spectr

    movzx   eax,[cred]                    ; ����
    mov     ebx,12*65536+190               ; [x ��砫��] *65536 + [y ��砫��]
    call    draw_value                    ; �뢮��� १����

    movzx   eax,[cgreen]                  ; ������
    mov     ebx,37*65536+190              ; [x ��砫��] *65536 + [y ��砫��]
    call    draw_value                    ; �뢮��� १����

    movzx   eax,[cblue]                   ; ᨭ��
    mov     ebx,62*65536+190              ; [x ��砫��] *65536 + [y ��砫��]
    call    draw_value                    ; �뢮��� १����

    movzx   eax,[calpha]                  ; ����
    mov     ebx,87*65536+190              ; [x ��砫��] *65536 + [y ��砫��]
    call    draw_value                    ; �뢮��� १����

    ;.................................................................................................
    ; �뢮��� �㪢� r g b a
    ;.................................................................................................
    mov     eax,SF_DRAW_TEXT  ; 4 - �뢥�� ��ப� ⥪�� � ����
    mov     ebx,18 shl 16+DRAWY+32              ; [���न��� �� �� x]*65536 + [���न��� �� �� y]
    mov     ecx, 0x00000000               ; 0xX0RRGGBB (RR, GG, BB ������ 梥� ⥪��)
    add     ecx, [sc.work_text]
    mov     edx,cname                     ; 㪠��⥫� �� ��砫� ��ப�
    mov     esi,1                         ; �뢮���� esi ᨬ�����
    newline:                              ; 横�
      int     0x40                        ; ���뢠���
      add     ebx,25 shl 16               ; ������塞
      inc     edx                         ; ������塞
      cmp     [edx],byte 'x'              ; �ࠢ����� � ���⮬ �
    jne    newline                        ; �᫨ �� ��� ��� �� ࠢ��

    ;.................................................................................................
    ; ���ᮢ�� ᫠���஢
    ;.................................................................................................
    ; �㭪�� 13 - ���ᮢ��� ��אַ㣮�쭨�

     mov ebx, 18*65536+18
     mov ecx, 55*65536+55

     push dword 0xFC5663
     push dword 0xFA0919
     push dword 0xE20516
     push dword 0xFA0919

     call Draw_base

     add ebx, 20*65536+20

     push dword 0x33F742
     push dword 0x0ADD18
     push dword 0x08CE19
     push dword 0x08CE19

     call Draw_base

     add ebx, 20*65536+20

     push dword 0x88A6FF
     push dword 0x3366FF
     push dword 0x114DFF
     push dword 0x114DFF

     call Draw_base

     add ebx, 20*65536+20

     push dword 0xDADADA
     push dword 0xB9B9B9
     push dword 0xA9A9A9
     push dword 0xA9A9A9

     call Draw_base

    ;.................................................................................................
    ; ���ᮢ�� ����㭪��
    ;.................................................................................................
     mov ebx, 13*65536+13
     mov ecx, (55-3)*65536+(55-3)
     movzx   eax,[cred]
     call draw_slider

     mov ebx, (13+25*1)*65536+(13+25*1)
     mov ecx, (55-3)*65536+(55-3)
     movzx   eax,[cgreen]
     call draw_slider

     mov ebx, (13+25*2)*65536+(13+25*2)
     mov ecx, (55-3)*65536+(55-3)
     movzx   eax,[cblue]
     call draw_slider

     mov ebx, (13+25*3)*65536+(13+25*3)
     mov ecx, (55-3)*65536+(55-3)
     movzx   eax,[calpha]
     call draw_slider


    ret                                   ; �����頥� �ࠢ�����
;end_draw_result

Draw_base:
push ebp
mov ebp, esp

add ebx, 1*65536+4
mcall SF_DRAW_LINE, , , 0
add ecx, 128*65536+128
int     0x40

sub ebx, 1*65536+4
sub ecx, (128-1)*65536+1
int     0x40

add ebx, 1*65536+1
mov edx, dword [ebp+20]
int     0x40

add ebx, 1*65536+1
mov edx, dword [ebp+16]
int     0x40

add ebx, 1*65536+1
mov edx, dword [ebp+12]
int     0x40

add ebx, 1*65536+1
mov edx, dword [ebp+8]
int     0x40

add ebx, 1*65536+1
mov edx, 0
int     0x40

sub ecx, 1*65536+(128-1)

pop ebp
ret 4*4



draw_slider:
shr eax, 1
mov edx, eax
shl edx, 16
or eax, edx
sub ecx, eax
add ecx, 127*65536+127

add ecx, 1*65536+5
mcall SF_DRAW_LINE, , , 0
add ebx, 15*65536+15
int     0x40

sub ebx, 14*65536+1
sub ecx, 1*65536+5
int     0x40

mov edx, 0xFFFFFF
add ecx, 1*65536+1
int     0x40

mov edx, 0xE1E1E1
add ecx, 1*65536+1
int     0x40
add ecx, 1*65536+1
int     0x40
add ecx, 1*65536+1
int     0x40

mov edx, 0xB9B9B9
add ecx, 1*65536+1
int     0x40

mov edx, 0
add ecx, 1*65536+1
int     0x40

ret

;end_slider
