;----------------------------------------------------------
;---------------------sound of events----------------------
;----------------------------------------------------------
align 4
sound:
	mcall SF_SPEAKER_PLAY,55
	ret

;----------------------------------------------------------
;---------------------user events--------------------------
;----------------------------------------------------------

;description:
; ��६�饭�� �஫������ � ���� ���孨� 㣮� (0,0)
align 4
scrollbar_move_00:
	and [PosX],0
	and [PosY],0
	mov [Scroll1CoordinatX],ci_scrollh_coord_x_min
	mov [Scroll2CoordinatY],ci_scrollv_coord_y_min
	ret