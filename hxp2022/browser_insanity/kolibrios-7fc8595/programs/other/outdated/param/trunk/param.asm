use32

   org 0x0

   db 'MENUET01'
   dd 0x01
   dd START
   dd I_END
   dd 0x100000
   dd 0x7fff0
   dd I_PARAM              ; 㪠��⥫� �� ��ࠬ����

include "lang.inc"
include "cmdipc.inc"       ; ��������� 䠩� CMDIPC.INC

START:
 call initipc              ; ���樠����஢��� ��� ࠡ��� � CMD

 mov eax,47                ; �뢥�� ᮮ�饭��
 mov ebx,mess
 call print

 call eol                  ; �ய����� ��ப�
 call eol

 cmp [I_PARAM],byte 0      ; �஢����, ���� �� ��ࠬ����
 jz noparam

 mov eax,43
 mov ebx,mess1
 call print

 call eol

 mov eax,30                ; �뢥�� ��ࠬ����
 mov ebx,I_PARAM
 call print

 jmp end1                  ; ���室 � ����� �ணࠬ��

noparam:
 mov eax,40                ; �뢥�� ᮮ�饭�� � ⮬, �� ��� ��ࠬ��஢
 mov ebx,mess2
 call print

end1:
 jmp endipc               ; �������� �ணࠬ��

mess db 'PARAM.ASM - Test params in IPC programs for CMD'

mess1 db 'This program was started with this params: '
mess2 db 'This program was started without params!'

I_PARAM db 0

I_END: