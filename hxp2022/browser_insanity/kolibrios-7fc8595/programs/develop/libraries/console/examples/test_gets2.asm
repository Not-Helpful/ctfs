format PE GUI 0.8 ; initialize console ourselves
include 'proc32.inc'
include '../../../../import.inc'

start:
        push    caption
        push    25
        push    80
        push    25
        push    80
        call    [con_init]

; C-equivalent of the following code:
; for (;;)
; {
;   con_write_asciiz("Enter string (empty for exit): ");
;   if (!con_gets2(mycallback,s,256)) break;
;   if (s[0] == '\n') break;
;   con_write_asciiz("You entered: ");
;   con_write_asciiz(s);
; }
mainloop:
        push    str1
        call    [con_write_asciiz]
        push    256
        push    s
        push    mycallback
        call    [con_gets2]
        test    eax, eax
        jz      done
        cmp     [s], 10
        jz      done
        push    str2
        call    [con_write_asciiz]
        push    s
        call    [con_write_asciiz]
        jmp     mainloop
done:
        push    1
        call    [con_exit]
exit:
        xor     eax, eax
        ret

proc mycallback stdcall, keycode:dword, pstr:dword, pn:dword, ppos:dword
        mov     eax, [keycode]
        cmp     al, 0x0F
        jz      .tab
        cmp     al, 0x3B
        jz      .f1
        cmp     al, 0x48
        jz      .up
        cmp     al, 0x50
        jz      .down
        xor     eax, eax
        ret
.tab:
; Tab pressed - insert "[autocomplete]" to current position
        push    esi edi
        mov     eax, [ppos]
        mov     eax, [eax]
        mov     ecx, [pn]
        mov     ecx, [ecx]
        mov     esi, [pstr]
        mov     esi, [esi]
        add     ecx, esi
        add     esi, eax
        mov     edx, esi
@@:
        lodsb
        test    al, al
        jnz     @b
        lea     edi, [esi+str3.len]
        cmp     edi, ecx
        jbe     @f
        mov     edi, ecx
        lea     esi, [edi-str3.len]
@@:
        cmp     esi, edx
        jbe     @f
        dec     esi
        dec     edi
        mov     al, [esi]
        mov     [edi], al
        jmp     @b
@@:
        cmp     edi, ecx
        jb      @f
        dec     edi
@@:
        mov     ecx, edi
        sub     ecx, edx
        mov     edi, edx
        mov     esi, str3
        rep     movsb
        mov     eax, [pstr]
        sub     edi, [eax]
        mov     eax, [ppos]
        mov     [eax], edi
        pop     edi esi
        xor     eax, eax
        inc     eax
        ret
.f1:
; F1 pressed - say message
        push    str4
        call    [con_write_asciiz]
        push    str1
        call    [con_write_asciiz]
        push    2
        pop     eax
        ret
.up:
        push    esi
        mov     esi, str5
        mov     ecx, str5.len
        jmp     @f
.down:
        push    esi
        mov     esi, str6
        mov     ecx, str6.len
@@:
        push    edi
        mov     edi, [pstr]
        mov     edi, [edi]
        mov     eax, [ppos]
        mov     [eax], ecx
        rep     movsb
        xor     eax, eax
        stosb
        pop     edi esi
        inc     eax
        ret
endp


align 4
data import
library console, 'console.dll'
import console, \
        con_init, 'con_init', \
        con_write_asciiz, 'con_write_asciiz', \
        con_exit, 'con_exit', \
        con_gets2, 'con_gets2'
end data

caption            db 'Console test - gets2()',0
str1               db 'Enter string (empty for exit): ',0
str2               db 'You entered: ',0
str3               db '[autocomplete]'
str3.len = $ - str3
str4               db 13,10,'Help? What help do you need?',13,10,0
str5               db 'previous line in the history'
str5.len = $ - str5
str6               db 'next line in the history'
str6.len = $ - str6

s rb 256
