use32
	org 0
	db 'MENUET01' ;������. �ᯮ��塞��� 䠩�� �ᥣ�� 8 ����
	dd 1, start, i_end, mem, stacktop, openfile_path, sys_path

include '../../../macros.inc'
include '../../../proc32.inc'
include '../../../KOSfuncs.inc'
include '../../../load_img.inc'
include '../../../load_lib.mac'
include 'vox_draw.inc'
include 'vox_rotate.inc'
include 'str.inc'

@use_library mem.Alloc,mem.Free,mem.ReAlloc,dll.Load
caption db 'Voxel editor 22.03.18',0 ;������� ����

IMAGE_TOOLBAR_ICON_SIZE equ 16*16*3
image_data_toolbar dd 0
cursors_count equ 4

;���祭�� ��������� �� 㬮�砭��, ��� ini 䠩��
ini_def_window_t equ 10
ini_def_window_l equ 10
ini_def_window_w equ 550
ini_def_window_h equ 415
ini_def_buf_w equ 198 ;=192+6
ini_def_buf_h equ 231 ;=224+7
ini_def_s_zoom equ 5
ini_def_t_size equ 10
ini_def_color_b equ 0xffffff
;���ᠭ�� ��ࠬ��஢ ��� ini 䠩��
ini_name db 'vox_editor.ini',0
ini_sec_window db 'Window',0
key_window_t db 't',0
key_window_l db 'l',0
key_window_w db 'w',0
key_window_h db 'h',0
key_buf_w db 'buf_w',0
key_buf_h db 'buf_h',0
ini_sec_options db 'Options',0
key_s_zoom db 's_zoom',0
key_t_size db 'tile_size',0
key_f_size db 'file_size',0
key_col_b db 'c_background',0

OT_MAP_X  equ  0
OT_MAP_Y  equ  0
OT_CAPT_X_COLOR equ  5 ;����� ��� ������ 梥�
OT_CAPT_Y_COLOR equ 30
PEN_MODE_NONE equ -1
PEN_MODE_CLEAR equ 0 ;०�� ��࠭��
PEN_MODE_SELECT_COLOR equ 2 ;०�� �롮� 梥�
PEN_MODE_BRUSH equ 3 ;०�� ࠡ��� � ������

run_file_70 FileInfoBlock

align 4
start:
	load_libraries l_libs_start,l_libs_end
	;�஢�ઠ �� ᪮�쪮 㤠筮 ���㧨���� ������⥪�
	mov	ebp,lib_0
	.test_lib_open:
	cmp	dword [ebp+ll_struc_size-4],0
	jz	@f
		mcall SF_TERMINATE_PROCESS ;exit not correct
	@@:
	add ebp,ll_struc_size
	cmp ebp,l_libs_end
	jl .test_lib_open
	mcall SF_STYLE_SETTINGS,SSF_GET_COLORS,sc,sizeof.system_colors
	mcall SF_SET_EVENTS_MASK,0xC0000027
	stdcall [OpenDialog_Init],OpenDialog_data ;�����⮢�� �������

;--- load ini file ---
	copy_path ini_name,sys_path,file_name,0
	;window startup pozition
	stdcall dword[ini_get_int],file_name,ini_sec_window,key_window_l,ini_def_window_l
	mov word[wnd_s_pos+2],ax
	stdcall dword[ini_get_int],file_name,ini_sec_window,key_window_w,ini_def_window_w
	mov word[wnd_s_pos],ax
	stdcall dword[ini_get_int],file_name,ini_sec_window,key_window_t,ini_def_window_t
	mov word[wnd_s_pos+6],ax
	stdcall dword[ini_get_int],file_name,ini_sec_window,key_window_h,ini_def_window_h
	mov word[wnd_s_pos+4],ax
	;image buffer size
	stdcall dword[ini_get_int],file_name,ini_sec_window,key_buf_w,ini_def_buf_w
	mov [buf_0.w],eax
	mov [buf_0z.w],eax
	add ax,15
	mov [buf_pl.l],ax ;����� ��� �ࠢ��� ����
	stdcall dword[ini_get_int],file_name,ini_sec_window,key_buf_h,ini_def_buf_h
	mov [buf_0.h],eax
	mov [buf_0z.h],eax
	;梥� 䮭�
	stdcall dword[ini_get_color],file_name,ini_sec_window,key_col_b,ini_def_color_b
	mov [buf_0.color],eax
	mov [buf_pl.color],eax

	;���⠡, ��᫥ ���ண� �㤥� 㢥��祭��
	stdcall dword[ini_get_int],file_name,ini_sec_options,key_s_zoom,ini_def_s_zoom
	mov [scaled_zoom],eax
	;ࠧ��� �����⨪� �� ���᪮�� �祭��
	stdcall dword[ini_get_int],file_name,ini_sec_options,key_t_size,ini_def_t_size
	mov [tile_size],eax

	stdcall dword[ini_get_int],file_name,ini_sec_options,key_f_size,64
	shl eax,10
	mov [max_open_file_size],eax

	mov ecx,[scaled_zoom]
	xor eax,eax
	inc eax
	shl eax,cl
	imul eax,[tile_size]
	mov [buf_pl.w],eax
	add eax,[tile_size]
	mov [buf_pl.h],eax

	;*** ����㧪� ����஢
	include_image_file 'cursors_gr.png',image_data_toolbar
	stdcall [buf2d_create_f_img], buf_curs_8,[image_data_toolbar] ;ᮧ���� ����
	stdcall mem.Free,[image_data_toolbar] ;�᢮������� ������

	include_image_file 'cursors.png',image_data_toolbar
	stdcall [buf2d_create_f_img], buf_curs,[image_data_toolbar] ;ᮧ���� ����
	stdcall mem.Free,[image_data_toolbar] ;�᢮������� ������

	stdcall [buf2d_conv_24_to_8], buf_curs_8,1 ;������ ���� �஧�筮�� 8���
	stdcall [buf2d_conv_24_to_32],buf_curs,buf_curs_8 ;������ ���� rgba 32���


	stdcall [buf2d_create], buf_0 ;ᮧ����� ���� ����ࠦ����
	stdcall [buf2d_create], buf_0z ;ᮧ����� ���� ��㡨��
	stdcall [buf2d_create], buf_pl ;ᮧ����� ���� ��� �祭��

	stdcall [buf2d_vox_brush_create], buf_vox_g3, vox_6_7_z
	stdcall [buf2d_vox_brush_create], buf_vox_g2, vox_6_4_z

	include_image_file 'toolbar.png', image_data_toolbar

	stdcall mem.Alloc,[max_open_file_size]
	mov dword[open_file_vox],eax

	call but_new_file

	;��ࢮ��砫쭠� ��⠭���� �����
	stdcall set_pen_mode,1,0,((9 shl 8)+9) shl 16 ;pen

	;�஢�ઠ ��������� ��ப�
	cmp dword[openfile_path],0
	je @f
		call but_open_file_cmd_lin
	@@:

align 4
red_win:
	call draw_window

align 4
still:
	mcall SF_WAIT_EVENT

	cmp al,1
	jz red_win
	cmp al,2
	jz key
	cmp al,3
	jz button
	cmp al,6
	jne @f
		mcall SF_THREAD_INFO,procinfo,-1
		cmp ax,word[procinfo+4]
		jne @f ;���� �� ��⨢��
		call mouse
	@@:
	jmp still

align 4
mouse:
	pushad
	mcall SF_MOUSE_GET,SSF_BUTTON
	bt eax,1 ;right button
	jnc @f
		mcall SF_MOUSE_GET,SSF_WINDOW_POSITION
		mov ebx,eax
		shr ebx,16
		and eax,0xffff
		stdcall get_buf_color, buf_0
		stdcall get_buf_color, buf_pl
		jmp .end_f
	@@:
	bt eax,0 ;left button
	jnc .end_f
		mcall SF_MOUSE_GET,SSF_WINDOW_POSITION
		mov ebx,eax
		shr ebx,16
		and eax,0xffff

		cmp dword[v_pen_mode],PEN_MODE_SELECT_COLOR
		jne .end_2
			stdcall get_buf_color, buf_0
			stdcall get_buf_color, buf_pl
			jmp .end_f
		.end_2:


		push eax ebx
		mov edx,[v_zoom]
		cmp edx,[scaled_zoom]
		jle @f
		;०�� ����⠡�஢���� ����ࠦ����
		sub edx,[scaled_zoom]
		sub ax,word[buf_0.t]
		sub bx,word[buf_0.l]
		stdcall get_mouse_ev_scale, [buf_vox], ebx, eax, [scaled_zoom],edx
		cmp eax,0
		je @f
			mov ebx,eax
			and eax,0x3fffffff
			rol ebx,2
			and ebx,3
			dec ebx

			shl ebx,2
			add ebx,cam_x
			mov dword[ebx],eax ;change [cam_x] or [cam_y] or [cam_z]
			call draw_objects

			pop ebx eax
			jmp .end_f
		@@:
		pop ebx eax


		;eax - mouse coord y
		;ebx - mouse coord x
		movzx edx,word[buf_pl.t]
		add edx,OT_MAP_Y
		cmp eax,edx
		jl .end_f
			sub eax,edx
			xor edx,edx
			mov ecx,[tile_size] ;H
			div ecx
		movzx edx,word[buf_pl.l]
		add edx,OT_MAP_X
		cmp ebx,edx
		jl .end_f
			call convert_y ;�८�ࠧ������ ���न���� y
			cmp eax,0
			jge .end_0 ;��࠭�祭�� �� ������ ���न��� y
				cmp eax,-1
				jne .end_f
				;���塞 �祭��, ������ �� �����⨪
				sub ebx,edx
				mov eax,ebx
				xor edx,edx
				mov ecx,[tile_size] ;W
				div ecx
				mov [n_plane],eax
				jmp .end_1
			.end_0:
			mov [v_cur_y],eax ;Y-coord
			sub ebx,edx
			mov eax,ebx
			xor edx,edx
			mov ecx,[tile_size] ;W
			div ecx
			mov [v_cur_x],eax ;X-coord

			cmp dword[v_pen_mode],PEN_MODE_CLEAR
			jl .end_1
			cmp dword[v_pen_mode],1
			jg .end_1
				mov eax,[v_cur_x]
				mov ebx,[n_plane]
				mov edx,[v_cur_y]

				mov ecx,[v_zoom]
				cmp ecx,[scaled_zoom]
				jle .no_c_coord_0
					;�८�ࠧ������ ���न���, � ��⮬ 㢥��祭��
					;sub ecx,[scaled_zoom] ;� ecx ����� ����⠡� (ecx>0)
					mov ecx,[scaled_zoom]

					mov edi,[cam_x]
					shl edi,cl
					add eax,edi
					mov edi,[cam_y]
					shl edi,cl
					add ebx,edi
					mov edi,[cam_z]
					shl edi,cl
					add edx,edi
				.no_c_coord_0:

				;�⫨��騩�� ��ࠬ��� ��� �㭪樨 ᮧ����� ���ᥫ�
				cmp dword[v_pen_mode],1
				jne @f
					push dword[v_color]
				@@:

				mov ecx,dword[v_zoom]
				mov edi,eax
				mov esi,ebx
				mcall SF_KEYBOARD,SSF_GET_CONTROL_KEYS
				and eax,3 ;3 -> ��� 0 ���� Shift �����, ��� 1 �ࠢ� Shift �����
                jz .shift_end
                    ;�᫨ ����� Shift, � ।����㥬 �� ���孥� �஢��
                    ;��� �⮣� �� ���न���� ����� �� 2 � �� ���⠡� �⭨���� 1
                    shr edx,1
                    shr esi,1
                    shr edi,1
                    dec ecx
                .shift_end:
                
                ;�맮� ���� ��ࠬ��஢ ��� �㭪権
				push ecx edx esi edi
				push dword[open_file_vox]

				;�맮� �㭪権
				cmp dword[v_pen_mode],1
				jne @f
					call buf2d_vox_obj_create_node
					;stdcall buf2d_vox_obj_create_node, [open_file_vox], edi,esi,edx, [v_zoom], [v_color]
					jmp .end_1
				@@:
					call buf2d_vox_obj_delete_node
					;stdcall buf2d_vox_obj_delete_node, [open_file_vox], edi,esi,edx, [v_zoom]

			.end_1:
			call draw_objects
			call draw_pok
	.end_f:
	popad
	ret

;input:
; eax - coord y
; ebx - coord x
align 4
proc get_buf_color, buf:dword
pushad
	mov edi,[buf]
	cmp ax,buf2d_t
	jl .end_f
	sub ax,buf2d_t
	cmp eax,buf2d_h
	jg .end_f
	cmp bx,buf2d_l
	jl .end_f
	sub bx,buf2d_l
	cmp ebx,buf2d_w
	jg .end_f
		stdcall [buf2d_get_pixel], edi,ebx,eax
		mov [v_color],eax
		call on_change_color ;�⮡ࠦ��� ��������� 梥�
	.end_f:
popad
	ret
endp

;�८�ࠧ��뢠�� ���न���� y (���祭�� ������ 㢥��稢����� � ���� �����)
align 4
convert_y:
	push ecx edx
	mov ecx,[v_zoom]
	cmp ecx,[scaled_zoom]
	jle @f
		mov ecx,[scaled_zoom]
	@@:
	mov edx,1
	cmp ecx,1
	jl @f
		shl edx,cl
	@@:
	sub edx,eax
	dec edx
	mov eax,edx
	pop edx ecx
	ret

align 4
draw_window:
pushad
	mcall SF_REDRAW,SSF_BEGIN_DRAW

	; *** �ᮢ���� �������� ���� (�믮������ 1 ࠧ �� ����᪥) ***
	mov edx,[sc.work]
	or  edx,(3 shl 24)+0x30000000
	mov edi,caption
	mcall SF_CREATE_WINDOW,dword[wnd_s_pos],dword[wnd_s_pos+4]

	; *** ᮧ����� ������ �� ������ ***
	mcall SF_DEFINE_BUTTON,(5 shl 16)+20,(5 shl 16)+20,3,[sc.work_button]

	mov ebx,(30 shl 16)+20
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,30 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40
	add ebx,25 shl 16
	inc edx
	int 0x40

	; *** �ᮢ���� ������ �� ������� ***
	mcall SF_PUT_IMAGE,[image_data_toolbar],(16 shl 16)+16,(7 shl 16)+7 ;icon new

	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;icon open
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;icon save
	int 0x40

	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(30 shl 16) ;㢥���. ����⠡
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;㬥���. ����⠡
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;camera 3g 2g
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;������ z
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;������ x
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;������ y
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;ᤢ�� ���᪮�� +
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;ᤢ�� ���᪮�� -
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�����㬥�� ��࠭���
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�����㬥�� �����
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�����㬥�� ����窠
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�롮� 梥�
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�ᢥ饭��
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;७��� 2*2
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;ᮧ���� �����
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;���ᮢ��� �����
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;㤠���� �����
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�ਭ� ���� -1
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�ਭ� ���� +1
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;���� ���� -1
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;���� ���� +1
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;��ࠧ��� ����� ���.
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;��ࠧ��� ����� ���.
	int 0x40
	add ebx,IMAGE_TOOLBAR_ICON_SIZE
	add edx,(25 shl 16) ;�������� ����� 90 ��.
	int 0x40

	; *** �ᮢ���� ���஢ ***
	call draw_objects
	call draw_pok

	mcall SF_REDRAW,SSF_END_DRAW
popad
	ret

