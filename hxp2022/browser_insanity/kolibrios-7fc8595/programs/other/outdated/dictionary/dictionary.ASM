
use32                ; �࠭����, �ᯮ����騩 32 ࠧ�來�� �������
    org 0                ; ������ ���� ����, �ᥣ�� 0x0
    db 'MENUET01'        ; �����䨪��� �ᯮ��塞��� 䠩�� (8 ����)
    dd 1                 ; ����� �ଠ� ��������� �ᯮ��塞��� 䠩��
    dd start             ; ����, �� ����� ��⥬� ��।��� �ࠢ�����
                         ; ��᫥ ����㧪� �ਫ������ � ������
    dd i_end             ; ࠧ��� �ਫ������
    dd mem               ; ��ꥬ �ᯮ��㥬�� �����, ��� �⥪� �⢥��� 0�100 ���� � ��஢��� �� �୨�� 4 ����
    dd mem               ; �ᯮ����� ������ �⥪� � ������ �����, �ࠧ� �� ⥫�� �ணࠬ��. ���設� �⥪� � ��������� �����, 㪠������ ���
    dd 0                ; 㪠��⥫� �� ��ப� � ��ࠬ��ࠬ�.
    dd 0;pathprog       ;���� � ��� �ண�

include "../../../macros.inc"
include "../../../proc32.inc"
include "API.INC"
include "../../../dll.inc"
include '../../../develop/libraries/box_lib/trunk/box_lib.mac'
;include '../../../KOSfuncs.inc'
;include '../../../load_lib.mac'

start:
        mcall 68,11      ;���樠�����㥬 ����
        test eax,eax
        jz Win1.Exit
        stdcall dll.Load, @IMPORT


;       mov ecx,1024
;       mov edi,pathprog
;       xor al,al
;
;       repne scasb
;
;       dec edi
;       mov esi,WordFile
;      @@:
;       lodsb
;       stosb
;       test al,al
;       jne @b

        ;GetFileInfo fStruc,pathprog,fInfo  ;�஢�ઠ �� ����稥 䠩��
        ;test eax,eax                    ;������ � ������ ࠧ��� 䠩��
        ;je WordFileOK

        ;stdcall [mb_create],msgNotFound,mbThread
        ;jmp Win1.Redraw

;WordFileOK:
;       stdcall mem.Alloc,dword [fInfo+32]
;       mov ebx,dword [fInfo+32]
;       mov [filBuffer],eax
;       add dword[fInfo+32],eax  ;����� �࠭���� 㪠��⥫� �� ����� ����
;       ReadFile fStruc,pathprog,ebx,eax,0
;       test eax,eax
;       jz Win1.Redraw
;
;       add al,30h
;       mov [NumErr],al
;       stdcall [mb_create],msgNotFound1,mbThread
;


align 4
Win1.Redraw:
        RedrawWinBeg

        xor eax,eax
        mov ebx,(524*10000h+500)
        mov ecx,(548*10000h+200)
        mov edx,73FFFFFFh
        mov edi,Win1.Caption
        int 40h                      ;���� � �஧��� 䮭o�

        mcall 9,ThreadInfo,-1

        mov eax,13
        mov ebx,[ThreadInfo+3Eh]
        inc ebx
        mov ecx,[ThreadInfo+42h]
        inc ecx
        mov edx,clWhite
        int 40h                      ;� ⥯��� �� �஧���:)

        call Perevod                 ; � ����ᮢ�� �ࠧ� ��ॢ���� ����񭭮� ᫮��
        call NextPerev
        stdcall [edit_box_draw],EditIN
        RedrawWinEnd

align 4
Win1.Events:
        WaitMessage
        dec eax
        jz Win1.Redraw
        dec eax
        jz Win1.Key
        dec eax
        jz Win1.ButtonPress

        ;stdcall [edit_box_mouse],EditIN

        jmp Win1.Events

Win1.ButtonPress:
        GetButtonPressed

        cmp ah,idbExit
        je Win1.Exit

        jmp Win1.Events

Win1.Key:
        GetKeyPressed
        stdcall [edit_box_key],EditIN
        jmp Win1.FonRedraw


Win1.Exit:

        ExitProcess

Win1.FonRedraw:               ;����ᮢ�� ������ �뢮��
        mcall 9,ThreadInfo,-1

        mov eax,13
        mov ebx,[ThreadInfo+3Eh]
        inc ebx
        mov ecx,20
        shl ecx,16
        add ecx,[ThreadInfo+42h]
        sub ecx,19
        mov edx,clWhite
        int 40h

        call Perevod
        call NextPerev
jmp Win1.Events

;-------------------------------------------------------------------------------

Perevod:              ;ᠬ ��ॢ��
        mov edi,dict;[filBuffer]

    Perev:
        xor ebx,ebx
      @@:                 ;�ࠢ���� ���. ᫮�� � ᫮��� ��� esi
        mov al,[text+ebx]
        test al,al
        je endWord
        cmp [ebx+edi],al
        jne WordNotFound
        inc ebx
        jmp @b

  endWord:
        cmp byte[ebx+edi],20h
        jne WordNotFound

        add edi,ebx
        dec edi              ;�ய�᪠�� �஡��� ��᫥ ������᪮�� ᫮��
      @@:
        inc edi
        cmp byte[edi],20h
        je @b

        xor ebx,ebx
     CopyWord:               ;�����㥬 ��ॢ�� � ��ப� ��� �뢮��
        mov al,[edi+ebx]
        cmp al,0Dh
        je @f
        mov [perevText+ebx],al
        inc ebx
        jmp CopyWord
      @@:
        mov byte[perevText+ebx],0

        OutText 7,25,perevText
        ret

  WordNotFound:          ;�᫨ ᫮�� �� ����諮
        add edi,ebx
      @@:
        cmp byte[edi],0Dh
        je NextWord
        inc edi
        cmp edi,SizeDict;dword [fInfo+32]
        jae endPerev
        jmp @b

    NextWord:
        add edi,2
        cmp edi,SizeDict;dword [fInfo+32]
        jae endPerev
        jmp Perev
    endPerev:
        ret


;-------------------------------------------------------------------------------
NextPerev:
        mov ecx,Lines
        mov edi,dict;[filBuffer]
  LinePerev:           ;横� �ᮢ���� ��ப�
        xor ebx,ebx
      @@:                 ;�ࠢ���� ���. ᫮�� � ᫮��� ��� esi
        mov al,[text+ebx]
        test al,al
        je N_endWord
        cmp [ebx+edi],al
        jne N_WordNotFound
        inc ebx
        jmp @b

  N_endWord:
        cmp ebx,0
        jne N_Ppoisk
        ret

      N_Ppoisk:             ;���� ��砫� ��ப�
        add edi,ebx
      @@:
        dec edi
        cmp byte[edi],0Ah
        jne @b
        inc edi

                             ;########�ய�᪠�� 㦥 ��ॢ��񭭮� ᫮��########
        xor ebx,ebx
    N_NoDouble:
        mov al,[text+ebx]
        test al,al
        je N_Double
        cmp [ebx+edi],al
        jne N_NoDblOk
        inc ebx
        jmp N_NoDouble

    N_Double:
        cmp byte[ebx+edi],20h
        jne N_NoDblOk

        add edi,ebx
      @@:
        inc edi
        cmp byte[edi],0Ah
        jne @b
        add edi,2
        jmp LinePerev

     N_NoDblOk:              ;############�뢮� १���⮢####################
        xor ebx,ebx        ;�����㥬 १����
     N_CopyWord:
        mov al,[edi+ebx]
        cmp al,20h
        je @f
        mov [perevText+ebx],al
        inc ebx
        jmp N_CopyWord
      @@:
        mov byte[perevText+ebx],0
        add edi,ebx

        mov eax,Lines
        sub eax,ecx
        dec eax
        shl eax,3
        add eax,45
        push ecx
        push edi
        OutText 7,ax,perevText
        pop edi
        pop ecx

      @@:
        inc edi
        cmp byte[edi],20h
        je @b


        xor ebx,ebx
     N_CopyPerev:
        mov al,[edi+ebx]
        cmp al,0Dh
        je @f
        mov [perevText+ebx],al
        inc ebx
        jmp N_CopyPerev
      @@:
        mov byte[perevText+ebx],0

        mov eax,Lines
        sub eax,ecx
        dec eax
        shl eax,3
        add eax,45
        push ecx
        push edi
        OutText 127,ax,perevText
        pop edi
        pop ecx

      @@:
        inc edi
        cmp byte[edi],0Ah
        jne @b
        inc edi

        loop @f      ;����������� �� LinePerev
        ret
      @@:
        jmp LinePerev

  N_WordNotFound:
        add edi,ebx
      @@:
        cmp byte[edi],0Dh
        je N_NextWord
        inc edi
        cmp edi,SizeDict;dword [fInfo+32]
        jae N_endPerev
        jmp @b

    N_NextWord:
        add edi,2
        cmp edi,SizeDict;dword [fInfo+32]
        jae N_endPerev
        jmp LinePerev
    N_endPerev:
        ret

;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
;------DATA---------------------------------------------------------------------
;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------

        idbExit = 1

        Lines   = 16        ;������� ��ப

        clTheme = 080B0FFh

        Win1.Caption    db 'Dictionary ENG -> RUS',0
        Win1X           = 524
        Win1Y           = 548
        Win1W           = 500
        Win1H           = 200

        Memo.X  = 5
        Memo.Y  = 20
        Memo.W  = 400
        Memo.H  = 370

        EditIN edit_box 350,5,5,0FFFFFFh,06F9480h,0,00h,0,40,\
                        text,mouse_dd,ed_focus,0,0



;       msgNotFound:
;                       dw 0
;                       db '�訡��',0
;                       db '���� dictionary.wrd �� ������',0
;                       db '�᭮',0
;                       db 0
;
;       msgNotFound1:
;                       dw 0
;                       db '!!!',0
;                       db '�訡�� �⥭�� '
;                    NumErr:    db 0
;                               db 0
;                       db '�᭮',0
;                       db 0
;
;       WordFile        db '.wrd',0


;-------------------------------------------------------------------------------
@IMPORT:
library box_lib,'box_lib.obj',msgbox,'msgbox.obj'
import  box_lib,\
        edit_box_draw,'edit_box_draw',\
        edit_box_key,'edit_box_key';,\
        ;edit_box_mouse,'edit_box_mouse'
import  msgbox,\
        mb_create,'mb_create'

dict:
include 'dictionary.wrd'

SizeDict = $;-dict


i_end:
;-------------------------------------------------------------------------------

        ;WordFP         rb 1024
;        m1 dd 0
        ;filBuffer      rd 1


        ThreadInfo:     rb 1024
        ;pathprog
        mouse_dd        rd 1
        text            rb 40
        perevText       rb 300
        ;fStruc         rb 30
        ;fInfo          rb 40
        mbThread        rb 1024


        rb 4096
mem:

