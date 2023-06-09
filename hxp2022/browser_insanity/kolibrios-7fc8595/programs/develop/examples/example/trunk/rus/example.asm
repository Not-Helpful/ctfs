;   ���⮩ �ਬ�� �ணࠬ�� ��� KolibriOS
;   ����稢��� ��� ����⮩ ������
;
;   �������஢��� FASM'��
;        ����� ������ example.asm �१ �ணࠬ�� FASM (�� ��� ����
;        �� ࠡ�祬 �⮫�)
;        � ����� ���� ������ F9 � Tinypad'�. ��� �������樨 
;        �⮡ࠦ����� �� ��᪥ �⫠��� (�ணࠬ�� BOARD)
;
;   �� ����� ����� �� �ணࠬ��஢���� ��� ������:
;        ����� �㭪樨 ����頥��� � ॣ���� eax.
;        �맮� ��⥬��� �㭪樨 �����⢫���� �������� "int 0x40".
;        �� ॣ�����, �஬� � 㪠������ � �����頥��� ���祭��,
;        ������ ॣ���� 䫠��� eflags, ��࠭�����.
;
;    �ਬ��:
;        mov eax, 1    ;�㭪�� 1 - ���⠢��� ��� � ����
;                      ;ᯨ᮪ ���㭪権 �. � DOCPACK - sysfuncr.txt
;        mov ebx, 10   ; ���न��� x=10
;        mov ecx, 20   ; ���न��� y=10
;        mov edx, 0xFFFfff ;梥� �窨
;        int 0x40      ;�맢��� �㭪��
;
;    ���� ᠬ�� � �ᯮ�짮������ �����:
;        mcall 1, 10, 20, 0xFFFfff
;---------------------------------------------------------------------

  use32              ; ������� 32-���� ०�� ��ᥬ����
  org    0           ; ������ � ���

  db     'MENUET01'  ; 8-����� �����䨪��� MenuetOS
  dd     1           ; ����� ��������� (1 ���� 2, �. ���-�)
  dd     START       ; ���� ��ࢮ� �������
  dd     I_END       ; ࠧ��� �ணࠬ��
  dd     MEM         ; ������⢮ �����
  dd     STACKTOP    ; ���� ���設� �����
  dd     0           ; ���� ���� ��� ��ࠬ��஢
  dd     0           ; ��१�ࢨ஢���

include "macros.inc" ; ������ �������� ����� ��ᥬ����騪��!

;---------------------------------------------------------------------
;---  ������ ���������  ----------------------------------------------
;---------------------------------------------------------------------

START:

red:                    ; ����ᮢ��� ����

    call draw_window    ; ��뢠�� ��楤��� ���ᮢ�� ����

;---------------------------------------------------------------------
;---  ���� ��������� �������  ----------------------------------------
;---------------------------------------------------------------------

still:
    mcall 10            ; �㭪�� 10 - ����� ᮡ���

    cmp  eax,1          ; ����ᮢ��� ���� ?
    je   red            ; �᫨ �� - �� ���� red
    cmp  eax,2          ; ����� ������ ?
    je   key            ; �᫨ �� - �� key
    cmp  eax,3          ; ����� ������ ?
    je   button         ; �᫨ �� - �� button

    jmp  still          ; �᫨ ��㣮� ᮡ�⨥ - � ��砫� 横��


;---------------------------------------------------------------------


  key:                  ; ����� ������ �� ���������
    mcall 2             ; �㭪�� 2 - ����� ��� ᨬ���� (� ah)

    mov  [Music+1], ah  ; ������� ��� ᨬ���� ��� ��� ����

    ; �㭪�� 55-55: ��⥬�� ������� ("PlayNote")
    ;   esi - ���� �������

    ;   mov  eax,55
    ;   mov  ebx,eax
    ;   mov  esi,Music
    ;   int  0x40

    ; ��� ���⪮:
    mcall 55, eax, , , Music

    jmp  still          ; �������� � ��砫� 横��

;---------------------------------------------------------------------

  button:
    mcall 17            ; 17 - ������� �����䨪��� ����⮩ ������

    cmp   ah, 1         ; �᫨ �� ����� ������ � ����஬ 1,
    jne   still         ;  ��������

  .exit:
    mcall -1            ; ���� ����� �ணࠬ��


;---------------------------------------------------------------------
;---  ����������� � ��������� ����  ----------------------------------
;---------------------------------------------------------------------

draw_window:

    mcall 12, 1       ; �㭪�� 12: ᮮ���� �� � ��砫� ���ᮢ��
	
    mcall 48, 3, sc,sizeof.system_colors
	
    ; �����: ᭠砫� ������ ��ਠ�� (���������஢����)
    ; ��⥬ ���⪨� ������ � �ᯮ�짮������ ����ᮢ

;   mov  eax,0                   ; �㭪�� 0: ��।����� ����
;   mov  ebx,200*65536+300       ; [x ����] *65536 + [x ࠧ���]
;   mov  ecx,200*65536+150       ; [y ����] *65536 + [y ࠧ���]
;   mov  edx, [sc.work]          ; 梥� 䮭�
;   or   edx, 0x33000000         ; � ⨯ ���� 3
;   mov  edi,header              ; ��������� ����
;   int  0x40

    mov   edx, [sc.work]         ; 梥� 䮭�
    or    edx, 0x33000000        ; � ⨯ ���� 3
    mcall 0, <200,300>, <200,150>, , ,title

    ; �뢮� ⥪�⮢�� ��ப�
    mov   ecx, [sc.work_text]    ; 梥� 䮭�
    or    ecx, 0x90000000        ; � ⨯ ��ப�
    mcall 4, <10, 20>, , message


    mcall 12, 2                  ; �㭪�� 12.2, �����稫� �ᮢ���

    ret                          ; ��室�� �� ��楤���


;---------------------------------------------------------------------
;---  ������ ���������  ----------------------------------------------
;---------------------------------------------------------------------

; ��� ⠪�� ��� ���⪠� "�������".
; ��ன ���� ��������� ����⨥� �������

Music:
  db  0x90, 0x30, 0

sc system_colors

message db '������ ���� �������...',0
title db '�ਬ�� �ணࠬ��',0

;---------------------------------------------------------------------

I_END:                  ; ��⪠ ���� �ணࠬ��
  rb 4096               ; ������ ��� �⥪�
align 16
STACKTOP:               ; ��⪠ ���設� �⥪� (�� ���������� �⥪
                        ; ���� � ��஭� 㬥��襭�� ���ᮢ, ��⮬�
                        ; ������ ��� ���� � ���� �ணࠬ�� ����砥���
                        ; ࠭�� 祬 ��� ���設�)
MEM:                    ; ��⪠ 㪠�뢠��� �� ����� �ணࠬ�� ����
                        ; ࠧ��� �ᯮ��㥬�� �� ����⨢��� �����
; ���� ��⪨ MEM �ᥣ�� ������ ���� ����� 祬 ���� ��⪨ I_END.
; ��⪠ STACKTOP ������ �ᯮ�������� ��᫥ ��⪨ I_END � ��। ��⪮�
;   MEM. STACKTOP ����� ��室���� � ��। I_END, �� �� �� �ࠢ��쭮.
; ����� ��⮪ ����� ���� � ��묨 �������ﬨ, ������� ᮡ���
;   �ࠢ���� ���冷� �� �ᯮ�������.