macro wo txt,f1,p1,p2,p3{
@@: db txt
rb @b+40-$
dd f1+0
db p1
dw p2+0
db p3
}
text:
wo<'!'>,,0,,1
wo<'!='>,,0,,1
wo<'"'>,,4,34,3
wo<'&&'>,,0,,1
wo<'',39,''>,,4,39,3
wo<'('>,,0,,1
wo<')'>,,0,,1
wo<'+'>,,0,,1
wo<','>,,0,,1
wo<'.286'>,,3,,1
wo<'.386'>,,3,,1
wo<'.386p'>,,3,,1
wo<'.486'>,,3,,1
wo<'.486p'>,,3,,1
wo<'.586'>,,3,,1
wo<'.586p'>,,3,,1
wo<'.bottom'>,,2,,9
wo<'.break'>,,3,,6
wo<'.code'>,f1.19-f1,3,,1
wo<'.const'>,f1.20-f1,3,,1
wo<'.continue'>,,3,,6
wo<'.data'>,f1.22-f1,3,,1
wo<'.data?'>,f1.23-f1,3,,1
wo<'.else'>,,3,,6
wo<'.elseif'>,,3,,6
wo<'.endif'>,f1.26-f1,3,,6
wo<'.endw'>,,3,,6
wo<'.height'>,,2,,9
wo<'.if'>,,3,,6
wo<'.left'>,,2,,9
wo<'.model'>,,3,,1
wo<'.right'>,,2,,9
wo<'.top'>,,2,,9
wo<'.while'>,,3,,6
wo<'.width'>,,2,,9
wo<'0'>,,24,,3
wo<'0b'>,,10,,3
wo<'0h'>,,10,,3
wo<'1'>,,24,,3
wo<'1b'>,,10,,3
wo<'1h'>,,10,,3
wo<'2'>,,24,,3
wo<'2h'>,,10,,3
wo<'3'>,,24,,3
wo<'3h'>,,10,,3
wo<'4'>,,24,,3
wo<'4h'>,,10,,3
wo<'5'>,,24,,3
wo<'5h'>,,10,,3
wo<'6'>,,24,,3
wo<'6h'>,,10,,3
wo<'7'>,,24,,3
wo<'7h'>,,10,,3
wo<'8'>,,24,,3
wo<'8h'>,,10,,3
wo<'9'>,,24,,3
wo<'9h'>,,10,,3
wo<':'>,,0,,1
wo<';'>,f1.57-f1,4,13,4
wo<'<'>,,0,,1
wo<'<='>,,0,,1
wo<'=='>,,0,,1
wo<'>'>,,0,,1
wo<'>='>,,0,,1
wo<'?'>,,0,,1
wo<'@@'>,f1.64-f1,3,,6
wo<'@b'>,f1.65-f1,3,,6
wo<'@f'>,f1.66-f1,3,,6
wo<'@r'>,f1.67-f1,3,,6
wo<'SF_APM'>,f1.68-f1,3,,5
wo<'SF_BACKGROUND_GET'>,,3,,5
wo<'SF_BACKGROUND_SET'>,,3,,5
wo<'SF_BLITTER'>,,3,,5
wo<'SF_BOARD'>,f1.72-f1,3,,5
wo<'SF_CD'>,,3,,5
wo<'SF_CHANGE_WINDOW'>,f1.74-f1,3,,5
wo<'SF_CHECK_EVENT'>,f1.75-f1,3,,5
wo<'SF_CLIPBOARD'>,,3,,5
wo<'SF_CREATE_THREAD'>,f1.77-f1,3,,5
wo<'SF_CREATE_WINDOW'>,f1.78-f1,3,,5
wo<'SF_CURRENT_FOLDER'>,,3,,5
wo<'SF_DEBUG'>,,3,,5
wo<'SF_DEFINE_BUTTON'>,f1.81-f1,3,,5
wo<'SF_DRAW_LINE'>,f1.82-f1,3,,5
wo<'SF_DRAW_NUMBER'>,f1.83-f1,3,,5
wo<'SF_DRAW_RECT'>,f1.84-f1,3,,5
wo<'SF_DRAW_TEXT'>,f1.85-f1,3,,5
wo<'SF_FILE'>,,3,,5
wo<'SF_GET_BUTTON'>,f1.87-f1,3,,5
wo<'SF_GET_GRAPHICAL_PARAMS'>,f1.88-f1,3,,5
wo<'SF_GET_IMAGE'>,f1.89-f1,3,,5
wo<'SF_GET_KEY'>,f1.90-f1,3,,5
wo<'SF_GET_PIXEL'>,f1.91-f1,3,,5
wo<'SF_GET_PIXEL_OWNER'>,f1.92-f1,3,,5
wo<'SF_GET_SCREEN_SIZE'>,f1.93-f1,3,,5
wo<'SF_GET_SYS_DATE'>,f1.94-f1,3,,5
wo<'SF_GET_SYS_TIME'>,f1.95-f1,3,,5
wo<'SF_IPC'>,,3,,5
wo<'SF_KEYBOARD'>,f1.97-f1,3,,5
wo<'SF_MEMORY_RESIZE'>,f1.98-f1,3,,5
wo<'SF_MIDI'>,f1.99-f1,3,,5
wo<'SF_MOUSE_GET'>,f1.100-f1,3,,5
wo<'SF_NETWORK_GET'>,,3,,5
wo<'SF_NETWORK_PROTOCOL'>,f1.102-f1,3,,5
wo<'SF_NETWORK_SOCKET'>,,3,,5
wo<'SF_PCI'>,,3,,5
wo<'SF_PCI_BIOS'>,,3,,5
wo<'SF_PORT_IN_OUT'>,f1.106-f1,3,,5
wo<'SF_PUT_IMAGE'>,f1.107-f1,3,,5
wo<'SF_PUT_IMAGE_EXT'>,f1.108-f1,3,,5
wo<'SF_PUT_PIXEL'>,f1.109-f1,3,,5
wo<'SF_RD_TO_FLOPPY'>,f1.110-f1,3,,5
wo<'SF_REDRAW'>,f1.111-f1,3,,5
wo<'SF_SCREEN_PUT_IMAGE'>,f1.112-f1,3,,5
wo<'SF_SEND_MESSAGE'>,f1.113-f1,3,,5
wo<'SF_SET_CAPTION'>,f1.114-f1,3,,5
wo<'SF_SET_EVENTS_MASK'>,f1.115-f1,3,,5
wo<'SF_SET_PORTS'>,f1.116-f1,3,,5
wo<'SF_SET_TIME_DATE'>,f1.117-f1,3,,5
wo<'SF_SET_WINDOW_SHAPE'>,f1.118-f1,3,,5
wo<'SF_SLEEP'>,f1.119-f1,3,,5
wo<'SF_SPEAKER_PLAY'>,f1.120-f1,3,,5
wo<'SF_STYLE_SETTINGS'>,,3,,5
wo<'SF_SYS_MISC'>,,3,,5
wo<'SF_SYSTEM'>,,3,,5
wo<'SF_SYSTEM_GET'>,,3,,5
wo<'SF_SYSTEM_SET'>,,3,,5
wo<'SF_TERMINATE_PROCESS'>,f1.126-f1,3,,5
wo<'SF_THREAD_INFO'>,f1.127-f1,3,,5
wo<'SF_WAIT_EVENT'>,f1.128-f1,3,,5
wo<'SF_WAIT_EVENT_TIMEOUT'>,f1.129-f1,3,,5
wo<'SSF_ACCEPT'>,,3,,5
wo<'SSF_ACCESS_HD_LBA'>,,3,,5
wo<'SSF_ACCESS_PCI'>,,3,,5
wo<'SSF_ADD_SYS_FOLDER'>,f1.133-f1,3,,5
wo<'SSF_APPLY'>,,3,,5
wo<'SSF_ARP_ADD_STATIC_ENTRY'>,,3,,5
wo<'SSF_ARP_CONFLICTS_COUNT'>,,3,,5
wo<'SSF_ARP_DEL_ENTRY'>,,3,,5
wo<'SSF_ARP_GET_ENTRY_COUNT'>,,3,,5
wo<'SSF_ARP_PACKETS_RECEIVED'>,,3,,5
wo<'SSF_ARP_PACKETS_SENT'>,,3,,5
wo<'SSF_ARP_READ_ENTRY'>,,3,,5
wo<'SSF_ARP_SEND_ANNOUNCE'>,,3,,5
wo<'SSF_BEGIN_DRAW'>,,3,,5
wo<'SSF_BIND'>,,3,,5
wo<'SSF_BITS_PER_PIXEL'>,,3,,5
wo<'SSF_BUTTON'>,,3,,5
wo<'SSF_BUTTON_EXT'>,,3,,5
wo<'SSF_BYTES_PER_LINE'>,,3,,5
wo<'SSF_CLOSE'>,,3,,5
wo<'SSF_CONNECT'>,,3,,5
wo<'SSF_CONTROL_DRIVER'>,,3,,5
wo<'SSF_CREATE_FILE'>,,3,,5
wo<'SSF_CREATE_FOLDER'>,,3,,5
wo<'SSF_CURSOR_CENTER'>,,3,,5
wo<'SSF_DEBUG_READ'>,,3,,5
wo<'SSF_DEBUG_WRITE'>,,3,,5
wo<'SSF_DEFINE_BREAKPOINT'>,,3,,5
wo<'SSF_DEL_CURSOR'>,,3,,5
wo<'SSF_DEL_SLOT'>,,3,,5
wo<'SSF_DEL_SYS_HOTKEY'>,,3,,5
wo<'SSF_DELETE'>,,3,,5
wo<'SSF_DETACH'>,,3,,5
wo<'SSF_DEVICE_COUNT'>,,3,,5
wo<'SSF_DEVICE_NAME'>,,3,,5
wo<'SSF_DEVICE_POINER'>,,3,,5
wo<'SSF_DEVICE_TYPE'>,,3,,5
wo<'SSF_EJECT_TRAY'>,,3,,5
wo<'SSF_END_DRAW'>,,3,,5
wo<'SSF_ETHERNET_READ_MAC'>,,3,,5
wo<'SSF_FOCUS_WINDOW'>,,3,,5
wo<'SSF_FOREIGN_WINDOW'>,,3,,5
wo<'SSF_GET_ACTIVE_WINDOW'>,,3,,5
wo<'SSF_GET_ADRR_MODE'>,,3,,5
wo<'SSF_GET_CF'>,f1.174-f1,3,,5
wo<'SSF_GET_COLORS'>,,3,,5
wo<'SSF_GET_CONTROL_KEYS'>,,3,,5
wo<'SSF_GET_CPU_REQUENCY'>,,3,,5
wo<'SSF_GET_FONT_SIZE'>,,3,,5
wo<'SSF_GET_FONT_SMOOTH'>,,3,,5
wo<'SSF_GET_FREE_RAM'>,,3,,5
wo<'SSF_GET_IDLE_COUNT'>,,3,,5
wo<'SSF_GET_INFO'>,,3,,5
wo<'SSF_GET_INPUT_MODE'>,,3,,5
wo<'SSF_GET_LAST_BUS'>,,3,,5
wo<'SSF_GET_OPTIONS'>,,3,,5
wo<'SSF_GET_PAIR'>,,3,,5
wo<'SSF_GET_RAM_INFO'>,,3,,5
wo<'SSF_GET_REGISTERS'>,,3,,5
wo<'SSF_GET_SCREEN_AREA'>,,3,,5
wo<'SSF_GET_SKIN_HEIGHT'>,,3,,5
wo<'SSF_GET_SKIN_MARGINS'>,,3,,5
wo<'SSF_GET_SLOT_COUNT'>,f1.192-f1,3,,5
wo<'SSF_GET_TASK_SWITCH_COUNT'>,,3,,5
wo<'SSF_GET_THREAD_SLOT'>,,3,,5
wo<'SSF_GET_TOTAL_RAM'>,,3,,5
wo<'SSF_GET_VERSION'>,,3,,5
wo<'SSF_HEAP_INIT'>,,3,,5
wo<'SSF_ICMP_ECHO_REPLY'>,,3,,5
wo<'SSF_ICMP_PACKETS_RECEIVED'>,,3,,5
wo<'SSF_ICMP_PACKETS_SENT'>,,3,,5
wo<'SSF_IMAGE_BG'>,,3,,5
wo<'SSF_INFO_DISC_SYS'>,,3,,5
wo<'SSF_INSERT_TRAY'>,,3,,5
wo<'SSF_IP4_PACKETS_RECEIVED'>,,3,,5
wo<'SSF_IP4_PACKETS_SENT'>,,3,,5
wo<'SSF_IP4_READ_DNS'>,,3,,5
wo<'SSF_IP4_READ_GATEWAY'>,,3,,5
wo<'SSF_IP4_READ_IP'>,,3,,5
wo<'SSF_IP4_READ_SUBNET'>,,3,,5
wo<'SSF_IP4_WRITE_DNS'>,,3,,5
wo<'SSF_IP4_WRITE_GATEWAY'>,,3,,5
wo<'SSF_IP4_WRITE_IP'>,,3,,5
wo<'SSF_IP4_WRITE_SUBNET'>,,3,,5
wo<'SSF_KERNEL_VERSION'>,,3,,5
wo<'SSF_KEYBOARD_LAYOUT'>,,3,,5
wo<'SSF_LAST_DRAW'>,,3,,5
wo<'SSF_LINK_STATUS'>,,3,,5
wo<'SSF_LISTEN'>,,3,,5
wo<'SSF_LOAD_CURSOR'>,,3,,5
wo<'SSF_LOAD_DLL'>,,3,,5
wo<'SSF_LOAD_DRIVER'>,,3,,5
wo<'SSF_LOAD_DRIVER_PE'>,,3,,5
wo<'SSF_LOAD_FILE'>,,3,,5
wo<'SSF_LOCK_INPUT'>,,3,,5
wo<'SSF_MAP_BG'>,,3,,5
wo<'SSF_MEM_ALLOC'>,,3,,5
wo<'SSF_MEM_CLOSE'>,,3,,5
wo<'SSF_MEM_FREE'>,,3,,5
wo<'SSF_MEM_FREE_EXT'>,,3,,5
wo<'SSF_MEM_OPEN'>,,3,,5
wo<'SSF_MEM_REALLOC'>,,3,,5
wo<'SSF_MINIMIZE_ALL'>,,3,,5
wo<'SSF_MINIMIZE_WINDOW'>,,3,,5
wo<'SSF_MODE_BG'>,,3,,5
wo<'SSF_MOUSE_SETTINGS'>,,3,,5
wo<'SSF_MPU_MIDI_BASE'>,,3,,5
wo<'SSF_OPEN'>,,3,,5
wo<'SSF_OUTPUT'>,,3,,5
wo<'SSF_PERFORMANCE'>,,3,,5
wo<'SSF_PIXEL_BG'>,,3,,5
wo<'SSF_RD_TO_HDD'>,,3,,5
wo<'SSF_READ_BYTE'>,,3,,5
wo<'SSF_READ_CB'>,,3,,5
wo<'SSF_READ_DWORD'>,,3,,5
wo<'SSF_READ_FILE'>,,3,,5
wo<'SSF_READ_FOLDER'>,,3,,5
wo<'SSF_READ_MEMORY'>,,3,,5
wo<'SSF_READ_MSR'>,,3,,5
wo<'SSF_READ_WORD'>,,3,,5
wo<'SSF_RECEIVE'>,,3,,5
wo<'SSF_REDRAW_BG'>,,3,,5
wo<'SSF_REDRAW_RECT'>,,3,,5
wo<'SSF_RESET'>,,3,,5
wo<'SSF_RESET_DEVICE'>,,3,,5
wo<'SSF_RESUME'>,,3,,5
wo<'SSF_RX_BYTE_COUNT'>,,3,,5
wo<'SSF_RX_PACKET_COUNT'>,,3,,5
wo<'SSF_SCREEN_POSITION'>,,3,,5
wo<'SSF_SCREEN_SIZE'>,,3,,5
wo<'SSF_SCROLL_DATA'>,,3,,5
wo<'SSF_SEND'>,,3,,5
wo<'SSF_SEND_MESSAGE'>,,3,,5
wo<'SSF_SET_AREA'>,,3,,5
wo<'SSF_SET_BUTTON_STYLE'>,,3,,5
wo<'SSF_SET_CF'>,f1.265-f1,3,,5
wo<'SSF_SET_COLORS'>,,3,,5
wo<'SSF_SET_CURSOR'>,,3,,5
wo<'SSF_SET_END'>,,3,,5
wo<'SSF_SET_EXCEPTION_HANDLER'>,,3,,5
wo<'SSF_SET_EXCEPTION_STATE'>,,3,,5
wo<'SSF_SET_FONT_SIZE'>,,3,,5
wo<'SSF_SET_FONT_SMOOTH'>,,3,,5
wo<'SSF_SET_INFO'>,,3,,5
wo<'SSF_SET_INPUT_MODE'>,,3,,5
wo<'SSF_SET_MESSAGE_AREA'>,,3,,5
wo<'SSF_SET_OPTIONS'>,,3,,5
wo<'SSF_SET_REGISTERS'>,,3,,5
wo<'SSF_SET_SCREEN_AREA'>,,3,,5
wo<'SSF_SET_SCREEN_LIMITS'>,,3,,5
wo<'SSF_SET_SKIN'>,,3,,5
wo<'SSF_SET_SYS_HOTKEY'>,,3,,5
wo<'SSF_SHUTDOWN'>,,3,,5
wo<'SSF_SIZE_BG'>,,3,,5
wo<'SSF_SPEAKER'>,,3,,5
wo<'SSF_START_APP'>,,3,,5
wo<'SSF_STOP_DEVICE'>,,3,,5
wo<'SSF_SUSPEND'>,,3,,5
wo<'SSF_SWITCH_TASK'>,,3,,5
wo<'SSF_SYS_LANG'>,,3,,5
wo<'SSF_TCP_PACKETS_RECEIVED'>,,3,,5
wo<'SSF_TCP_PACKETS_SENT'>,,3,,5
wo<'SSF_TERMINATE'>,,3,,5
wo<'SSF_TERMINATE_THREAD'>,,3,,5
wo<'SSF_TERMINATE_THREAD_ID'>,,3,,5
wo<'SSF_TIME_COUNT'>,,3,,5
wo<'SSF_TIME_COUNT_PRO'>,,3,,5
wo<'SSF_TX_BYTE_COUNT'>,,3,,5
wo<'SSF_TX_PACKET_COUNT'>,,3,,5
wo<'SSF_UDP_PACKETS_RECEIVED'>,,3,,5
wo<'SSF_UDP_PACKETS_SENT'>,,3,,5
wo<'SSF_UNFOCUS_WINDOW'>,,3,,5
wo<'SSF_UNLOCK_BUFFER'>,,3,,5
wo<'SSF_UNLOCK_INPUT'>,,3,,5
wo<'SSF_UNMAP_BG'>,,3,,5
wo<'SSF_WAIT_RETRACE'>,,3,,5
wo<'SSF_WAIT_SIGNAL'>,,3,,5
wo<'SSF_WINDOW_BEHAVIOR'>,,3,,5
wo<'SSF_WINDOW_POSITION'>,,3,,5
wo<'SSF_WRITE_BYTE'>,,3,,5
wo<'SSF_WRITE_CB'>,,3,,5
wo<'SSF_WRITE_DWORD'>,,3,,5
wo<'SSF_WRITE_FILE'>,,3,,5
wo<'SSF_WRITE_MEMORY'>,,3,,5
wo<'SSF_WRITE_MSR'>,,3,,5
wo<'SSF_WRITE_WORD'>,,3,,5
wo<'SSSF_ALLOW_RDPMC'>,,3,,5
wo<'SSSF_CACHE_OFF'>,,3,,5
wo<'SSSF_CACHE_ON'>,,3,,5
wo<'SSSF_CACHE_STATUS'>,,3,,5
wo<'SSSF_GET_DOUBLE_CLICK_DELAY'>,,3,,5
wo<'SSSF_GET_SPEED'>,,3,,5
wo<'SSSF_GET_SPEEDUP'>,,3,,5
wo<'SSSF_GET_STATE'>,,3,,5
wo<'SSSF_GET_WB'>,,3,,5
wo<'SSSF_MINIMIZE'>,,3,,5
wo<'SSSF_MINIMIZE_ID'>,,3,,5
wo<'SSSF_RESTORE'>,,3,,5
wo<'SSSF_RESTORE_ID'>,,3,,5
wo<'SSSF_SET_BUTTON'>,,3,,5
wo<'SSSF_SET_DOUBLE_CLICK_DELAY'>,,3,,5
wo<'SSSF_SET_POS'>,,3,,5
wo<'SSSF_SET_SPEED'>,,3,,5
wo<'SSSF_SET_SPEEDUP'>,,3,,5
wo<'SSSF_SET_WB'>,,3,,5
wo<'SSSF_TOGGLE'>,,3,,5
wo<'['>,,0,,1
wo<']'>,,0,,1
wo<'aaa'>,f1.338-f1,3,,1
wo<'aad'>,,3,,1
wo<'aam'>,,3,,1
wo<'aas'>,,3,,1
wo<'adc'>,,3,,1
wo<'add'>,f1.343-f1,3,,1
wo<'addr'>,,3,,1
wo<'af'>,f1.345-f1,3,,2
wo<'ah'>,f1.346-f1,3,,2
wo<'al'>,f1.347-f1,3,,2
wo<'align'>,,3,,1
wo<'and'>,,3,,1
wo<'ax'>,f1.350-f1,3,,2
wo<'bh'>,,3,,2
wo<'bl'>,,3,,2
wo<'bound'>,,3,,1
wo<'bp'>,f1.354-f1,3,,2
wo<'bsf'>,,3,,1
wo<'bsr'>,,3,,1
wo<'bswap'>,,3,,1
wo<'bt'>,f1.358-f1,3,,1
wo<'btc'>,f1.359-f1,3,,1
wo<'btr'>,f1.360-f1,3,,1
wo<'bts'>,f1.361-f1,3,,1
wo<'bx'>,f1.362-f1,3,,2
wo<'byte'>,f1.363-f1,3,,8
wo<'call'>,f1.364-f1,3,,1
wo<'case'>,,3,,6
wo<'casemap'>,,3,,1
wo<'cbw'>,,3,,1
wo<'cdq'>,,3,,1
wo<'cf'>,f1.369-f1,3,,2
wo<'ch'>,,3,,2
wo<'cl'>,f1.371-f1,3,,2
wo<'clc'>,f1.372-f1,3,,1
wo<'cld'>,f1.373-f1,3,,1
wo<'cli'>,f1.374-f1,3,,1
wo<'cmc'>,,3,,1
wo<'cmp'>,f1.376-f1,3,,1
wo<'cmps'>,,3,,1
wo<'cmpsb'>,f1.378-f1,3,,1
wo<'cmpsd'>,f1.379-f1,3,,1
wo<'cmpsq'>,,3,,1
wo<'cmpsw'>,f1.381-f1,3,,1
wo<'cmpxchg'>,,3,,1
wo<'comment *'>,f1.383-f1,5,42,4
wo<'cr0'>,,3,,2
wo<'cr1'>,,3,,2
wo<'cr2'>,,3,,2
wo<'cr3'>,,3,,2
wo<'cr4'>,,3,,2
wo<'cs'>,f1.389-f1,3,,2
wo<'cwd'>,f1.390-f1,3,,1
wo<'cwde'>,,3,,1
wo<'cx'>,f1.392-f1,3,,2
wo<'daa'>,f1.393-f1,3,,1
wo<'das'>,f1.394-f1,3,,1
wo<'db'>,f1.395-f1,3,,8
wo<'dd'>,f1.396-f1,3,,8
wo<'dec'>,f1.397-f1,3,,1
wo<'df'>,f1.398-f1,3,,2
wo<'dh'>,,3,,2
wo<'di'>,,3,,2
wo<'div'>,f1.401-f1,3,,1
wo<'dl'>,,3,,2
wo<'dq'>,f1.403-f1,3,,8
wo<'dqword'>,,3,,8
wo<'dr0'>,f1.405-f1,3,,2
wo<'dr1'>,f1.406-f1,3,,2
wo<'dr2'>,f1.407-f1,3,,2
wo<'dr3'>,f1.408-f1,3,,2
wo<'dr4'>,f1.409-f1,3,,2
wo<'dr5'>,f1.410-f1,3,,2
wo<'dr6'>,f1.411-f1,3,,2
wo<'dr7'>,f1.412-f1,3,,2
wo<'ds'>,f1.413-f1,3,,2
wo<'dt'>,f1.414-f1,3,,8
wo<'dup'>,f1.415-f1,3,,1
wo<'dw'>,f1.416-f1,3,,8
wo<'dword'>,f1.417-f1,3,,8
wo<'dx'>,f1.418-f1,3,,2
wo<'eax'>,f1.419-f1,3,,2
wo<'ebp'>,,3,,2
wo<'ebx'>,f1.421-f1,3,,2
wo<'ecx'>,f1.422-f1,3,,2
wo<'edi'>,f1.423-f1,3,,2
wo<'edx'>,f1.424-f1,3,,2
wo<'eip'>,f1.425-f1,3,,2
wo<'end'>,f1.426-f1,3,,1
wo<'endm'>,f1.427-f1,3,,1
wo<'endp'>,f1.428-f1,3,,5
wo<'ends'>,f1.429-f1,3,,1
wo<'enter'>,,3,,1
wo<'equ'>,,3,,1
wo<'es'>,f1.432-f1,3,,2
wo<'esc'>,f1.433-f1,3,,1
wo<'esi'>,,3,,2
wo<'esp'>,,3,,2
wo<'f2xm1'>,f1.436-f1,3,,1
wo<'fabs'>,f1.437-f1,3,,1
wo<'fadd'>,f1.438-f1,3,,1
wo<'faddp'>,,3,,1
wo<'fbld'>,f1.440-f1,3,,1
wo<'fchs'>,f1.441-f1,3,,1
wo<'fcom'>,f1.442-f1,3,,1
wo<'fcomp'>,f1.443-f1,3,,1
wo<'fcompp'>,f1.444-f1,3,,1
wo<'fcos'>,f1.445-f1,3,,1
wo<'fdecstp'>,f1.446-f1,3,,1
wo<'fdiv'>,f1.447-f1,3,,1
wo<'fdivp'>,,3,,1
wo<'fdivr'>,,3,,1
wo<'fdivrp'>,,3,,1
wo<'ffree'>,f1.451-f1,3,,1
wo<'ficom'>,f1.452-f1,3,,1
wo<'ficomp'>,f1.453-f1,3,,1
wo<'fild'>,f1.454-f1,3,,1
wo<'fimul'>,,3,,1
wo<'fincstp'>,f1.456-f1,3,,1
wo<'finit'>,f1.457-f1,3,,1
wo<'fistp'>,,3,,1
wo<'fisub'>,,3,,1
wo<'fld'>,f1.460-f1,3,,1
wo<'fld1'>,f1.461-f1,3,,1
wo<'fldenvw'>,,3,,1
wo<'fldl2e'>,f1.463-f1,3,,1
wo<'fldl2t'>,f1.464-f1,3,,1
wo<'fldlg2'>,f1.465-f1,3,,1
wo<'fldln2'>,f1.466-f1,3,,1
wo<'fldpi'>,f1.467-f1,3,,1
wo<'fldz'>,f1.468-f1,3,,1
wo<'fmul'>,f1.469-f1,3,,1
wo<'fmulp'>,,3,,1
wo<'fnsavew'>,,3,,1
wo<'fnstenvw'>,,3,,1
wo<'fpatan'>,f1.473-f1,3,,1
wo<'fprem'>,f1.474-f1,3,,1
wo<'fptan'>,f1.475-f1,3,,1
wo<'frndint'>,f1.476-f1,3,,1
wo<'frstorw'>,,3,,1
wo<'fs'>,,3,,2
wo<'fsavew'>,,3,,1
wo<'fscale'>,f1.480-f1,3,,1
wo<'fsin'>,f1.481-f1,3,,1
wo<'fsincos'>,f1.482-f1,3,,1
wo<'fsqrt'>,f1.483-f1,3,,1
wo<'fst'>,f1.484-f1,3,,1
wo<'fstenvw'>,,3,,1
wo<'fstp'>,f1.486-f1,3,,1
wo<'fstsw'>,,3,,1
wo<'fsub'>,f1.488-f1,3,,1
wo<'fsubp'>,,3,,1
wo<'fsubr'>,,3,,1
wo<'fsubrp'>,,3,,1
wo<'ftst'>,f1.492-f1,3,,1
wo<'fword'>,,3,,8
wo<'fxam'>,f1.494-f1,3,,1
wo<'fxch'>,f1.495-f1,3,,1
wo<'fxtract'>,f1.496-f1,3,,1
wo<'fyl2x'>,f1.497-f1,3,,1
wo<'fyl2xp1'>,f1.498-f1,3,,1
wo<'gdtr'>,f1.499-f1,3,,2
wo<'gs'>,,3,,2
wo<'hlt'>,f1.501-f1,3,,1
wo<'idiv'>,f1.502-f1,3,,1
wo<'if'>,f1.503-f1,3,,2
wo<'imul'>,f1.504-f1,3,,1
wo<'in'>,,3,,1
wo<'inc'>,f1.506-f1,3,,1
wo<'include'>,,3,,2
wo<'includelib'>,f1.508-f1,3,,2
wo<'ins'>,,3,,1
wo<'insb'>,,3,,1
wo<'insd'>,,3,,1
wo<'insw'>,,3,,1
wo<'int'>,,3,,1
wo<'into'>,,3,,1
wo<'ip'>,f1.515-f1,3,,2
wo<'iret'>,,3,,1
wo<'iretd'>,,3,,1
wo<'ja'>,f1.518-f1,3,,6
wo<'jae'>,f1.519-f1,3,,6
wo<'jb'>,f1.520-f1,3,,6
wo<'jbe'>,f1.521-f1,3,,6
wo<'jc'>,f1.522-f1,3,,6
wo<'jcc'>,,3,,1
wo<'jcxz'>,f1.524-f1,3,,6
wo<'je'>,f1.525-f1,3,,6
wo<'jecxz'>,f1.526-f1,3,,6
wo<'jg'>,f1.527-f1,3,,6
wo<'jge'>,f1.528-f1,3,,6
wo<'jl'>,f1.529-f1,3,,6
wo<'jle'>,f1.530-f1,3,,6
wo<'jmp'>,f1.531-f1,3,,6
wo<'jna'>,,3,,6
wo<'jnae'>,,3,,6
wo<'jnb'>,,3,,6
wo<'jnbe'>,,3,,6
wo<'jnc'>,,3,,6
wo<'jne'>,,3,,6
wo<'jng'>,,3,,6
wo<'jnge'>,,3,,6
wo<'jnl'>,,3,,6
wo<'jnle'>,,3,,6
wo<'jno'>,,3,,6
wo<'jnp'>,,3,,6
wo<'jns'>,,3,,6
wo<'jnz'>,f1.545-f1,3,,6
wo<'jo'>,f1.546-f1,3,,6
wo<'jp'>,,3,,6
wo<'jpe'>,,3,,6
wo<'jpo'>,f1.549-f1,3,,6
wo<'js'>,f1.550-f1,3,,6
wo<'jz'>,f1.551-f1,3,,6
wo<'lahf'>,,3,,1
wo<'lds'>,,3,,1
wo<'ldtr'>,f1.554-f1,3,,2
wo<'lea'>,,3,,1
wo<'leave'>,,3,,1
wo<'les'>,,3,,1
wo<'lfs'>,,3,,1
wo<'lgdt'>,,3,,1
wo<'lgs'>,,3,,1
wo<'lidt'>,,3,,1
wo<'lldt'>,,3,,1
wo<'local'>,f1.563-f1,3,,1
wo<'lock'>,,3,,1
wo<'lods'>,,3,,1
wo<'lodsb'>,f1.566-f1,3,,1
wo<'lodsd'>,f1.567-f1,3,,1
wo<'lodsq'>,,3,,1
wo<'lodsw'>,f1.569-f1,3,,1
wo<'loop'>,,3,,6
wo<'loope'>,f1.571-f1,3,,6
wo<'loopne'>,f1.572-f1,3,,6
wo<'loopnz'>,f1.573-f1,3,,6
wo<'loopz'>,f1.574-f1,3,,6
wo<'lss'>,,3,,1
wo<'m2m'>,f1.576-f1,3,,5
wo<'macro'>,,3,,1
wo<'mcall'>,f1.578-f1,3,,5
wo<'mm0'>,,3,,2
wo<'mm1'>,,3,,2
wo<'mm2'>,,3,,2
wo<'mm3'>,,3,,2
wo<'mm4'>,,3,,2
wo<'mm5'>,,3,,2
wo<'mm6'>,,3,,2
wo<'mm7'>,,3,,2
wo<'mov'>,f1.587-f1,3,,1
wo<'movs'>,,3,,1
wo<'movsb'>,,3,,1
wo<'movsd'>,,3,,1
wo<'movsw'>,,3,,1
wo<'movsx'>,,3,,1
wo<'movzx'>,,3,,1
wo<'mul'>,,3,,1
wo<'neg'>,,3,,1
wo<'nop'>,f1.596-f1,3,,1
wo<'not'>,,3,,1
wo<'of'>,f1.598-f1,3,,2
wo<'offset'>,,3,,1
wo<'option'>,,3,,1
wo<'or'>,,3,,1
wo<'out'>,,3,,1
wo<'outs'>,,3,,1
wo<'packssdw'>,,3,,1
wo<'packsswb'>,,3,,1
wo<'packuswb'>,,3,,1
wo<'paddb'>,f1.607-f1,3,,1
wo<'paddd'>,f1.608-f1,3,,1
wo<'paddsb'>,f1.609-f1,3,,1
wo<'paddsw'>,f1.610-f1,3,,1
wo<'paddusb'>,f1.611-f1,3,,1
wo<'paddusw'>,f1.612-f1,3,,1
wo<'paddw'>,f1.613-f1,3,,1
wo<'pand'>,f1.614-f1,3,,1
wo<'pandn'>,f1.615-f1,3,,1
wo<'pcmpeqb'>,f1.616-f1,3,,1
wo<'pcmpeqd'>,f1.617-f1,3,,1
wo<'pcmpeqw'>,f1.618-f1,3,,1
wo<'pcmpgtb'>,f1.619-f1,3,,1
wo<'pcmpgtd'>,f1.620-f1,3,,1
wo<'pcmpgtw'>,f1.621-f1,3,,1
wo<'pf'>,f1.622-f1,3,,2
wo<'pmaddwd'>,f1.623-f1,3,,1
wo<'pmulhw'>,f1.624-f1,3,,1
wo<'pmullw'>,f1.625-f1,3,,1
wo<'pop'>,,3,,1
wo<'popa'>,f1.627-f1,3,,1
wo<'popad'>,f1.628-f1,3,,1
wo<'popf'>,,3,,1
wo<'popfd'>,,3,,1
wo<'por'>,f1.631-f1,3,,1
wo<'proc'>,f1.632-f1,3,,5
wo<'pshimd'>,,3,,1
wo<'pshimq'>,,3,,1
wo<'pshimw'>,,3,,1
wo<'pslld'>,,3,,1
wo<'psllq'>,,3,,1
wo<'psllw'>,,3,,1
wo<'psrad'>,,3,,1
wo<'psraw'>,,3,,1
wo<'psrld'>,,3,,1
wo<'psrlq'>,,3,,1
wo<'psrlw'>,,3,,1
wo<'psubb'>,,3,,1
wo<'psubd'>,,3,,1
wo<'psubsb'>,,3,,1
wo<'psubsw'>,,3,,1
wo<'psubusb'>,,3,,1
wo<'psubusw'>,,3,,1
wo<'psubw'>,,3,,1
wo<'ptr'>,,3,,1
wo<'punpckhbw'>,,3,,1
wo<'punpckhdq'>,,3,,1
wo<'punpckhwd'>,,3,,1
wo<'punpcklbw'>,,3,,1
wo<'punpckldq'>,,3,,1
wo<'punpcklwd'>,,3,,1
wo<'push'>,f1.658-f1,3,,1
wo<'pusha'>,f1.659-f1,3,,1
wo<'pushad'>,f1.660-f1,3,,1
wo<'pushf'>,f1.661-f1,3,,1
wo<'pushfd'>,,3,,1
wo<'pword'>,,3,,8
wo<'pxor'>,f1.664-f1,3,,1
wo<'qword'>,f1.665-f1,3,,8
wo<'rcl'>,,3,,1
wo<'rcr'>,,3,,1
wo<'rep'>,,3,,1
wo<'repe'>,,3,,1
wo<'repne'>,,3,,1
wo<'repnz'>,,3,,1
wo<'repz'>,,3,,1
wo<'ret'>,,3,,1
wo<'retf'>,,3,,1
wo<'rol'>,f1.675-f1,3,,1
wo<'ror'>,f1.676-f1,3,,1
wo<'sahf'>,f1.677-f1,3,,1
wo<'sal'>,,3,,1
wo<'sar'>,,3,,1
wo<'sbb'>,,3,,1
wo<'scas'>,,3,,1
wo<'scasb'>,f1.682-f1,3,,1
wo<'scasd'>,f1.683-f1,3,,1
wo<'scasw'>,f1.684-f1,3,,1
wo<'setcc'>,,3,,1
wo<'sf'>,f1.686-f1,3,,2
wo<'sgdt'>,f1.687-f1,3,,1
wo<'shl'>,f1.688-f1,3,,1
wo<'shld'>,f1.689-f1,3,,1
wo<'shr'>,f1.690-f1,3,,1
wo<'si'>,f1.691-f1,3,,2
wo<'sizeof'>,,3,,1
wo<'sp'>,f1.693-f1,3,,2
wo<'ss'>,f1.694-f1,3,,2
wo<'st0'>,,3,,2
wo<'st1'>,,3,,2
wo<'st2'>,,3,,2
wo<'st3'>,,3,,2
wo<'st4'>,,3,,2
wo<'st5'>,,3,,2
wo<'st6'>,,3,,2
wo<'st7'>,,3,,2
wo<'stc'>,,3,,1
wo<'std'>,,3,,1
wo<'stdcall'>,f1.705-f1,3,,5
wo<'sti'>,,3,,1
wo<'stos'>,,3,,1
wo<'stosb'>,f1.708-f1,3,,1
wo<'stosd'>,f1.709-f1,3,,1
wo<'stosw'>,f1.710-f1,3,,1
wo<'struc'>,f1.711-f1,3,,5
wo<'struct'>,,3,,1
wo<'sub'>,f1.713-f1,3,,1
wo<'switch'>,,3,,6
wo<'tbyte'>,,3,,8
wo<'test'>,,3,,1
wo<'tf'>,f1.717-f1,3,,2
wo<'tword'>,f1.718-f1,3,,8
wo<'uses'>,f1.719-f1,3,,1
wo<'word'>,f1.720-f1,3,,8
wo<'xadd'>,,3,,1
wo<'xchg'>,f1.722-f1,3,,1
wo<'xlat'>,,3,,1
wo<'xlatb'>,,3,,1
wo<'xmm0'>,,3,,2
wo<'xmm1'>,,3,,2
wo<'xmm2'>,,3,,2
wo<'xmm3'>,,3,,2
wo<'xmm4'>,,3,,2
wo<'xmm5'>,,3,,2
wo<'xmm6'>,,3,,2
wo<'xmm7'>,,3,,2
wo<'xor'>,f1.733-f1,3,,1
wo<'zf'>,f1.734-f1,3,,2
wo<'||'>,,0,,1
f1: db 0
.19:db 'ᥪ�� ����',0
.20:db 'ᮤ�ন� ������� ����⠭�',0
.22:db '���樠����஢���� �����',0
.23:db '�����樠����஢���� �����',0
.26:db '����� �᫮����� �����',0
.57:db '��������� �������਩',0
.64:db '��������� ��⪠',0
.65:db '������ ��������� ��⪠ (⮦� �� @r)',0
.66:db '������ ��������� ��⪠',0
.67:db '������ ��������� ��⪠ (⮦� �� @b)',0
.68:db 'Advanced Power Management (APM) (���. �㭪�� �� KOSfuncs.inc)',0
.72:db 'ࠡ�� � ��᪮� �⫠��� (���. �㭪�� �� KOSfuncs.inc)',0
.74:db '�������� ���������/ࠧ���� ���� (���. �㭪�� �� KOSfuncs.inc)',0
.75:db '�஢����, ���� �� ᮡ�⨥, ��� �������� (���. �㭪�� �� KOSfuncs.inc)',0
.77:db 'ᮧ���� ��⮪ (���. �㭪�� �� KOSfuncs.inc)',0
.78:db '��।����� � ���ᮢ��� ���� (���. �㭪�� �� KOSfuncs.inc)',0
.81:db '��।�����/㤠���� ������ (���. �㭪�� �� KOSfuncs.inc)',0
.82:db '���ᮢ��� ��१�� (���. �㭪�� �� KOSfuncs.inc)',0
.83:db '�뢥�� �᫮ � ���� (���. �㭪�� �� KOSfuncs.inc)',0
.84:db '���ᮢ��� ��אַ㣮�쭨� � ���� (���. �㭪�� �� KOSfuncs.inc)',0
.85:db '���ᮢ��� ��ப� ⥪�� (���. �㭪�� �� KOSfuncs.inc)',0
.87:db '������� ��� ����⮩ ������ (���. �㭪�� �� KOSfuncs.inc)',0
.88:db '������� ��ࠬ���� ��� ��אַ�� ����㯠 � ��䨪� (���. �㭪�� �� KOSfuncs.inc)',0
.89:db '������ ������� ��࠭� (���. �㭪�� �� KOSfuncs.inc)',0
.90:db '������� ��� ����⮩ ������ (���. �㭪�� �� KOSfuncs.inc)',0
.91:db '������ 梥� �窨 �� ��࠭� (���. �㭪�� �� KOSfuncs.inc)',0
.92:db '㧭��� ���� �ਭ������� �窠 ��࠭� (���. �㭪�� �� KOSfuncs.inc)',0
.93:db '������� ࠧ���� ��࠭� (���. �㭪�� �� KOSfuncs.inc)',0
.94:db '������� ��⥬��� ���� (���. �㭪�� �� KOSfuncs.inc)',0
.95:db '������� ��⥬��� �६� (���. �㭪�� �� KOSfuncs.inc)',0
.97:db 'ࠡ�� � ��������ன (���. �㭪�� �� KOSfuncs.inc)',0
.98:db '�����।����� ������ �ਫ������ (���. �㭪�� �� KOSfuncs.inc)',0
.99:db '����䥩� MIDI (���. �㭪�� �� KOSfuncs.inc)',0
.100:db 'ࠡ�� � ����� (���. �㭪�� �� KOSfuncs.inc)',0
.102:db '�⥢� ��樨 � ����⨪� (���. �㭪�� �� KOSfuncs.inc)',0
.106:db '����/�뢮� � ���� (���. �㭪�� �� KOSfuncs.inc)',0
.107:db '�뢥�� ����ࠦ���� � ���� (���. �㭪�� �� KOSfuncs.inc)',0
.108:db '�뢥�� ����ࠦ���� � �����ன � ���� (���. �㭪�� �� KOSfuncs.inc)',0
.109:db '���⠢��� ��� � ���� (ebx = x-���न��� (�⭮�⥫쭮 ����), ecx = y-���न��� (�⭮�⥫쭮 ����), edx = 0x00RRGGBB - 梥� �窨) (���. �㭪�� �� KOSfuncs.inc)',0
.110:db '��࠭��� ࠬ��� �� ��᪥�� (���. �㭪�� �� KOSfuncs.inc)',0
.111:db '�����/�������� ����ᮢ�� ���� (���. �㭪�� �� KOSfuncs.inc)',0
.112:db '������� ������� �� ᫮� 䮭� (���. �㭪�� �� KOSfuncs.inc)',0
.113:db '��᫠�� ᮮ�饭�� ���� (���. �㭪�� �� KOSfuncs.inc)',0
.114:db '��⠭����� ��������� ���� �ணࠬ�� (���. �㭪�� �� KOSfuncs.inc)',0
.115:db '��⠭����� ���� ��� ��������� ᮡ�⨩ (���. �㭪�� �� KOSfuncs.inc)',0
.116:db '��१�ࢨ஢���/�᢮������ ��㯯� ���⮢ �����/�뢮�� (���. �㭪�� �� KOSfuncs.inc)',0
.117:db '��⠭����� ��⥬��� ����/�६� (���. �㭪�� �� KOSfuncs.inc)',0
.118:db '��⠭���� ��� ���� (���. �㭪�� �� KOSfuncs.inc)',0
.119:db '��㧠 (���. �㭪�� �� KOSfuncs.inc)',0
.120:db '����� �ந��뢠�� ����� �� ���஥���� ᯨ��� (���. �㭪�� �� KOSfuncs.inc)',0
.126:db '�������� �믮������ ��⮪�/����� (���. �㭪�� �� KOSfuncs.inc)',0
.127:db '���ଠ�� � ��⮪� �믮������ (���. �㭪�� �� KOSfuncs.inc)',0
.128:db '������� ᮡ��� (���. �㭪�� �� KOSfuncs.inc)',0
.129:db '������� ᮡ��� � ⠩���⮬ (���. �㭪�� �� KOSfuncs.inc)',0
.133:db '��⠭����� ���. ��⥬��� ��४��� ��� �� (����㭪�� ��� ���. �㭪樨 SF_CURRENT_FOLDER)',0
.174:db '������� ⥪���� ����� ��� ��⮪� (����㭪�� ��� ���. �㭪樨 SF_CURRENT_FOLDER)',0
.192:db '㧭��� ������⢮ ᫮⮢ � ���� ������ (����㭪�� ��� ���. �㭪樨 SF_CLIPBOARD)',0
.265:db '��⠭����� ⥪���� ����� ��� ��⮪� (����㭪�� ��� ���. �㭪樨 SF_CURRENT_FOLDER)',0
.338:db '�ᯮ������ ��᫥ ᫮����� ������� ࠧ�鸞 �ᯠ�������� BCD-�ᥫ (Ascii Adjust after Addition - ASCII-���४�� ��᫥ ᫮�����)',0
.343:db '�ਡ����� � ��ࢮ�� ���࠭�� ��ன',0
.345:db '䫠���� ॣ���� �������⥫�� �ਧ��� ��७��',0
.346:db 'ॣ���� ��饣� �����祭�� 1 ����',0
.347:db 'ॣ���� ��饣� �����祭�� 1 ����',0
.350:db 'ॣ���� ��饣� �����祭�� 2 ����',0
.354:db 'ॣ���� 㪠��⥫�',0
.358:db '��।����, ��⠭����� �� � �������� ᫮�� ��।������ ���. ���祭�� ��࠭��� ��� ����頥���� � cf',0
.359:db '���祭�� ��࠭��� ��� ����頥���� � cf, ��������� ���祭�� ���',0
.360:db '���祭�� ��࠭��� ��� ����頥���� � cf, � ��� �����뢠����� 0',0
.361:db '���祭�� ��࠭��� ��� ����頥���� � cf, � ��� �����뢠����� 1',0
.362:db 'ॣ���� ��饣� �����祭�� 2 ����',0
.363:db '1 ����',0
.364:db '�맮� ����ணࠬ��. ��। �맮��� ����頥� � ���� ���� �।��饩 �������',0
.369:db '䫠���� ॣ���� ��७��',0
.371:db 'ॣ���� ��饣� �����祭�� 1 ����',0
.372:db '��� 䫠�� ��७�� cf=0',0
.373:db '��� �ਧ���� ���ࠢ����� df=0',0
.374:db '��� �ਧ���� ࠧ�襭�� ���뢠��� if=0',0
.376:db '�ࠢ����� ���࠭��� � �� १���⠬ �ࠢ����� ��⠭�������� 䫠�� (af, cf, of, pf, sf � zf)',0
.378:db '�ࠢ����� 1-�� ���⮢�� ��ப. ��ப� �� esi �ࠢ�������� � ��ப�� edi.',0
.379:db '�ࠢ����� 4-� ���⮢�� ��ப. ��ப� �� esi �ࠢ�������� � ��ப�� edi.',0
.381:db '�ࠢ����� 2-� ���⮢�� ��ப. ��ப� �� esi �ࠢ�������� � ��ப�� edi.',0
.383:db '���������� �������਩',0
.389:db 'ᥣ����� ॣ���� - ᥣ���� ����',0
.390:db '�८�ࠧ������ ᫮�� � ������� ᫮��. ����� �� ��������.',0
.392:db 'ॣ���� ��饣� �����祭�� 2 ����',0
.393:db '�����筠� ���४�� ��� ᫮�����. ������� ���������� �� 䫠�� af. cf, pf, sf � zf (䫠� of ����।����).',0
.394:db '�����筠� ���४�� ��� ���⠭��. ������� ���������� �� 䫠�� af, cf, pf, sf � zf.',0
.395:db '1 ����',0
.396:db '4 ���� - 2 ᫮��',0
.397:db '������ �� ���࠭�� �������. ������� ���������� �� 䫠�� af, of, pf, sf � zf.',0
.398:db '䫠���� ॣ���� ���ࠢ�����',0
.401:db '�������. ������� ���������� �� 䫠�� af, cf, of, pf sf � zf (�� �� ��।�����).',0
.403:db '8 ���� - 4 ᫮��',0
.405:db '�⫠���� ॣ���� 0-�',0
.406:db '�⫠���� ॣ���� 1-�',0
.407:db '�⫠���� ॣ���� 2-�',0
.408:db '�⫠���� ॣ���� 3-�',0
.409:db '�⫠���� ॣ���� 4-�',0
.410:db '�⫠���� ॣ���� 5-�',0
.411:db '�⫠���� ॣ���� 6-�',0
.412:db '�⫠���� ॣ���� 7-�',0
.413:db 'ᥣ����� ॣ���� - ᥣ���� ������',0
.414:db '10 ����',0
.415:db '�㡫�஢���� ��砫쭮�� ���祭��',0
.416:db '2 ���� - 1 ᫮��',0
.417:db '4 ����',0
.418:db 'ॣ���� ��饣� �����祭�� 2 ����',0
.419:db 'ॣ���� ��饣� �����祭�� 4 ����',0
.421:db 'ॣ���� ��饣� �����祭�� 4 ����',0
.422:db 'ॣ���� ��饣� �����祭�� 4 ����',0
.423:db '������� ॣ���� 4 ����',0
.424:db 'ॣ���� ��饣� �����祭�� 4 ����',0
.425:db 'ॣ���� 㪠��⥫� ������',0
.426:db '����� �ணࠬ��',0
.427:db '����� �����',0
.428:db '����� �㭪樨 proc',0
.429:db '����� �������� struct',0
.432:db 'ᥣ����� ॣ����',0
.433:db '��४��祭�� �� ᮯ�����. ����� �� ��������.',0
.436:db '���᫥��� �⥯��� x �� �᭮����� 2 ����� 1',0
.437:db '���祭�� �� ����� �᫠ st(0) ',0
.438:db '᫮���� 2 �᫠ � ������饩 �窮�',0
.440:db '����㦠�� �� ����� � ���設� �⥪� st(0) ����筮-�����筮� �᫮',0
.441:db '��������� ����� �᫠',0
.442:db '�ࠢ�����',0
.443:db '�ࠢ����� � �����祭�� �� �⥪�',0
.444:db '�ࠢ����� � ������� �����祭�� �� �⥪�',0
.445:db '��ᨭ��',0
.446:db '㬥����� 㪠��⥫� �⥪� sp �� 1',0
.447:db '�������� 2 �᫠ � ������饩 �窮�',0
.451:db '�᢮�������� ॣ���� �⥪� ᮯ�����',0
.452:db '楫��᫥���� �ࠢ�����',0
.453:db '楫��᫥���� �ࠢ����� � �����祭�� �� �⥪�',0
.454:db '����㦠�� �� ����� � ���設� �⥪� st(0) 楫�� �᫮ ',0
.456:db '㢥����� 㪠��⥫� �⥪� sp �� 1',0
.457:db '���樠����஢��� fpu',0
.460:db '����㦠�� �� ����� � ���設� �⥪� st(0) ����⢥���� �᫮',0
.461:db '����㧪� �������',0
.463:db '����㧪� �᫠ 1/ln(2)',0
.464:db '����㧪� �᫠ ln(10)/ln(2)',0
.465:db '����㧪� �᫠ log(2)/ln(10)',0
.466:db '����㧪� �᫠ ln(2)',0
.467:db '����㦠�� � ���設� �⥪� st(0) �᫮ Pi',0
.468:db '����㧪� ���',0
.469:db '㬭������',0
.473:db '��⠭���� ��⭮��',0
.474:db '���᫥��� ���⪠ �� �������',0
.475:db '���᫥��� ⠭����',0
.476:db '���㣫���� �᫠ st(0) �� 楫���',0
.480:db '㬭������ �� 2^y',0
.481:db '���᫥��� ᨭ��',0
.482:db '���᫥��� ᨭ�� � ��ᨭ��',0
.483:db '�����祭�� �����⭮�� ����',0
.484:db '���㧪� १���� st(0)',0
.486:db '���㧪� १���� st(0) � �᢮�������� �⥪�',0
.488:db '���⠭��',0
.492:db '�ࠢ����� ���࠭�� � �㫥�',0
.494:db '������ ���࠭��',0
.495:db '�����',0
.496:db '�뤥����� ���浪� �᫠ � �������',0
.497:db '���᫥��� y*log2(x)',0
.498:db '���᫥��� y*log2(x+1)',0
.499:db '6-����� ॣ����, � ���஬ ᮤ�ন��� ������� ���� ������쭮� ���ਯ�୮� ⠡����',0
.501:db '��⠭�� ���ய�����. ����� �� ��������.',0
.502:db '楫�� ������� �������� ����稭. ������� ���������� �� 䫠�� af, cf, of, pf, sf � zf.',0
.503:db '䫠���� ॣ���� ࠧ�襭�� ���뢠���',0
.504:db '楫�� 㬭������ �������� ����稭. ������� ���������� �� 䫠�� cf � of (䫠�� af pf sf � zf �� ��।�����).',0
.506:db '�ਡ����� � ���࠭�� �������',0
.508:db '㪠�뢠�� ������⥪� ������',0
.515:db 'ॣ���� 㪠��⥫� ������',0
.518:db '���室 �᫨ cf=0 � zf=0 (ja - Jump if Above)',0
.519:db '���室 �᫨ cf=0 (jae - Jump if Above or Equal)',0
.520:db '���室 �᫨ cf=1 (jb - Jump if Below)',0
.521:db '���室 �᫨ cf=1 ��� zf=1 (jbe - Jump if Below or Equal)',0
.522:db '���室 �᫨ cf=1 (jc - Jump if Carry)',0
.524:db '���室 �᫨ cx=0 (jcxz - Jump if CX Zero)',0
.525:db '���室 �᫨ zf=1 (je - Jump if Equal)',0
.526:db '���室 �᫨ ecx=0 (jecxz - Jump if ECX Zero)',0
.527:db '���室 �᫨ zf=0 � sf=of (jg - Jump if Greater (signed))',0
.528:db '���室 �᫨ sf=of (jge - Jump if Greater or Equal (signed))',0
.529:db '���室 �᫨ sf!=of (jl - Jump if Less (signed))',0
.530:db '���室 �᫨ zf=1 ��� sf!=of (jle - Jump if Less or Equal (signed))',0
.531:db '���室 ��� �᫮���',0
.545:db '���室 �᫨ zf=0 (jnz - Jump if Not Zero)',0
.546:db '���室 �᫨ of=1 (jo - Jump if Overflow)',0
.549:db '���室 �᫨ pf=0 (jpo - Jump if Parity Odd)',0
.550:db '���室 �᫨ sf=1 (js - Jump if Signed (signed))',0
.551:db '���室 �᫨ zf=1 (jz - Jump if Zero)',0
.554:db '10-����� ॣ����, ᮤ�ঠ騩 16-���� ᥫ���� (������) ��� gdt � 8-����� ���ਯ��',0
.563:db '१�ࢨ��� ������ �� �⥪� ��� �������� ��६�����',0
.566:db '����㧪� 1-�� ���⮢�� ��ப',0
.567:db '����㧪� 4-� ���⮢�� ��ப',0
.569:db '����㧪� 2-� ���⮢�� ��ப',0
.571:db '���室 �᫨ ecx!=0 � 䫠� zf=1',0
.572:db '���室 �᫨ ecx!=0 � 䫠� zf=0',0
.573:db '���室 �᫨ ecx!=0 � 䫠� zf=0',0
.574:db '���室 �᫨ ecx!=0 � 䫠� zf=1',0
.576:db '����� ��� ����஢���� ���祭��, �ᯮ���� ����樨 push � pop',0
.578:db '����� ��� �맮�� ��⥬��� �㭪権 ��뢠�� int 0x40, ��ࠬ���� ���� � ॣ�����',0
.587:db '�������� ���祭�� ��ண� ���࠭�� � ����',0
.596:db '����� ������',0
.598:db '䫠���� ॣ���� ��९�������',0
.607:db '᫮����� 㯠�������� ���� ��� ����饭�� (� 横���᪨� ��९��������)',0
.608:db '᫮����� 㯠�������� ������� ᫮� ��� ����饭�� (� 横���᪨� ��९��������)',0
.609:db '᫮����� 㯠�������� ���� � ������� ����饭���',0
.610:db '᫮����� 㯠�������� ᫮� � ������� ����饭���',0
.611:db '᫮����� 㯠�������� ���� � ���������� ����饭���',0
.612:db '᫮����� 㯠�������� ᫮� � ���������� ����饭���',0
.613:db '᫮����� 㯠�������� ᫮� ��� ����饭�� (� 横���᪨� ��९��������)',0
.614:db '�����᪮� "�"',0
.615:db '�����᪮� "�-��"',0
.616:db '�ࠢ����� (�� ࠢ���⢮) 㯠�������� ����. �� ���� ������� १���� ���� ������묨 (true) �� ᮢ������� ᮮ⢥������� ������⮢ ���࠭��� � �㫥�묨 (false) - �� ��ᮢ�������',0
.617:db '�ࠢ����� (�� ࠢ���⢮) 㯠�������� ������� ᫮�. �� ���� ������� १���� ���� ������묨 (true) �� ᮢ������� ᮮ⢥������� ������⮢ ���࠭��� � �㫥�묨 (false) - �� ��ᮢ�������',0
.618:db '�ࠢ����� (�� ࠢ���⢮) 㯠�������� ᫮�. �� ���� ������� १���� ���� ������묨 (true) �� ᮢ������� ᮮ⢥������� ������⮢ ���࠭��� � �㫥�묨 (false) - �� ��ᮢ�������',0
.619:db '�ࠢ����� (�� ����稭�) 㯠�������� �������� ����. �� ���� ������� १���� ���� ������묨 (true), �᫨ ᮮ⢥�����騩 ������� ���࠭�� �����祭�� ����� ������� ���࠭�� ���筨��, � �㫥�묨 (false) � ��⨢��� ��砥',0
.620:db '�ࠢ����� (�� ����稭�) 㯠�������� �������� ������� ᫮�. �� ���� ������� १���� ���� ������묨 (true), �᫨ ᮮ⢥�����騩 ������� ���࠭�� �����祭�� ����� ������� ���࠭�� ���筨��, � �㫥�묨 (false) � ��⨢��� ��砥',0
.621:db '�ࠢ����� (�� ����稭�) 㯠�������� �������� ᫮�. �� ���� ������� १���� ���� ������묨 (true), �᫨ ᮮ⢥�����騩 ������� ���࠭�� �����祭�� ����� ������� ���࠭�� ���筨��, � �㫥�묨 (false) � ��⨢��� ��砥',0
.622:db '䫠���� ॣ���� �⭮��',0
.623:db '��������� 4-� �������� ᫮� ���࠭�� ���筨�� �� 4 �������� ᫮�� ���࠭�� �����祭��. ��� ������� ᫮�� १���⮢ 㬭������ ������ ᫮� �㬬������� � �����뢠���� � ����襥 ������� ᫮�� ���࠭�� �����祭��. ��� ������� ᫮�� १���⮢ 㬭������ ����� ᫮� �㬬������� � �����뢠���� � ���襥 ������� ᫮�� ���࠭�� �����祭��',0
.624:db '㬭������ 㯠�������� �������� ᫮� � ��࠭����� ⮫쪮 ����� 16 ��� ������⮢ १����',0
.625:db '㬭������ 㯠�������� �������� ��� ����������� ᫮� � ��࠭����� ⮫쪮 ������ 16 ��� १����',0
.627:db '���㧪� �� �⥪� 2-� ������ ॣ���஢ ��饣� �����祭��',0
.628:db '���㧪� �� �⥪� 4-� ������ ॣ���஢ ��饣� �����祭��',0
.631:db '�����᪮� "���"',0
.632:db '����� ��� ���ᠭ�� �㭪樨 (�����)',0
.658:db '����㧪� ᫮�� � �⥪',0
.659:db '����㧪� � �⥪ 2-� ������ ॣ���஢ ��饣� �����祭��',0
.660:db '����㧪� � �⥪ 4-� ������ ॣ���஢ ��饣� �����祭��',0
.661:db '����㧪� ᮤ�ন���� ॣ���� flags � �⥪',0
.664:db '�᪫���饥 "���"',0
.665:db '8 ����',0
.675:db '横���᪨� ᤢ�� �����',0
.676:db '横���᪨� ᤢ�� ��ࠢ�',0
.677:db '��࠭�� ॣ���� ah � ॣ���� 䫠��� (���������� �� af, cf, pf, sf, zf)',0
.682:db '�ࠢ������ ���祭�� al � ���祭��� �� ����� edi',0
.683:db '�ࠢ������ ���祭�� eax � ���祭��� �� ����� edi',0
.684:db '�ࠢ������ ���祭�� ax � ���祭��� �� ����� edi',0
.686:db '䫠���� ॣ���� �����',0
.687:db '��࠭���� ॣ���� gdtr (������쭮� ���ਯ�୮� ⠡����) � �����',0
.688:db 'ᤢ�� ����� �� ��।. ���. ��� (㢥��稢��� �᫮ � 2^n ࠧ)',0
.689:db '3-� ���࠭���� ������� ᤢ��� �����. 1-� ���࠭��� ����� ���� ���� ॣ����, ���� �祩�� �����, 2-� ���࠭��� ������ ���� ॣ���� ��饣� �����祭��, ���쨬 - ॣ���� cl ��� ���࠭�.',0
.690:db 'ᤢ�� ��ࠢ� �� ��।. ���. ��� (㬥��蠥� �᫮ � 2^n ࠧ)',0
.691:db '������� ॣ����',0
.693:db 'ॣ���� 㪠��⥫�',0
.694:db 'ᥣ����� ॣ���� - ᥣ���� �⥪�',0
.705:db '����� ��� �맮�� �㭪樨 (������ call) � ������� ��ࠬ��஢ � �⥪ (������ push)',0
.708:db '������ al �� ����� edi, � ����ᨬ��� �� df ���� ��������� �� 1',0
.709:db '������ eax �� ����� edi, � ����ᨬ��� �� df ���� ��������� �� 4',0
.710:db '������ ax �� ����� edi, � ����ᨬ��� �� df ���� ��������� �� 2',0
.711:db '����� ��� ���ᠭ�� ��������',0
.713:db '������ �� ��ࢮ�� ���࠭�� ��ன',0
.717:db '䫠���� ॣ���� ����஢��',0
.718:db '10 ����',0
.719:db '�������� � ��楤��� (�㭪���) ��� ��� ��࠭���� � ����⠭������� 㪠������ ॣ���஢',0
.720:db '2 ����',0
.722:db '����� ���祭�ﬨ',0
.733:db '������ �᪫���饥 ��� | 0+0=0 | 0+1=1 | 1+0=1 | 1+1=0 |',0
.734:db '䫠���� ॣ���� �㫥���� १����',0
