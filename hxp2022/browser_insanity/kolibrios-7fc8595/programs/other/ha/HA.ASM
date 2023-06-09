;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Hot Angles ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Compile with FASM
; Version 0.3.7: Oct 14, 2018

; Copyright (c) 2018, Efremenkov Sergey aka TheOnlyMirage
; All rights reserved.
; Redistribution and use in source and binary forms, with or without modification,
; are permitted provided that the following conditions are met:
;    * Redistributions of source code must retain the above copyright notice, this
;    list of conditions and the following disclaimer.
;    * Redistributions in binary form must reproduce the above copyright  notice,
;    this list of conditions and the following disclaimer in the documentation and/or
;    other materials provided with the distribution.
;    * Neither the name of the <organization> nor the names of its contributors may
;    be used to endorse or promote products derived from this software without
;    specific prior written permission.

; THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
; INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
; PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
; HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
; OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
; SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
; --------------------------------------------------------------------------------------

format binary as "" ;"kex"
use32
org 0x0    ; ������� ����� ���������� ����, ������ 0x0

UNLOCKd = 0
LOCKd   = 1
SUPERLOCKd = 2

; ���������
db 'MENUET01'     ;���������� �������������
dd 0x01           ;������
dd START_DEBUG    ;����� ����� ������ ���������
dd I_END          ;����� �����, �� ����� ������ ����� ���������
dd 0x100000       ;��������� ���-�� ������ ��� �������� ���������
dd 0x7fff0        ;��������� �������� �������� esp - ����� ����� ������� ����� ��� ��� ���� ������ � ������� ������� ������� 
dd 0, 0           ;����� ������ ���������� � ����� ������ ���� ������������ �����


include '../../macros.inc'

START_DEBUG:
   call copyKill         ;���������� ������ �� ���������� �������
   mcall  68, 11         ;������������� ����
   call loadConfig       ;��������� ������������ ����������

   cmp byte[mode], 0     ;������� ��������� - �����
   jne @f
   mcall -1
@@:
   ;����� ����� �� ������� �������?
   cmp byte[mode], 3 ;������������� �� ���������� ��� ������� � ����������� �� ������ ������
   jne @f
   mov ebx, 00000100000000000000000000100010b    ;���� ��, �� ������������� �� �������
   mcall 40
   jmp init03
@@:
   ;����� ��������� ������� ��������?
   cmp byte[mode], 2 ;������������� �� ���������� ��� ������� � ����������� �� ������ ������
   jne @f
   mov ebx, 00000100000000000000000000100010b    ;���� ��, �� ������������� �� �������
   mcall 40
   jmp init02
@@:
   ; �� ���� ��������� ������� - ������������ ����� ������
   ;mode=1 ������������ ����� ������ - ������� ��� ��������� � ����
   mov byte[mode], 1
   mov ebx, 00000100000000000000000000100000b
   mcall 40
   jmp init01



init02:
   mov dword[backAdr], mode02
   call setHotKey
mode02:
   mcall 10
   cmp eax, 2     ;��������� ������� �������
   je hotkey

   cmp byte[keyState], 0
   je mode02
   cmp   eax, 6   ;��������� ����������� � ������� ����
   je    mouse

   jmp mode02


setHotKey:    ;���������� ������� �������
   push eax ebx ecx edx
   xor ecx, ecx
   mov cl, byte[keyActivate]  ;������� ������� �������
   mov edx, 0x000
   mcall 66, 4, ecx, edx

   ;mov cl, byte[keyActivate]
   add cl, 128              ;���������� ������� �������
   ;mov edx, 0x000
   mcall 66, 4, ecx, edx
   pop edx ecx ebx eax
   ret


hotkey:
   mcall 2
   cmp eax, 1     ;����� ������ ����?
   je hotkey.end

   cmp al, 2      ;��� ���������� ������ ���� ��� ������� �������, ����� �������
   jne hotkey.end

   cmp ah, byte[keyActivate]   ;���� ������ ���� ������� �������
   jne @f

   ;�������� ��� mode 3
   cmp byte[state], SUPERLOCKd
   je hotkey.end
   cmp byte[keyState], 1
   je hotkey.end

   push eax ebx
   mcall 37, 0 ;���������� �������(���������) ���������� ����
   ;mov dword[o.x], eax
   mov word[o.y], ax
   shr eax, 16
   mov word[o.x], ax
   pop ebx eax

   mov byte[keyState], 1
   mov byte[state], UNLOCKd
   jmp hotkey.end
@@:
   push edx
   xor edx, edx
   mov dl, byte[keyActivate]
   add dl, 128
   cmp ah, dl   ;���� �������� ���� ������� �������
   jne @f       ;hotkey.end

   mov byte[keyState], 0
   mov byte[state], LOCKd
@@:
   pop edx
.end:
   jmp dword[backAdr]


init01:
   mov dword[backAdr], mode01
mode01:
  mov     eax, 10                 ; function 10 : wait until event
  mcall                           ; event type is returned in eax

  cmp   eax, 6           ;��������� ����������� � ������� ����
  je    mouse

  jmp mode01


mouse:
   push ebx
   mcall 37, 0   ;�������� ������� ���������� ����
   pop ebx

  cmp eax, 0 ;����� ������� ����
  jne @f
  ; -- ����� �������� �����. ����� ��� ������ �������� ����  (X=0, Y=0)
  push ecx
  mov ecx, 0
  call run_command
  pop ecx

  jmp dword[backAdr] ;finish
@@:
  call get_screen_size ;����� ��������� ������� ������

  cmp ax, word[screen.height]    ;Ymouse = Yscreen ?
  je Ytrue
  ;���� Y �� �����, �� ��� ���������� Y=0 � X=ScreenWidth (������ ������� ����)

  cmp ax, 0
  jne unlockend
  shr eax, 16
  cmp ax, word[screen.width]
  jne unlockend
  ; -- ����� �������� ��� ������� ��������� ����
  push ecx
  mov ecx, 2
  call run_command
  pop ecx

  jmp dword[backAdr]
Ytrue:
  ;���� Y �����, �� ��� ���������� X=0 (����� ������ ����) ��� X=ScreenWidth (������ ������)
  shr eax, 16
  cmp ax, 0
  jne @f
  ; -- X=0, Y = Height  (����� ������ ����)
  push ecx
  mov ecx, 1
  call run_command
  pop ecx
  jmp dword[backAdr]
@@:
  cmp ax, word[screen.width]
  jne unlockend
  ; -- (������ ������ ����)
  push ecx
  mov ecx, 3
  call run_command
  pop ecx

  jmp dword[backAdr]

unlockend:
  mov byte[state], UNLOCKd
  jmp dword[backAdr]



;�������� ������ ������
get_screen_size:
   push eax
   mcall 14
   ;������ � eax = [xsize]*65536 + [ysize]
   ;mov dword[screen], eax
   mov word[screen.height], ax
   shr eax, 16
   mov word[screen.width], ax
   pop eax
   ret





;������ ����������: ecx - �������� ����: lu=0, ld=1, ru=2, rd=3
run_command:
   cmp byte[state], UNLOCKd
   jne run_command.end

   push eax ebx ecx

   cmp ecx, 0
   jne @f
   mov eax, apps.path1
   cmp byte[eax], 0 ;���� �� ������ ����� (��� ����� ������ '-'), �� ����� 0
   je .set0
   mov dword[struct70.path_adr], eax
   mov eax, apps.param1
   mov dword[struct70.param_adr], eax
   jmp .end_set_path
@@:
   cmp ecx, 1
   jne @f
   mov eax, apps.path2
   cmp byte[eax], 0 ;���� �� ������ ����� (��� ����� ������ '-'), �� ����� 0
   je .set0
   mov dword[struct70.path_adr], eax
   mov eax, apps.param2
   mov dword[struct70.param_adr], eax
   jmp .end_set_path
@@:
   cmp ecx, 2
   jne @f
   mov eax, apps.path3
   cmp byte[eax], 0 ;���� �� ������ ����� (��� ����� ������ '-'), �� ����� 0
   je .set0
   mov dword[struct70.path_adr], eax
   mov eax, apps.param3
   mov dword[struct70.param_adr], eax
   jmp .end_set_path
@@:
   cmp ecx, 3
   jne .set0 ;.end_set_path
   mov eax, apps.path4
   cmp byte[eax], 0 ;���� �� ������ ����� (��� ����� ������ '-'), �� ����� 0
   je .set0
   mov dword[struct70.path_adr], eax
   mov eax, apps.param4
   mov dword[struct70.param_adr], eax
   jmp .end_set_path
.set0:
   ;mov dword[struct70.path_adr], 0
   ;mov dword[struct70.param_adr], 0
   jmp @f
.end_set_path:
   mcall 70, struct70
@@:
   mov byte[state], LOCKd
   ;mov byte[keyState], 0
   pop ecx ebx eax
.end:
   ret

struct70: ;������ �������������� ���������
  .func       dd 7 ; ����� ����������
  .mask       dd 0
  .param_adr  dd 0 ; ��������� �� ASCIIZ-������ � �����������
  .other      dd 0, 0
  .path       db 0
  .path_adr   dd 0 ; ��������� �� ������ � ����

;��� ����������������� �����
fileName: db 'SETTINGS/HA.CFG', 0


;�������� �� ����� ������� ������
gotoEndString:
   cmp eax, edx  ;���� ���� ����������, ��
   ja @f         ;�������
   cmp byte[eax], 10
   je @f
   cmp byte[eax], 0
   je @f
   cmp byte[eax], 13
   je @f
   ;����� ��������� �� ��������� ������
   inc eax
   jmp gotoEndString
@@:
   ret

;���������� �������� � ������ ������ �� ������� ����������� �������
gotoStartString:
   cmp eax, edx  ;���� ���� ����������, ��
   ja @f         ;�������
   cmp byte[eax], 10
   je .next
   cmp byte[eax], 0
   je .next
   cmp byte[eax], 13
   je .next
   jmp @f ;���� ��� ������ ������, �� �������
.next:   ;��������� �� ��������� ������
   inc eax
   jmp gotoStartString
@@:
   ret


sep: db '|' ;������ ����������� ������ ���� + ��������� �������
readPath:
   push ebx esi edi
   mov bh, 0 ; 0 -  ���� ����, ��� ��������� ��� �� �����������
   mov byte[esi], 0   ;����������������� ������-������ �������� (�� ������ ������)
   mov byte[edi], 0
@@:
   cmp eax, edx  ;���� ���� ����������, ��
   ja @f         ;�������
   mov bl, byte[eax]
   ;���� ��������� ������ �� ����� ������
   cmp bl, 10
   je @f  ;����� �����
   cmp bl, 0
   je @f
   cmp bl, 13
   je @f
   ;� �� ������ ����������
   cmp bl, byte[sep]
   jne .read
   ;���� sep ��� ��������� �����, ��
   cmp bh, 0
   jne .read ;������ ���������� ��������� ��������� ������  (� ��� ����� ���� ��� ������)
   ;����� ����� ����������� 0 � ��������� � ������ � �����������
   mov byte[esi], 0
   call trim ;��� �� ������� ������ ������ ��������� � ������� �� ����� ����� ������
   mov esi, edi
   mov bh, 1
   inc eax
   jmp @b
.read: ;�� ���������� ������ � ��� ����� � ��������� �� ��������� ������
   mov byte[esi], bl
   inc esi
   inc eax
   jmp @b
@@:
   mov byte[esi], 0 ;����� ����������� ����
   pop edi esi ebx
   ret

trim:  ;esi - ��������� ������� ������ ������
   ;push esi
   mov byte[esi], 0
   dec esi
   cmp byte[esi], 9   ;tab
   je trim
   cmp byte[esi], 32  ;space
   je trim
   inc esi
   ;pop esi
   ret


cfgFileAdr: dd 0     ;����� ����������������� ����� � ������

loadConfig:
   push eax ebx ecx edx
   mcall 68, 27, fileName   ;��������� ���������������� ���� � ���
   mov dword[cfgFileAdr], eax
   cmp eax, 0
   je loadConfig.exit       ;���� ����� ������������ ���, �� ��������� ������ ����������
   ;����� ������ ��������� � ���, ������ � edx
   cmp edx, 0               ;���� ���� ����, � ��� ��� ������, �� ��������� ������
   je loadConfig.exit

   add edx, eax             ;����� ����� � edx - ����� ����� �����

   mov byte[mode], 0
   cmp byte[eax], '0'       ;���� �������� ���������� ���������� ����� ������: �� �������
   je loadConfig.exit       ;�� ��������� ������ ����������
   cmp byte[eax], 110 ;'n'
   je loadConfig.exit

   ;����� ���������� �����
   cmp byte[eax], 121 ;'y'  ;������������ �����
   jne @f
   mov byte[mode], 1
   jmp loadConfig.modeEnd
@@:
   cmp byte[eax], '1'       ;������������ �����
   jne @f
   mov byte[mode], 1
   jmp loadConfig.modeEnd
@@:
   cmp byte[eax], '2'       ;����� ��������� �� ������� �������
   jne @f
   mov byte[mode], 2
   jmp loadConfig.modeEnd
@@:
   cmp byte[eax], '3'       ;����� ����� ��� ������� �������
   jne @f
   mov byte[mode], 3
   jmp loadConfig.modeEnd
@@:
   mov byte[mode], 0        ;�� ���� ��������� ������� - ���������
   jmp loadConfig.exit
.modeEnd:

   ;��� �� ����� ���� ������
   call gotoEndString
   ;������� ������ ��������� ������
   call gotoStartString

   push esi edi

   ;��������� ���� ��� ������ �������� ����
   mov esi, apps.path1
   mov edi, apps.param1
   call readPath
   call gotoStartString  ;������� ������ ��������� ������

   ;��������� ���� ��� ������ ������� ����
   mov esi, apps.path2
   mov edi, apps.param2
   call readPath
   call gotoStartString

   ;��������� ���� ��� ������� �������� ����
   mov esi, apps.path3
   mov edi, apps.param3
   call readPath
   call gotoStartString

   ;��������� ���� ��� ������� ������� ����
   mov esi, apps.path4
   mov edi, apps.param4
   call readPath
   call gotoStartString

   ;�������� ������ �� '-'
   call checkPathAdr

   pop edi esi

   ;���������� ������ � ������ �������
   call gotoEndString
   call gotoStartString

   ;��������� ������� ������������� �������
   push esi edi ecx
   mov esi, keystr
   mov edi, keystr
   call readPath
   ;����������� ������ � �����
   mov esi, keystr
   call strToInteger
   mov byte[keyActivate], cl
   pop ecx edi esi
   call gotoStartString

   ;��������� ������
   push esi edi ecx
   mov esi, radstr
   mov edi, radstr
   call readPath
   ;����������� ������ � �����
   mov esi, radstr
   call strToInteger
   ;������ ecx - �������� �������
   ;!!! �������� ��������, ����� ����� �� ���� ������ ������� ������
   ;��� ���������� ������� �����
   push eax edx
   mov eax, ecx ;dword[radius2]
   mul ecx
   mov dword[radius2], eax
   pop edx eax

   pop ecx edi esi

   ;��������� ������ ��������� ���������� ��� �� ����� (���� ��� ���� �������� ������ ��� �������)
   jmp .end
.exit:
   pop edx ecx ebx eax
   mcall -1 ;������� ��� ���������
.end:
   mov ecx, dword[cfgFileAdr]    ;���� ���� ��� ��������, ��
   cmp ecx, 0
   je @f
   mcall 68, 13, ecx  ;��������� ���� �� ������
@@:
   pop edx ecx ebx eax
   ret


checkPathAdr:
   push eax ebx
   xor eax, eax

   mov ebx, apps.path1
   cmp byte[ebx], '-'
   jne @f
   ;cmp byte[ebx+1], 0
   ;jne @f
   mov byte[ebx], 0
@@:
   mov ebx, apps.path2
   cmp byte[ebx], '-'
   jne @f
   ;cmp byte[ebx+1], 0
   ;jne @f
   mov byte[ebx], 0
@@:
   mov ebx, apps.path3
   cmp byte[ebx], '-'
   jne @f
   ;cmp byte[ebx+1], 0
   ;jne @f
   mov byte[ebx], 0
@@:
   mov ebx, apps.path4
   cmp byte[ebx], '-'
   jne @f
   ;cmp byte[ebx+1], 0
   ;jne @f
   mov byte[ebx], 0
@@:
   pop ebx eax
   ret

;�������������� ������ � ����� �����
strToInteger: ;����: esi - ��������� �� ������ � ���������� ������� �����, �����: e�x - �����
   push eax ebx edx edi
   xor eax, eax  ;�������� eax
   xor ecx, ecx
   mov edi, esi
.get_last_symbol:
   ;������ ��������� ������
   mov al, byte[edi]

   ;���� ��� ����, �� ������ �����������
   cmp al, 0
   je @f

   ;����� ��������� �� ��������� ������
   inc edi
   jmp .get_last_symbol
@@:   ;����� �� ���������� ������� � ����� ����� �� ���� � edi
   dec edi

   cmp edi, esi    ;����� ���������� ������� ������ ���� ������ ������ ������� �������
   jae @f
   jmp .error  ;����� ������
@@:
   ;������ � edi ��������� ������, � esi ��������� �� ������ ������ (�� ����� ������ ������)
   mov cl, byte[edi]
   sub cl, 48 ;0x30 ;'0'
   dec edi         ;��������� �� ���� ������ �� �����
   mov ebx, 10     ;��������� �������
.tranform_cicle:
   cmp edi, esi        ;���� ������ ��� �������� ������, �� ����� ������������� - �������
   jb .end

   mov eax, 0
   mov al, byte[edi]
   sub al, 48 ;'0'
   cmp al, 9 ;0x39           ;���� ����� ������ 9, �� ������ � ������ ���� ���-�� �� ���
   ja .error
   cmp al, 0 ;0x30           ;���� ����� ������ 0, �� ������ � ������ ���� ���-�� �� ���
   jb .error
   mov edx, 0
   mul ebx

   add ecx, eax

   dec edi
   mov edx, 0
   mov eax, 10
   mul ebx
   mov ebx, eax
   jmp .tranform_cicle
.error:
   mov ecx, 0
.end:
   pop edi edx ebx eax
   ret


;������� ��� ���� � ��������� ����� ������
selfName db '@HA',0
selfNameSize = 10 ;�� 11 byte
;
compareBytes:
   push edi esi ecx ebx
   xor eax, eax
   mov ecx, selfNameSize    ;max ������ ����� 11
@@:
   mov bl, byte[edi]
   cmp bl, byte[esi]
   jne compareBytes.no
   inc edi
   inc esi
   cmp ecx, 0
   je @f
   dec ecx
   jmp @b
.no:
   mov eax, 1
@@:
   pop ebx ecx esi edi
   ret
;
copyKill:
   push eax ebx ecx esi edi

   ;������ ������ ���� ����������
   mcall 9, buf, -1
   mov eax, dword[buf+30]
   mov dword[selfPID], eax

   ;���������, ������� ������� �� ��������:
   mov esi, selfName       ;������ ������ - ��� �������� ����������
   mov edi, buf            ;������ ������ - ��� �������� �����
   add edi, 10

   mov ecx, 1
@@:
   mcall 9, buf, ecx
   mov dword[slotMax], eax

   ;���� ��� �� ����, �� ���������� ��������
   mov eax, dword[buf+30]
   cmp eax, dword[selfPID]
   je copyKill.propusk

   call compareBytes   ;���������� 11 ���� �����, ��������� � eax

   cmp eax, 0
   je copyKill.selfKill

.propusk:
   inc ecx
   cmp ecx, dword[slotMax]
   ja @f
   jmp @b

.selfKill:
   pop edi esi ecx ebx eax
   mcall -1
   ret
@@:
   pop edi esi ecx ebx eax
   ret


;MODE 3
init03:
   ;mov dword[radius2], 100; 10*10
   mov dword[backAdr], mode03
   call setHotKey
mode03:
   mcall 10
   cmp eax, 2     ;��������� ������� �������
   je hotkey

   ;cmp byte[keyState], 0
   ;je mode03
   cmp   eax, 6   ;��������� ����������� � ������� ����
   je    mouse03

   jmp mode03

mouse03:
   cmp byte[keyState], 0     ;���� ������� �� ������, �� ������� ��������� ����������
   je mouse03.updateCoord

   cmp byte[state], LOCKd    ;���� ���� ������������, �� ������� ��������� ����������
   je mouse03.updateCoord

   cmp byte[state], SUPERLOCKd  ;���� �������� ���� ��������� � �������� ����������, �� ��� ���������� ������� ���������
   je @f

   call checkPointInCircle   ;����� ���� ���������� ������ ���������, �� �������� �������� ������� ����
   jmp @f
.updateCoord:
   push eax ebx
   mcall 37, 0 ;���������� �������(���������) ���������� ����
   ;mov dword[o.x], eax
   mov word[o.y], ax
   shr eax, 16
   mov word[o.x], ax
   pop ebx eax
@@:
   jmp dword[backAdr]


radius2 dd 0  ;������� ������� ��� mode 3
o:            ;���������� ��������� � ������� �����
 .x:   dw 0
 .y:   dw 0
 .cx:  dw 0
 .cy:  dw 0

;�������� ������ �� ������� �����
; sqrt( (x2-x1)^2 + (y2-y1)^2 ) <= radius
; (x2-x1)^2 + (y2-y1)^2 <= radius^2
checkPointInCircle:
   push eax ebx ecx edx
   mcall 37, 0 ;�������� ������� ���������� ����
   ;mov dword[o.cx], eax
   mov word[o.cy], ax
   shr eax, 16
   mov word[o.cx], ax

   xor eax, eax
   xor edx, edx
   mov ax, word[o.x]
   mov dx, word[o.cx]
   cmp dx, ax
   jae @f
   sub ax, dx
   mov dx, ax
   jmp .xend
@@:
   sub dx, ax
.xend:
   mov eax, edx
   mul dx

   mov ebx, eax

   xor eax, eax
   xor edx, edx
   mov ax, word[o.y]
   mov dx, word[o.cy]
   cmp dx, ax
   jae @f
   sub ax, dx
   mov dx, ax
   jmp .yend
@@:
   sub dx, ax
.yend:
   mov eax, edx
   mul dx

   add ebx, eax

   cmp ebx, dword[radius2]
   jbe @f
   call activateCorner ;����� ���������� ������ ����
 @@:
   pop edx ecx ebx eax
   ret

;�������� � ������� ������ ���� ���� � ������������ ���
activateCorner:
   push eax ecx
   xor eax, eax

   mov ax, word[o.cx]
   cmp ax, word[o.x]
   je activateCorner.end       ;���� ���������� �����, �� ������� (������ ���� �� ������)
   ja activateCorner.right

   ;����� ����� �������
   mov ax, word[o.cy]
   cmp ax, word[o.y]
   je activateCorner.end       ;���� ���������� �����, �� ������� (������ ���� �� ������)
   jb activateCorner.leftup

   ;����� ����� ������ ����
   mov ecx, 1
   call run_command
   mov byte[keyState], 0
   mov byte[state], SUPERLOCKd
   jmp activateCorner.end

.leftup:
   ;����� ������� ����
   mov ecx, 0
   call run_command
   mov byte[keyState], 0
   mov byte[state], SUPERLOCKd
   jmp activateCorner.end

.right: ;������ ������� ������
   mov ax, word[o.cy]
   cmp ax, word[o.y]
   je activateCorner.end       ;���� ���������� �����, �� ������� (������ ���� �� ������)
   jb activateCorner.rightup

   ;����� ������ ������ ����
   mov ecx, 3
   call run_command
   mov byte[keyState], 0
   mov byte[state], SUPERLOCKd
   jmp activateCorner.end

.rightup:
   ;������ ������� ����
   mov ecx, 2
   call run_command
   mov byte[keyState], 0
   mov byte[state], SUPERLOCKd
   jmp activateCorner.end

.end:
   pop ecx eax
   ret



keyActivate db 41 ;16 ;'Q' ;������� ���������
keyState    db 0  ;0-������� �� �������, 1 - ������� �������

backAdr rd 1      ;����� ��� �������� �� �������� ����
slotMax rd 1
selfPID rd 1
buf rb 1024

;���������� ������ ��� �������� ���������� ������
screen:
  .width  rw 1
  .height rw 1

state: rb 1  ;���������: 0=unlock, 1=lock, 2=superlock for mode 3
mode:  rb 1  ;����� ������ ����������: 0=�� ��������, 1=������������, 2=�� ������� �������


keystr: rb 4 ;������ �� ��������� �������� ������������� �������
radstr: rb 5 ;������ �� ��������� �������
apps:
 .path1: rb 512
 .path2: rb 512
 .path3: rb 512
 .path4: rb 512
 .param1: rb 512
 .param2: rb 512
 .param3: rb 512
 .param4: rb 512
appsEnd:


I_END:
