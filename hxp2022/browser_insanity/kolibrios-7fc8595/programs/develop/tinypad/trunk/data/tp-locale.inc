
sz htext,'TINYPAD ',APP_VERSION

menubar_res main_menu,\
  ru,'����'	,mm.File    ,onshow.file   ,\
  ru,'�ࠢ��'	,mm.Edit    ,onshow.edit   ,\
  ru,'����'	,mm.Search  ,onshow.search ,\
  ru,'�����'	,mm.Run     ,onshow.run    ,\
  ru,'����஢��',mm.Encoding,onshow.recode ,\
  ru,'��樨'	,mm.Options ,onshow.options,\
\
  en,'File'	,mm.File    ,onshow.file   ,\
  en,'Edit'	,mm.Edit    ,onshow.edit   ,\
  en,'Search'	,mm.Search  ,onshow.search ,\
  en,'Run'	,mm.Run     ,onshow.run    ,\
  en,'Encoding'	,mm.Encoding,onshow.recode ,\
  en,'Options'	,mm.Options ,onshow.options,\
\
  it,'File'	,mm.File    ,onshow.file   ,\
  it,'Modificare'	,mm.Edit    ,onshow.edit   ,\
  it,'Ricerca'	,mm.Search  ,onshow.search ,\
  it,'Correre'	,mm.Run     ,onshow.run    ,\
  it,'Codifica'	,mm.Encoding,onshow.recode ,\
  it,'Opzioni'	,mm.Options ,onshow.options,\
\
  et,'Fail'	,mm.File    ,onshow.file   ,\
  et,'Muuda'	,mm.Edit    ,onshow.edit   ,\
  et,'Otsi'	,mm.Search  ,onshow.search ,\
  et,'K�ivita'	,mm.Run     ,onshow.run    ,\
  et,'Kodeering',mm.Encoding,onshow.recode ,\
  et,'Seaded'	,mm.Options ,onshow.options,\
\
  sp,'Archivo'	,mm.File    ,onshow.file   ,\
  sp,'Editar'	,mm.Edit    ,onshow.edit   ,\
  sp,'Buscar'	,mm.Search  ,onshow.search ,\
  sp,'Ejecutar'	,mm.Run     ,onshow.run    ,\
  sp,'Codificaci�n',mm.Encoding,onshow.recode,\
  sp,'Opciones'	,mm.Options ,onshow.options

popup_res mm.File,\
  ru,'����'	 ,'Ctrl+N'	,New	,\
  ru,'������...','Ctrl+O'	,Open	,\
  ru,'���࠭���' ,'Ctrl+S'	,Save	,\
  ru,'���࠭��� ���...','Ctrl+Shift+S',SaveAs,\
  ru,'-','',,\
  ru,'�������'	 ,'Ctrl+F4'	,Close	,\
  ru,'-','',,\
  ru,'��室'	 ,'Alt+X'	,Exit	,\
\
  en,'New'	 ,'Ctrl+N'	,New	,\
  en,'Open...'	 ,'Ctrl+O'	,Open	,\
  en,'Save'	 ,'Ctrl+S'	,Save	,\
  en,'Save as...','Ctrl+Shift+S',SaveAs	,\
  en,'-','',,\
  en,'Close'	 ,'Ctrl+F4'	,Close	,\
  en,'-','',,\
  en,'Exit'	 ,'Alt+X'	,Exit	,\
\
  it,'Nuovo'	 ,'Ctrl+N'	,New	,\
  it,'Aperto...'	 ,'Ctrl+O'	,Open	,\
  it,'Salva'	 ,'Ctrl+S'	,Save	,\
  it,'Salva come...','Ctrl+Shift+S',SaveAs	,\
  it,'-','',,\
  it,'Chiudi'	 ,'Ctrl+F4'	,Close	,\
  it,'-','',,\
  it,'Uscita'	 ,'Alt+X'	,Exit	,\
\
  et,'Uus'	,'Ctrl+N'	,New	,\
  et,'Ava...'	,'Ctrl+O'	,Open	,\
  et,'Salvesta'	,'Ctrl+S'	,Save	,\
  et,'Salvesta nimega...','Ctrl+Shift+S',SaveAs,\
  et,'-','',,\
  et,'Sulge'	,'Ctrl+F4'	,Close	,\
  et,'-','',,\
  et,'V�lju'	,'Alt+X'	,Exit	,\
\
  sp,'Nuevo'	,'Ctrl+N' ,New	,\
  sp,'Abrir...'	,'Ctrl+O' ,Open	,\
  sp,'Guardar'	,'Ctrl+S' ,Save	,\
  sp,'Guardar como...','Ctrl+Shift+S',SaveAs,\
  sp,'-','',,\
  sp,'Cerrar'	,'Ctrl+F4',Close,\
  sp,'-','',,\
  sp,'Salir'	,'Alt+X'  ,Exit

popup_res mm.Edit,\
  ru,'��१���'		,'Ctrl+X',Cut	,\
  ru,'����஢���'	,'Ctrl+C',Copy	,\
  ru,'��⠢���'		,'Ctrl+V',Insert,\
  ru,'�������'		,''	 ,Delete,\
  ru,'-','',,\
  ru,'�뤥���� ���'	,'Ctrl+A',SelAll,\
\
  en,'Cut'	 ,'Ctrl+X',Cut   ,\
  en,'Copy'	 ,'Ctrl+C',Copy  ,\
  en,'Paste'	 ,'Ctrl+V',Insert,\
  en,'Delete'	 ,''	  ,Delete,\
  en,'-','',,\
  en,'Select all','Ctrl+A',SelAll,\
\
  it,'Taglio'	 ,'Ctrl+X',Cut   ,\
  it,'Copia'	 ,'Ctrl+C',Copy  ,\
  it,'Incolla'	 ,'Ctrl+V',Insert,\
  it,'Elimina'	 ,'' ,Delete,\
  it,'-','',,\
  it,'Seleziona tutto','Ctrl+A',SelAll,\
\
  et,'L�ika'	,'Ctrl+X',Cut	,\
  et,'Kopeeri'	,'Ctrl+C',Copy	,\
  et,'Kleebi'	,'Ctrl+V',Insert,\
  et,'Kustuta'	,''	 ,Delete,\
  et,'-','',,\
  et,'Vali k�ik','Ctrl+A',SelAll,\
\
  sp,'Cortar'	,'Ctrl+X',Cut	,\
  sp,'Copiar'	,'Ctrl+C',Copy	,\
  sp,'Pegar'	,'Ctrl+V',Insert,\
  sp,'Eliminar'	,''	 ,Delete,\
  sp,'-','',,\
  sp,'Seleccionar todo','Ctrl+A',SelAll

popup_res mm.Search,\
  ru,'��३�...' ,'Ctrl+G',Position,\
  ru,'-','',,\
  ru,'����...'   ,'Ctrl+F',Find    ,\
  ru,'���� �����','F3'    ,FindNext,\
  ru,'��������...','Ctrl+H',Replace ,\
\
  en,'Position...','Ctrl+G',Position,\
  en,'-','',,\
  en,'Find...'    ,'Ctrl+F',Find    ,\
  en,'Find next'  ,'F3'    ,FindNext,\
  en,'Replace...' ,'Ctrl+H',Replace ,\
\
  it,'Posizione...','Ctrl+G',Position,\
  it,'-','',,\
  it,'Trova...'    ,'Ctrl+F',Find    ,\
  it,'Trova il prossimo'  ,'F3'    ,FindNext,\
  it,'Sostituire...' ,'Ctrl+H',Replace ,\
\
  et,'Positsioon...','Ctrl+G',Position,\
  et,'-','',,\
  et,'Leia...'      ,'Ctrl+F',Find    ,\
  et,'Leia j�rgmine','F3'    ,FindNext,\
  et,'Asenda...'    ,'Ctrl+H',Replace ,\
\
  sp,'Posici�n...'  ,'Ctrl+G',Position,\
  sp,'-','',,\
  sp,'Buscar...'    ,'Ctrl+F',Find    ,\
  sp,'Buscar siguiente','F3' ,FindNext,\
  sp,'Reemplazar...','Ctrl+H',Replace

popup_res mm.Run,\
  ru,'��������'	,'F9'	  ,Run     ,\
  ru,'�������� � ��������','F10',Debug   ,\
  ru,'�������஢���'	,'Ctrl+F9',Compile ,\
  ru,'-','',,\
  ru,'��᪠ �⫠���'	,''	  ,DbgBoard,\
  ru,'���⥬�� �㭪樨',''	  ,SysFuncs,\
\
  en,'Run'		,'F9'	  ,Run     ,\
  en,'Run in debugger'	,'F10'	  ,Debug   ,\
  en,'Compile'		,'Ctrl+F9',Compile ,\
  en,'-','',,\
  en,'Debug board'	,''	  ,DbgBoard,\
  en,'System functions'	,''	  ,SysFuncs,\
\
  it,'Correre'		,'F9'	  ,Run     ,\
  it,'Esegui nel debugger','F10',Debug   ,\
  it,'Compilare','Ctrl+F9',Compile ,\
  it,'-','',,\
  it,'Scheda di debug'	,''	  ,DbgBoard,\
  it,'Funzioni di sistema',''	  ,SysFuncs,\
\
  et,'K�ivita'		,'F9'	  ,Run     ,\
  et,'K�ivita aastal siluri','F10',Debug   ,\
  et,'Kompileeri'	,'Ctrl+F9',Compile ,\
  et,'-','',,\
  et,'Silumis paneel'	,''	  ,DbgBoard,\
  et,'S�steemi funktsioonid',''	  ,SysFuncs,\
\
  sp,'Ejecutar'		,'F9'	  ,Run     ,\
  sp,'Ejecutar en el depurador','F10',Debug,\
  sp,'Compilar'		,'Ctrl+F9',Compile ,\
  sp,'-','',,\
  sp,'Depuraci�n'	,''	  ,DbgBoard,\
  sp,'Funciones del sistema'   ,'',SysFuncs

popup_res mm.Encoding,\
  @!,<'CP866  ',0x1A,' CP1251'>,'',CP866.CP1251,\
  @!,<'CP1251 ',0x1A,' CP866' >,'',CP1251.CP866,\
  @!,<'-'>,'',,\
  @!,<'CP866  ',0x1A,' KOI8-R'>,'',CP866.KOI8R ,\
  @!,<'KOI8-R ',0x1A,' CP866' >,'',KOI8R.CP866 ,\
  @!,<'-'>,'',,\
  @!,<'CP1251 ',0x1A,' KOI8-R'>,'',CP1251.KOI8R,\
  @!,<'KOI8-R ',0x1A,' CP1251'>,'',KOI8R.CP1251

popup_res mm.Options,\
  ru,'��������'	  ,'Ctrl +',ZoomIn	,\
  ru,'��������'	  ,'Ctrl -',ZoomOut	,\
  ru,'-','',,\
  ru,'����� ��ப'		,'',LineNumbers	,\
  ru,'������᭮� �뤥�����'	,'',SecureSel	,\
  ru,'��⮬���᪨� ᪮���'	,'',AutoBrackets,\
  ru,'��⮬���᪨� �����'	,'',AutoIndents	,\
  ru,'��⨬��쭮� ��࠭����'	,'',OptimalFill	,\
  ru,'-','',,\
  ru,'���譨� ���...'		,'',Appearance	,\
\
  en,'Zoom in'		  ,'Ctrl +',ZoomIn	,\
  en,'Zoom out'		  ,'Ctrl -',ZoomOut	,\
  en,'-','',,\
  en,'Line numbers'		,'',LineNumbers	,\
  en,'Secure selection'		,'',SecureSel	,\
  en,'Automatic brackets'	,'',AutoBrackets,\
  en,'Automatic indents'	,'',AutoIndents	,\
  en,'Optimal fill on saving'	,'',OptimalFill	,\
  en,'-','',,\
  en,'Appearance...'		,'',Appearance	,\
\
  it,'Ingrandire'		  ,'Ctrl +',ZoomIn	,\
  it,'Rimpicciolisci'		  ,'Ctrl -',ZoomOut	,\
  it,'-','',,\
  it,'Numeri di riga'		,'',LineNumbers	,\
  it,'Selezione sicura'		,'',SecureSel	,\
  it,'Staffe automatiche'	,'',AutoBrackets,\
  it,'Rientri automatici'	,'',AutoIndents	,\
  it,'Combina spazi'	,'',OptimalFill	,\
  it,'-','',,\
  it,'Aspetto...'		,'',Appearance	,\
\
  et,'Zoom in'		  ,'Ctrl +',ZoomIn	,\
  et,'Zoom out'		  ,'Ctrl -',ZoomOut	,\
  et,'-','',,\
  et,'Rea numbrid'		,'',LineNumbers	,\
  et,'Turvaline valimine'	,'',SecureSel	,\
  et,'Automaatsed sulud'	,'',AutoBrackets,\
  et,'Automaatsed taandread'	,'',AutoIndents	,\
  et,'Optimaalne t�itmine salvestamisel','',OptimalFill,\
  et,'-','',,\
  et,'V�limus...'		,'',Appearance	,\
\
  sp,'Zoom in'		  ,'Ctrl +',ZoomIn	,\
  sp,'Zoom out'		  ,'Ctrl -',ZoomOut	,\
  sp,'-','',,\
  sp,'N�meros en l�neas'	,'',LineNumbers	,\
  sp,'Selecci�n segura'		,'',SecureSel	,\
  sp,'Par�ntesis autom�ticos'	,'',AutoBrackets,\
  sp,'Identaci�n autom�tica'	,'',AutoIndents	,\
  sp,'Llenado �ptimo al guardar','',OptimalFill	,\
  sp,'-','',,\
  sp,'Apariencia...'		,'',Appearance

lsz s_defname,\
  ru,<'����ﭭ�',0>,\
  en,<'Untitled',0>,\
  it,<'Senza titolo',0>,\
  et,<'Nimetu',0>,\
  sp,<'Sin t�tulo',0>

lsz s_modified,\
  ru,'��������',\
  en,'Modified',\
  it,'Modificato',\
  et,'Muudetud',\
  sp,'Modificado'

lsz s_2filename,\
  ru,'��� 䠩��:',\
  en,'Filename:',\
  en,'Nome del file:',\
  et,'Faili nimi:',\
  sp,'Nombre de archivo:'
lsz s_2open,\
  ru,'������',\
  en,'Open',\
  it,'Aperto',\
  et,'Ava',\
  sp,'Abrir'
lsz s_2save,\
  ru,'���࠭���',\
  en,'Save',\
  it,'Salva',\
  et,'Salvesta',\
  sp,'Guardar'
lsz s_2save_no,\
  ru,'���',\
  en,'No',\
  it,'No',\
  et,'Ei',\
  sp,'No'
lsz s_2find,\
  ru,'����',\
  en,'Find',\
  it,'Trova',\
  et,'Leia',\
  sp,'Buscar'
db ':'
lsz s_2replace,\
  ru,'��������',\
  en,'Replace',\
  it,'Sostituire',\
  et,'Asenda',\
  sp,'Reemplazar'
db ':'
lsz s_2cancel,\
  ru,'�⬥��',\
  en,'Cancel',\
  it,'Annulla',\
  et,'T�hista',\
  sp,'Cancelar'
lsz s_color,\
  ru,'����: 0x',\
  en,'Color: 0x',\
  it,'Colore: 0x',\
  et,'V�rv: 0x',\
  sp,'Color: 0x'
lsz s_tabpos,\
  ru,'��ᯮ������� ��������',\
  en,'Tabs placement',\
  it,'Posizionamento delle schede',\
  et,'Saki asetus',\
  sp,'Lugar de tabulador'

lsz s_enter_filename,\
  ru,<'������ ��� 䠩��',0>,\
  en,<'Enter filename',0>,\
  it,<'Inserisci il nome del file',0>,\
  et,<'Sisesta faili nimi',0>,\
  sp,<'Ingresa el nombre del archivo',0>

lsz s_ask_save,\
  ru,<'������ ��࠭���?',0>,\
  en,<'Would you like to save?',0>,\
  it,<'Vorresti salvare?',0>,\
  et,<'Kas soovite salvestada?',0>,\	; Now correct
  sp,<'�Quieres guardar?',0>

lsz s_enter_text_to_find,\
  ru,<'������ ⥪�� ��� ���᪠',0>,\
  en,<'Enter text to find',0>,\
  it,<'Inserisci il testo per trovare',0>,\
  et,<'Sisesta otsitav tekst',0>,\
  sp,<'Ingresa el texto a buscar',0>

lsz s_enter_text_to_replace,\
  ru,<'������ ⥪�� ��� ������',0>,\
  en,<'Enter text to replace',0>,\
  it,<'Inserisci il testo da sostituire',0>,\
  et,<'Sisesta asendatav tekst',0>,\
  sp,<'Ingresa el texto a reemplazar',0>

lsz s_text_not_found,\
  ru,<'���⨣��� ����� 䠩��, ⥪�� �� ������',0>,\
  en,<'Reached end of file, text not found',0>,\
  it,<'Raggiunta la fine del file, testo non trovato',0>,\
  et,<'Faili l�pp, teksti ei leitud',0>,\
  sp,<'Se lleg� al final del archivo, texto no encontrado',0>

lszc s_fs_error,b,\
  ru,<'������ �����襭� �ᯥ譮 (0)',0>,\
  ru,<'',0>,\
  ru,<'�㭪�� �� �����ন������ ��� ������ 䠩����� ��⥬� (2)',0>,\
  ru,<'�������⭠� 䠩����� ��⥬� (3)',0>,\
  ru,<'',0>,\
  ru,<'���������� ������ 䠩� (5)',0>,\
  ru,<'������ �����襭� �ᯥ譮 (6)',0>,\
  ru,<'���� ��室���� �� �࠭�栬� ����� �ணࠬ�� (7)',0>,\
  ru,<'�� ��᪥ ��� ᢮������� ���� (8)',0>,\
  ru,<'������ FAT 㭨�⮦��� (9)',0>,\
  ru,<'����� ������ (10)',0>,\
  ru,<'�訡�� ���ன�⢠ (11)',0>,\
\
  en,<'Operation executed successfully (0)',0>,\
  en,<'',0>,\
  en,<'Function is not supported for the given filesystem (2)',0>,\
  en,<'Unknown filesystem (3)',0>,\
  en,<'',0>,\
  en,<'Unable to open file (5)',0>,\
  en,<'Operation executed successfully (6)',0>,\
  en,<'Pointer lies outside of application memory (7)',0>,\
  en,<'Disk is full (8)',0>,\
  en,<'FAT table is destroyed (9)',0>,\
  en,<'Access denied (10)',0>,\
  en,<'Device error (11)',0>,\
\
  it,<'Operazione eseguita correttamente (0)',0>,\
  it,<'',0>,\
  it,<'La funzione non e supportata per il file system specificato (2)', 0>, \
  it,<'Unknown filesystem (3)',0>,\
  it,<'',0>,\
  it,<'Impossibile aprire il file (5)',0>,\
  it,<'Operazione eseguita correttamente (6)',0>,\
  it,<'Il puntatore si trova al di fuori della memoria dell',96,'applicazione (7)', 0>, \
  it,<'Il disco e pieno (8)',0>,\
  it,<'La tabella FAT e distrutta (9)',0>,\
  it,<'Accesso negato (10)',0>,\
  it,<'Errore dispositivo (11)',0>,\
\
  et,<'Operatsioon k�ivitati edukalt (0)',0>,\
  et,<'',0>,\
  et,<'Failis�steem ei toeta funktsiooni (2)',0>,\
  et,<'Tundmatu failis�steem (3)',0>,\
  et,<'',0>,\
  et,<'Faili ei suudetud avada (5)',0>,\
  et,<'Operatsioon k�ivitatud edukalt (6)',0>,\
  et,<'Viit on v�ljaspool programmi m�lu (7)',0>,\
  et,<'Ketas t�is (8)',0>,\
  et,<'FAT tabel h�vitatud (9)',0>,\
  et,<'Juurdep��s keelatud (10)',0>,\
  et,<'Seadme viga (11)',0>,\
\
  sp,<'Operaci�n ejecutada correctamente (0)',0>,\
  sp,<'',0>,\
  sp,<'La funci�n no est� soportada por el sistema de archivos dado (2)',0>,\
  sp,<'Sistema de archivos desconocido (3)',0>,\
  sp,<'',0>,\
  sp,<'No es posible abrir el archivo (5)',0>,\
  sp,<'Operaci�n ejecutada correctamente (6)',0>,\
  sp,<'El puntero est� fuera de la memoria de la aplicaci�n (7)',0>,\
  sp,<'El disco est� lleno (8)',0>,\
  sp,<'La tabla FAT est� destruida (9)',0>,\
  sp,<'Acceso denegado (10)',0>,\
  sp,<'Error de dispositivo (11)',0>

lszc s_appearance,b,\
  ru,'�����',\
  ru,'���',\
  ru,'����� �뤥�����',\
  ru,'��� �뤥�����',\
  ru,'�������',\
  ru,'��᫠',\
  ru,'��ப�',\
  ru,'�������ਨ',\
  ru,'������� ��ப�',\
  ru,'���࠭�� ��ப�',\
\
  en,'Text',\
  en,'Background',\
  en,'Selection text',\
  en,'Selection background',\
  en,'Symbols',\
  en,'Numbers',\
  en,'Strings',\
  en,'Comments',\
  en,'Modified lines',\
  en,'Saved lines',\
\
  it,'Testo',\
  it,'Sfondo',\
  it,'Testo di selezione',\
  it,'Sfondo di selezione',\
  it,'Simboli',\
  it,'Numeri',\
  it,'Stringhe',\
  it,'Commenti',\
  it,'Linee modificate',\
  it,'Linee salvate',\
\
  et,'Tekst',\
  et,'Taust',\
  et,'Valitud tekst',\
  et,'Valitud taust',\
  et,'S�mbolid',\
  et,'Numbrid',\
  et,'Stringid',\
  et,'Kommentaarid',\
  et,'Muudetud read',\
  et,'Salvestatud read',\
\
  sp,'Texto',\
  sp,'Fondo',\
  sp,'Texto de selecci�n',\
  sp,'Fondo de selecci�n',\
  sp,'S�mbolos',\
  sp,'N�meros',\
  sp,'Cadenas',\
  sp,'Comentarios',\
  sp,'L�neas modificadas',\
  sp,'L�neas guardadas'

lsz sysfuncs_filename,\
  ru,<'SYSFUNCR.TXT',0>,\
  en,<'SYSFUNCS.TXT',0>,\
  it,<'SYSFUNCS.TXT',0>,\
  et,<'SYSFUNCET.TXT',0>,\
  sp,<'SYSFUNCS.TXT',0>

sz s_example,'/sys/example.asm'
sz s_still  ,'still'
