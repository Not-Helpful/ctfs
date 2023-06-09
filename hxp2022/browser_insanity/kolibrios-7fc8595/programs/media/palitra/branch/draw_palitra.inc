draw_palitra:
    ; �㭪�� 13 - ���ᮢ��� ��אַ㣮�쭨�
    ;mcall   SF_DRAW_RECT, 110 shl 16+148, 9 shl 16+148, [sc.work]

    cmp     [renmode],2
    je      cyrcle_draw
    ;cmp     [renmode],1
    ;je      picker_draw
    cmp     [renmode],0
    je      sheme_draw
    ret

    ;.................................................................................................
    ; ���ᮢ�� ��㣮��� ����ࠬ��
    ;.................................................................................................
    cyrcle_draw:
    ;mov     eax,13
    ;mov     edx,0x666666
    ;mov     ebx,108*65536+152
    ;mov     ecx,125*65536+33
    ;mcall
    ;mov     edx,0xF3F3F3
    ;mov     ebx,109*65536+150
    ;mov     ecx,126*65536+31
    ;mcall

    ;mov     eax,4                         ; 4 - �뢥�� ��ப� ⥪�� � ����
    ;mov     ebx,115 shl 16+131            ; [���न��� �� �� x]*65536 + [���न��� �� �� y]
    ;mov     ecx,0x666666                  ; 0xX0RRGGBB (RR, GG, BB ������ 梥� ⥪��)
    ;mov     edx,hint                      ; 㪠��⥫� �� ��砫� ��ப�
    ;mov     esi,24                        ; �뢮���� esi ᨬ�����
    ;mcall
    ;mov     ebx,125 shl 16+144            ; [���न��� �� �� x]*65536 + [���न��� �� �� y]
    ;mov     edx,hint2                     ; 㪠��⥫� �� ��砫� ��ப�
    ;mov     esi,21                        ; �뢮���� esi ᨬ�����
    ;mcall

    ;mov     edx,[color]
    ;mov     ebx,109*65536+150
    ;mov     ecx, 10*65536+150
    ;mcall
    call    mouse_local                   ; ����砥� ���न���� ��� �⭮�⥫쭮 ����
    mov     ecx, [mouse_x]                ; ����ᨬ � ॣ����
    mov     edx, [mouse_y]                ; ����ᨬ � ॣ����
    cmp     ecx, WIN_W-10
    jg      cyrcle_draw_2
    cmp     edx, WIN_H
    jle     end_cyrcle_draw

    cyrcle_draw_2:
        mcall   SF_SLEEP,10
    call    desktop_get
    call    mouse_global

    mov     ebx,112*65536+11
    mov     esi,0                         ; counter=8
    circle_loop:
      mov     ecx, 10*65536+11
      mov     edi,0
      circle_loop2:
        call    circle_pixel_read
        mcall   SF_DRAW_RECT
        add     ecx,11 shl 16
        inc     edi
        cmp     edi,13
        jne     circle_loop2

      add     ebx,11 shl 16
      inc     esi
      cmp     esi,13
      jne     circle_loop

    mcall   SF_DRAW_RECT, 177*65536+13, 76*65536+13, 0
    mov     ecx, [mouse_x]
    mov     edx, [mouse_y]
    inc     ecx
    inc     edx
    mov     ebx, edx
    imul    ebx, [desctop_w]
    add     ebx, ecx
    mcall   SF_GET_PIXEL
    mov     edx,eax
    mcall   SF_DRAW_RECT, 178*65536+11, 77*65536+11
    ret
    end_cyrcle_draw:
    mcall   SF_DRAW_RECT, 111*65536+145, 9*65536+145, 0x666666
    ret

    circle_pixel_read:
    push    ecx ebx
    mov     ecx, [mouse_x]
    mov     edx, [mouse_y]
    inc     ecx
    add     ecx, esi
    cmp     ecx, 6
    jl      _cpr_exit
    sub     ecx, 6
    inc     edx
    add     edx, edi
    cmp     edx, 6
    jl      _cpr_exit
    sub     edx, 6

    mov     ebx, edx
    imul    ebx, [desctop_w]
    add     ebx, ecx
    mcall   SF_GET_PIXEL
    mov     edx,eax
    pop     ebx ecx
    ret

    _cpr_exit:
    xor     edx,edx
    pop     ebx ecx
    ret

    ;picker_draw:
    ;ret

    ;.................................................................................................
    ; ���ᮢ�� 䮭� ��� ������
    ;.................................................................................................

    sheme_draw:
    mov     eax,SF_DRAW_RECT  ; �㭪�� 13 - ���ᮢ��� ��אַ㣮�쭨�
    mov     edx,0x222222                  ; 梥�
    mov     ecx, palitra_yw               ; ��砫�� ���न���� �� y [�-� y]*65536 + [ࠧ���]
    mov     esi,2                         ; ���稪 ����� ��������
    re_draw:
    mov     ebx,palitra_xw             ; ��砫�� ���न���� �� x [�-� x]*65536 + [ࠧ���]
    mov     edi,2                         ; ���稪 ������⢠ ��������
    for_fon_loop:
      int     0x40                        ; ���뢠���
      add     ebx,(palitra_w+2) shl 16               ; ���頥� ��������� ����� �� �
      dec     edi                         ; �����蠥� ���稪 ������
      cmp     edi,0                       ; �ࠢ������ � �㫥�
    jnz     for_fon_loop                  ; �᫨ �� ���� � � ��砫� 横��
    dec     esi                           ; �����蠥� ���
    cmp     esi,0                         ; �ࠢ������ � �㫥�
    mov     ecx,(palitra_w+DRAWY+3) shl 16+palitra_w              ; ��砫�� ���न���� �� y [�-� y]*65536 + [ࠧ���]
    jnz     re_draw                       ; �᫨ �� ���� � � ��砫� 横��

    ;.................................................................................................
    ; ���ᮢ�� ������ �� 横��
    ;.................................................................................................
    mov     eax,SF_DRAW_RECT  ; �㭪�� 13 - ���ᮢ��� ��אַ㣮�쭨�
    mov     edx,0x0FFFFFFF                ; 梥�
    mov     esi,4                         ; ���稪 ������⢠ ����楢 (#4,8)
    mov     ebx,(palitra_x-CELLW-3) shl 16+CELLW               ; ��砫�� ���न���� �� x [�-� x]*65536 + [ࠧ���]
    for_abz:
      ;;push    esi                       ; ���࠭塞 ���祭�� ���稪� ����� � �⥪
      cmp     esi,2
      jne     x2_line
      mov     ebx,(palitra_x-CELLW-3) shl 16+CELLW
      x2_line:
      add     ebx,3 shl 16                ; ���頥� ��������� ����� �� x
      mov     edi,8                       ; ���稪 ������⢠ ������ � ��ப�
      for_stolbik:
        push    edi                       ; ���࠭塞 ���祭�� ���稪� ����� � �⥪
        mov     edi,8                     ; ���稪 ������⢠ ������ � ��ப�
        mov     ecx,  (1-CELLW/3) shl 16+CELLW          ; ��砫�� ���न���� �� y [�-� y]*65536 + [ࠧ���]
        cmp     esi,2
        jg      y2_line                   ; �᫨ ����� 4 � ����ਬ
        mov     ecx,(palitra_w+4-(CELLW/3)) shl 16+CELLW
        y2_line:
        add     ebx,(CELLW+1) shl 16              ; ���頥� ��������� ����� �� x
        for_loop:
          add     ecx,(CELLW+1) shl 16            ; ���頥� ��������� ����� �� y
          int     0x40                    ; ���뢠���
          call    sub_red
          dec     edi                     ; �����蠥� ���稪 ������
          cmp     edi,0                   ; �ࠢ������ � �㫥�
          jnz     for_loop                ; �᫨ �� ���� � � ��砫� 横��
      call    sub_green
      pop     edi                         ; ���� ����⠭�������� ���稪 �����
      dec     edi                         ; �����蠥� ���
      cmp     edi,0                       ; �ࠢ������ � �㫥�
      jnz     for_stolbik                 ; �᫨ �� ���� � � ��砫� 横��
    call    sub_blue
    ;;pop     esi                         ; ���� ����⠭�������� ���稪 �����
    dec     esi                           ; �����蠥� ���
    cmp     esi,0                         ; �ࠢ������ � �㫥�
    jnz     for_abz                       ; �᫨ �� ���� � � ��砫� 横��
    ret                                   ; �����頥� �ࠢ�����
;end_draw_palitra-------------------------------------------------------------------------------------


sub_red:
    ;.................................................................................................
    ; ������ ᬥ饭�� ��᭮�� 梥� � �����樨 梥� �������
    ;.................................................................................................
    push    eax
    mov     eax,[pnext]
  ;sub_red_0                              ; palitra
    cmp     al,0
    jne     sub_red_1
    sub     edx,0x40
    jmp     sub_red_e
  sub_red_1:                              ; random
    cmp     al,1
    jne     sub_red_2
    sub     edx,0x20
    jmp     sub_red_e
  sub_red_2:                              ; gree
    cmp     al,2
    jne     sub_red_3
    sub     edx,0x010101
    jmp     sub_red_e
  sub_red_3:                              ; red
    cmp     al,3
    jne     sub_red_4
    sub     edx,0x0101
    jmp     sub_red_e
  sub_red_4:                              ; green
    cmp     al,4
    jne     sub_red_5
    sub     edx,0x010001
    jmp     sub_red_e
  sub_red_5:                              ; blue
    cmp     al,5
    jne     sub_red_e
    sub     edx,0x010100
    jmp     sub_red_e
  sub_red_e:
    pop     eax
    ret                                   ; �����頥� �ࠢ�����
;end_sub_red------------------------------------------------------------------------------------------

sub_green:
    ;.................................................................................................
    ; ������ ᬥ饭�� ��᭮�� 梥� � �����樨 梥� �������
    ;.................................................................................................
    push    eax
    mov     eax,[pnext]
  ;sub_green_0
    cmp     al,0
    jne     sub_green_1
    sub     edx,0x4000
    jmp     sub_green_e
  sub_green_1:
    cmp     al,1
    jne     sub_green_e
    sub     edx,0x2000
    ;jmp     sub_green_e
  sub_green_e:
    pop     eax
    ret                                   ; �����頥� �ࠢ�����
;end_sub_green----------------------------------------------------------------------------------------


sub_blue:
    ;.................................................................................................
    ; ������ ᬥ饭�� ��᭮�� 梥� � �����樨 梥� �������
    ;.................................................................................................
    push    eax
    mov     eax,[pnext]
  ;sub_blue_0
    cmp     al,0
    jne     sub_blue_1
    sub     edx,0x600000
    jmp     sub_blue_e
  sub_blue_1:
    cmp     al,1
    jne     sub_blue_e
    sub     edx,0x400000
    ;jmp     sub_blue_e
  sub_blue_e:
    pop     eax
    ret                                   ; �����頥� �ࠢ�����
;end_sub_blue-----------------------------------------------------------------------------------------