align 4
draw_pok:
	mov eax,SF_DRAW_NUMBER
	mov ecx,[v_zoom]
	mov ebx,(3 shl 16)+(1 shl 31)
	mov edx,((350+6*9) shl 16)+OT_CAPT_Y_COLOR+2
	mov esi,[sc.work_button_text]
	or  esi,(1 shl 30)
	mov edi,[sc.work_button]
	int 0x40 ;����⠡
	mov ecx,[n_plane]
	add edx,115 shl 16 ;9
	int 0x40 ;����� �祭��

	;���������� ��ࠬ��஢ �����
	mov dword[txt_curor.size],0
	mov eax,dword[v_cur_x]
	mov edi,txt_curor.size
	stdcall convert_int_to_str,10
	stdcall str_cat, edi,txt_mull
	mov eax,dword[v_cur_y]
	mov edi,txt_buf
	stdcall convert_int_to_str,16
	stdcall str_cat, txt_curor.size,edi
	stdcall str_cat, txt_curor.size,txt_space ;�������騩 �஡��

	;���������� ��ࠬ��஢ ����
	mov dword[txt_brush.size],0
	mov eax,dword[brush_w]
	mov edi,txt_brush.size
	stdcall convert_int_to_str,10
	stdcall str_cat, edi,txt_mull
	mov eax,dword[brush_h]
	mov edi,txt_buf
	stdcall convert_int_to_str,16
	stdcall str_cat, txt_brush.size,edi
	stdcall str_cat, txt_brush.size,txt_space ;�������騩 �஡��

	mov ecx,[sc.work_text]
	or  ecx,0x80000000 ;or (1 shl 30)
	mov edx,txt_color
	mcall SF_DRAW_TEXT,(OT_CAPT_X_COLOR shl 16)+OT_CAPT_Y_COLOR+2

	mov edx,txt_curor
	add ebx,115 shl 16
	or  ecx,(1 shl 30)
	mov edi,[sc.work]
	int 0x40

	mov edx,txt_brush
	add ebx,115 shl 16
	int 0x40

	mov edx,txt_zoom
	add ebx,115 shl 16
	int 0x40

	mov edx,txt_n_plane
	add ebx,115 shl 16
	int 0x40

	call on_change_color
	ret

align 4
on_change_color:
pushad
	mcall SF_DRAW_RECT,((OT_CAPT_X_COLOR+35) shl 16)+16,(OT_CAPT_Y_COLOR shl 16)+12,[v_color]

	mov ecx,edx
	mov edx,((OT_CAPT_X_COLOR+55) shl 16)+OT_CAPT_Y_COLOR+2
	mov esi,[sc.work_text]
	add esi,(1 shl 30)
	mov edi,[sc.work]
	mcall SF_DRAW_NUMBER,(1 shl 8)+(6 shl 16)
popad
	ret

align 4
key:
	mcall SF_GET_KEY
	jmp still


align 4
button:
	mcall SF_GET_BUTTON
	cmp ah,3
	jne @f
		call but_new_file
		call draw_objects
		call draw_pok
	@@:
	cmp ah,4
	jne @f
		call but_open_file
	@@:
	cmp ah,5
	jne @f
		call but_save_file
	@@:
	cmp ah,6
	jne @f
		call but_camera_3g_2g
	@@:
	cmp ah,7
	jne @f
		call but_zoom_p
	@@:
	cmp ah,8
	jne @f
		call but_zoom_m
	@@:
	cmp ah,9
	jne @f
		call but_r_z
	@@:
	cmp ah,10
	jne @f
		call but_r_x
	@@:
	cmp ah,11
	jne @f
		call but_r_y
	@@:
	cmp ah,12
	jne @f
		call but_plane_inc
	@@:
	cmp ah,13
	jne @f
		call but_plane_dec
	@@:
	cmp ah,14
	jne @f
		call but_mode_pen
	@@:
	cmp ah,15
	jne @f
		call but_mode_brush
	@@:
	cmp ah,16
	jne @f
		call but_mode_clear
	@@:
	cmp ah,17
	jne @f
		stdcall set_pen_mode,PEN_MODE_SELECT_COLOR,3,((9 shl 8)+9) shl 16
		call draw_palete
	@@:
	cmp ah,18
	jne @f
		call but_light
	@@:
	cmp ah,19
	jne @f
		call but_rend_2_2
	@@:
	cmp ah,20
	jne @f
		call but_brush_copy
	@@:
	cmp ah,21
	jne @f
		call but_brush_draw
	@@:
	cmp ah,22
	jne @f
		call but_brush_clear
	@@:
	cmp ah,23
	jne @f
		call but_bru_w_m
	@@:
	cmp ah,24
	jne @f
		call but_bru_w_p
	@@:
	cmp ah,25
	jne @f
		call but_bru_h_m
	@@:
	cmp ah,26
	jne @f
		call but_bru_h_p
	@@:
	cmp ah,27
	jne @f
		call but_bru_flip_h
	@@:
	cmp ah,28
	jne @f
		call but_bru_flip_v
	@@:
	cmp ah,29
	jne @f
		call but_bru_rot_90
	@@:
	cmp ah,1
	jne still
.exit:
	stdcall [buf2d_delete],buf_0
	stdcall [buf2d_delete],buf_0z
	cmp dword[buf_r_img],0
	je @f
		stdcall [buf2d_delete],buf_r_img
		stdcall [buf2d_delete],buf_r_z
	@@:
	stdcall [buf2d_vox_brush_delete], buf_vox_g3
	stdcall [buf2d_vox_brush_delete], buf_vox_g2
	stdcall [buf2d_delete],buf_curs
	stdcall [buf2d_delete],buf_curs_8
	stdcall mem.Free,[image_data_toolbar]
	stdcall mem.Free,[open_file_vox]
	mcall SF_TERMINATE_PROCESS

;����� ��� ���樠����樨 ���ᥫ쭮�� ��ꥪ�
align 4
vox_new_data:
	db 2,0,0,0
	db 0,1,2,3,4,5,6,7 ;default table
	dd 0 ;null node

;���樠������ ���ᥫ쭮�� ��ꥪ�
align 4
proc but_new_file uses ecx edi esi
	mov ecx,vox_offs_data+4
	mov esi,vox_new_data
	mov edi,[open_file_vox]
	cld
	rep movsb
	ret
endp

align 4
open_file_vox dd 0 ;㪠��⥫� �� ������� ��� ������ 䠩���

align 4
but_open_file:
	pushad
	copy_path open_dialog_name,communication_area_default_path,file_name,0
	mov [OpenDialog_data.type],0
	stdcall [OpenDialog_Start],OpenDialog_data
	cmp [OpenDialog_data.status],2
	je .end_open_file
	;��� �� 㤠筮� ����⨨ �������

	call but_open_file_cmd_lin
	call draw_objects
	.end_open_file:
	popad
	ret

align 4
but_open_file_cmd_lin:
	pushad
	mov [run_file_70.Function], SSF_GET_INFO
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov dword[run_file_70.Count], 0
	mov dword[run_file_70.Buffer], open_b
	mov byte[run_file_70+20], 0
	mov dword[run_file_70.FileName], openfile_path
	mcall SF_FILE,run_file_70

	mov ecx,dword[open_b+32] ;+32 qword: ࠧ��� 䠩�� � �����
	cmp ecx,[max_open_file_size] ;�஢��塞 ࠧ��� �뤥������ �����
	jle @f
		mov [max_open_file_size],ecx
		stdcall mem.ReAlloc,[open_file_vox],ecx
		mov [open_file_vox],eax
		notify_window_run txt_need_memory
	@@:
	
	mov [run_file_70.Function], SSF_READ_FILE
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov dword[run_file_70.Count], ecx
	m2m dword[run_file_70.Buffer], dword[open_file_vox]
	mov byte[run_file_70+20], 0
	mov dword[run_file_70.FileName], openfile_path
	mcall SF_FILE,run_file_70
	cmp ebx,0xffffffff
	je .end_open_file

	mcall SF_SET_CAPTION,1,openfile_path

	;---
	mov eax,[open_file_vox]
	movzx eax,byte[eax]
	and eax,0xff ;��६ ����⠡ �� 㬮�砭��
	mov dword[v_zoom],eax ;��६ ����⠡ �� 㬮�砭��
	mov dword[cam_x],0
	mov dword[cam_y],0
	mov dword[cam_z],0
	.end_open_file:
	popad
	ret

align 4
but_save_file:
	pushad
		copy_path open_dialog_name,communication_area_default_path,file_name,0
		mov [OpenDialog_data.type],1
		stdcall [OpenDialog_Start],OpenDialog_data
		cmp [OpenDialog_data.status],2
		je .end_save_file
		;��� �� 㤠筮� ����⨨ �������

		mov eax,dword[v_zoom] ;������ ����⠡ �� 㬮�砭��
		mov ebx,[open_file_vox]
		mov byte[ebx],al

		stdcall buf2d_vox_obj_get_size, ebx
		mov dword[run_file_70.Count], eax ;ࠧ��� 䠩��
		mov [run_file_70.Function], SSF_CREATE_FILE
		mov [run_file_70.Position], 0
		mov [run_file_70.Flags], 0
		mov ebx, dword[open_file_vox]
		mov [run_file_70.Buffer], ebx
		mov byte[run_file_70+20], 0
		mov dword[run_file_70.FileName], openfile_path
		mcall SF_FILE,run_file_70 ;����㦠�� 䠩� ����ࠦ����
		cmp ebx,0xffffffff
		je .end_save_file

		.end_save_file:
	popad
	ret

;ᬥ�� ���� ������ �� ��ᬮ�� 3 � 2 �࠭��
align 4
but_camera_3g_2g:
	cmp dword[buf_vox],buf_vox_g3
	je @f
		mov dword[buf_vox],buf_vox_g3
		jmp .end_0
	@@:
		mov dword[buf_vox],buf_vox_g2
	.end_0:
	call draw_objects
	ret

;㢥��祭�� ����⠡�
align 4
but_zoom_p:
	cmp dword[v_zoom],10 ;���ᨬ���� ࠧ���, �� ���ண� ����� 㢥����� 2^10=1024
	jge @f
		inc dword[v_zoom]
		shl dword[n_plane],1
		push eax
		mov eax,[v_zoom]
		cmp eax,[scaled_zoom]
		jl .end_0
			push ecx
			mov ecx,[scaled_zoom]
			xor eax,eax
			inc eax
			shl eax,cl
			shl dword[cam_x],1
			shl dword[cam_y],1
			shl dword[cam_z],1
			cmp eax,[n_plane]
			jg .end_1
				;��४�஢�� ����㭪�
				sub [n_plane],eax
				inc dword[cam_y]
			.end_1:
			pop ecx
		.end_0:
		pop eax
		call draw_objects
		call draw_pok
	@@:
	ret

;㬥��襭�� ����⠡�
align 4
but_zoom_m:
	cmp dword[v_zoom],1
	jl @f
		dec dword[v_zoom]
		shr dword[n_plane],1
		push eax
		mov eax,[v_zoom]
		cmp eax,[scaled_zoom]
		jl .end_0
			shr dword[cam_x],1
			shr dword[cam_y],1
			jnc .end_1
				;��४�஢�� ����㭪�
				push ecx
				mov ecx,[scaled_zoom]
				dec ecx
				xor eax,eax
				inc eax
				shl eax,cl
				add [n_plane],eax
				pop ecx
			.end_1:
			shr dword[cam_z],1
		.end_0:
		pop eax
		call draw_objects
		call draw_pok
	@@:
	ret

align 4
but_r_z:
	stdcall vox_obj_rot_z, [open_file_vox]
	call draw_objects
	ret

align 4
but_r_x:
	stdcall vox_obj_rot_x, [open_file_vox]
	call draw_objects
	ret

align 4
but_r_y:
	stdcall vox_obj_rot_y, [open_file_vox]
	call draw_objects
	ret

;ᤢ����� ���᪮��� �१�
align 4
but_plane_inc:
push eax ecx
	inc dword[n_plane]
	mov eax,[v_zoom]
	cmp eax,[scaled_zoom]
	jle .end_0
		;�ந�室�� ����⠡�஢����
		mov ecx,[scaled_zoom]
		xor eax,eax
		inc eax
		shl eax,cl
		cmp eax,[n_plane]
		jg @f
			mov dword[n_plane],0
			inc dword[cam_y] ;���室�� � �ᥤ��� ��
			neg ecx
			;inc ecx
			add ecx,[v_zoom]
			xor eax,eax
			inc eax
			shl eax,cl
			cmp eax,[cam_y]
			jg @f
				mov dword[cam_y],0 ;��横������ �᫨ �뫥��� �� �।��� ��᫥����� �㡠
		@@:
		jmp .end_1
	.end_0:
		;����⠡�஢���� �� �ந�室��
		mov ecx,eax
		xor eax,eax
		inc eax
		shl eax,cl
		cmp eax,[n_plane]
		jg .end_1
			mov dword[n_plane],0
	.end_1:
	call draw_objects
	call draw_pok
pop ecx eax
	ret

;ᤢ����� ���᪮��� �१�
align 4
but_plane_dec:
	dec dword[n_plane]
	cmp dword[n_plane],0
	jge .end_f
push eax ecx
	mov ecx,[scaled_zoom]
	xor eax,eax
	inc eax
	shl eax,cl
	dec eax
	mov dword[n_plane],eax

	mov eax,[v_zoom]
	cmp eax,[scaled_zoom]
	jle .end_0
		;�ந�室�� ����⠡�஢����
		dec dword[cam_y] ;���室�� � �ᥤ��� ��
		cmp dword[cam_y],0
		jge .end_0

		mov ecx,eax
		sub ecx,[scaled_zoom]
		xor eax,eax
		inc eax
		shl eax,cl
		dec eax
		mov dword[cam_y],eax ;�᫨ ����� �㡠 �������� ����� 0 ��ࠢ�塞 �� ���ᨬ��쭮� ���祭��
	.end_0:
pop ecx eax
	.end_f:
	call draw_objects
	call draw_pok
	ret

align 4
but_mode_pen:
	push eax
	mov eax,dword[v_pen_mode]
	stdcall set_pen_mode,1,0,((9 shl 8)+9) shl 16 ;pen
	cmp eax,PEN_MODE_SELECT_COLOR
	jne @f
		call draw_objects
	@@:
	pop eax
	ret

align 4
but_mode_brush:
	push eax
	mov eax,dword[v_pen_mode]
	stdcall set_pen_mode,3,1,((9 shl 8)+9) shl 16 ;brush
	cmp eax,PEN_MODE_SELECT_COLOR
	jne @f
		call draw_objects
	@@:
	pop eax
	ret

align 4
but_mode_clear:
	push eax
	mov eax,dword[v_pen_mode]
	stdcall set_pen_mode,PEN_MODE_CLEAR,2,((15 shl 8)+9) shl 16
	cmp eax,PEN_MODE_SELECT_COLOR
	jne @f
		call draw_objects
	@@:
	pop eax
	ret

align 4
but_light:
	xor dword[mode_light],1
	call draw_objects
	ret

align 4
but_rend_2_2:
push edi
	cmp dword[buf_r_img],0
	jne @f
		;ᮧ����� ���� ��� ७���
		push ecx esi
		mov edi,buf_r_img
		mov esi,buf_0
		mov ecx,BUF_STRUCT_SIZE
		cld
		rep movsb ;�����㥬 �� ��ࠬ���� � �᭮����� ����
		mov edi,buf_r_img
		mov buf2d_data,0
		shl buf2d_w,1 ;㢥��稢��� ࠧ��� ����
		shl buf2d_h,1
		stdcall [buf2d_create],buf_r_img

		mov edi,buf_r_z
		mov esi,buf_0z
		mov ecx,BUF_STRUCT_SIZE
		cld
		rep movsb ;�����㥬 �� ��ࠬ���� � �᭮����� ����
		mov edi,buf_r_z
		mov buf2d_data,0
		shl buf2d_w,1 ;㢥��稢��� ࠧ��� ����
		shl buf2d_h,1
		stdcall [buf2d_create],buf_r_z
		pop esi ecx
	@@:
	stdcall [buf2d_clear], buf_r_img, [buf_0.color] ;��⨬ ����
	stdcall [buf2d_clear], buf_r_z, 0 ;��⨬ ����

	push eax ebx ecx
		mov eax,[v_zoom]
		cmp eax,[scaled_zoom]
		jle .end_scaled
			;७��� 㢥��祭��� ��� ��ꥪ�
			mov ebx,[scaled_zoom]
			sub eax,ebx
			inc ebx
			stdcall [buf2d_vox_obj_draw_3g_scaled], buf_r_img, buf_r_z, [buf_vox],\
				[open_file_vox], 0,0, 0, ebx, [cam_x],[cam_y],[cam_z],eax, [sc.work_graph]
			bt dword[mode_light],0
			jnc @f
				stdcall [buf2d_vox_obj_draw_3g_shadows], buf_r_img, buf_r_z, [buf_vox], 0,0, 0, ebx, 3
			@@:
			xor ebx,ebx
			xor ecx,ecx
			mov edi,buf_r_img
			stdcall [buf2d_img_hdiv2], edi
			shr buf2d_h,1
			stdcall [buf2d_img_wdiv2], edi
			shr buf2d_w,1
			jmp .show
		.end_scaled:

		inc eax
		stdcall [buf2d_vox_obj_draw_3g], buf_r_img, buf_r_z, [buf_vox], [open_file_vox], 0,0, 0, eax
		stdcall [buf2d_vox_obj_draw_1g], buf_r_img, buf_r_z, [open_file_vox], 0,0, eax
		bt dword[mode_light],0
		jnc @f
			stdcall [buf2d_vox_obj_draw_3g_shadows], buf_r_img, buf_r_z, [buf_vox], 0,0, 0, eax, 3
		@@:

		mov edi,buf_r_img
		stdcall [buf2d_img_hdiv2], edi
		shr buf2d_h,1
		stdcall [buf2d_img_wdiv2], edi
		shr buf2d_w,1

		stdcall [buf2d_vox_obj_get_img_w_3g], [buf_vox],[v_zoom]
		mov ebx,[buf_0.w]
		sub ebx,eax
		shr ebx,1 ;ebx - ��� 業�஢�� �����쪨� ����ࠦ���� �� ��ਧ��⠫�
		stdcall [buf2d_vox_obj_get_img_h_3g], [buf_vox],[v_zoom]
		cmp eax,[buf_0.h]
		jg @f
			mov ecx,[buf_0.h]
			sub ecx,eax
			shr ecx,1 ;ecx - ��� 業�஢�� �����쪨� ����ࠦ���� �� ���⨪���
		@@:
		.show:
		stdcall [buf2d_bit_blt], buf_0, ebx,ecx, edi
		shl buf2d_h,1
		shl buf2d_w,1
	pop ecx ebx eax
pop edi
	stdcall [buf2d_draw], buf_0 ;������塞 ���� �� ��࠭�
	ret

;㬥��蠥� �ਭ� ����
align 4
but_bru_w_m:
	cmp dword[brush_w],1
	jle @f
		dec dword[brush_w]
		pushad
		call draw_pok
		call draw_plane
		popad
	@@:
	ret
;㢥��稢��� �ਭ� ����
align 4
but_bru_w_p:
	cmp dword[brush_w],32
	jge @f
		inc dword[brush_w]
		pushad
		call draw_pok
		call draw_plane
		popad
	@@:
	ret
;㬥��蠥� ����� ����
align 4
but_bru_h_m:
	cmp dword[brush_h],1
	jle @f
		dec dword[brush_h]
		pushad
		call draw_pok
		call draw_plane
		popad
	@@:
	ret
;㢥��稢��� ����� ����
align 4
but_bru_h_p:
	cmp dword[brush_h],32
	jge @f
		inc dword[brush_h]
		pushad
		call draw_pok
		call draw_plane
		popad
	@@:
	ret

align 4
but_bru_flip_h:
	stdcall [buf2d_flip_h],buf_brush
	call draw_plane
	ret

align 4
but_bru_flip_v:
	stdcall [buf2d_flip_v],buf_brush
	call draw_plane
	ret

align 4
but_bru_rot_90:
	stdcall [buf2d_rotate],buf_brush,90
	call draw_plane
	ret

align 4
but_brush_copy:
	cmp dword[v_pen_mode],PEN_MODE_BRUSH
	jne .end_f
pushad
	mov eax,[v_cur_x]
	mov ebx,[n_plane]
	mov edx,[v_cur_y]
		
	mov ecx,[v_zoom]
	cmp ecx,[scaled_zoom]
	jle @f
		;�८�ࠧ������ ���न���, � ��⮬ 㢥��祭��
		;sub ecx,[scaled_zoom] ;� ecx ����� ����⠡� (ecx>0)
		mov ecx,[scaled_zoom]

		mov edi,[cam_x]
		shl edi,cl
		add eax,edi
		mov edi,[cam_y]
		shl edi,cl
		add ebx,edi
		mov edi,[cam_z]
		shl edi,cl
		add edx,edi
	@@:

	cld
	mov edi,brush_data
	mov esi,edx
	sub esi,[brush_h]
	.cycle_0:
	mov ecx,[brush_w]
	@@:
		push eax
		stdcall buf2d_vox_obj_node_get_color, [open_file_vox], eax,ebx,edx, [v_zoom]
		cmp eax,[v_color]
		jne .end_0
			mov eax,1 shl 30
		.end_0:
		mov dword[edi],eax ;color
		pop eax
		inc eax
		add edi,4
		loop @b
	dec edx
	sub eax,[brush_w]
	cmp edx,esi
	jg .cycle_0

	call draw_objects
popad
	.end_f:
	ret

align 4
but_brush_draw:
	cmp dword[v_pen_mode],PEN_MODE_BRUSH
	jne .end_f
pushad
	mov eax,[v_cur_x]
	mov ebx,[n_plane]
	mov edx,[v_cur_y]
		
	mov ecx,[v_zoom]
	cmp ecx,[scaled_zoom]
	jle @f
		;�८�ࠧ������ ���न���, � ��⮬ 㢥��祭��
		;sub ecx,[scaled_zoom] ;� ecx ����� ����⠡� (ecx>0)
		mov ecx,[scaled_zoom]

		mov edi,[cam_x]
		shl edi,cl
		add eax,edi
		mov edi,[cam_y]
		shl edi,cl
		add ebx,edi
		mov edi,[cam_z]
		shl edi,cl
		add edx,edi
	@@:

	cld
	mov edi,brush_data
	mov esi,edx
	sub esi,[brush_h]
	.cycle_0:
	mov ecx,[brush_w]
	@@:
		bt dword[edi],31 ;��� �஧�筮��
		jc .end_2
		bt dword[edi],30 ;��� ⥪�饣� 梥�
		jnc .end_0
			push dword[v_color]
			jmp .end_1
		.end_0:
			push dword[edi]
		.end_1:
		stdcall buf2d_vox_obj_create_node, [open_file_vox], eax,ebx,edx, [v_zoom] ;, color
		.end_2:
		inc eax
		add edi,4
		loop @b
	dec edx
	sub eax,[brush_w]
	cmp edx,esi
	jg .cycle_0

	call draw_objects
popad
	.end_f:
	ret

align 4
but_brush_clear:
	cmp dword[v_pen_mode],PEN_MODE_BRUSH
	jne .end_f
pushad
	mov eax,[v_cur_x]
	mov ebx,[n_plane]
	mov edx,[v_cur_y]
		
	mov ecx,[v_zoom]
	cmp ecx,[scaled_zoom]
	jle @f
		;�८�ࠧ������ ���न���, � ��⮬ 㢥��祭��
		;sub ecx,[scaled_zoom] ;� ecx ����� ����⠡� (ecx>0)
		mov ecx,[scaled_zoom]

		mov edi,[cam_x]
		shl edi,cl
		add eax,edi
		mov edi,[cam_y]
		shl edi,cl
		add ebx,edi
		mov edi,[cam_z]
		shl edi,cl
		add edx,edi
	@@:

	cld
	mov edi,brush_data
	mov esi,edx
	sub esi,[brush_h]
	.cycle_0:
	mov ecx,[brush_w]
	@@:
		bt dword[edi],31 ;��� �஧�筮��
		jc .end_2
		stdcall buf2d_vox_obj_delete_node, [open_file_vox], eax,ebx,edx, [v_zoom]
		.end_2:
		inc eax
		add edi,4
		loop @b
	dec edx
	sub eax,[brush_w]
	cmp edx,esi
	jg .cycle_0

	call draw_objects
popad
	.end_f:
	ret

align 4
draw_palete:
	stdcall [buf2d_clear], buf_0, [buf_0.color] ;��⨬ ����
	stdcall buf2d_draw_palete, buf_0, 5,3, 9,6, 18, 512
	stdcall [buf2d_draw], buf_0 ;������塞 ���� �� ��࠭�
	ret

align 4
v_zoom dd 3 ;⥪�騩 ����⠡
v_cur_x dd 0 ;���न��� ����� x
v_cur_y dd 0 ;���न��� ����� y (�� ��� � ��ꥪ� z)
n_plane dd 0 ;���᪮��� �祭��
v_color dd 0xff ;梥� ��࠭���
v_pen_mode dd PEN_MODE_NONE ;०�� ࠡ��� ����� (�. ����⠭�� PEN_MODE_...)
mode_light dd 1 ;०�� �ᢥ饭��
cam_x dd 0
cam_y dd 0
cam_z dd 0
scaled_zoom dd 5 ;����⠡ ��᫥ ���ண� ��稭����� �ᮢ���� ��� ����ࠦ����
tile_size dd ? ;ࠧ��� �����⨪� �� ���᪮�� � �祭���
max_open_file_size dd ?

align 4
buf_brush: ;���� � �஧�筮���� ��� ����஢
	dd brush_data ;㪠��⥫� �� ���� ����ࠦ����
	dw 0 ;+4 left
	dw 0 ;+6 top
brush_w dd 5 ;�ਭ� ����
brush_h dd 5 ;���� ����
	dd 0 ;+16 color
	db 32 ;+20 bit in pixel

brush_data dd 1 shl 31,1 shl 30,1 shl 30,1 shl 30,1 shl 31
dd 1 shl 30,1 shl 30,1 shl 30,1 shl 30,1 shl 30
dd 1 shl 30,1 shl 30,1 shl 30,1 shl 30,1 shl 30
dd 1 shl 30,1 shl 30,1 shl 30,1 shl 30,1 shl 30
dd 1 shl 31,1 shl 30,1 shl 30,1 shl 30,1 shl 31
rd 999 ;32*32-25

txt_zoom db '����⠡:',0
txt_curor: db '�����: '
.size: rb 10
txt_n_plane db '��祭��:',0
txt_color db '����:',0
txt_brush: db '�����: '
.size: rb 10
txt_mull db '*',0
txt_space db ' ',0
txt_buf rb 16
txt_need_memory db '���� ����� ��� ࠡ��� � ���뢠��� 䠩���.',13,10,\
	'�� ।���஢���� 䠩�� �ணࠬ�� ����� ��������.',13,10,\
	'������� ࠧ��� ��६����� ',39,'file_size',39,' � 䠩�� ',39,'vox_editor.ini',39,'.',0

;�ᮢ���� ���� � ���ᥫ�묨 ��ꥪ⠬�
align 4
draw_objects:
	stdcall [buf2d_clear], buf_0, [buf_0.color] ;��⨬ ����
	stdcall [buf2d_clear], buf_0z, 0 ;��⨬ ����

	cmp dword[v_pen_mode],PEN_MODE_SELECT_COLOR
	jne @f
		call draw_palete
		jmp .end_f
	@@:
	push eax ebx ecx
	stdcall [buf2d_vox_obj_get_img_w_3g], [buf_vox],[v_zoom]
	mov ebx,[buf_0.w]
	sub ebx,eax
	shr ebx,1 ;ebx - ��� 業�஢�� �����쪨� ����ࠦ���� �� ��ਧ��⠫�

	xor ecx,ecx
	stdcall [buf2d_vox_obj_get_img_h_3g], [buf_vox],[v_zoom]
	cmp eax,[buf_0.h]
	jg @f
		mov ecx,[buf_0.h]
		sub ecx,eax
		shr ecx,1 ;ecx - ��� 業�஢�� �����쪨� ����ࠦ���� �� ���⨪���
	@@:

	mov eax,[v_zoom]
	cmp eax,[scaled_zoom]
	jg @f
		;����� ०�� ����ࠦ����
		stdcall [buf2d_vox_obj_draw_3g], buf_0, buf_0z, [buf_vox],\
			[open_file_vox], ebx,ecx, 0, eax
		stdcall [buf2d_vox_obj_draw_1g], buf_0, buf_0z,\
			[open_file_vox], 0,0, eax
		bt dword[mode_light],0
		jnc .end_1
			stdcall [buf2d_vox_obj_draw_3g_shadows], buf_0, buf_0z, [buf_vox], ebx,ecx, 0, eax, 3
		.end_1:
		jmp .end_0
	@@:
		;०�� ����⠡�஢���� ����ࠦ����
		sub eax,[scaled_zoom]
		stdcall [buf2d_vox_obj_draw_3g_scaled], buf_0, buf_0z, [buf_vox],\
			[open_file_vox], 0,0, 0, [scaled_zoom], [cam_x],[cam_y],[cam_z],eax, [sc.work_graph] ;scroll -> 2^eax
		bt dword[mode_light],0
		jnc .end_2
			stdcall [buf2d_vox_obj_draw_3g_shadows], buf_0, buf_0z, [buf_vox], 0,0, 0, [scaled_zoom], 3
		.end_2:
	.end_0:
	pop ecx ebx eax

	call draw_plane
	stdcall [buf2d_draw], buf_0 ;������塞 ���� �� ��࠭�
	.end_f:
	ret

;�ᮢ���� ���᪮�� � �祭��� ��ꥪ�
align 4
proc draw_plane uses eax
	stdcall [buf2d_clear], buf_pl, [buf_pl.color] ;��⨬ ����

	mov eax,[v_zoom]
	cmp eax,[scaled_zoom]
	jg @f
		;����� ०�� ����ࠦ����
		stdcall [buf2d_vox_obj_draw_pl], buf_pl, [open_file_vox],\
			OT_MAP_X,OT_MAP_Y,[tile_size], eax, [n_plane], [sc.work_graph]
		jmp .end_0
	@@:
		;०�� ����⠡�஢���� ����ࠦ����
		sub eax,[scaled_zoom]
		stdcall [buf2d_vox_obj_draw_pl_scaled], buf_pl, [open_file_vox],\
			OT_MAP_X,OT_MAP_Y,[tile_size], [scaled_zoom], [n_plane], [sc.work_graph],[cam_x],[cam_y],[cam_z],eax
	.end_0:

	call draw_vox_cursor
	stdcall [buf2d_draw], buf_pl ;������塞 ���� �� ��࠭�
	.end_f:
	ret
endp

;�ᮢ���� �����
align 4
draw_vox_cursor:
pushad
	mov ecx,[v_zoom]
	cmp ecx,[scaled_zoom]
	jle @f
		mov ecx,[scaled_zoom]
	@@:
	xor edx,edx
	inc edx
	shl edx,cl

	mov eax,[v_cur_x]
	cmp eax,edx
	jge .end_f ;����� �� �।����� ����
	mov edi,[tile_size]
	imul eax,edi
	add eax,OT_MAP_X
	mov ebx,edx
	dec ebx
	sub ebx,[v_cur_y]
	imul ebx,edi
	add ebx,OT_MAP_Y
	inc eax
	cmp dword[v_pen_mode],PEN_MODE_BRUSH
	je .brush
	inc ebx
    sub edi,2
	stdcall [buf2d_rect_by_size], buf_pl, eax,ebx, edi,edi,[sc.work_graph]
	dec ebx
	add edi,2

	;��ਧ��⠫�� �����
	sub eax,2
	mov ecx,edi
	imul edi,edx
	shr ecx,1
	add ebx,ecx ;業�஢�� �� �।��� ���⪨
	mov ecx,OT_MAP_X
	add edi,ecx
	stdcall [buf2d_line], buf_pl, ecx,ebx, eax,ebx,[sc.work_graph]
	add eax,[tile_size]
	inc eax
	cmp eax,edi
	jge @f ;�᫨ ����� �� ��� ����
		dec edi
		stdcall [buf2d_line], buf_pl, eax,ebx, edi,ebx,[sc.work_graph]
	@@:
	jmp .end_f

	;ࠬ�� ��� ����
	.brush:
	dec eax
	mov ecx,[brush_w]
	imul ecx,[tile_size]
	;mov edi,eax
	mov edi,ecx
	mov esi,[brush_h]
	imul esi,[tile_size]
	stdcall [buf2d_rect_by_size], buf_pl, eax,ebx, edi,esi,[sc.work_graph]

    ;�ᮢ���� �祪 ��� ����
    mov ecx,[brush_w]
    mov edx,[tile_size]
    sub eax,edx ;eax-=tile_size
    shr edx,2
    add eax,edx ;eax+=tile_size/4
    add ebx,edx ;ebx+=tile_size/4
    mov edx,eax
    mov esi,[tile_size]
    imul esi,ecx
    imul ecx,[brush_h]
    add esi,edx
    ;eax = from edx to esi
    mov edi,brush_data
    cld
    @@:
        add eax,[tile_size]
        bt dword[edi],31
        jc .no_pixel
            bt dword[edi],30
            jc .sel_color
                push dword[edi]
                jmp .set_pixel
            .sel_color:
                push [v_color]
            .set_pixel:
            stdcall [buf2d_rect_by_size], buf_pl, eax,ebx, 3,3 ;, [edi]
        .no_pixel:
        add edi,4
        cmp eax,esi
        jl .end_line        
            mov eax,edx
            add ebx,[tile_size]
        .end_line:
    loop @b

	.end_f:
popad
	ret

;hot_p - ���न���� ����祩 �窨 �����, ᬥ饭�� �� ��� 16 ((cx shl 8) + cy) shl 16
align 4
proc set_pen_mode uses eax ebx ecx edx, mode:dword, icon:dword, hot_p:dword
	mov eax,[mode]
	cmp [v_pen_mode],eax
	je @f
		mov [v_pen_mode],eax
		mov edx,[hot_p]
		mov dx,2 ;LOAD_INDIRECT
		mov ecx,[icon]
		shl ecx,12 ;㬭����� �� 4 ��
		add ecx,[buf_curs.data]
		mcall SF_MOUSE_GET,SSF_LOAD_CURSOR

		cmp eax,0
		je @f
			mov [cursor_pointer],eax
			mcall SF_MOUSE_GET,SSF_SET_CURSOR,[cursor_pointer]
	@@:
	ret
endp

;����� ��� ������� ������ 䠩���
align 4
OpenDialog_data:
.type			dd 0 ;0 - ������, 1 - ��࠭���, 2 - ����� ��४���
.procinfo		dd procinfo	;+4
.com_area_name		dd communication_area_name	;+8
.com_area		dd 0	;+12
.opendir_path		dd plugin_path	;+16
.dir_default_path	dd default_dir ;+20
.start_path		dd file_name ;+24 ���� � ������� ������ 䠩���
.draw_window		dd draw_window	;+28
.status 		dd 0	;+32
.openfile_path		dd openfile_path	;+36 ���� � ���뢠����� 䠩��
.filename_area		dd filename_area	;+40
.filter_area		dd Filter
.x:
.x_size 		dw 420 ;+48 ; Window X size
.x_start		dw 10 ;+50 ; Window X position
.y:
.y_size 		dw 320 ;+52 ; Window y size
.y_start		dw 10 ;+54 ; Window Y position

default_dir db '/sys',0

communication_area_name:
	db 'FFFFFFFF_open_dialog',0
open_dialog_name:
	db 'opendial',0
communication_area_default_path:
	db '/sys/File managers/',0

Filter:
dd Filter.end - Filter ;.1
.1:
db 'VOX',0
.end:
db 0


system_dir_0 db '/sys/lib/'
lib_name_0 db 'proc_lib.obj',0
system_dir_1 db '/sys/lib/'
lib_name_1 db 'libimg.obj',0
system_dir_2 db '/sys/lib/'
lib_name_2 db 'buf2d.obj',0
system_dir_3 db '/sys/lib/'
lib_name_3 db 'libini.obj',0


l_libs_start:
	lib_0 l_libs lib_name_0, file_name, system_dir_0, import_proclib
	lib_1 l_libs lib_name_1, file_name, system_dir_1, import_libimg
	lib_2 l_libs lib_name_2, file_name, system_dir_2, import_buf2d
	lib_3 l_libs lib_name_3, file_name, system_dir_3, import_libini
l_libs_end:

align 4
import_libimg:
	dd alib_init1
	img_is_img  dd aimg_is_img
	img_info    dd aimg_info
	img_from_file dd aimg_from_file
	img_to_file dd aimg_to_file
	img_from_rgb dd aimg_from_rgb
	img_to_rgb  dd aimg_to_rgb
	img_to_rgb2 dd aimg_to_rgb2
	img_decode  dd aimg_decode
	img_encode  dd aimg_encode
	img_create  dd aimg_create
	img_destroy dd aimg_destroy
	img_destroy_layer dd aimg_destroy_layer
	img_count   dd aimg_count
	img_lock_bits dd aimg_lock_bits
	img_unlock_bits dd aimg_unlock_bits
	img_flip    dd aimg_flip
	img_flip_layer dd aimg_flip_layer
	img_rotate  dd aimg_rotate
	img_rotate_layer dd aimg_rotate_layer
	img_draw    dd aimg_draw

	dd 0,0
	alib_init1   db 'lib_init',0
	aimg_is_img  db 'img_is_img',0 ;��।���� �� �����, ����� �� ������⥪� ᤥ���� �� ��� ����ࠦ����
	aimg_info    db 'img_info',0
	aimg_from_file db 'img_from_file',0
	aimg_to_file db 'img_to_file',0
	aimg_from_rgb db 'img_from_rgb',0
	aimg_to_rgb  db 'img_to_rgb',0 ;�८�ࠧ������ ����ࠦ���� � ����� RGB
	aimg_to_rgb2 db 'img_to_rgb2',0
	aimg_decode  db 'img_decode',0 ;��⮬���᪨ ��।���� �ଠ� ����᪨� ������
	aimg_encode  db 'img_encode',0
	aimg_create  db 'img_create',0
	aimg_destroy db 'img_destroy',0
	aimg_destroy_layer db 'img_destroy_layer',0
	aimg_count   db 'img_count',0
	aimg_lock_bits db 'img_lock_bits',0
	aimg_unlock_bits db 'img_unlock_bits',0
	aimg_flip    db 'img_flip',0
	aimg_flip_layer db 'img_flip_layer',0
	aimg_rotate  db 'img_rotate',0
	aimg_rotate_layer db 'img_rotate_layer',0
	aimg_draw    db 'img_draw',0

align 4
import_proclib:
	OpenDialog_Init dd aOpenDialog_Init
	OpenDialog_Start dd aOpenDialog_Start
dd 0,0
	aOpenDialog_Init db 'OpenDialog_init',0
	aOpenDialog_Start db 'OpenDialog_start',0

align 4
import_buf2d:
	init dd sz_init
	buf2d_create dd sz_buf2d_create
	buf2d_create_f_img dd sz_buf2d_create_f_img
	buf2d_clear dd sz_buf2d_clear
	buf2d_draw dd sz_buf2d_draw
	buf2d_delete dd sz_buf2d_delete
	buf2d_line dd sz_buf2d_line
	buf2d_rect_by_size dd sz_buf2d_rect_by_size
	buf2d_filled_rect_by_size dd sz_buf2d_filled_rect_by_size
	buf2d_circle dd sz_buf2d_circle
	buf2d_img_hdiv2 dd sz_buf2d_img_hdiv2
	buf2d_img_wdiv2 dd sz_buf2d_img_wdiv2
	buf2d_conv_24_to_8 dd sz_buf2d_conv_24_to_8
	buf2d_conv_24_to_32 dd sz_buf2d_conv_24_to_32
	buf2d_bit_blt dd sz_buf2d_bit_blt
	buf2d_bit_blt_transp dd sz_buf2d_bit_blt_transp
	buf2d_bit_blt_alpha dd sz_buf2d_bit_blt_alpha
	buf2d_curve_bezier dd sz_buf2d_curve_bezier
	buf2d_convert_text_matrix dd sz_buf2d_convert_text_matrix
	buf2d_draw_text dd sz_buf2d_draw_text
	buf2d_crop_color dd sz_buf2d_crop_color
	buf2d_offset_h dd sz_buf2d_offset_h
	buf2d_flood_fill dd sz_buf2d_flood_fill
	buf2d_set_pixel dd sz_buf2d_set_pixel
	buf2d_get_pixel dd sz_buf2d_get_pixel
	buf2d_flip_h dd sz_buf2d_flip_h
	buf2d_flip_v dd sz_buf2d_flip_v
	buf2d_rotate dd sz_buf2d_rotate
	buf2d_vox_brush_create dd sz_buf2d_vox_brush_create
	buf2d_vox_brush_delete dd sz_buf2d_vox_brush_delete
	buf2d_vox_obj_get_img_w_3g dd sz_buf2d_vox_obj_get_img_w_3g
	buf2d_vox_obj_get_img_h_3g dd sz_buf2d_vox_obj_get_img_h_3g
	buf2d_vox_obj_draw_1g dd sz_buf2d_vox_obj_draw_1g
	buf2d_vox_obj_draw_3g dd sz_buf2d_vox_obj_draw_3g
	buf2d_vox_obj_draw_3g_scaled dd sz_buf2d_vox_obj_draw_3g_scaled
	buf2d_vox_obj_draw_3g_shadows dd sz_buf2d_vox_obj_draw_3g_shadows
	buf2d_vox_obj_draw_pl dd sz_buf2d_vox_obj_draw_pl
	buf2d_vox_obj_draw_pl_scaled dd sz_buf2d_vox_obj_draw_pl_scaled

	dd 0,0
	sz_init db 'lib_init',0
	sz_buf2d_create db 'buf2d_create',0
	sz_buf2d_create_f_img db 'buf2d_create_f_img',0
	sz_buf2d_clear db 'buf2d_clear',0
	sz_buf2d_draw db 'buf2d_draw',0
	sz_buf2d_delete db 'buf2d_delete',0
	sz_buf2d_line db 'buf2d_line',0
	sz_buf2d_rect_by_size db 'buf2d_rect_by_size',0
	sz_buf2d_filled_rect_by_size db 'buf2d_filled_rect_by_size',0
	sz_buf2d_circle db 'buf2d_circle',0
	sz_buf2d_img_hdiv2 db 'buf2d_img_hdiv2',0
	sz_buf2d_img_wdiv2 db 'buf2d_img_wdiv2',0
	sz_buf2d_conv_24_to_8 db 'buf2d_conv_24_to_8',0
	sz_buf2d_conv_24_to_32 db 'buf2d_conv_24_to_32',0
	sz_buf2d_bit_blt db 'buf2d_bit_blt',0
	sz_buf2d_bit_blt_transp db 'buf2d_bit_blt_transp',0
	sz_buf2d_bit_blt_alpha db 'buf2d_bit_blt_alpha',0
	sz_buf2d_curve_bezier db 'buf2d_curve_bezier',0
	sz_buf2d_convert_text_matrix db 'buf2d_convert_text_matrix',0
	sz_buf2d_draw_text db 'buf2d_draw_text',0
	sz_buf2d_crop_color db 'buf2d_crop_color',0
	sz_buf2d_offset_h db 'buf2d_offset_h',0
	sz_buf2d_flood_fill db 'buf2d_flood_fill',0
	sz_buf2d_set_pixel db 'buf2d_set_pixel',0
	sz_buf2d_get_pixel db 'buf2d_get_pixel',0
	sz_buf2d_flip_h db 'buf2d_flip_h',0
	sz_buf2d_flip_v db 'buf2d_flip_v',0
	sz_buf2d_rotate db 'buf2d_rotate',0
	sz_buf2d_vox_brush_create db 'buf2d_vox_brush_create',0
	sz_buf2d_vox_brush_delete db 'buf2d_vox_brush_delete',0
	sz_buf2d_vox_obj_get_img_w_3g db 'buf2d_vox_obj_get_img_w_3g',0
	sz_buf2d_vox_obj_get_img_h_3g db 'buf2d_vox_obj_get_img_h_3g',0
	sz_buf2d_vox_obj_draw_1g db 'buf2d_vox_obj_draw_1g',0
	sz_buf2d_vox_obj_draw_3g db 'buf2d_vox_obj_draw_3g',0
	sz_buf2d_vox_obj_draw_3g_scaled db 'buf2d_vox_obj_draw_3g_scaled',0
	sz_buf2d_vox_obj_draw_3g_shadows db 'buf2d_vox_obj_draw_3g_shadows',0
	sz_buf2d_vox_obj_draw_pl db 'buf2d_vox_obj_draw_pl',0
	sz_buf2d_vox_obj_draw_pl_scaled db 'buf2d_vox_obj_draw_pl_scaled',0

align 4
import_libini:
	dd alib_init2
	ini_get_str   dd aini_get_str
	ini_get_int   dd aini_get_int
	ini_get_color dd aini_get_color
dd 0,0
	alib_init2     db 'lib_init',0
	aini_get_str   db 'ini_get_str',0
	aini_get_int   db 'ini_get_int',0
	aini_get_color db 'ini_get_color',0

;���� �᭮����� ����ࠦ����
align 4
buf_0: dd 0 ;㪠��⥫� �� �a�� ����ࠦ����
.l: dw 5 ;+4 left
.t: dw 45 ;+6 top
.w: dd 192+6 ;+8 w
.h: dd 224+7 ;+12 h
.color: dd 0xffffff ;+16 color
	db 24 ;+20 bit in pixel

;���� ��㡨�� �᭮����� ����ࠦ����
align 4
buf_0z: dd 0
	dw 0 ;+4 left
	dw 0 ;+6 top
.w: dd 192+6 ;+8 w
.h: dd 224+7 ;+12 h
.color: dd 0 ;+16 color
	db 32 ;+20 bit in pixel

;���� ��� �ᮢ���� �१� ��ꥪ�
align 4
buf_pl: dd 0
.l: dw 15+192+6 ;+4 left
.t: dw 45 ;+6 top
.w: dd 320 ;+8 w
.h: dd 330 ;+12 h
.color: dd 0xffffff ;+16 color
	db 24 ;+20 bit in pixel

;���� ��� ���襭��� ७���
align 4
buf_r_img:
	rb BUF_STRUCT_SIZE
align 4
buf_r_z:
	rb BUF_STRUCT_SIZE

align 4
buf_curs: ;���� � ����ࠬ�
.data: dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 0 ;+4 left
	dw 0 ;+6 top
	dd 32 ;+8 w
	dd 32*cursors_count ;+12 h
	dd 0 ;+16 color
	db 24 ;+20 bit in pixel

align 4
buf_curs_8: ;���� � �஧�筮���� ��� ����஢
.data: dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 0 ;+4 left
	dw 0 ;+6 top
	dd 32 ;+8 w
	dd 32*cursors_count ;+12 h
	dd 0 ;+16 color
	db 24 ;+20 bit in pixel

;����� ��� ᮧ����� �������쭮�� �����筮�� ���ᥫ�
align 4
vox_6_7_z: ;���ᥫ� ��� ����� 3 �࠭�
dd 0,0,1,1,0,0,\
   0,2,2,2,2,0,\
   2,2,2,2,2,2,\
   2,3,2,2,3,2,\
   2,3,3,3,3,2,\
   0,3,3,3,3,0,\
   0,0,3,3,0,0

align 4
vox_6_4_z: ;���ᥫ�, ��� ����� 2 ������ �࠭� � ���孥� �࠭� �� �����
dd 1,2,3,3,2,1,\
   1,2,3,3,2,1,\
   1,2,3,3,2,1,\
   1,2,3,3,2,1

align 4
buf_vox dd buf_vox_g3

buf_vox_g3:
	db 6,7,4,3 ;w,h,h_osn,n
	rb BUF_STRUCT_SIZE*(3+1)

align 4
buf_vox_g2:
	db 6,4,0,3 ;w,h,h_osn,n
	rb BUF_STRUCT_SIZE*(3+1)

align 16
i_end:
	procinfo process_information
	sc system_colors
	mouse_dd dd ?
	cursor_pointer dd ? ;㪠��⥫� �� ����� ��� �����
	wnd_s_pos: ;���� ��� ����஥� ���⮢�� ����樨 ����
		rq 0
	rb 4096
align 16
stacktop:
	sys_path rb 1024
	file_name rb 2048 ;4096 
	plugin_path rb 1024 ;4096
	openfile_path rb 4096
	filename_area rb 256
mem:
