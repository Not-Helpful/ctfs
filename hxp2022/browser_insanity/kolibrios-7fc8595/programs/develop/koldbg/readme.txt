��������.

koldbg ������������ ����� ������������� �������� ��� ������������ ������� KolibriOS. ����� ��������� - ������� ��������� (Diamond). ������ ������������ ��������� ����������� ��������� � ������ � ���. ���� � ��� ���� �����-���� ������� �� ������ � ���������� ��� ����� �����-�� ����������� ���������, ������� ��� ���, ����������� �� ����� board.kolibrios.org � ��������������� ���� - http://board.kolibrios.org/viewtopic.php?f=45&t=358, ��� �� ������ ������ - mailto:diamondz@land.ru.

����� ��������.

� ������ ������ ������� koldbg ����� ���������� ������ ���� ���������. ������ ����� ��������� ����������� ��� �������. ���� ������� ��������� �� ���������, ���������� ����������� �������� �� ������� ����������.

koldbg ����������� ��������� �������, �������� � ����������. ��������� ������ ������������ � ������ ����� ���� ���������. �������������� ����������� ������� ����� Backspace, Delete, Home, End, ������� �����/������, ������� �����/���� (������������� ������� ������). ������� ��������������� � �������� ��������. � �������� ����������� ������������ ������������ ��������� ����� ��������.

� ����� ������ �������� ����� ��������� �������� "quit" (��� ����������). �������, ����� � ������ ������ �� ������ �������� � ������ ������� ���� ����.

������ ��������� ��� ���������� ��������� ������ �������� � ����, ��� ������� ��������� �� ���������. ����� koldbg ����� ��������� � ���������
�������, � ���� ������ �� ���������� ��������� ��������� � ������, ��������� ��� ������ �������� ��������� ������, � �����������, ���������� ���
����������� (���� ��� ����).

���� ������� ��������� �� ���������, �� ����� ��������� ��������� �������� load:
load <������ ��� ������������ �����> [<���������>]
��������:
load /sys/example
LOAD   /sys/aclock w200 h200
 LoaD  /hd0/1/menuetos/dosbox/dosbox
��, ��� ����� ����� ������� ������� ����� ����� ������������ �����, �������� ��������� ��������� � �������� ��������� ������.
������� load �������� � ���������� � ���� ��������� (������� ���� ���� ��������� ������). ���� ��������� ������� ���������, �� �� ���� �������� ��������������� ���������; ���� �� �������, �� � ��������� ����� ������� ������� ������. �������� ��������� - "file not found", ���� ����������� ������� ��� �����.

�������� ����� ��������� ����� � ����������� �� ������ � ��������� (�����, ���������� ����������) - ��������� �����, ������ ������ ������� ����� ��� 0x<hex_��������_������> <���> (������, �� ������� ����� ���, ������������). ����� ���� ����� ���� ������ ������� ��� ������������ ������������� ��� ���������� ��������� fasm'��.
����� �������� �������������� �������� load-symbols:
load-symbols <������ ��� ����� ��������>
����� ����, ��� ���������� ������� load �������� ��������� ������� ����� � ����� �� ������, ��� ����������� ��������, � ����������� .dbg (/sys/example.dbg ��� ������� �� �������� ����), � ���� ����� ����, ��������� ��� ������������� (������� ��������� "Symbols loaded", ���� �� �
�������).

����� ��������� ���, ��� ����������� ��������� ���������. ����� ������� �������� �������� ���������: ������� �������� ���� �������� (�����-������ ���������� ������), ����� ������������� ��������� �� ������� ���, ������� �������� ���������� ��� ������� ���������, ������������� � ������ �������� ���, ����� ���� ������� ��� ����������. ���� ��������� ���������, �� � "���������" ��� �� ����� � ��� ������� ����� �������������� ������ ��� ������������. koldbg ���������� ����������� ������������ ����������� (mxp, mxp_lzo, mxp_nrv, mtappack) � � ���� ������ ���������� ������������� ������ �� "����������" ����. ������������� ����������� (������ 'y' ��� <Enter>), �� ����� � ����������. ��� ������ � � ������, ����� ��������� ��������� ���-�� �����������, ����� ������������ ������� "unpack" (��� ����������). ��������� � ������ � ������,
����� �� �������, ��� ��������� ��������� � ��� ���������� ��� �� ����� �� ��������� ����! [������� � ������ Kolibri 0.6.5.0, ���� ���� ����� ��� ����������, ��������� ���������� ����� ����������� ��� � ����� �������� ����� kpack'�� � ��� ���� ��� ������������ ��������� � ���� � ���������� ��������� ��� �������.]

����������� ��������� ����� ������� �������� "terminate" (��� ����������). ������� "detach" (��� ����������) ����������� �� ���������, ����� ���� ��������� ���������� ����������� ���������, ��� ���� �� ��������� �� ����. ����� ����� ���� ������ ��������� �������� ���� ������������.

����� ������ ��������� ��������� ��� ������� �������� "reload" (��� ����������). ���� ��� ���� ����������� ���������, �� ��� ����������� �
����������� (� ������ ������) ����� ��������� (� ��� �� ��������� �������), � ���� ������ ������� ���������� ��������:
terminate
load <last program name> <last program arguments>
� ��������� ������ ������ ����������� ���������, ������� ���������� ��������� (� ������� ������ ������ � koldbg) (� ��� �� ��������� �������), �.�. ����� �� �� �����, ��� � load <last program name> <last program arguments>, �� ������� reload � ����� ������� ������ � �������; ����� ����, load �������, ��� ����������� ����� ���������, � ��������� ���� ������ (��. ����) �� ������� �����, � reload ��������� ������� �����.

������ �������� ������� "help", ������� ����� ��������� �� "h".
��� ������� ������� �� ������.
help ��� ���������� ���������� ������ ����� ������.
help � ��������� ������ ������� ������ ������ ���� ������ � ��������
�������������.
help � ��������� ������� ������� ���������� � �������� �������.
��������:
help
help control
h LoaD

���� ��������� ������� �� ��������� ���������, ������������� ������ ����:
- ������ ���������. ��� ������� ����������� ��������� ���������� �� ��� � ��������� ("Running"/"Paused"), ��� ���������� �������� "No program loaded".
- ���� ��������� - ���������� �������� ��������� ������ ����������, �������� eip, �������� ������ � ��������� FPU/MMX. ������� ������ ������������ ����� ���������: ������ hex-�������� � ��������� ��������� ������: CF,PF,AF,ZF,SF,DF,OF: ���� ���� �������, �� ������������ ��������� �����, ���� ����������, �� ���������. ��������, ������������ � ����������� �������, �������������� ���������.
- ���� ������ (���� �����) - ���������� ���������� ������ ����������� ���������
- ���� ���� (���� �������������) - ���������� ��� ��������� � ���� ������������������� ����������
- ���� ���������
- ���� ��������� ������

� ���� ����� ����� ������������� ������, ������� � ������ ������, ��� ����� ���� �������:
d <���������>
������� d ��� ���������� ������������ ���� ����� ����. �� �� ����� ��������� � ���� ���� � ������� u <���������> ��� ������ u.
��������:
d esi - ���������� ������, ����������� �� ������ esi (��������, ������� ����� ����������� ���������� rep movsb)
d esp - ���������� ����
u eip - ��������������� ����������, ������� � �������

��������� � koldbg ����� ��������
- ����������������� ���������
- ����� ���� ��������� ������ ���������� (8 32-������, 8 16-������ � 8 8-������) � �������� eip; �������� 16- � 8-������ ��������� �����������
  ������ �� 32 ���
- ������ �������������� �������� +,-,*,/ (�� ������������ ������������) � ������
- [���� ���� ���������� � ��������] �����, ����������� �� dbg-�����
��� ���������� ������������ �� ������ 2^32.
������� ���������:
eax
eip+2
ecx-esi-1F
al+AH*bl
ax + 2* bH*(eip+a73)
3*esi*di/EAX
�������
? <���������> ��������� �������� ���������� ���������.

�������� ��������� ����������� ��������� ����� �������� �������� r, ������� ��� ��������� ������������� �����:
r <�������> <���������>
r <�������>=<���������>
(� ����� ������� ����� ����������� ������� �� �����). � �������� �������� ����� ��������� ����� �� �������������� - 24 �������� ������ ���������� � eip.


��������, ������� load ������� ��������� ��������� ��� �������. ����� ����� �������� ��������� �������������� � �� �����������.
������� F7 (������ ��������� ������ - ������� "s") ������ ���� ��� � ����������� ���������, ����� ���� ���������� ������������ ���������, ������� ���������� ����� ���������� ��������� � ������. ��������� ����� int 40h (� ����� ���������� sysenter � syscall) ��� ���� ��������� ����� �����.
������� F8 (������ ��������� ������ - ������� "p") ����� ������ ��� � ����������� ���������, �� ��� ���� ������ ��������, ��������� �������� �
��������� rep/repz/repnz � ����� loop ����������� ��� ���� ���.
������� ���������� ���������� ������������, ��� �������, �� ��������� �������� ���������, ����� �����, ��������, ��������� ����������� �������� ��������� �/��� �����-�� ���������� � ������.
������� g <���������> ������������ ���������� ��������� � ���, ���� ���������� ����� �� eip=���������������� ������, � � ���� ������ ���������������� ���������. ������� "g" ��� ���������� ������ ������������ ���������� ���������.

������������� ���������� ��������� ����� �������� "stop" (��� ����������).

������ ���������, ����� ��������� ��������� �����������, �� ��� ����������� ����������� ������� ��������� ��������������� � ���������� ������� ��������. ��������������� ������� ���������� ������� ��������, breakpoint(s), � ����������� - �������. ���������� ��� ����� �������� - �� ���������� �����, �.�. ��������� ���������� ��� eip=<�������� ��������>. ����� ����� �������� ��������������� ��������:
bp <���������>
���������. ���� ���� ������ ���� ����� ����� ��������, ������� ������ �� ������������ ������� "g" � ����������.

������ ��� ����� �������� - �� ��������� � ��������� ������� ������. ����� ����� �������� ����� ���� �� ������ ������ (��������� ������������
���������� ����������� ����������� x86, ��� ����������� ������ 4 ����� �����).
bpm <���������> - ��������� �� ����� ������ � ����� �� ���������� ������
bpm w <���������> - ��������� �� ������ ����� �� ���������� ������
bpmb/bpmw/bpmd <���������> - ��������� �� ������ � �������������� �����, ����� � �������� ����� �� ���������� ������. bpm � bpmb - ��������. ��� ������������� bpmw/bpmd ����� ������ ���� �������� �������������� �� ������� ����� (�.�. ���� ������) ��� �� ������� �������� ����� (�.�. �������� �� 4).
bpmb,bpmw,bpmd w <���������> - ���������� ��� ����� �� ������.

������ ������������� ����� �������� ����� ����������� �������� "bl", ���������� � ���������� ����� �������� ����� �������� � ������� "bl <�����>". �������� ����� �������� ��������� �������� "bc <�����>", �������� �������� ����� ��������� �������� "bd <�����>", ����� ��� ������ ����� �����, ����������� ������� "be <�����>".

���������.

1. ��� ������� ����������� �������� ����� ��������� � ��� ���������� int3 (�������� �������� �� ���������� �������!). ����� ���������� �������� ���������� ��� ���������� �������, ��� ������� � ���������� ��������, �� ��� ������ ��� ���������� ������ �������������� �������� (� ���������� "int3 command at xxx"). ��� ��������� �� ������ � ���, ����� ������ ������������ � �������� g �/��� bp. ����� ����� ������������ ���� � ����������� � �������� � ��������� ���, ����� �� ������ ��� ����� �������������� ��������� ������ ��� "g" � "bp", �� � "u","d","?" ����� �������� �������� ����� �����/����������.
2. ���� ����� � ���� ���� ������������ �� 16-������ ������� ���������.
3. ����� ��������� �����������, ���� ��������� � ������ ���������� ����������, ����������� � ������� �� �������������; ��������� �������� ��������� � ���� ������ ����������. �������, ������� "d" � ���� ������ ���������� ����������, ������ � ������ ������ �������.
