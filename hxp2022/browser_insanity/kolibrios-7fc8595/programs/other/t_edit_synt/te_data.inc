fn_col_option dd def_col_file
fn_syntax_dir db 'info/',0
def_col_file db 'default.syn',0

system_dir_0 db '/sys/lib/'
lib_name_0 db 'box_lib.obj',0

system_dir_1 db '/sys/lib/'
lib_name_1 db 'libimg.obj',0
;---------------------------------------------------------------------

align 4
import_box_lib:
dd alib_init2 ;�㭪�� ����᪠���� ����ᮬ 1 ࠧ �� ������祭�� �������⥪�, ��⮬� � �ணࠬ�� ��⪠ �� ��� �� �㦭�

edit_box_draw  dd aEdit_box_draw
edit_box_key   dd aEdit_box_key
edit_box_mouse dd aEdit_box_mouse

scrollbar_ver_draw  dd aScrollbar_ver_draw
scrollbar_ver_mouse dd aScrollbar_ver_mouse
scrollbar_hor_draw  dd aScrollbar_hor_draw
scrollbar_hor_mouse dd aScrollbar_hor_mouse

tl_data_init dd sz_tl_data_init
tl_data_clear dd sz_tl_data_clear
tl_info_clear dd sz_tl_info_clear
tl_key dd sz_tl_key
tl_mouse dd sz_tl_mouse
tl_draw dd sz_tl_draw
tl_info_undo dd sz_tl_info_undo
tl_info_redo dd sz_tl_info_redo
tl_node_add dd sz_tl_node_add
tl_node_set_data dd sz_tl_node_set_data
tl_node_get_data dd sz_tl_node_get_data
tl_node_delete dd sz_tl_node_delete
tl_cur_beg dd sz_tl_cur_beg
tl_cur_next dd sz_tl_cur_next
tl_cur_perv dd sz_tl_cur_perv
tl_node_close_open dd sz_tl_node_close_open
tl_node_lev_inc dd sz_tl_node_lev_inc
tl_node_lev_dec dd sz_tl_node_lev_dec
tl_node_move_down dd sz_tl_node_move_down
tl_save_mem dd sz_tl_save_mem
tl_load_mem dd sz_tl_load_mem

ted_but_sumb_upper dd sz_ted_but_sumb_upper
ted_but_sumb_lover dd sz_ted_but_sumb_lover
ted_can_save dd sz_ted_can_save
ted_clear dd sz_ted_clear
ted_delete dd sz_ted_delete
ted_draw dd sz_ted_draw
ted_init dd sz_ted_init
ted_init_scroll_bars dd sz_ted_init_scroll_bars
ted_init_syntax_file dd sz_ted_init_syntax_file
ted_is_select dd sz_ted_is_select
ted_key dd sz_ted_key
ted_mouse dd sz_ted_mouse
ted_open_file dd sz_ted_open_file
ted_save_file dd sz_ted_save_file
ted_text_add dd sz_ted_text_add
ted_but_select_word dd sz_ted_but_select_word
ted_but_cut dd sz_ted_but_cut
ted_but_copy dd sz_ted_but_copy
ted_but_paste dd sz_ted_but_paste
ted_but_undo dd sz_ted_but_undo
ted_but_redo dd sz_ted_but_redo
ted_but_reverse dd sz_ted_but_reverse
ted_but_find dd sz_ted_but_find
ted_text_colored dd sz_ted_text_colored

PathShow_prepare dd sz_PathShow_prepare
PathShow_draw    dd sz_PathShow_draw

dd 0,0
alib_init2 db 'lib_init',0

aEdit_box_draw	db 'edit_box_draw',0
aEdit_box_key	db 'edit_box_key',0
aEdit_box_mouse db 'edit_box_mouse',0

aScrollbar_ver_draw  db 'scrollbar_v_draw',0
aScrollbar_ver_mouse db 'scrollbar_v_mouse',0
aScrollbar_hor_draw  db 'scrollbar_h_draw',0
aScrollbar_hor_mouse db 'scrollbar_h_mouse',0

sz_tl_data_init db 'tl_data_init',0
sz_tl_data_clear db 'tl_data_clear',0
sz_tl_info_clear db 'tl_info_clear',0
sz_tl_key db 'tl_key',0
sz_tl_mouse db 'tl_mouse',0
sz_tl_draw db 'tl_draw',0
sz_tl_info_undo db 'tl_info_undo',0
sz_tl_info_redo db 'tl_info_redo',0
sz_tl_node_add db 'tl_node_add',0
sz_tl_node_set_data db 'tl_node_set_data',0
sz_tl_node_get_data db 'tl_node_get_data',0
sz_tl_node_delete db 'tl_node_delete',0
sz_tl_cur_beg db 'tl_cur_beg',0
sz_tl_cur_next db 'tl_cur_next',0
sz_tl_cur_perv db 'tl_cur_perv',0
sz_tl_node_close_open db 'tl_node_close_open',0
sz_tl_node_lev_inc db 'tl_node_lev_inc',0
sz_tl_node_lev_dec db 'tl_node_lev_dec',0
sz_tl_node_move_down db 'tl_node_move_down',0
sz_tl_save_mem db 'tl_save_mem',0
sz_tl_load_mem db 'tl_load_mem',0

sz_ted_but_sumb_upper	db 'ted_but_sumb_upper',0
sz_ted_but_sumb_lover	db 'ted_but_sumb_lover',0
sz_ted_can_save 		db 'ted_can_save',0
sz_ted_clear			db 'ted_clear',0
sz_ted_delete			db 'ted_delete',0
sz_ted_draw				db 'ted_draw',0
sz_ted_init				db 'ted_init',0
sz_ted_init_scroll_bars db 'ted_init_scroll_bars',0
sz_ted_init_syntax_file db 'ted_init_syntax_file',0
sz_ted_is_select		db 'ted_is_select',0
sz_ted_key				db 'ted_key',0
sz_ted_mouse			db 'ted_mouse',0
sz_ted_open_file		db 'ted_open_file',0
sz_ted_save_file		db 'ted_save_file',0
sz_ted_text_add 		db 'ted_text_add',0
sz_ted_but_select_word	db 'ted_but_select_word',0
sz_ted_but_cut			db 'ted_but_cut',0
sz_ted_but_copy 		db 'ted_but_copy',0
sz_ted_but_paste		db 'ted_but_paste',0
sz_ted_but_undo 		db 'ted_but_undo',0
sz_ted_but_redo 		db 'ted_but_redo',0
sz_ted_but_reverse		db 'ted_but_reverse',0
sz_ted_but_find	db 'ted_but_find',0
sz_ted_text_colored		db 'ted_text_colored',0
sz_ted_go_to_position	db 'ted_go_to_position',0

sz_PathShow_prepare db 'PathShow_prepare',0
sz_PathShow_draw db 'PathShow_draw',0

align 4
import_libimg:
        dd alib_init1
        img_to_rgb2 dd aimg_to_rgb2
        img_decode  dd aimg_decode
        img_destroy dd aimg_destroy
dd 0,0
        alib_init1   db 'lib_init',0
        aimg_to_rgb2 db 'img_to_rgb2',0
        aimg_decode  db 'img_decode',0 ;��⮬���᪨ ��।���� �ଠ� ����᪨� ������
        aimg_destroy db 'img_destroy',0
;---------------------------------------------------------------------
;���୨� �஫���� ��� ������� ListBox
align 4
ws_dir_lbox scrollbar 16,0, 30,70, 15, 100,30,0, 0,0,0, 1
;---------------------------------------------------------------------

count_of_dir_list_files equ 15

el_focus dd 0
mouse_dd dd 0

tree1 tree_list 264,count_of_dir_list_files+2, tl_key_no_edit+tl_draw_par_line+tl_list_box_mode,\
    16,16, 0x8080ff,0x0000ff,0xffffff, 5,5,180-17,185, 12,0,0, el_focus,\
    ws_dir_lbox,0

;dir_list memory
tree_file_struct:
	dd 1
	dd 0,0,count_of_dir_list_files
	dd dir_mem
	db 0
	dd file_name

dir_mem rb 32+304*count_of_dir_list_files

edit1 edit_box 310+16-CAPT_PATH_WIDTH, 210+CAPT_PATH_WIDTH, 25, 0xffffff, 0xff, 0xff0000, 0, 0x80, MAX_COLOR_WORD_LEN, ed_buffer.127, mouse_dd, 0

ed_buffer: ;⥪�� ��� edit
  .127: rb MAX_COLOR_WORD_LEN+2

;------------------------------------------------------------------------------
align 4
tedit0: ;������� ⥪�⮢��� ।����
	.wnd BOX 195,5+40,325,240 ;+ 0
	.rec BOX 30,13,7,10   ;+16
	.drag_m db 0 ;+32 �뤥����� �� ���
	.drag_k db 0 ;+33 �뤥����� �� ����������
	.sel rb 16 ;+34 ������� �뤥�����
	.seln rb 16 ;+50 �������⥫쭠� ������� �뤥�����
	.tex	  dd 0 ;+66 text memory pointer
	.tex_1	  dd 0 ;+70 text first symbol pointer
	.tex_end  dd 0 ;+74 text end memory pointer
	.cur_x	  dd 0 ;+78 ���न��� x �����
	.cur_y	  dd 0 ;+82 ���न��� y �����
	.max_chars dd 25002 ;+86 ���ᨬ��쭮� �᫮ ᨬ����� � ����� ���㬥��
	.count_colors_text dd 1 ;+90 �������⢮ 梥⮢ ⥪��
	.count_key_words   dd 0 ;+94 �������⢮ ���祢�� ᫮�
	.color_cursor	   dd 0xff0000 ;+98 梥� �����
	.color_wnd_capt    dd 0x0080c0 ;+102 梥� ����� ����� ����
	.color_wnd_work    dd	   0x0 ;+106 梥� 䮭� ����
	.color_wnd_bord    dd 0xffffff ;+110 梥� ⥪�� �� �����
	.color_select	   dd 0x0000ff ;+114 梥� �뤥�����
	.color_cur_text    dd 0xffff00 ;+118 梥� ᨬ���� ��� ����஬
	.color_wnd_text    dd 0x80ffff ;+122 梥� ⥪�� � ����
	.syntax_file	   dd 0 ;+126 㪠��⥫� �� ��砫� 䠩�� ᨭ⠪��
	.syntax_file_size  dd 500 ;+130 ���ᨬ���� ࠧ��� 䠩�� ᨭ⠪��
	.text_colors	   dd 0 ;+134 㪠��⥫� �� ���ᨢ 梥⮢ ⥪��
	.help_text_f1	   dd 0 ;+138 㪠��⥫� �� ⥪�� �ࠢ�� (�� ����⨨ F1)
	.help_id	   dd -1 ;+142 �����䨪��� ��� �ࠢ��
	.key_words_data    dd 0 ;+146 㪠��⥫� �� �������� ���祢�� ᫮� TexColViv
	.tim_ch      dd ? ;+150 ������⢮ ��������� � 䠩��
	.tim_undo    dd ? ;+154 ������⢮ �⬥������ ����⢨�
	.tim_ls      dd ? ;+158 �६� ��᫥����� ��࠭����
	.tim_co      dd ? ;+162 �६� ��᫥���� 梥⮢�� ࠧ��⪨
	.el_focus    dd el_focus ;+166 㪠��⥫� �� ��६����� ������� � 䮪��
	.err_save    db 0 ;+170 �訡�� ��࠭���� 䠩��
	.panel_id    db 0 ;+171 ����� ����⮩ ������
	.key_new     db 0 ;+172 ᨬ���, ����� �㤥� ���������� � ����������
	.symbol_new_line db 20 ;+173 ᨬ��� �����襭�� ��ப�
	.scr_w	     dd scrol_w1 ;+174 ���⨪���� �஫����
	.scr_h	     dd scrol_h1 ;+178 ��ਧ��⠫�� �஫����
	.arr_key_pos dd 0 ;+182 㪠��⥫� �� ���ᨢ ����権 ���祢�� ᫮�
	.buffer      dd buf ;+186 㪠��⥫� �� ���� ����஢����/��⠢��
	.buffer_find dd 0 ;+190 㪠��⥫� �� ���� ��� ���᪠
	.cur_ins     db 1 ;+194 ०�� ࠡ��� ����� (����� ��� ������)
	.mode_color  db 1 ;+195 ०�� �뤥����� ᫮� 梥⮬ (0-�몫. 1-���.)
	.mode_invis  db 0 ;+196 ०�� ������ �����⠥��� ᨬ�����
	.gp_opt      db 0 ;+197 ��樨 �����頥�� �㭪樥� ted_get_pos_by_cursor
	.fun_on_key_ctrl_all dd ted_but_ctrl_all ;+198 㪠��⥫� �� �㭪�� ��뢠���� �� ����⨨ Ctrl+N,O,S,F,G,H
	dd 0,0,0
	.buffer_size	   dd BUF_SIZE ;+214 ࠧ��� ���� ����஢����/��⠢��
	.fun_find_err	   dd 0 ;+218 㪠��⥫� �� �㭪�� ��뢠���� �᫨ ���� �����稫�� ��㤠筮
	.fun_init_synt_err dd 0 ;+222 㪠��⥫� �� �㭪�� ��뢠���� �� �訡�筮� ����⨨ 䠩�� ᨭ⠪��
	.fun_draw_panel_buttons dd 0 ;+226 㪠��⥫� �� �㭪�� �ᮢ���� ������ � ��������
	.fun_draw_panels	dd 0 ;+230 㪠��⥫� �� �㭪�� �ᮢ���� ������ ���᪠|...|ᨭ⠪��
	dd 0
	.fun_save_err		dd 0 ;+238 㪠��⥫� �� �㭪�� ��뢠���� �᫨ ��࠭���� 䠩�� �����稫��� ��㤠筮
	.increase_size dd 1000 ;+242 �᫮ ᨬ����� �� ����� �㤥� 㢥稢����� ������ �� ��墠⪥
	.ptr_free_symb dd ? ;+246 㪠��⥫� �� ᢮������ ������, � ������ ����� ��������� ᨬ��� (�ᯮ������ ����� ������� ��� �᪮७�� ��⠢�� ⥪��)
	.font_size dd 0   ;+250 �����⥫� ��� ࠧ��� ����
;------------------------------------------------------------------------------
align 4
scrol_w1 scrollbar 16,85, 100,15, 15, 100,0,0, 0xeeeeee,0xbbddff,0x808080, 1

align 4
scrol_h1 scrollbar 85,30,  16,100, 15, 100,0,0, 0xeeeeee,0xbbddff,0x808080, 1
;---------------------------------------------------------------------
PathShow_data_1:
.type			dd 0 ;+0
.start_y		dw 10 ;+4
.start_x		dw 210+CAPT_PATH_WIDTH ;+6
.font_size_x		dw 6	;+8	; 6 - for font 0, 8 - for font 1
.area_size_x		dw 310+16-CAPT_PATH_WIDTH	;+10
.font_number		dd 0 ;+12	; 0 - monospace, 1 - variable
.background_flag	dd 1 ;+16
.font_color		dd 0x0 ;+20
.background_color	dd 0xffffff ;+24
.text_pointer		dd file_name ;+28
.work_area_pointer	dd file_name_rez ;+32
.temp_text_length	dd 0 ;+36

align 4
str_file_70:
  rb (5*4+1+4) ;���� ��� �������� ��� ࠡ��� � 䠩��� (�. 70)

text_buffer db 500 dup(0)

align 4
;conv_tabl rb 128 ;⠡��� ��� �������஢���� scan-���� � ascii-���
buf db BUF_SIZE dup(0) ;���� ��� ����஢���� | ��⠢��

capt_header db 'macro wo txt,lf1,p1,p2,p3{',13
	db '@@: db txt',13,'rb @b+40-$',13
	db 'if lf1 eq',13,'dd 0',13 ;�᫨ ��뫪� f1 �����
	db 'else if lf1 eq 0',13,'dd 0',13 ;�᫨ ��뫪� f1 ࠢ�� 0
	db 'else',13,'dd f1.#lf1-f1',13,'end if',13 ;�᫨ ��뫪� f1 ������ ��⪮�
	db 'db p1',13,'dw p2+0',13,'db p3',13,'}',13
	db 'count_colors_text dd (text-color_wnd_text)/4',13
	db 'count_key_words dd (f1-text)/48',13,0
col_1 db 'color_cursor dd ',0	;+ 98 梥� �����
col_2 db 'color_wnd_capt dd ',0 ;+102 梥� ����� ����� ����
col_3 db 'color_wnd_work dd ',0 ;+106 梥� 䮭� ����
col_4 db 'color_wnd_bord dd ',0 ;+110 梥� ⥪�� �� �����
col_5 db 'color_select dd ',0	;+114 梥� �뤥�����
col_6 db 'color_cur_text dd ',0 ;+118 梥� ᨬ���� ��� ����஬
col_7 db 'color_wnd_text:',13,0 ;+122 梥� ⥪�� � ����

capt_lbl_wo db 'text:',13,0
capt_beg_word db 'wo<',39,0
capt_beg_db db ':db ',39,0
capt_end_word db 39,'>,',0
capt_type_dd db 9,'dd ',0
capt_lbl_f1 db 'f1: db 0',13,0
capt_end_word_f1 db 39,',0',13,0
capt_point db '.',0
capt_null db '0',0

KM_SHIFT equ 0x00010000
KM_CTRL equ 0x00020000
KM_ALT equ 0x00040000
KM_NUMLOCK equ 0x00080000

; KEY CODES
KEY_F1 equ 0x0000003B
KEY_F2 equ 0x0000003C
KEY_F3 equ 0x0000003D

