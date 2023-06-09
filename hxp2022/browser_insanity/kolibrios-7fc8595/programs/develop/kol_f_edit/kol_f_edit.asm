use32
	org 0
	db 'MENUET01'
	dd 1,start,i_end,mem,stacktop,buf_cmd_lin,sys_path

include '../../KOSfuncs.inc'
include '../../macros.inc'
include '../../proc32.inc'
include '../../load_lib.mac'
include '../../develop/libraries/box_lib/trunk/box_lib.mac'
include '../../dll.inc'
include '../../system/skincfg/trunk/kglobals.inc'
include '../../system/skincfg/trunk/unpacker.inc'
include 'strlen.inc'
include 'obj_codes.inc'

@use_library mem.Alloc,mem.Free,mem.ReAlloc, dll.Load

hed db 'kol_f_edit 29.09.20',0

sizeof.TreeList equ 20 ;need for element 'tree_list'

BUF_STRUCT_SIZE equ 21
buf2d_data equ dword[edi] ;����� ���� ����ࠦ����
buf2d_w equ dword[edi+8] ;�ਭ� ����
buf2d_h equ dword[edi+12] ;���� ����
buf2d_l equ word[edi+4] ;����� ᫥��
buf2d_t equ word[edi+6] ;����� ᢥ���
buf2d_size_lt equ dword[edi+4] ;����� ᫥�� � �ࠢ� ��� ����
buf2d_color equ dword[edi+16] ;梥� 䮭� ����
buf2d_bits equ byte[edi+20] ;������⢮ ��� � 1-� �窥 ����ࠦ����


MAX_CED_OBJECTS equ 200
MAX_OPT_FIELDS equ 11
MAX_OBJ_TYPES equ 17 ;���ᨬ��쭮� �᫮ ��ꥪ⮢
MAX_OBJ_CAPTIONS equ 1000 ;ࠧ��� �������⥫��� �����ᥩ �����ᥩ
WND_CAPT_COLOR equ 0xb0d0ff
BUF_SIZE equ 1000

;modif
BIT_MOD_ACI equ 0 ;��ࢮ��砫�� ����ன�� ������⮢
BIT_MOD_ACM equ 1 ;ᮡ��� �� ���
BIT_MOD_ACD equ 2 ;����� ��ꥪ⮢
BIT_MOD_ABU equ 3 ;��뢠��� ������
BIT_MOD_WI_CAPT equ 0 ;�⨫� ���� �������
BIT_MOD_WI_CORD_OTN_CL_OBL equ 1 ;�⨫� ���� ���न���� �⭮�⥫쭮 ������᪮� ������
BIT_MOD_WI_REDR equ 2 ;�⨫� ���� ����ᮢ�� ����
BIT_MOD_WI_GRAD equ 3 ;�⨫� ���� �ࠤ����
BIT_MOD_CHE equ 0 ; ch_flag_en - ��࠭ CheckBox
BIT_MOD_CHE_T equ 1 ;ᢥ���
BIT_MOD_CHE_M equ 2 ;�� 業���
BIT_MOD_CHE_B equ 3 ;᭨��
BIT_MOD_TXT_ASCII_0 equ 0 ;⥪�� �����稢. 0
BIT_MOD_TXT_NO_TRAN equ 1 ;⥪�� �஧���
BIT_MOD_TXT_CHAR2 equ 2 ;⥪�� 2-� ���⮬
BIT_MOD_EDIT_FOC equ 0 ;EditBox � 䮪��
BIT_MOD_EDIT_FIO equ 1 ;
;CPP_MOD_RE_GR equ 1 ;�ࠤ����� ��אַ㣮�쭨�
BIT_MOD_BUT_NFON equ 0 ;�⨫� Button �� �ᮢ��� ������
BIT_MOD_BUT_NBORD equ 1 ;�⨫� Button �� �ᮢ��� �࠭���
BIT_MOD_IMPORT_FUNCT_COMMENT equ 0 ;������஢��� �㭪��

macro load_image_file path,buf,size { ;����� ��� ����㧪� ����ࠦ����
	;path - ����� ���� ��६����� ��� ��ப��� ��ࠬ��஬
	if path eqtype '' ;�஢��塞 ����� �� ��ப�� ��ࠬ��� path
		jmp @f
			local .path_str
			.path_str db path ;�ନ�㥬 �������� ��६�����
			db 0
		@@:
		;32 - �⠭����� ���� �� ���஬� ������ ���� ���� � ��⥬�� ��⥬
		copy_path .path_str,[32],file_name,0
	else
		copy_path path,[32],file_name,0 ;�ନ�㥬 ����� ���� � 䠩�� ����ࠦ����, ���ࠧ㬥���� �� �� � ����� ����� � �ணࠬ���
	end if

	stdcall mem.Alloc, dword size ;�뤥�塞 ������ ��� ����ࠦ����
	mov [buf],eax

	mov [run_file_70.Function], 0
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov [run_file_70.Count], dword size
	m2m [run_file_70.Buffer], eax
	mov byte[run_file_70+20], 0
	mov [run_file_70.FileName], file_name
	mcall 70,run_file_70 ;����㦠�� 䠩� ����ࠦ����
	cmp ebx,0xffffffff
	je @f
		;��।��塞 ��� ����ࠦ���� � ��ॢ���� ��� �� �६���� ���� image_data
		stdcall [img_decode], [buf],ebx,0
		mov [image_data],eax
		;�८�ࠧ㥬 ����ࠦ���� � �ଠ�� rgb
		stdcall [img_to_rgb2], [image_data],[buf]
		;㤠�塞 �६���� ���� image_data
		stdcall [img_destroy], [image_data]
	@@:
}

struct FileInfoBlock
	Function dd ?
	Position dd ?
	Flags	 dd ?
	Count	 dd ?
	Buffer	 dd ?
	rezerv	 db ?
	FileName dd ?
ends

struct object
	id dd ? ;�����䨪��� ��ꥪ�
	txt rb MAX_LEN_OBJ_TXT ;⥪�⮢� ᢮��⢠
	lvl db 0
	clo db 0
	typid dd ? ;����� ��ꥪ� ��।����饣� ⨯ ��६�����
	modif dd ? ;��⮢� ᢮��⢠
ends

struct ObjOpt
	dd ?
	bl_type db ?
	graph db ?
	info rb 30
	caption rb MAX_OPT_CAPTION
	Col rw MAX_OPT_FIELDS
	img rw MAX_OPT_FIELDS ;������� ���⨭�� (� 䠩�� 'icon.bmp')
	bit_prop dd 0 ;��⮢� ᢮��⢠ (������, ��������)
	bit_val dd 0 ;��⮢� ᢮��⢠ (���祭��, ����⠭��)
ends

SKIN_H equ 22
SKIN_W1 equ 5
SKIN_W2 equ 7
SKIN_W3 equ 23
fn_skin_1 db 'left.bmp',0
fn_skin_2 db 'base.bmp',0
fn_skin_3 db 'oper.bmp',0
IMAGE_FILE_SKIN1_SIZE equ 3*(SKIN_W1+3)*SKIN_H+54
IMAGE_FILE_SKIN2_SIZE equ 3*(SKIN_W2+3)*SKIN_H+54
IMAGE_FILE_SKIN3_SIZE equ 3*(SKIN_W3+3)*SKIN_H+54

IMAGE_FILE_FONT1_SIZE equ 96*144*3 ;ࠧ��� 䠩�� � 1-� ��⥬�� ���⮬

fn_icon db 'icon.bmp',0
count_main_icons equ 35 ;�᫮ ������ � 䠩�� icon.bmp
bmp_icon rb 0x300*count_main_icons

TREE_ICON_SYS16_BMP_SIZE equ 256*3*11+54 ;ࠧ��� bmp 䠩�� � ��⥬�묨 ��������
icon_tl_sys dd 0 ;㪠��⥥�� �� ������ ��� �࠭���� ��⥬��� ������
icon_font_s1 dd 0 ;㪠��⥫� �� �६����� ������ ��� ����㧪� ����

fn_syntax db 'asm.syn',0 ;��� ����㦠����� 䠩�� ᨭ⠪��

;����� ��� �஢�ન ��⮢��� ᢮��⢠
macro test_bool_prop obj_reg,n_prop
{
	bt dword[obj_reg+u_object.modif-u_object],n_prop
}

include 'ced_wnd_m.inc'
include 'ced_wnd_prop.inc' ;䠩� � �㭪�ﬨ ���� ᢮��� ��ꥪ�
include 'ced_constr.inc' ;䠩� � �㭪�ﬨ ���� ���������
include 'ced_code_g.inc' ;䠩� � �㭪�ﬨ �����஢���� �����

align 4
start:
	load_libraries l_libs_start,load_lib_end

	;�஢�ઠ �� ᪮�쪮 㤠筮 ���㧨���� ��� ����
	mov	ebp,lib0
	cmp	dword [ebp+ll_struc_size-4],0
	jz	@f
		mcall -1 ;exit not correct
	@@:
	mov	ebp,lib1
	cmp	dword [ebp+ll_struc_size-4],0
	jz	@f
		mcall -1 ;exit not correct
	@@:
	mov	ebp,lib2
	cmp	dword [ebp+ll_struc_size-4],0
	jz	@f
		mcall -1 ;exit not correct
	@@:
	mov	ebp,lib3
	cmp	dword [ebp+ll_struc_size-4],0
	jz	@f
		mcall -1 ;exit not correct
	@@:

	;������� ࠧ��஢ ����� � ᢮��⢠��
	mov eax,prop_edits_top
	mov ebx,16+6 ;�ਭ� ������ + ������
	mov edi,edit2
	@@:
		mov ed_top,eax ;����� ᢥ���
		mov ed_left,ebx ;����� ᫥��
		add edi,ed_struc_size
		add eax,prop_edits_height
		cmp edi,prop_wnd_edits_end
		jl @b

	stdcall [buf2d_create], buf_fon

	mcall 48,3,sc,sizeof.system_colors
	mcall 40,0x27

	stdcall [tl_data_init], tree1
	stdcall [tl_data_init], tree2

	copy_path fn_icon,sys_path,file_name,0 ;�ନ�㥬 ����� ���� � 䠩�� ����ࠦ����, ���ࠧ㬥���� �� �� � ����� ����� � �ணࠬ���
	mov [run_file_70.Function], 0
	mov [run_file_70.Position], 54
	mov [run_file_70.Flags], 0
	mov [run_file_70.Count], 0x300*count_main_icons
	mov [run_file_70.Buffer], bmp_icon
	mov [run_file_70.rezerv], 0
	mov [run_file_70.FileName], file_name
	mcall 70,run_file_70

	cmp ebx,-1
	mov [err_ini0],1
	je @f ;if open file
		mov [err_ini0],0
		mov dword[tree1.data_img],bmp_icon
		mov dword[tree2.data_img],bmp_icon
	@@:

	;��⥬�� ������ 16*16 ��� tree_list
	load_image_file 'tl_sys_16.png', icon_tl_sys,TREE_ICON_SYS16_BMP_SIZE
	;�᫨ ����ࠦ���� �� ���뫮��, � � icon_tl_sys ����
	;�� ���樠����஢���� �����, �� �訡�� �� �㤥�, �. �. ���� �㦭��� ࠧ���
	mov eax,dword[icon_tl_sys]
	mov dword[tree1.data_img_sys],eax
	mov dword[tree2.data_img_sys],eax

	;1-� 䠩� ᪨��
	load_image_file fn_skin_1, icon_font_s1,IMAGE_FILE_SKIN1_SIZE
	stdcall [buf2d_create_f_img], buf_skin1,[icon_font_s1] ;ᮧ���� ����
	stdcall mem.Free,[icon_font_s1] ;�᢮������� ������
	;2-� 䠩� ᪨��
	load_image_file fn_skin_2, icon_font_s1,IMAGE_FILE_SKIN2_SIZE
	stdcall [buf2d_create_f_img], buf_skin2,[icon_font_s1] ;ᮧ���� ����
	stdcall mem.Free,[icon_font_s1] ;�᢮������� ������
	;3-� 䠩� ᪨��
	load_image_file fn_skin_3, icon_font_s1,IMAGE_FILE_SKIN3_SIZE
	stdcall [buf2d_create_f_img], buf_skin3,[icon_font_s1] ;ᮧ���� ����
	stdcall mem.Free,[icon_font_s1] ;�᢮������� ������

	;ᨬ���� 1-�� ��⥬���� ����
	load_image_file 'font6x9.bmp', icon_font_s1,IMAGE_FILE_FONT1_SIZE
	stdcall [buf2d_create_f_img], buf_font,[icon_font_s1] ;ᮧ���� ����
	stdcall mem.Free,[icon_font_s1] ;�᢮������� ������
	stdcall [buf2d_conv_24_to_8], buf_font,1 ;������ ���� �஧�筮�� 8 ���
	stdcall [buf2d_convert_text_matrix], buf_font


	copy_path fn_obj_opt,sys_path,fp_obj_opt,0
	;load options file
	mov [run_file_70.Position], 0
	mov [run_file_70.Count], sizeof.ObjOpt*MAX_OBJ_TYPES+MAX_OBJ_CAPTIONS
	mov [run_file_70.Buffer], obj_opt
	mov [run_file_70.FileName], fp_obj_opt
	mcall 70,run_file_70

	cmp ebx,-1
	mov [err_ini1],1
	je .open_end ;jmp if not open file
		mov [err_ini1],0

		mov eax,obj_opt ;������塞 ��ꥪ��
		@@:
			mov ebx,dword[eax]
			cmp ebx,0
			je @f
			;xor ecx,ecx ;� ecx �㤥� ������ ������
			mov cx,word[eax+obj_opt.img-obj_opt]
			cmp cx,0
			jge .zero
				xor cx,cx ;��-�� �� ���稫� � ����⥫�� �����ᮬ
			.zero:
			shl ecx,16
			stdcall dword[tl_node_add], tree1,ecx,eax ;������塞 �������� ��ꥪ�
			stdcall dword[tl_cur_next], tree1 ;��७�ᨬ ����� ����, ��-�� �� �������� ���冷�
			add eax,sizeof.ObjOpt ;���室 �� ᫥���騩 ��ꥪ�
			jmp @b
		@@:
		stdcall dword[tl_cur_beg], tree1 ;��७�ᨬ ����� �����

	.open_end:

	stdcall [OpenDialog_Init],OpenDialog_data ;�����⮢�� �������
	stdcall [ted_init], tedit0
	copy_path fn_syntax,sys_path,file_name,0

	; *** init syntax file ***
	; �஢��塞 ࠧ��� 䠩�� ᨭ⠪��
	mov [run_file_70.Function], 5
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov dword[run_file_70.Count], 0
	mov dword[run_file_70.Buffer], open_b
	mov byte[run_file_70+20], 0
	mov dword[run_file_70.FileName], file_name
	mcall 70,run_file_70
	cmp eax,0
	jne @f

	mov edi,tedit0
	mov ecx,dword[open_b+32] ;+32 qword: ࠧ��� 䠩�� � �����
	mov ted_syntax_file_size,ecx

	stdcall mem.Alloc,ecx ;�뤥�塞 ������ ��� 䠩�� ᨭ⠪��
	mov ted_syntax_file,eax

	;�஡㥬 ������ 䠩� ᨭ⠪��
	call open_unpac_synt_file
	jmp .end_0
	@@:
		notify_window_run txt_not_syntax_file
	.end_0:

	;get cmd line
	cmp [buf_cmd_lin],0
	je @f ;if file names exist
		mov esi,buf_cmd_lin
		call strlen ;eax=strlen
		mov edi,[edit1.text]
		mov [edit1.size],eax
		mov ecx,eax
		rep movsb
		call but_open_proj
	@@:



align 4
red_win:
	call draw_window

align 4
still:
	mcall 10

	cmp al,1
	jne @f
		call draw_window
	@@:
	cmp al,2
	jz key
	cmp al,3
	jz button
	cmp al,6
	jne @f 
		call mouse
	@@:

	jmp still

align 4
draw_window:
pushad
	mcall 12,1

	xor eax,eax
	mov ebx,20*65536+670
	mov ecx,20*65536+370
	mov edx,[sc.work]
	or  edx,0x33000000
	mov edi,hed
	int 0x40

	mov eax,8 ;button 'Open Project'
	mov esi,0x80ff
	mov ebx,230*65536+18
	mov ecx,5*65536+18
	mov edx,5
	int 0x40
	stdcall draw_icon, 22,231,6 ;22 - open

	;button 'Save Project'
	mov ebx,250*65536+18
	mov ecx,5*65536+18
	mov edx,6
	int 0x40
	stdcall draw_icon, 17,251,6 ;17 - save

	;button 'Show Constructor'
	mov ebx,310*65536+18
	mov ecx,5*65536+18
	mov edx,11
	int 0x40
	stdcall draw_icon, 12,311,6 ;12 - window

	;button 'Show Code'
	mov ebx,330*65536+18
	mov edx,12
	int 0x40
	stdcall draw_icon, 11,331,6 ;11 - text

	;button 'Update: Code, Constructor'
	mov ebx,350*65536+18
	mov edx,13
	int 0x40
	stdcall draw_icon, 32,351,6 ;32 - update

	;button 'Save Code'
	mov ebx,370*65536+18
	mov edx,14
	int 0x40
	stdcall draw_icon, 17,371,6 ;17 - save

	;button ']P'
	mov ebx,390*65536+18
	mov edx,15
	int 0x40
	stdcall draw_icon, 18,391,6 ;18 - ���� ���� �����

	;button 'Show color text'
	mov ebx,410*65536+18
	mov edx,16
	int 0x40
	stdcall draw_icon, 19,411,6

	;button 'Add Object'
	mov ebx,125*65536+18
	mov ecx,30*65536+18
	mov edx,31
	int 0x40
	stdcall draw_icon, 14,126,31 ;14 - add object

	;button 'Move Up'
	mov ebx,155*65536+18
	mov edx,21
	int 0x40
	stdcall draw_icon, 23,156,31 ;23 - move up

	;button 'Move Down'
	mov ebx,175*65536+18
	mov edx,22
	int 0x40
	stdcall draw_icon, 24,176,31 ;24 - move down

	;button 'Copy'
	mov ebx,195*65536+18
	mov edx,23
	int 0x40
	stdcall draw_icon, 30,196,31 ;30 - copy

	;button 'Paste'
	mov ebx,215*65536+18
	mov edx,24
	int 0x40
	stdcall draw_icon, 31,216,31 ;31 - paste

	;button 'Property'
	mov ebx,235*65536+18
	mov edx,25
	int 0x40
	stdcall draw_icon, 7,236,31 ;7 - property

	;button 'Undo'
	mov ebx,255*65536+18
	mov edx,26
	int 0x40
	stdcall draw_icon, 33,256,31 ;33 - undo

	;button 'Redo'
	mov ebx,275*65536+18
	mov edx,27
	int 0x40
	stdcall draw_icon, 34,276,31 ;34 - redo

; 10 30 50 70 90

	cmp [err_opn],1
	jne @f
		mcall 4,10*65536+35,0x80ff0000,txtErrOpen
	@@:

	stdcall [edit_box_draw], edit1
	stdcall [edit_box_draw], edit_sav

	mov dword[w_scr_t1.all_redraw],1
	;stdcall [scrollbar_ver_draw], w_scr_t1
	stdcall [tl_draw], tree1
	mov dword[w_scr_t2.all_redraw],1
	;stdcall [scrollbar_ver_draw], w_scr_t2
	stdcall [tl_draw], tree2

	cmp byte[show_mode],0 ;�᫮��� �������� ���� ���������
	jne @f
		stdcall [buf2d_draw], buf_fon
	@@:
	cmp byte[show_mode],1 ;�᫮��� �������� ⥪�⮢��� ����
	jne @f
		stdcall [ted_draw], tedit0
	@@:
	mcall 12,2
popad
	ret

align 4
mouse:
	stdcall [edit_box_mouse], edit1
	stdcall [edit_box_mouse], edit_sav
	stdcall [tl_mouse], tree1
	stdcall [tl_mouse], tree2
	cmp byte[show_mode],1 ;�᫮��� �������� ⥪�⮢��� ����
	jne @f
		stdcall [ted_mouse], tedit0
	@@:
	ret


align 4
key:
	mcall 2
	stdcall [edit_box_key], edit1
	stdcall [edit_box_key], edit_sav
	stdcall [tl_key], tree1
	stdcall [tl_key], tree2

	jmp still

align 4
button:
	mcall 17
	cmp ah,5
	jne @f
		call but_open_proj
		jmp still
	@@:
	cmp ah,6
	jne @f
		call but_save_proj
		jmp still
	@@:
	;cmp ah,10
	;jne @f
		;call but_element_change
	;@@:
	cmp ah,11
	jne @f
		call but_show_constructor
		jmp still
	@@:
	cmp ah,12
	jne @f
		call but_show_code
		jmp still
	@@:
	cmp ah,13
	jne @f
		call but_update
		jmp still
	@@:
	cmp ah,14
	jne @f
		call but_save_asm
		jmp still
	@@:
	cmp ah,15
	jne @f
		call but_show_invis
		jmp still
	@@:
	cmp ah,16
	jne @f
		call but_show_syntax
		jmp still
	@@:
	cmp ah,21
	jne @f
		call but_obj_move_up
		jmp still
	@@:
	cmp ah,22
	jne @f
		call but_obj_move_down
		jmp still
	@@:
	cmp ah,23
	jne @f
		call but_obj_copy
		jmp still
	@@:
	cmp ah,24
	jne @f
		call but_obj_paste
		jmp still
	@@:
	cmp ah,25
	jne @f
		call on_file_object_select
		jmp still
	@@:
	cmp ah,26
	jne @f
		stdcall [tl_info_undo], tree2
		stdcall [tl_draw], tree2
		jmp still
	@@:
	cmp ah,27
	jne @f
		stdcall [tl_info_redo], tree2
		stdcall [tl_draw], tree2
		jmp still
	@@:
	cmp ah,31
	jne @f
		call on_add_object
		jmp still
	@@:
	cmp ah,1
	jne still
.exit:
	stdcall mem.Free,[icon_tl_sys]
	mov dword[tree1.data_img],0
	mov dword[tree2.data_img],0
	mov dword[tree1.data_img_sys],0
	mov dword[tree2.data_img_sys],0
	stdcall dword[tl_data_clear], tree1
	stdcall dword[tl_data_clear], tree2
	stdcall [buf2d_delete],buf_fon ;㤠�塞 ����
	stdcall [buf2d_delete],buf_font ;㤠�塞 ����  
	stdcall [buf2d_delete],buf_skin1
	stdcall [buf2d_delete],buf_skin2
	stdcall [buf2d_delete],buf_skin3
	stdcall [ted_delete], tedit0
	cmp dword[unpac_mem],0
	je @f
		stdcall mem.Free,[unpac_mem]
	@@:
	mcall -1

align 4
open_file_data dd 0 ;㪠��⥫� �� ������ ��� ������ 䠩���
open_file_size dd 0 ;ࠧ��� ����⮣� 䠩��

align 4
but_open_proj:
	copy_path open_dialog_name,communication_area_default_path,file_name,0
	pushad
	mov [OpenDialog_data.type],0
	stdcall [OpenDialog_Start],OpenDialog_data
	cmp [OpenDialog_data.status],2
	je .open_end
	;��� �� 㤠筮� ����⨨ �������

	mov [run_file_70.Function], 5
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov dword[run_file_70.Count], 0
	mov dword[run_file_70.Buffer], open_b
	mov byte[run_file_70+20], 0
	mov dword[run_file_70.FileName], openfile_path
	mcall 70,run_file_70

	mov ecx,dword[open_b+32] ;+32 qword: ࠧ��� 䠩�� � �����
	mov [open_file_size],ecx
	stdcall mem.ReAlloc,[open_file_data],ecx
	mov [open_file_data],eax
	
	mov [run_file_70.Function], 0
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov dword[run_file_70.Count], ecx
	m2m dword[run_file_70.Buffer], eax
	mov byte[run_file_70+20], 0
	mov dword[run_file_70.FileName], openfile_path
	mcall 70,run_file_70 ;����㦠�� 䠩�
	cmp ebx,0xffffffff
	mov [err_opn],1
	je .open_end ;if open file
		mov [err_opn],0
		stdcall [edit_box_set_text], edit1,openfile_path

		stdcall dword[tl_info_clear], tree2
		mov eax,[open_file_data] ;������塞 ��ꥪ��
		@@:
			mov ebx,dword[eax]
			cmp ebx,0
			je @f

			call find_obj_in_opt ;edi = pointer to ObjOpt struct

			mov cx,word[edi+obj_opt.img-obj_opt]
			cmp cx,0
			jge .zero
				xor cx,cx ;��-�� �� ���稫� � ����⥫�� �����ᮬ
			.zero:
			shl ecx,16 ;� ecx ������ ������
			mov cl,byte[eax+u_object.lvl-u_object] ;�஢��� ��ꥪ�

			;tl_node_close_open - �� ���室��, �.�. ������� �� 㧫� ����騥 ���୨�
			mov ch,byte[eax+u_object.clo-u_object] ;�������/������

			stdcall dword[tl_node_add], tree2,ecx,eax ;������塞 ��ꥪ�

			stdcall dword[tl_cur_next], tree2 ;��७�ᨬ ����� ����, ��-�� �� �������� ���冷�
			add eax,sizeof.object ;���室 �� ᫥���騩 ��ꥪ�
			jmp @b
		@@:
		stdcall dword[tl_cur_beg], tree2 ;��७�ᨬ ����� �����

		mov [foc_obj],0
		call draw_constructor
		call code_gen
	.open_end:
	call draw_window ;����ᮢ�� ���� ���� � �� ��砥, ���� �᫨ 䠩� �� ������
	popad
	ret

;��࠭���� 䠩�� ����� �� ���
align 4
but_save_proj:
	copy_path open_dialog_name,communication_area_default_path,file_name,0
	pushad
	mov [OpenDialog_data.type],1
	stdcall [OpenDialog_Start],OpenDialog_data
	cmp [OpenDialog_data.status],2
	je .end_save_file
	;��� �� 㤠筮� ����⨨ �������

	;��६ ࠧ��� �����, ����室���� ��� ��࠭���� 䠩��
	xor ecx,ecx
	stdcall [tl_node_poi_get_info], tree2,0
	@@:
		cmp eax,0
		je @f
		inc ecx
		stdcall [tl_node_poi_get_next_info], tree2,eax ;���室�� � ᫥��饬� 㧫�
		jmp @b
	@@:
	;movzx eax,word[tree2.info_size]
	imul ecx,sizeof.object ;eax
	add ecx,4 ;��⪠ ���� 䠩��
	mov [open_file_size],ecx
	stdcall mem.ReAlloc,[open_file_data],ecx
	mov [open_file_data],eax

	mov edi,[open_file_data]
	stdcall [tl_node_poi_get_info], tree2,0
	mov edx,eax
	@@:
		cmp edx,0
		je @f
		stdcall [tl_node_poi_get_data], tree2,edx
		mov esi,eax ;����砥� ����� 㧫�

		mov bl,byte[edx+2] ;bl - �஢��� ��ꥪ�
		mov byte[esi+u_object.lvl-u_object],bl
		mov bl,byte[edx+3] ;bl - ����⨥/�����⨥ ��ꥪ�
		mov byte[esi+u_object.clo-u_object],bl

		;����塞 ���� ������ ��� ⨯� ��ꥪ�
		mov ebx,[esi+u_object.typid-u_object] ;ebx - ⨯ ��ꥪ�
		;��࠭塞 ⨯ ��ꥪ�
		push ebx
			imul ebx,sizeof.TreeList
			add ebx,[tree2.data_nodes] ;ebx - 㪠��⥫� ��ꥪ� 㪠�뢠�騩 ⨯
			stdcall get_obj_npp,ebx
			mov [esi+u_object.typid-u_object],eax
			mov eax,esi
			;�����㥬 ��ꥪ� � ������ ��� ��࠭����
			movzx ecx,word[tree2.info_size]
			cld
			rep movsb
		;����⠭�������� ⨯ ��ꥪ�
		pop dword[eax+u_object.typid-u_object]

		stdcall [tl_node_poi_get_next_info], tree2,edx
		mov edx,eax ;���室�� � ᫥��饬� 㧫�
		jmp @b
	@@:
	mov dword[edi],0 ;��⪠ ���� 䠩��
	add edi,4

	stdcall [edit_box_set_text], edit1,openfile_path
	mov ecx,[open_file_size] ;ecx - ࠧ��� ��࠭塞��� 䠩��       
	mov [run_file_70.Function], 2
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov [run_file_70.Count], ecx
	m2m [run_file_70.Buffer], [open_file_data]
	mov [run_file_70.rezerv], 0
	mov dword[run_file_70.FileName], openfile_path
	mcall 70,run_file_70

	.end_save_file:
	popad
	ret

;���� ����� �� ���浪� �� 㪠��⥫� �� �������� ��ꥪ�
;output:
; eax - ����� ��ꥪ�
align 4
proc get_obj_npp uses ebx ecx, p_obj_str:dword
	mov ecx,2
	mov ebx,[p_obj_str]

	stdcall [tl_node_poi_get_info], tree2,0
	@@:
		cmp eax,0
		je .no_exist
		cmp eax,ebx
		je @f

		inc ecx
		stdcall [tl_node_poi_get_next_info], tree2,eax ;���室�� � ᫥��饬� 㧫�
		jmp @b
	.no_exist: ;����� ���� ��뫪� �� �� �������騩 ��ꥪ�
		xor ecx,ecx ;����塞 㪠��⥫�, ��-�� �� ��࠭��� � 䠩� ����
	@@:
	mov eax,ecx
	ret
endp

;�㭪�� ��� ��࠭���� ᮧ������� asm 䠩��
align 4
but_save_asm:
	push edi
	mov edi, tedit0

	stdcall [ted_save_file],edi,run_file_70,[edit_sav.text]
	cmp ted_err_save,0
	jne @f
		stdcall [mb_create],msgbox_1,thread ;message: ���� �� ��࠭��
	@@:
	pop edi
	ret

;�㭪�� ��� ������/����� ��������� ᨬ�����
align 4
but_show_invis:
	push edi
	mov edi,tedit0

	xor ted_mode_invis,1
	cmp byte[show_mode],1 ;�᫮��� �������� ⥪�⮢��� ����
	jne @f
		stdcall [ted_draw],edi
	@@:
	pop edi
	ret

;
align 4
but_show_syntax:
	push edi
	mov edi,tedit0

	xor ted_mode_color,1
	cmp byte[show_mode],1 ;�᫮��� �������� ⥪�⮢��� ����
	jne @f
		stdcall [ted_draw],edi
	@@:
	pop edi
	ret

align 4
ted_save_err_msg:
	mov byte[msgbox_0.err],al
	stdcall [mb_create],msgbox_0,thread ;message: Can-t save text file!
	ret

;�㭪�� ��뢠���� �� ����⨨ Enter � ���� tree2
;�������� ⥪�⮢� ���� ���祭�ﬨ ��ࠬ��஢ ������ �� ��ꥪ⮢
;�㭪�� ���⭠� � ������ but_element_change
align 4
on_file_object_select:
	cmp byte[prop_wnd_run],0
	jne @f
		mov byte[prop_wnd_run],1
		stdcall [tl_node_get_data], tree2
		mov dword[foc_obj],eax
		cmp eax,0
		je @f
			pushad
			;�� ����⢨� �� ����ன�� ������⮢ �ࠢ����� �믮������� � ���� � ᢮��⢠��
			mcall 51,1,prop_start,prop_thread
			popad
	@@:
	;call draw_window
	ret

;�㭪�� ��뢠���� �� ����⨨ Enter � ���� tree1
;�������� ���� ��ꥪ� � ���� tree2
align 4
on_add_object:
push eax ebx ecx
	stdcall [tl_node_get_data], tree1
	cmp eax,0
	je @f
		xor ecx,ecx
		mov cx,word[eax+obj_opt.img-obj_opt] ;cx - ������ ������� ������ ������塞��� ��ꥪ�

		cmp ecx,count_main_icons ;� ����� ���� ecx ���� 0, ��⮬� ����⥫�� �᫠ ⮦� �஢�������
		jl .end_0
			;�᫨ ������ ���, �� 㬮�砭�� ��६ 0-�
			xor cx,cx
		.end_0:

		shl ecx,16
		stdcall mem_clear, u_object,sizeof.object
		mov ebx,dword[eax]
		mov dword[u_object.id],ebx
		stdcall dword[tl_node_add], tree2,ecx,u_object ;������塞 ��ꥪ�
	@@:
pop ecx ebx eax
	call draw_window
	ret

align 4
but_ctrl_o:
	ret
align 4
but_ctrl_n:
	ret
align 4
but_ctrl_s:
	ret

;����⨥ � �ᯠ����� 䠩�� ���ᢥ⪨ ᨭ⠪��
;input:
; ted_syntax_file - ���� ��� ���뢠����� 䠩�� ᨭ⠪��
; ted_syntax_file_size - ࠧ��� ���뢠����� 䠩�� ᨭ⠪��
;output:
; ebx - �᫮ ���⠭��� ���� �� 䠩��
align 4
open_unpac_synt_file:
push eax edi esi
	mov edi, tedit0
	mov [run_file_70.Function], 0
	mov [run_file_70.Position], 0
	mov [run_file_70.Flags], 0
	mov ecx, ted_syntax_file_size
	mov dword[run_file_70.Count], ecx
	m2m dword[run_file_70.Buffer], ted_syntax_file
	mov byte[run_file_70+20], 0
	mov [run_file_70.FileName], file_name
	mcall 70, run_file_70
	cmp ebx,-1
	jne .end_0
		;�᫨ �������� �訡�� �� ����⨨ 䠩�� ᨭ⠪��
		mov byte[txt_not_syntax_file.err],'0'
		add byte[txt_not_syntax_file.err],al
		notify_window_run txt_not_syntax_file ;Can-t open color options file!
		jmp @f
	.end_0:

		mov eax,ted_syntax_file
		cmp dword[eax],'KPCK'
		jne .end_unpack

		mov ecx,dword[eax+4] ;ecx - ࠧ��� 䠩�� ᨭ⠪�� ��᫥ �ᯠ�����
		cmp dword[unpac_mem],0
		jne .end_1
			;��ࢮ��砫쭮� �뤥����� �६����� ����� ��� �ᯠ����� 䠩��
			stdcall mem.Alloc,ecx
			mov [unpac_mem],eax
			mov [unpac_mem_size],ecx
		.end_1:
		cmp dword[unpac_mem_size],ecx
		jge .end_2
			;�᫨ ��� �ᯠ�������� 䠩�� �� 墠⠥� �६����� �����
			stdcall mem.ReAlloc,[unpac_mem],ecx ;������ �뤥�塞 �६����� ������
			mov [unpac_mem],eax
			mov [unpac_mem_size],ecx
		.end_2:

		;�ᯠ����� 䠩�� �� �६����� ������
		stdcall unpack,ted_syntax_file,[unpac_mem]

		cmp ted_syntax_file_size,ecx
		jge .end_3
			;�᫨ ��� �ᯠ�������� 䠩�� �� 墠⠥� �����
			stdcall mem.ReAlloc,ted_syntax_file,ecx ;������ �뤥�塞 ������
			mov ted_syntax_file,eax
			mov ted_syntax_file_size,ecx
		.end_3:

		;����஢���� �ᯠ��������� 䠩�� �� �६����� ����� � ������ �������
		mov edi,ted_syntax_file
		mov esi,[unpac_mem]
		cld
		rep movsb

		.end_unpack:
		;�ਬ������ 䠩�� ���ᢥ⪨
		stdcall [ted_init_syntax_file], tedit0
	@@:
pop esi edi eax
	ret

align 4
txt_not_syntax_file:
	db '�訡�� �� ����⨨ 䠩�� � 梥⮢묨 ����ன����! (��� �訡�� ='
	.err: db '?'
	db ')',0

align 4
buf_fon: ;䮭��� ����
	dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 310 ;+4 left
	dw 50 ;+6 top
	dd 340 ;+8 w
	dd 280 ;+12 h
	dd 0xffffff ;+16 color
	db 24 ;+20 bit in pixel

align 4
buf_font: ;���� ������ � ���⮬
	dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 25 ;+4 left
	dw 25 ;+6 top
	dd 96 ;+8 w
	dd 144 ;+12 h
	dd 0 ;+16 color
	db 24 ;+20 bit in pixel

align 4
buf_skin1:
	dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 0 ;+4 left
	dw 0 ;+6 top
	dd SKIN_W1 ;+8 w
	dd SKIN_H ;+12 h
	dd 0 ;+16 color
	db 24 ;+20 bit in pixel
align 4
buf_skin2:
	dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 0 ;+4 left
	dw 0 ;+6 top
	dd SKIN_W2 ;+8 w
	dd SKIN_H ;+12 h
	dd 0 ;+16 color
	db 24 ;+20 bit in pixel
align 4
buf_skin3:
	dd 0 ;㪠��⥫� �� ���� ����ࠦ����
	dw 0 ;+4 left
	dw 0 ;+6 top
	dd SKIN_W3 ;+8 w
	dd SKIN_H ;+12 h
	dd 0 ;+16 color
	db 24 ;+20 bit in pixel

show_mode db 0 ;०�� ��� ������ ��।�������� ����
txtErrOpen db '�� ������ 䠩�, �஢���� �ࠢ��쭮��� �����',0
txtErrIni1 db '�� ������ 䠩� � ���ﬨ',0
err_opn db 0 ;१. ������ 䠩�� �����
err_ini0 db 0 ;१. ������ 䠩�� � ��������
err_ini1 db 0 ;१. ������ 䠩�� � ���ﬨ
unpac_mem dd 0
unpac_mem_size dd 0

edit1 edit_box 210, 10, 5, 0xffffff, 0xff80, 0xff, 0xff0000, 0x4080, 300, ed_text1, mouse_dd, 0, 7, 7

edit2 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text2, mouse_dd, 0
edit3 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text3, mouse_dd, 0
edit4 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text4, mouse_dd, 0
edit5 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text5, mouse_dd, 0
edit6 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text6, mouse_dd, 0
edit7 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text7, mouse_dd, 0
edit8 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text8, mouse_dd, 0
edit9 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text9, mouse_dd, 0
edit10 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text10, mouse_dd, 0
edit11 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text11, mouse_dd, 0
edit12 edit_box 115, 32, 20, 0xffffff, 0x80ff, 0xff, 0x808080, 0, MAX_LEN_OBJ_TXT, ed_text12, mouse_dd, 0
prop_wnd_edits_end: ;����� ⥪�⮢�� �����, �⢥���� �� ᢮��⢠

edit_sav edit_box 210, 310, 30, 0xffffff, 0xff80, 0xff, 0xff0000, 0x4080, 300, ed_text_sav, mouse_dd, 0


ed_text1 db '/hd0/1/',0
	rb 295
ed_text2 rb MAX_LEN_OBJ_TXT+2
ed_text3 rb MAX_LEN_OBJ_TXT+2
ed_text4 rb MAX_LEN_OBJ_TXT+2
ed_text5 rb MAX_LEN_OBJ_TXT+2
ed_text6 rb MAX_LEN_OBJ_TXT+2
ed_text7 rb MAX_LEN_OBJ_TXT+2
ed_text8 rb MAX_LEN_OBJ_TXT+2
ed_text9 rb MAX_LEN_OBJ_TXT+2
ed_text10 rb MAX_LEN_OBJ_TXT+2
ed_text11 rb MAX_LEN_OBJ_TXT+2
ed_text12 rb MAX_LEN_OBJ_TXT+2
ed_text_sav rb 302

txt_null db 'null',0
mouse_dd dd ?

el_focus dd tree1
;��ॢ� � ᯨ᪮� ��������� ⨯�� ��ꥪ⮢
tree1 tree_list sizeof.ObjOpt,20+2, tl_key_no_edit+tl_draw_par_line+tl_list_box_mode,\
	16,16, 0xffffff,0xb0d0ff,0xd000ff, 5,50,125,280, 0,obj_opt.info-obj_opt,0, el_focus,\
	w_scr_t1,on_add_object
;��ॢ� � ��ꥪ⠬� � ���짮��⥫�᪮� 䠩��
tree2 tree_list sizeof.object,MAX_CED_OBJECTS+2, tl_draw_par_line,\
	16,16, 0xffffff,0xb0d0ff,0xd000ff, 155,50,130,280, 13,u_object.txt-u_object,MAX_LEN_OBJ_TXT, el_focus,\
	w_scr_t2,on_file_object_select

msgbox_0:
  db 1,0
  db 'Warning',0
  db 'Error saving file!',13,\
     'Maybe the file name is not entered correctly.',13,\
     '  (error code ='
  .err: db '?'
  db ')',0
  db 'Close',0
  db 0

msgbox_1:
	db 1,0
	db ':)',0
	db 'File was saved',0
	db 'Ok',0
	db 0

struct TexSelect
	x0 dd ?
	y0 dd ?
	x1 dd ?
	y1 dd ?
ends
;------------------------------------------------------------------------------
align 4
tedit0: ;������� ⥪�⮢��� ।����
	.wnd BOX 310,50,325,260 ;+ 0
	.rec BOX 30,13,7,10   ;+16
	.drag_m db 0 ;+32 �뤥����� �� ���
	.drag_k db 0 ;+33 �뤥����� �� ����������
	.sel  TexSelect 0,0,0,0 ;+34 ������� �뤥�����
	.seln TexSelect ;+50 �������⥫쭠� ������� �뤥�����
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
	.syntax_file_size  dd 55*1024 ;+130 ���ᨬ���� ࠧ��� 䠩�� ᨭ⠪��
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
	.buffer      dd text_buffer ;+186 㪠��⥫� �� ���� ����஢����/��⠢��
	.buffer_find dd 0 ;+190 㪠��⥫� �� ���� ��� ���᪠
	.cur_ins     db 1 ;+194 ०�� ࠡ��� ����� (����� ��� ������)
	.mode_color  db 1 ;+195 ०�� �뤥����� ᫮� 梥⮬ (0-�몫. 1-���.)
	.mode_invis  db 0 ;+196 ०�� ������ �����⠥��� ᨬ�����
	.gp_opt      db 0 ;+197 ��樨 �����頥�� �㭪樥� ted_get_pos_by_cursor
	.fun_on_key_ctrl_o dd but_ctrl_o ;+198 㪠��⥫� �� �㭪�� ��뢠���� �� ����⨨ Ctrl+O (����⨥ 䠩��)
	.fun_on_key_ctrl_f dd 0 ;+202 ... Ctrl+F (�맮��/����� ������ ���᪠)
	.fun_on_key_ctrl_n dd but_ctrl_n ;+206 ... Ctrl+N (ᮧ����� ������ ���㬥��)
	.fun_on_key_ctrl_s dd 0 ;+210 ... Ctrl+S
	.buffer_size	   dd BUF_SIZE ;+214 ࠧ��� ���� ����஢����/��⠢��
	.fun_find_err	   dd 0 ;+218 㪠��⥫� �� �㭪�� ��뢠���� �᫨ ���� �����稫�� ��㤠筮
	.fun_init_synt_err dd 0 ;+222 㪠��⥫� �� �㭪�� ��뢠���� �� �訡�筮� ����⨨ 䠩�� ᨭ⠪��
	.fun_draw_panel_buttons dd 0 ;+226 㪠��⥫� �� �㭪�� �ᮢ���� ������ � ��������
	.fun_draw_panel_find	dd 0 ;+230 㪠��⥫� �� �㭪�� �ᮢ���� ������ ���᪠
	.fun_draw_panel_syntax	dd 0 ;+234 㪠��⥫� �� �㭪�� �ᮢ���� ������ ᨭ⠪��
	.fun_save_err		dd ted_save_err_msg ;+238 㪠��⥫� �� �㭪�� ��뢠���� �᫨ ��࠭���� 䠩�� �����稫��� ��㤠筮
	.increase_size dd 1000 ;+242 �᫮ ᨬ����� �� ����� �㤥� 㢥稢����� ������ �� ��墠⪥
	.ptr_free_symb dd ? ;+246 㪠��⥫� �� ᢮������ ������, � ������ ����� ��������� ᨬ��� (�ᯮ������ ����� ������� ��� �᪮७�� ��⠢�� ⥪��)
;------------------------------------------------------------------------------
align 4
scrol_w1:
.x:
.size_x   dw 16 ;+0
.start_x  dw 85 ;+2
.y:
.size_y   dw 100 ; +4
.start_y  dw  15 ; +6
.btn_high dd  15 ; +8
.type	  dd   1 ;+12
.max_area dd 100 ;+16
rb 4+4
.bckg_col dd 0xeeeeee ;+28
.frnt_col dd 0xbbddff ;+32
.line_col dd 0x808080 ;+36
.redraw   dd   0 ;+40
.delta	  dw   0 ;+44
.delta2   dw   0 ;+46
.run_x:
rb 32
.all_redraw dd 0 ;+80
.ar_offset  dd 1 ;+84
;---------------------------------------------------------------------
align 4
scrol_h1:
.x:
.size_x     dw 85 ;+0
.start_x    dw 30 ;+2
.y:
.size_y     dw 16 ;+4
.start_y    dw 100 ;+6
.btn_high   dd 15 ;+8
.type	    dd 1  ;+12
.max_area   dd 100 ;+16
rb 4+4
.bckg_col   dd 0xeeeeee ;+28
.frnt_col   dd 0xbbddff ;+32
.line_col   dd 0x808080 ;+36
.redraw     dd 0  ;+40
.delta	    dw 0  ;+44
.delta2     dw 0  ;+46
.run_x:
rb 32
.all_redraw dd 0 ;+80
.ar_offset  dd 1 ;+84



align 4
w_scr_t1:
.size_x     dw 16 ;+0
rb 2+2+2
.btn_high   dd 15 ;+8
.type	    dd 1  ;+12
.max_area   dd 100  ;+16
rb 4+4
.bckg_col   dd 0xeeeeee ;+28
.frnt_col   dd 0xbbddff ;+32
.line_col   dd 0  ;+36
rb 4+2+2
.run_x:
rb 32
.all_redraw dd 0 ;+80
.ar_offset  dd 1 ;+84

align 4
w_scr_t2:
.size_x     dw 16 ;+0
rb 2+2+2
.btn_high   dd 15 ;+8
.type	    dd 1  ;+12
.max_area   dd 100  ;+16
rb 4+4
.bckg_col   dd 0xeeeeee ;+28
.frnt_col   dd 0xbbddff ;+32
.line_col   dd 0  ;+36
rb 4+2+2
.run_x:
rb 32
.all_redraw dd 0 ;+80
.ar_offset  dd 1 ;+84

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
db 'CED',0
db 'ASM',0
.end:
db 0


data_of_code dd 0
sc system_colors

image_data dd 0 ;������ ��� �८�ࠧ������ ���⨭�� �㭪�ﬨ libimg

text_buffer db BUF_SIZE dup(0)
fn_obj_opt db 'ob_o.opt',0
obj_opt ObjOpt
	rb sizeof.ObjOpt*(MAX_OBJ_TYPES-1)+MAX_OBJ_CAPTIONS
	db 0 ;eof options

cur_x dd 0
cur_y dd 0
foc_obj dd 0 ;��ꥪ� � 䮪��
obj_count_txt_props dd 0 ;������⢮ �ᯮ��㥬�� ⥪�⮢�� ᢮���
obj_m_win dd 0 ;������� �������� ����

	system_dir0 db '/sys/lib/'
	lib0_name db 'box_lib.obj',0

	system_dir1 db '/sys/lib/'
	lib1_name db 'proc_lib.obj',0

	system_dir2 db '/sys/lib/'
	lib2_name db 'buf2d.obj',0

	system_dir3 db '/sys/lib/'
	lib3_name db 'libimg.obj',0

	system_dir4 db '/sys/lib/'
	lib4_name db 'msgbox.obj',0

align 4
import_buf2d_lib:
	dd sz_lib_init
	buf2d_create dd sz_buf2d_create
	buf2d_create_f_img dd sz_buf2d_create_f_img
	buf2d_clear dd sz_buf2d_clear
	buf2d_draw dd sz_buf2d_draw
	buf2d_delete dd sz_buf2d_delete
	buf2d_line dd sz_buf2d_line
	buf2d_rect_by_size dd sz_buf2d_rect_by_size
	buf2d_filled_rect_by_size dd sz_buf2d_filled_rect_by_size
	;buf2d_circle dd sz_buf2d_circle
	buf2d_img_hdiv2 dd sz_buf2d_img_hdiv2
	buf2d_img_wdiv2 dd sz_buf2d_img_wdiv2
	buf2d_conv_24_to_8 dd sz_buf2d_conv_24_to_8
	buf2d_conv_24_to_32 dd sz_buf2d_conv_24_to_32
	buf2d_bit_blt dd sz_buf2d_bit_blt
	buf2d_bit_blt_transp dd sz_buf2d_bit_blt_transp
	buf2d_bit_blt_alpha dd sz_buf2d_bit_blt_alpha
	;buf2d_curve_bezier dd sz_buf2d_curve_bezier
	buf2d_convert_text_matrix dd sz_buf2d_convert_text_matrix
	buf2d_draw_text dd sz_buf2d_draw_text
	;buf2d_crop_color dd sz_buf2d_crop_color
	buf2d_offset_h dd sz_buf2d_offset_h	
