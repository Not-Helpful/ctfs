; This program parses .fas file generated by fasm
; and prints the list of dependencies for make.
; Usage: fasmdep [-e] [<input file> [<output file>]].
; If input file is not given, the program reads from stdin.
; If output file is not given, the program writes to stdout.
; If the option -e is given, the program also creates an empty
; goal for every dependency, this prevents make errors when
; files are renamed.

; This definition controls the choice of platform-specific code.
;define OS WINDOWS
define OS LINUX

; Program header.
match =WINDOWS,OS { include 'windows_header.inc' }
match =LINUX,OS { include 'linux_header.inc' }

include 'fas.inc'

; Main code
start:
; 1. Setup stack frame, zero-initialize all local variables.
virtual at ebp - .localsize
.begin:
.flags          dd      ?       ; 1 if '-e' is given
.in             dd      ?       ; handle of input file
.out            dd      ?       ; handle of output file
.buf            dd      ?       ; pointer to data of .fas file
.allocated      dd      ?       ; number of bytes allocated for .buf
.free           dd      ?       ; number of bytes free in .buf
.outstart       dd      ?       ; offset in .buf for start of data to output
.names          dd      ?       ; offset in .buf for start of output names
.include        dd      ?       ; offset in .buf to value of %INCLUDE%
.testname       dd      ?       ; offset in .buf for start of current file name
.prevfile       dd      ?       ; offset in .buf for previous included file name
.prevfilefrom   dd      ?       ; offset in .buf for .asm/.inc for .prevfile
.localsize = $ - .begin
match =LINUX,OS {
.argc           dd      ?
.argv:
}
end virtual

        mov     ebp, esp
        xor     eax, eax
repeat .localsize / 4
        push    eax
end repeat
; 2. Call the parser of the command line.
        call    get_params
; 3. Load the input file.
; Note that stdin can be a pipe,
; useful in bash-construction "fasm input.asm -s >(fasmdep > input.Po)",
; so its size is not always known in the beginning.
; So, we must read input file in portions, reallocating memory if needed.
.readloop:
; 3a. If the size is less than 32768 bytes, reallocate buffer.
; Otherwise, goto 3c.
        cmp     [.free], 32768
        jae     .norealloc
; 3b. Reallocate buffer.
; Start with 65536 bytes and then double the size every time.
        mov     eax, 65536
        mov     ecx, [.allocated]
        add     ecx, ecx
        jz      @f
        mov     eax, ecx
@@:
        call    realloc
.norealloc:
; 3c. Read the next portion.
        call    read
        sub     [.free], eax
        test    eax, eax
        jnz     .readloop
; 4. Sanity checks.
; We don't use .section_* and .symref_*, so allow them to be absent.
        mov     edi, [.allocated]
        sub     edi, [.free]
; Note that edi = number of bytes which were read
; and simultaneously pointer to free space in the buffer relative to [.buf].
        cmp     edi, fas_header.section_offs
        jb      badfile
        mov     ebx, [.buf]
        cmp     [ebx+fas_header.signature], FAS_SIGNATURE
        jnz     badfile
        cmp     [ebx+fas_header.headersize], fas_header.section_offs
        jb      badfile
; 5. Get %INCLUDE% environment variable, it will be useful.
        mov     [.include], edi
        mov     esi, include_variable
        sub     esi, ebx
        call    get_environment_variable
; 6. Start writing dependencies: copy output and input files.
        mov     [.outstart], edi
; 6a. Copy output name.
        mov     esi, [ebx+fas_header.output]
        call    copy_asciiz_escaped
; 6b. Write ": ".
        stdcall alloc_in_buf, 2
        mov     word [edi+ebx], ': '
        inc     edi
        inc     edi
; 6c. Copy input name.
        mov     [.names], edi
        mov     esi, [ebx+fas_header.input]
        call    copy_asciiz_escaped
; 7. Scan for 'include' dependencies.
; 7a. Get range for scanning.
        mov     edx, [ebx+fas_header.preproc_size]
        mov     esi, [ebx+fas_header.preproc_offs]
        add     edx, esi
.include_loop:
; 7b. Loop over preprocessed lines in the range.
        cmp     esi, edx
        jae     .include_done
; 7c. For every line, ignore header and do internal loop over tokens.
        add     esi, preproc_line_header.contents
.include_loop_int:
; There are five types of tokens:
; 1) "start preprocessor data" with code ';' <byte length> <length*byte token>
; 2) "quoted string" with code '"' <dword length> <length*byte string>
; 3) "word" with code 1Ah <byte length> <length*byte word>
; 4) one-byte tokens like "+", "(" and so on
; 5) "end-of-line" token with code 0.
        mov     al, [esi+ebx]
        inc     esi
; 7d. First, check token type parsing the first byte.
; For preprocessor tokens, continue to 7e.
; For quoted strings, go to 7g.
; For words, go to 7h.
; For end-of-line, exit the internal loop, continue the external loop.
; Otherwise, just continue the internal loop.
        cmp     al, ';'
        jnz     .notprep
; 7e. For "include" tokens length=7, token is "include", the next token is
; quoted string.
; These tokens are handled in 7f, other preprocessor tokens in 7g.
        cmp     byte [esi+ebx], 7
        jnz     .notinclude
        cmp     dword [esi+ebx+1], 'incl'
        jnz     .notinclude
        cmp     dword [esi+ebx+5], 'ude"'
        jnz     .notinclude
; 7f. Skip over end of this token and the type byte of the next token;
; this gives the pointer to length-prefixed string, which should be added
; to dependencies. Note that doing that skips that string,
; so after copying just continue the internal loop.
        add     esi, 9
        call    add_separator
        call    copy_name_escaped
        jmp     .include_loop_int
.quoted:
; 7g. To skip a word, load the dword length and add it to pointer.
        add     esi, [esi+ebx]
        add     esi, 4
        jmp     .include_loop_int
.notinclude:
; 7h. To skip this token, load the byte length and add it to pointer.
; Note that word tokens and preprocessor tokens have a similar structure,
; so both are handled here.
        movzx   eax, byte [esi+ebx]
        lea     esi, [esi+eax+1]
        jmp     .include_loop_int
.notprep:
        cmp     al, 1Ah
        jz      .notinclude
        cmp     al, '"'
        jz      .quoted
        test    al, al
        jnz     .include_loop_int
        jmp     .include_loop
.include_done:
; 8. Scan for 'file' dependencies.
; 8a. Get range for scanning.
; Note that fas_header.asm_size can be slighly greater than the
; real size, so we break from the loop when there is no space left
; for the entire asm_row structure, not when .asm_size is exactly reached.
        mov     esi, [ebx+fas_header.asm_offs]
        mov     edx, [ebx+fas_header.asm_size]
        add     edx, esi
        sub     edx, asm_row.sizeof
        push    edx
        jc      .file_done
.file_loop:
; 8b. Loop over assembled lines in the range.
        cmp     esi, [esp]
        ja      .file_done
; 8c. For every assembled line, skip "word" and one-byte tokens
; scanning for three predefined word tokens.
; Note that lines like "a:b:c:d file 'something'" are possible and valid.
; go to 8d for token 'file',
; go to 8e for token 'format',
; go to 8f for token 'section',
; continue the loop otherwise.
        mov     eax, [esi+ebx+asm_row.preproc_offs]
        add     eax, [ebx+fas_header.preproc_offs]
; We save/restore esi since it is used for another thing in the internal loop;
; we push eax, which currently contains ebx-relative pointer to
; preproc_line_header, to be able to access it from resolve_name.
        push    esi eax
.file_tokens_loop:
        mov     cl, byte [eax+ebx+preproc_line_header.contents]
        cmp     cl, 1Ah
        jnz     .file_noword_token
        movzx   ecx, byte [eax+ebx+preproc_line_header.contents+1]
        cmp     cl, 4
        jnz     .file_no_file
        cmp     dword [eax+ebx+preproc_line_header.contents+2], 'file'
        jnz     .file_no_file4
; 8d. For lines starting with 'file' token, loop over tokens and get names.
; Note that there can be several names in one line.
; Parsing of tokens is similar to step 5 with the difference that
; preprocessor token stops processing: 'file' directives are processed
; in assembler stage.
        lea     esi, [eax+preproc_line_header.contents+6]
.file_loop_int:
        mov     al, [esi+ebx]
        inc     esi
        test    al, al
        jz      .file_next
        cmp     al, ';'
        jz      .file_next
        cmp     al, 1Ah
        jz      .fileword
        cmp     al, '"'
        jnz     .file_loop_int
        call    resolve_name
        add     esi, [esi+ebx-4]
        jmp     .file_loop_int
.fileword:
        movzx   eax, byte [esi+ebx]
        lea     esi, [esi+eax+1]
        jmp     .file_loop_int
.file_no_file4:
        cmp     dword [eax+ebx+preproc_line_header.contents+2], 'data'
        jnz     .file_word_token
        jmp     .file_scan_from
.file_no_file:
        cmp     cl, 6
        jnz     .file_no_format
        cmp     dword [eax+ebx+preproc_line_header.contents+2], 'form'
        jnz     .file_no_format
        cmp     word [eax+ebx+preproc_line_header.contents+6], 'at'
        jnz     .file_no_format
; 8e. For lines starting with 'format' token, loop over tokens and look for stub name.
; Note that there can be another quoted string, namely file extension;
; stub name always follows the token 'on'.
        mov     edx, TokenOn
        call    scan_after_word
        jmp     .file_next
.file_no_format:
        cmp     cl, 7
        jnz     .file_no_section
        cmp     dword [eax+ebx+preproc_line_header.contents+2], 'sect'
        jnz     .file_no_section
        mov     edx, dword [eax+ebx+preproc_line_header.contents+6]
        and     edx, 0FFFFFFh
        cmp     edx, 'ion'
        jnz     .file_no_section
.file_scan_from:
        mov     edx, TokenFrom
        call    scan_after_word
        jmp     .file_next
.file_no_section:
.file_word_token:
        lea     eax, [eax+ecx+2]
        jmp     .file_tokens_loop
.file_noword_token:
        inc     eax
        test    cl, cl
        jz      .file_next
        cmp     cl, 3Bh
        jz      .file_next
        cmp     cl, 22h
        jnz     .file_tokens_loop
.file_next:
        pop     eax esi
        add     esi, asm_row.sizeof
        jmp     .file_loop
.file_done:
        pop     edx
; 9. Write result.
; 9a. Append two newlines to the end of buffer.
        stdcall alloc_in_buf, 2
        mov     word [edi+ebx], 10 * 101h
        inc     edi
        inc     edi
; 9b. If '-e' option was given, duplicate dependencies list as fake goals
; = copy all of them and append ":\n\n".
        cmp     [.flags], 0
        jz      .nodup
        lea     ecx, [edi+1]
        mov     esi, [.names]
        sub     ecx, esi
        stdcall alloc_in_buf, ecx
        add     esi, ebx
        add     edi, ebx
        rep     movsb
        mov     byte [edi-3], ':'
        mov     word [edi-2], 10 * 101h
        sub     edi, ebx
.nodup:
; 9c. Write to output file.
        mov     eax, [.outstart]
        sub     edi, eax
        add     eax, ebx
        call    write
; 10. Exit.
        xor     eax, eax
        call    exit

; Helper procedure for steps 8e and 8f of main algorithm.
; Looks for quoted strings after given word in edx.
scan_after_word:
        push    esi eax
        lea     esi, [eax+preproc_line_header.contents+2+ecx]
.loop:
        xor     ecx, ecx
.loop_afterword:
        mov     al, [esi+ebx]
        inc     esi
        test    al, al
        jz      .loop_done
        cmp     al, ';'
        jz      .loop_done
        cmp     al, 1Ah
        jz      .word
        cmp     al, '"'
        jnz     .loop
        test    ecx, ecx
        jz      .skip_quoted
        call    resolve_name
.loop_done:
        pop     eax esi
        ret
.skip_quoted:
        add     esi, [esi+ebx]
        add     esi, 4
        jmp     .loop
.word:
        movzx   ecx, byte [esi+ebx]
        lea     esi, [esi+ecx+1]
        cmp     cl, byte [edx]
        jnz     .loop
        push    esi edi
        add     esi, ebx
        sub     esi, ecx
        lea     edi, [edx+1]
        repz    cmpsb
        pop     edi esi
        jnz     .loop
        dec     ecx
        jmp     .loop_afterword

; Helper procedure for step 6 of the main procedure.
; Copies the ASCIIZ name from strings section to the buffer.
copy_asciiz_escaped:
        add     esi, [ebx+fas_header.strings_offs]
.loop:
        mov     al, [esi+ebx]
        test    al, al
        jz      .nothing
        call    copy_char_escaped
        jmp     .loop
.nothing:
        ret

; Helper procedure for step 7 of the main procedure.
; Copies the name with known length to the buffer.
copy_name_escaped:
        mov     ecx, [esi+ebx]
        add     esi, 4
        test    ecx, ecx
        jz      .nothing
        push    ecx
.loop:
        mov     al, [esi+ebx]
        call    copy_char_escaped
        dec     dword [esp]
        jnz     .loop
        pop     ecx
.nothing:
        ret

; Helper procedure for steps 7 and 8 of the main procedure.
; Writes separator of file names in output = " \\\n".
add_separator:
        stdcall alloc_in_buf, 3
        mov     word [edi+ebx], ' \'
        mov     byte [edi+ebx+2], 10
        add     edi, 3
        ret

; Helper procedure for step 7 of the main procedure.
; Resolves the path to 'file' dependency and copies
; the full name to the buffer.
resolve_name:
; FASM uses the following order to search for referenced files:
; * path of currently assembling file, which may be .asm or .inc
; * paths from %INCLUDE% for versions >= 1.70
; * current directory = file name is taken as is, without prepending dir name
; We mirror this behaviour, trying to find an existing file somewhere.
; There can be following reasons for the file can not be found anywhere:
; * it has been deleted between compilation and our actions
; * it didn't exist at all, compilation has failed
; * we are running in environment different from fasm environment.
; Assume that the last reason is most probable and that invalid dependency
; is better than absent dependency (it is easier to fix an explicit error
; than a silent one) and output file name without prepending dir name,
; as in the last case. Actually, we even don't need to test existence
; of the file in the current directory.
        add     esi, 4  ; skip string length
; 1. Get ebx-relative pointer to preproc_line_header, see the comment in start.7d
        mov     eax, [esp+4]
; 2. Get the path to currently processing file.
        push    esi
.getpath:
        test    byte [eax+ebx+preproc_line_header.line_number+3], 80h
        jz      @f
        mov     eax, [eax+ebx+preproc_line_header.line_offset]
        add     eax, [ebx+fas_header.preproc_offs]
        jmp     .getpath
@@:
        mov     edx, [eax+ebx+preproc_line_header.source_name]
        test    edx, edx
        jz      .frommain
        add     edx, [ebx+fas_header.preproc_offs]
        jmp     @f
.frommain:
        mov     edx, [ebx+fas_header.input]
        add     edx, [ebx+fas_header.strings_offs]
@@:
; 3. Check that it is not a duplicate of the previous dependency.
; 3a. Compare preprocessor units.
        cmp     edx, [start.prevfilefrom]
        jnz     .nodup
; 3b. Compare string lengths.
        mov     eax, [start.prevfile]
        mov     ecx, [eax+ebx-4]
        cmp     ecx, [esi+ebx-4]
        jnz     .nodup
; 3c. Compare string contents.
        push    esi edi
        lea     edi, [eax+ebx]
        add     esi, ebx
        rep     cmpsb
        pop     edi esi
        jnz     .nodup
; 3d. It is duplicate, just return.
        pop     esi
        ret
.nodup:
; 3e. It is not duplicate. Output separator.
        mov     [start.prevfilefrom], edx
        mov     [start.prevfile], esi
        call    add_separator
; 4. Cut the last component of the path found in step 2.
        mov     ecx, edx
        mov     esi, edx
.scanpath:
        mov     al, [edx+ebx]
        test    al, al
        jz      .scandone
        cmp     al, '/'
        jz      .slash
        cmp     al, '\'
        jnz     .scannext
.slash:
        lea     ecx, [edx+1]
.scannext:
        inc     edx
        jmp     .scanpath
.scandone:
        sub     ecx, esi
; 5. Try path found in step 4. If found, go to step 8.
        mov     [start.testname], edi
        stdcall copy_string, esi, ecx
        pop     esi
        call    expand_environment
        call    test_file_exists
        test    eax, eax
        jns     .found
        call    revert_testname
; 6. Try each of include paths. For every path, if file is found, go to step 8.
; Otherwise, continue loop over include path.
; Skip this step before 1.70.
        cmp     [ebx+fas_header.major], 1
        ja      .checkenv
        jb      .nocheckenv
        cmp     [ebx+fas_header.minor], 70
        jb      .nocheckenv
.checkenv:
        mov     ecx, [start.include]
.includeloop_ext:
        mov     eax, ecx
.includeloop_int:
        cmp     byte [eax+ebx], 0
        jz      @f
        cmp     byte [eax+ebx], ';'
        jz      @f
        inc     eax
        jmp     .includeloop_int
@@:
        push    eax
        sub     eax, ecx
        jz      @f
        stdcall copy_string, ecx, eax
        cmp     byte [edi+ebx-1], '/'
        jz      .hasslash
@@:
        stdcall alloc_in_buf, 1
        mov     byte [edi+ebx], '/'
        inc     edi
.hasslash:
        call    expand_environment
        call    test_file_exists
        pop     ecx
        test    eax, eax
        jns     .found
        call    revert_testname
        cmp     byte [ecx+ebx], 0
        jz      .notfound
        inc     ecx
        cmp     byte [ecx+ebx], 0
        jnz     .includeloop_ext
.nocheckenv:
.notfound:
; 7. File not found neither near the current preprocessor unit nor in %INCLUDE%.
; Assume that it is in the current directory.
        call    expand_environment
.found:
; 8. Currently we have file name from [start.testname] to edi;
; it is zero-terminated and not space-escaped. Fix both issues.
        dec     edi
        inc     [start.free]
        push    esi
        mov     edx, [start.testname]
.escapeloop:
        cmp     edx, edi
        jae     .escapedone
        cmp     byte [edx+ebx], ' '
        jnz     .noescape
        stdcall alloc_in_buf, 1
        mov     ecx, edi
        sub     ecx, edx
        push    edi
        add     edi, ebx
        lea     esi, [edi-1]
        std
        rep     movsb
        cld
        pop     edi
        inc     edi
        mov     byte [edx+ebx], '\'
        inc     edx
.noescape:
        inc     edx
        jmp     .escapeloop
.escapedone:
        pop     esi
        ret

; Helper procedure for resolve_name.
; Allocates space in the buffer and appends the given string to the buffer.
copy_string:
        mov     eax, [esp+8]
        test    eax, eax
        jz      .nothing
        stdcall alloc_in_buf, eax
        mov     ecx, [esp+4]
.copy:
        mov     al, [ecx+ebx]
        inc     ecx
        cmp     al, '\'
        jnz     @f
        mov     al, '/'
@@:
        mov     [edi+ebx], al
        inc     edi
        dec     dword [esp+8]
        jnz     .copy
.nothing:
        ret     8

; Helper procedure for resolve_name. Undoes appending of last file name.
revert_testname:
        add     [start.free], edi
        mov     edi, [start.testname]
        sub     [start.free], edi
        ret

; Helper procedure for resolve_name. Copies string from esi to edi,
; expanding environment variables.
expand_environment:
; 1. Save esi to restore it in the end of function.
        push    esi
; 2. Push string length to the stack to be used as a variable.
        pushd   [esi+ebx-4]
; 3. Scan loop.
.scan:
; 3a. Scan for '%' sign.
        call    find_percent
.justcopy:
; 3b. Copy the part from the beginning of current portion to '%' sign,
; advance pointer to '%' sign, or end-of-string if no '%' found.
        push    eax
        sub     eax, esi
        stdcall copy_string, esi, eax
        pop     esi
; 3c. If string has ended, break from the loop.
        cmp     dword [esp], 0
        jz      .scandone
; 3d. Advance over '%' sign.
        inc     esi
        dec     dword [esp]
; 3e. Find paired '%'.
        call    find_percent
; 3f. If there is no paired '%', just return to 3b and copy remaining data,
; including skipped '%'; after that, 3c would break from the loop.
        dec     esi
        cmp     dword [esp], 0
        jz      .justcopy
; 3g. Otherwise, get the value of environment variable.
; Since get_environment_variable requires zero-terminated string
; and returns zero-terminated string, temporarily overwrite trailing '%'
; and ignore last byte in returned string.
; Also convert any backslashes to forward slashes.
        inc     esi
        mov     byte [eax+ebx], 0
        push    eax
        push    edi
        call    get_environment_variable
        dec     edi
        inc     [start.free]
        pop     eax
.replaceslash:
        cmp     eax, edi
        jz      .replaceslash_done
        cmp     byte [eax+ebx], '\'
        jnz     @f
        mov     byte [eax+ebx], '/'
@@:
        inc     eax
        jmp     .replaceslash
.replaceslash_done:
        pop     esi
        mov     byte [esi+ebx], '%'
; 3h. Advance over trailing '%'.
        inc     esi
        dec     dword [esp]
; 3i. Continue the loop.
        jmp     .scan
.scandone:
; 4. Zero-terminate resulting string.
        stdcall alloc_in_buf, 1
        mov     byte [edi+ebx], 0
        inc     edi
; 5. Pop stack variable initialized in step 2.
        pop     eax
; 6. Restore esi saved in step 1 and return.
        pop     esi
        ret

; Helper procedure for expand_environment.
; Scans the string in esi with length [esp+4]
; until '%' is found or line ended.
find_percent:
        mov     eax, esi
        cmp     dword [esp+4], 0
        jz      .nothing
.scan:
        cmp     byte [eax+ebx], '%'
        jz      .nothing
        inc     eax
        dec     dword [esp+4]
        jnz     .scan
.nothing:
        ret

; Helper procedure for copy_{name,asciiz}_escaped.
; Allocates space and writes one character, possibly escaped.
copy_char_escaped:
        cmp     al, ' '
        jnz     .noescape
        stdcall alloc_in_buf, 1
        mov     byte [edi+ebx], '\'
        inc     edi
.noescape:
        stdcall alloc_in_buf, 1
        mov     al, [esi+ebx]
        inc     esi
        cmp     al, '\'
        jnz     @f
        mov     al, '/'
@@:
        mov     [edi+ebx], al
        inc     edi
        ret

; Helper procedure for ensuring that there is at least [esp+4]
; free bytes in the buffer.
alloc_in_buf:
        mov     eax, [esp+4]
        sub     [start.free], eax
        jb      .need_realloc
        ret     4
.need_realloc:
        mov     eax, [start.allocated]
        add     eax, eax
        push    ecx edx
        call    realloc
        pop     edx ecx
        cmp     [start.free], 0
        jl      .need_realloc
        mov     ebx, [start.buf]
        ret     4

badfile:
        mov     esi, badfile_string
        call    sayerr
        mov     al, 1
        call    exit

information:
        mov     esi, information_string
        call    sayerr
        mov     al, 2
        call    exit

nomemory:
        mov     esi, nomemory_string
        call    sayerr
        mov     al, 3
        call    exit

in_openerr:
        mov     esi, in_openerr_string
        jmp     in_err
readerr:
        mov     esi, readerr_string
in_err:
        call    sayerr
        mov     al, 4
        call    exit

out_openerr:
        mov     esi, out_openerr_string
        jmp     out_err
writeerr:
        mov     esi, writeerr_string
out_err:
        call    sayerr
        mov     al, 5
        call    exit

; Platform-specific procedures.
match =WINDOWS,OS { include 'windows_sys.inc' }
match =LINUX,OS { include 'linux_sys.inc' }

; Data
macro string a, [b] {
common
        db      a ## _end - a
a       db      b
a ## _end:
}

string information_string, 'Usage: fasmdep [-e] [<input.fas> [<output.Po>]]',10
string badfile_string, 'Not .fas file',10
string nomemory_string, 'No memory',10
string in_openerr_string, 'Cannot open input file',10
string readerr_string, 'Read error',10
string out_openerr_string, 'Cannot create output file',10
string writeerr_string, 'Write error',10

include_variable        db      'INCLUDE',0
TokenOn         db      2,'on'
TokenFrom       db      4,'from'