dd 0,0
	sz_lib_init db 'lib_init',0
	sz_buf2d_create db 'buf2d_create',0
	sz_buf2d_create_f_img db 'buf2d_create_f_img',0
	sz_buf2d_clear db 'buf2d_clear',0
	sz_buf2d_draw db 'buf2d_draw',0
	sz_buf2d_delete db 'buf2d_delete',0
	sz_buf2d_line db 'buf2d_line',0
	sz_buf2d_rect_by_size db 'buf2d_rect_by_size',0 ;�ᮢ���� ��אַ㣮�쭨��, 2-� ���न��� ������ �� ࠧ����
	sz_buf2d_filled_rect_by_size db 'buf2d_filled_rect_by_size',0
	;sz_buf2d_circle db 'buf2d_circle',0 ;�ᮢ���� ���㦭���
	sz_buf2d_img_hdiv2 db 'buf2d_img_hdiv2',0
	sz_buf2d_img_wdiv2 db 'buf2d_img_wdiv2',0
	sz_buf2d_conv_24_to_8 db 'buf2d_conv_24_to_8',0
	sz_buf2d_conv_24_to_32 db 'buf2d_conv_24_to_32',0
	sz_buf2d_bit_blt db 'buf2d_bit_blt',0
	sz_buf2d_bit_blt_transp db 'buf2d_bit_blt_transp',0
	sz_buf2d_bit_blt_alpha db 'buf2d_bit_blt_alpha',0
	;sz_buf2d_curve_bezier db 'buf2d_curve_bezier',0
	sz_buf2d_convert_text_matrix db 'buf2d_convert_text_matrix',0
	sz_buf2d_draw_text db 'buf2d_draw_text',0
	;sz_buf2d_crop_color db 'buf2d_crop_color',0
	sz_buf2d_offset_h db 'buf2d_offset_h',0

align 4
import_box_lib:
	dd alib_init2

	edit_box_draw dd aEdit_box_draw
	edit_box_key dd aEdit_box_key
	edit_box_mouse dd aEdit_box_mouse
	edit_box_set_text dd aEdit_box_set_text

	init_checkbox dd aInit_checkbox
	check_box_draw dd aCheck_box_draw
	check_box_mouse dd aCheck_box_mouse

	scrollbar_ver_draw dd aScrollbar_ver_draw
	scrollbar_hor_draw dd aScrollbar_hor_draw

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
	tl_node_move_up dd sz_tl_node_move_up
	tl_node_move_down dd sz_tl_node_move_down
	tl_cur_beg dd sz_tl_cur_beg
	tl_cur_next dd sz_tl_cur_next
	tl_cur_perv dd sz_tl_cur_perv
	tl_node_close_open dd sz_tl_node_close_open
	tl_node_lev_inc dd sz_tl_node_lev_inc
	tl_node_lev_dec dd sz_tl_node_lev_dec
	tl_node_poi_get_info dd sz_tl_node_poi_get_info
	tl_node_poi_get_next_info dd sz_tl_node_poi_get_next_info
	tl_node_poi_get_data dd sz_tl_node_poi_get_data

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
	;version_text_edit dd sz_ted_version

dd 0,0
 
	alib_init2 db 'lib_init',0

	aEdit_box_draw	db 'edit_box_draw',0
	aEdit_box_key	db 'edit_box_key',0
	aEdit_box_mouse db 'edit_box_mouse',0
	aEdit_box_set_text db 'edit_box_set_text',0

	aInit_checkbox db 'init_checkbox2',0
	aCheck_box_draw db 'check_box_draw2',0
	aCheck_box_mouse db 'check_box_mouse2',0

	aScrollbar_ver_draw  db 'scrollbar_v_draw',0
	aScrollbar_hor_draw  db 'scrollbar_h_draw',0
  
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
	sz_tl_node_move_up db 'tl_node_move_up',0
	sz_tl_node_move_down db 'tl_node_move_down',0
	sz_tl_cur_beg db 'tl_cur_beg',0
	sz_tl_cur_next db 'tl_cur_next',0
	sz_tl_cur_perv db 'tl_cur_perv',0
	sz_tl_node_close_open db 'tl_node_close_open',0
	sz_tl_node_lev_inc db 'tl_node_lev_inc',0
	sz_tl_node_lev_dec db 'tl_node_lev_dec',0
	sz_tl_node_poi_get_info db 'tl_node_poi_get_info',0
	sz_tl_node_poi_get_next_info db 'tl_node_poi_get_next_info',0
	sz_tl_node_poi_get_data db 'tl_node_poi_get_data',0

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
	sz_ted_but_find			db 'ted_but_find',0
	sz_ted_text_colored		db 'ted_text_colored',0
	;sz_ted_version db 'version_text_edit',0

align 4
import_proc_lib:
	OpenDialog_Init dd aOpenDialog_Init
	OpenDialog_Start dd aOpenDialog_Start
dd 0,0
	aOpenDialog_Init db 'OpenDialog_init',0
	aOpenDialog_Start db 'OpenDialog_start',0

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
import_msgbox_lib:
	mb_create dd amb_create
	mb_reinit dd amb_reinit
	mb_setfunctions dd amb_setfunctions
dd 0,0
	amb_create db 'mb_create',0
	amb_reinit db 'mb_reinit',0
	amb_setfunctions db 'mb_setfunctions',0

;library structures
l_libs_start:
	lib0 l_libs lib0_name, library_path, system_dir0, import_box_lib
	lib1 l_libs lib1_name, library_path, system_dir1, import_proc_lib
	lib2 l_libs lib2_name, library_path, system_dir2, import_buf2d_lib
	lib3 l_libs lib3_name, library_path, system_dir3, import_libimg
	lib4 l_libs lib4_name, library_path, system_dir4, import_msgbox_lib
load_lib_end:


align 16
run_file_70 FileInfoBlock
open_b rb 560

IncludeIGlobals
i_end:
IncludeUGlobals
	procinfo process_information
	buf_cmd_lin rb 1024
	file_name rb 1024 ;icon file path
	fp_obj_opt rb 1024 ;obj options file patch
	rb 1024
	prop_thread:
	rb 1024
	thread: ;������ ���୨� �⥪ ��� ���� ᮮ�饭��
	rb 1024
stacktop: ;������ �⥪ �᭮���� �ணࠬ��
	sys_path rb 1024
	library_path rb 1024
	plugin_path rb 4096
	openfile_path rb 4096
	filename_area rb 256
mem:
