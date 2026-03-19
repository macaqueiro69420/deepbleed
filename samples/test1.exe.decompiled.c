/*
 * ═══════════════════════════════════════════════════
 *  DEEP_BLEED Decompilation Output
 *  Binary:  test1.exe
 *  Arch:    X86_64
 *  Base:    0x140000000
 *  Entry:   0x140001410
 *  main():  0x140001190
 *  Functions: 94 (user: 94, external: 0)
 * ═══════════════════════════════════════════════════
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ═══ String References ═══ */
/* 0x140009000 = "Hello DeepBleed C: %d\n" */
/* 0x140009080 = "Argument domain error (DOMAIN)" */
/* 0x14000909F = "Argument singularity (SIGN)" */
/* 0x1400090C0 = "Overflow range error (OVERFLOW)" */
/* 0x1400090E0 = "Partial loss of significance (PLOSS)" */
/* 0x140009108 = "Total loss of significance (TLOSS)" */
/* 0x140009130 = "The result is too small to be represented (UNDERFLOW)" */
/* 0x140009166 = "Unknown error" */
/* 0x140009178 = "_matherr(): %s in %s(%g, %g)  (retval=%g)\n" */
/* 0x1400091C0 = "Mingw-w64 runtime failure:\n" */
/* 0x1400091E0 = "Address %p has no image-section" */
/* 0x140009200 = "  VirtualQuery failed for %d bytes at address %p" */
/* 0x140009238 = "  VirtualProtect failed with code 0x%x" */
/* 0x140009260 = "  Unknown pseudo relocation protocol version %d.\n" */
/* 0x140009298 = "  Unknown pseudo relocation bit size %d.\n" */
/* 0x1400092C8 = "%d bit pseudo relocation at %p out of range, targeting %p, yielding the value %p..." */
/* 0x140009350 = "(null)" */
/* 0x140009358 = "L\"(null)\"" */
/* 0x1400094E0 = "Infinity" */
/* 0x1400095FC = "vH7B" */
/* 0x14000962C = "W4vC" */
/* 0x1400098A0 = "GCC: (GNU) 13-win32" */
/* 0x1400098C0 = "GCC: (GNU) 13-win32" */
/* 0x1400098E0 = "GCC: (GNU) 13-win32" */
/* 0x140009900 = "GCC: (GNU) 13-win32" */
/* 0x140009920 = "GCC: (GNU) 13-win32" */
/* 0x140009940 = "GCC: (GNU) 13-win32" */
/* 0x140009960 = "GCC: (GNU) 13-win32" */
/* 0x140009980 = "GCC: (GNU) 13-win32" */
/* 0x1400099A0 = "GCC: (GNU) 13-win32" */
/* 0x1400099C0 = "GCC: (GNU) 13-win32" */
/* 0x1400099E0 = "GCC: (GNU) 13-win32" */
/* 0x140009A00 = "GCC: (GNU) 13-win32" */
/* 0x140009A20 = "GCC: (GNU) 13-win32" */
/* 0x140009A40 = "GCC: (GNU) 13-win32" */
/* 0x140009A60 = "GCC: (GNU) 13-win32" */
/* 0x140009A80 = "GCC: (GNU) 13-win32" */
/* 0x140009AA0 = "GCC: (GNU) 13-win32" */
/* 0x140009AC0 = "GCC: (GNU) 13-win32" */
/* 0x140009AE0 = "GCC: (GNU) 13-win32" */
/* 0x140009B00 = "GCC: (GNU) 13-win32" */
/* 0x140009B20 = "GCC: (GNU) 13-win32" */
/* 0x140009B40 = "GCC: (GNU) 13-win32" */
/* 0x140009B60 = "GCC: (GNU) 13-win32" */
/* 0x140009B80 = "GCC: (GNU) 13-win32" */
/* 0x140009BA0 = "GCC: (GNU) 13-win32" */
/* 0x140009BC0 = "GCC: (GNU) 13-win32" */
/* 0x140009BE0 = "GCC: (GNU) 13-win32" */
/* 0x140009C00 = "GCC: (GNU) 13-win32" */
/* 0x140009C20 = "GCC: (GNU) 13-win32" */
/* 0x140009C40 = "GCC: (GNU) 13-win32" */
/* 0x140009C60 = "GCC: (GNU) 13-win32" */
/* 0x140009C80 = "GCC: (GNU) 13-win32" */
/* 0x140009CA0 = "GCC: (GNU) 13-win32" */
/* 0x140009CC0 = "GCC: (GNU) 13-win32" */
/* 0x140009CE0 = "GCC: (GNU) 13-win32" */
/* 0x140009D00 = "GCC: (GNU) 13-win32" */
/* 0x140009D20 = "GCC: (GNU) 13-win32" */
/* 0x140009D40 = "GCC: (GNU) 13-win32" */
/* 0x140009D60 = "GCC: (GNU) 13-win32" */
/* 0x140009D80 = "GCC: (GNU) 13-win32" */
/* 0x14000D352 = "DeleteCriticalSection" */
/* 0x14000D36A = "EnterCriticalSection" */
/* 0x14000D382 = "GetLastError" */
/* 0x14000D392 = "InitializeCriticalSection" */
/* 0x14000D3AE = "IsDBCSLeadByteEx" */
/* 0x14000D3C2 = "LeaveCriticalSection" */
/* 0x14000D3DA = "MultiByteToWideChar" */
/* 0x14000D3F0 = "SetUnhandledExceptionFilter" */
/* 0x14000D40E = "Sleep" */
/* 0x14000D416 = "TlsGetValue" */
/* 0x14000D424 = "VirtualProtect" */
/* 0x14000D436 = "VirtualQuery" */
/* 0x14000D446 = "WideCharToMultiByte" */
/* 0x14000D45C = "__C_specific_handler" */
/* 0x14000D474 = "___lc_codepage_func" */
/* 0x14000D48A = "___mb_cur_max_func" */
/* 0x14000D4A0 = "__getmainargs" */
/* 0x14000D4B0 = "__initenv" */
/* 0x14000D4BC = "__iob_func" */
/* 0x14000D4CA = "__set_app_type" */
/* 0x14000D4DC = "__setusermatherr" */
/* 0x14000D4F0 = "_amsg_exit" */
/* 0x14000D4FE = "_cexit" */
/* 0x14000D508 = "_commode" */
/* 0x14000D514 = "_errno" */
/* 0x14000D51E = "_fmode" */
/* 0x14000D528 = "_initterm" */
/* 0x14000D534 = "_lock" */
/* 0x14000D53C = "_onexit" */
/* 0x14000D546 = "_unlock" */
/* 0x14000D550 = "abort" */
/* 0x14000D558 = "calloc" */
/* 0x14000D562 = "exit" */
/* 0x14000D56A = "fprintf" */
/* 0x14000D574 = "fputc" */
/* 0x14000D57C = "free" */
/* 0x14000D584 = "fwrite" */
/* 0x14000D58E = "localeconv" */
/* 0x14000D59C = "malloc" */
/* 0x14000D5A6 = "memcpy" */
/* 0x14000D5B0 = "memset" */
/* 0x14000D5BA = "signal" */
/* 0x14000D5C4 = "strerror" */
/* 0x14000D5D0 = "strlen" */
/* 0x14000D5DA = "strncmp" */
/* 0x14000D5E4 = "vfprintf" */
/* 0x14000D5F0 = "wcslen" */
/* 0x14000D62C = "KERNEL32.dll" */
/* 0x14000D6C4 = "msvcrt.dll" */

/* ═══ Forward Declarations ═══ */
void __tmainCRTStartup(int argc, char** argv, char** envp); /* MAIN @ 0x140001190 */
void mainCRTStartup(void); /* ENTRY_POINT @ 0x140001410 */
void atexit(int param_1, int param_2, int param_3, int param_4); /* USER @ 0x140001440 */
void printf(int param_1, int param_2, int param_3, int param_4); /* USER @ 0x140001480 */
void add(int param_1, int param_2); /* USER @ 0x1400014D4 */
int __cdecl main(void); /* USER @ 0x1400014E8 */
void __main(void); /* USER @ 0x1400015F0 */
void _setargv(int param_1, int param_2); /* USER @ 0x140001610 */
void _fpreset(int param_1, int param_2, int param_3); /* USER @ 0x1400017F0 */
void __report_error(int param_1, int param_2, int param_3); /* USER @ 0x140001800 */
void mark_section_writable(void); /* USER @ 0x140001870 */
void _pei386_runtime_relocator(int param_1, int param_2); /* USER @ 0x1400019E0 */
void __mingw_setusermatherr(void); /* USER @ 0x140001D80 */
void __mingwthr_run_key_dtors_part_0(void); /* USER @ 0x140001F50 */
void __mingw_TLScallback(void); /* USER @ 0x1400020F0 */
void __mingw_GetSectionForAddress(void); /* USER @ 0x140002320 */
int __mingw_GetSectionCount(void); /* USER @ 0x1400023A0 */
void _GetPEImageBase(void); /* USER @ 0x140002460 */
void ___chkstk_ms(void); /* USER @ 0x1400025F0 */
void __mingw_vfprintf(void); /* USER @ 0x140002630 */
void __pformat_cvt(void); /* USER @ 0x140002680 */
void __pformat_putc(void); /* USER @ 0x140002770 */
void __pformat_wputchars(void); /* USER @ 0x1400027D0 */
void __pformat_putchars(void); /* USER @ 0x140002970 */
void __pformat_puts(void); /* USER @ 0x140002AC0 */
void __pformat_emit_inf_or_nan(void); /* USER @ 0x140002B10 */
void __pformat_xint_isra_0(int param_1); /* USER @ 0x140002BB0 */
void __pformat_int_isra_0(int param_1); /* USER @ 0x1400030D0 */
void __pformat_emit_radix_point(void); /* USER @ 0x140003480 */
void __pformat_emit_float(void); /* USER @ 0x1400035D0 */
void __pformat_emit_efloat(void); /* USER @ 0x1400039B0 */
void __pformat_efloat(void); /* USER @ 0x140003A90 */
void __pformat_float(void); /* USER @ 0x140003B30 */
void __pformat_gfloat(void); /* USER @ 0x140003C10 */
void __pformat_emit_xfloat_isra_0(void); /* USER @ 0x140003D70 */
void __mingw_pformat(void); /* USER @ 0x140004230 */
void __rv_alloc_D2A(void); /* USER @ 0x140004C40 */
void __nrv_alloc_D2A(void); /* USER @ 0x140004C80 */
void __freedtoa(void); /* USER @ 0x140004D00 */
void __quorem_D2A(int param_1, int param_2, int param_3, int param_4); /* USER @ 0x140004D30 */
void __gdtoa(int param_1, int param_2, int param_3, int param_4); /* USER @ 0x140004EB0 */
void __rshift_D2A(void); /* USER @ 0x1400064D0 */
void __trailz_D2A(void); /* USER @ 0x1400065E0 */
void dtoa_lock(void); /* USER @ 0x140006620 */
void __Balloc_D2A(void); /* USER @ 0x140006760 */
void __Bfree_D2A(void); /* USER @ 0x140006860 */
void __multadd_D2A(void); /* USER @ 0x1400068D0 */
void __i2b_D2A(void); /* USER @ 0x140006990 */
void __mult_D2A(int param_1); /* USER @ 0x140006A50 */
void __pow5mult_D2A(void); /* USER @ 0x140006BC0 */
void __lshift_D2A(void); /* USER @ 0x140006D50 */
void __cmp_D2A(void); /* USER @ 0x140006E80 */
void __diff_D2A(void); /* USER @ 0x140006ED0 */
void __b2d_D2A(void); /* USER @ 0x1400070A0 */
char* strnlen(void); /* USER @ 0x140007300 */
void wcsnlen(void); /* USER @ 0x140007330 */
void __p__fmode(void); /* USER @ 0x140007360 */
void __p__commode(void); /* USER @ 0x140007370 */
void _lock_file(void); /* USER @ 0x140007380 */
void _unlock_file(void); /* USER @ 0x1400073F0 */
HANDLE mingw_set_invalid_parameter_handler(void); /* USER @ 0x140007470 */
void __acrt_iob_func(int param_1); /* USER @ 0x140007480 */
void __wcrtomb_cp(int param_1); /* USER @ 0x1400074B0 */
void wcrtomb(void); /* USER @ 0x140007540 */
void __mbrtowc_cp(int param_1, int param_2, int param_3, int param_4); /* USER @ 0x1400076A0 */
void mbrtowc(void); /* USER @ 0x1400077F0 */
void ___lc_codepage_func(void); /* USER @ 0x1400079F8 */
void ___mb_cur_max_func(void); /* USER @ 0x140007A00 */
void __getmainargs(void); /* USER @ 0x140007A08 */
void __iob_func(void); /* USER @ 0x140007A10 */
void __set_app_type(void); /* USER @ 0x140007A18 */
void _amsg_exit(void); /* USER @ 0x140007A28 */
void _cexit(void); /* USER @ 0x140007A30 */
void _errno(void); /* USER @ 0x140007A38 */
void _initterm(void); /* USER @ 0x140007A40 */
void _lock(void); /* USER @ 0x140007A48 */
void _onexit(void); /* USER @ 0x140007A50 */
void abort(void); /* USER @ 0x140007A60 */
void calloc(void); /* USER @ 0x140007A68 */
void exit(void); /* USER @ 0x140007A70 */
void fprintf(void); /* USER @ 0x140007A78 */
void fputc(void); /* USER @ 0x140007A80 */
void free(void); /* USER @ 0x140007A88 */
void fwrite(void); /* USER @ 0x140007A90 */
void localeconv(void); /* USER @ 0x140007A98 */
void malloc(void); /* USER @ 0x140007AA0 */
void memcpy(void); /* USER @ 0x140007AA8 */
void memset(void); /* USER @ 0x140007AB0 */
void signal(void); /* USER @ 0x140007AB8 */
char* strerror(void); /* USER @ 0x140007AC0 */
char* strlen(void); /* USER @ 0x140007AC8 */
char* strncmp(void); /* USER @ 0x140007AD0 */
void vfprintf(void); /* USER @ 0x140007AD8 */
void wcslen(void); /* USER @ 0x140007AE0 */

/* ═══════════════════════════════════════════════════
 * __tmainCRTStartup @ 0x140001190 (MAIN)
 * Blocks: 31 | SSA vars: 22
 * ═══════════════════════════════════════════════════ */
void __tmainCRTStartup(int argc, char** argv, char** envp) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t r12;
    int32_t rdi;
    int32_t rax;
    int32_t rsi;
    int32_t rcx;
    int32_t invalid;
    int32_t rdx;
    int32_t r13;
    uint64_t r8;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = rdi;
    [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
    if (t3 != 0) {
    }
    t3 = [rsi+0x0];
    if (t3 == 1) {
    }
    if (rdi == 0) {
    }
    t4 = [rax+0x0];
    if (t4 == 0) {
    }
    t7 = rdi - 8;
    strlen();
    t11 = &[rax+0x1];
    [r12+0x0] = malloc();
    t12 = 0 + 8;
    memcpy();
    /* compare t7 vs t12 */
    strlen();
    t11 = &[rax+0x1];
    [r12+0x0] = malloc();
    t6 = rbx + 8;
    memcpy();
    /* compare rdi vs t6 */
    t7 = rdi + r12;
    [rdi+0x0] = 0;
    *(DWORD*)0x14000C019 = r12;
    __main();
    t13 = *(DWORD*)0x14000C011;
    t4 = [rax+0x0];
    [rax+0x0] = t13;
    main();
    t10 = *(DWORD*)0x14000C006;
    *(DWORD*)0x14000C00A = t4;
    /* compare t10 vs t10 */
    do {
        t3 = rdi;
        [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
        if (t3 != 0) {
        }
        t3 = [rsi+0x0];
        if (t3 == 1) {
        }
        if (rdi == 0) {
        }
        t4 = [rax+0x0];
        if (t4 == 0) {
        }
        t7 = rdi - 8;
        strlen();
        t11 = &[rax+0x1];
        [r12+0x0] = malloc();
        t12 = 0 + 8;
        memcpy();
        /* compare t7 vs t12 */
        strlen();
        t11 = &[rax+0x1];
        [r12+0x0] = malloc();
        t6 = rbx + 8;
        memcpy();
        /* compare rdi vs t6 */
        t7 = rdi + r12;
        [rdi+0x0] = 0;
        *(DWORD*)0x14000C019 = r12;
        __main();
        t13 = *(DWORD*)0x14000C011;
        t4 = [rax+0x0];
        [rax+0x0] = t13;
        main();
        t10 = *(DWORD*)0x14000C006;
        *(DWORD*)0x14000C00A = t4;
        /* compare t10 vs t10 */
        do {
            t3 = rdi;
            [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
            if (t3 != 0) {
            }
            t3 = [rsi+0x0];
            if (t3 == 1) {
            }
            if (rdi == 0) {
            }
            t4 = [rax+0x0];
            if (t4 == 0) {
            }
            t7 = rdi - 8;
            strlen();
            t11 = &[rax+0x1];
            [r12+0x0] = malloc();
            t12 = 0 + 8;
            memcpy();
            /* compare t7 vs t12 */
            strlen();
            t11 = &[rax+0x1];
            [r12+0x0] = malloc();
            t6 = rbx + 8;
            memcpy();
            /* compare rdi vs t6 */
            t7 = rdi + r12;
            [rdi+0x0] = 0;
            *(DWORD*)0x14000C019 = r12;
            __main();
            t13 = *(DWORD*)0x14000C011;
            t4 = [rax+0x0];
            [rax+0x0] = t13;
            main();
            t10 = *(DWORD*)0x14000C006;
            *(DWORD*)0x14000C00A = t4;
            /* compare t10 vs t10 */
            do {
                t3 = rdi;
                [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                if (t3 != 0) {
                }
                t3 = [rsi+0x0];
                if (t3 == 1) {
                }
                if (rdi == 0) {
                }
                t4 = [rax+0x0];
                if (t4 == 0) {
                }
                t7 = rdi - 8;
                strlen();
                t11 = &[rax+0x1];
                [r12+0x0] = malloc();
                t12 = 0 + 8;
                memcpy();
                /* compare t7 vs t12 */
                strlen();
                t11 = &[rax+0x1];
                [r12+0x0] = malloc();
                t6 = rbx + 8;
                memcpy();
                /* compare rdi vs t6 */
                t7 = rdi + r12;
                [rdi+0x0] = 0;
                *(DWORD*)0x14000C019 = r12;
                __main();
                t13 = *(DWORD*)0x14000C011;
                t4 = [rax+0x0];
                [rax+0x0] = t13;
                main();
                t10 = *(DWORD*)0x14000C006;
                *(DWORD*)0x14000C00A = t4;
                /* compare t10 vs t10 */
                do {
                    t3 = rdi;
                    [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                    if (t3 != 0) {
                    }
                    t3 = [rsi+0x0];
                    if (t3 == 1) {
                    }
                    if (rdi == 0) {
                    }
                    t4 = [rax+0x0];
                    if (t4 == 0) {
                    }
                    t7 = rdi - 8;
                    strlen();
                    t11 = &[rax+0x1];
                    [r12+0x0] = malloc();
                    t12 = 0 + 8;
                    memcpy();
                    /* compare t7 vs t12 */
                    strlen();
                    t11 = &[rax+0x1];
                    [r12+0x0] = malloc();
                    t6 = rbx + 8;
                    memcpy();
                    /* compare rdi vs t6 */
                    t7 = rdi + r12;
                    [rdi+0x0] = 0;
                    *(DWORD*)0x14000C019 = r12;
                    __main();
                    t13 = *(DWORD*)0x14000C011;
                    t4 = [rax+0x0];
                    [rax+0x0] = t13;
                    main();
                    t10 = *(DWORD*)0x14000C006;
                    *(DWORD*)0x14000C00A = t4;
                    /* compare t10 vs t10 */
                    do {
                        t3 = rdi;
                        [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                        if (t3 != 0) {
                        }
                        t3 = [rsi+0x0];
                        if (t3 == 1) {
                        }
                        if (rdi == 0) {
                        }
                        t4 = [rax+0x0];
                        if (t4 == 0) {
                        }
                        t7 = rdi - 8;
                        strlen();
                        t11 = &[rax+0x1];
                        [r12+0x0] = malloc();
                        t12 = 0 + 8;
                        memcpy();
                        /* compare t7 vs t12 */
                        strlen();
                        t11 = &[rax+0x1];
                        [r12+0x0] = malloc();
                        t6 = rbx + 8;
                        memcpy();
                        /* compare rdi vs t6 */
                        t7 = rdi + r12;
                        [rdi+0x0] = 0;
                        *(DWORD*)0x14000C019 = r12;
                        __main();
                        t13 = *(DWORD*)0x14000C011;
                        t4 = [rax+0x0];
                        [rax+0x0] = t13;
                        main();
                        t10 = *(DWORD*)0x14000C006;
                        *(DWORD*)0x14000C00A = t4;
                        /* compare t10 vs t10 */
                        do {
                            t3 = rdi;
                            [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                            if (t3 != 0) {
                            }
                            t3 = [rsi+0x0];
                            if (t3 == 1) {
                            }
                            if (rdi == 0) {
                            }
                            t4 = [rax+0x0];
                            if (t4 == 0) {
                            }
                            t7 = rdi - 8;
                            strlen();
                            t11 = &[rax+0x1];
                            [r12+0x0] = malloc();
                            t12 = 0 + 8;
                            memcpy();
                            /* compare t7 vs t12 */
                            strlen();
                            t11 = &[rax+0x1];
                            [r12+0x0] = malloc();
                            t6 = rbx + 8;
                            memcpy();
                            /* compare rdi vs t6 */
                            t7 = rdi + r12;
                            [rdi+0x0] = 0;
                            *(DWORD*)0x14000C019 = r12;
                            __main();
                            t13 = *(DWORD*)0x14000C011;
                            t4 = [rax+0x0];
                            [rax+0x0] = t13;
                            main();
                            t10 = *(DWORD*)0x14000C006;
                            *(DWORD*)0x14000C00A = t4;
                            /* compare t10 vs t10 */
                            do {
                                t3 = rdi;
                                [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                if (t3 != 0) {
                                }
                                t3 = [rsi+0x0];
                                if (t3 == 1) {
                                }
                                if (rdi == 0) {
                                }
                                t4 = [rax+0x0];
                                if (t4 == 0) {
                                }
                                t7 = rdi - 8;
                                strlen();
                                t11 = &[rax+0x1];
                                [r12+0x0] = malloc();
                                t12 = 0 + 8;
                                memcpy();
                                /* compare t7 vs t12 */
                                strlen();
                                t11 = &[rax+0x1];
                                [r12+0x0] = malloc();
                                t6 = rbx + 8;
                                memcpy();
                                /* compare rdi vs t6 */
                                t7 = rdi + r12;
                                [rdi+0x0] = 0;
                                *(DWORD*)0x14000C019 = r12;
                                __main();
                                t13 = *(DWORD*)0x14000C011;
                                t4 = [rax+0x0];
                                [rax+0x0] = t13;
                                main();
                                t10 = *(DWORD*)0x14000C006;
                                *(DWORD*)0x14000C00A = t4;
                                /* compare t10 vs t10 */
                                do {
                                    t3 = rdi;
                                    [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                    if (t3 != 0) {
                                    }
                                    t3 = [rsi+0x0];
                                    if (t3 == 1) {
                                    }
                                    if (rdi == 0) {
                                    }
                                    t4 = [rax+0x0];
                                    if (t4 == 0) {
                                    }
                                    t7 = rdi - 8;
                                    strlen();
                                    t11 = &[rax+0x1];
                                    [r12+0x0] = malloc();
                                    t12 = 0 + 8;
                                    memcpy();
                                    /* compare t7 vs t12 */
                                    strlen();
                                    t11 = &[rax+0x1];
                                    [r12+0x0] = malloc();
                                    t6 = rbx + 8;
                                    memcpy();
                                    /* compare rdi vs t6 */
                                    t7 = rdi + r12;
                                    [rdi+0x0] = 0;
                                    *(DWORD*)0x14000C019 = r12;
                                    __main();
                                    t13 = *(DWORD*)0x14000C011;
                                    t4 = [rax+0x0];
                                    [rax+0x0] = t13;
                                    main();
                                    t10 = *(DWORD*)0x14000C006;
                                    *(DWORD*)0x14000C00A = t4;
                                    /* compare t10 vs t10 */
                                    do {
                                        t3 = rdi;
                                        [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                        if (t3 != 0) {
                                        }
                                        t3 = [rsi+0x0];
                                        if (t3 == 1) {
                                        }
                                        if (rdi == 0) {
                                        }
                                        t4 = [rax+0x0];
                                        if (t4 == 0) {
                                        }
                                        t7 = rdi - 8;
                                        strlen();
                                        t11 = &[rax+0x1];
                                        [r12+0x0] = malloc();
                                        t12 = 0 + 8;
                                        memcpy();
                                        /* compare t7 vs t12 */
                                        strlen();
                                        t11 = &[rax+0x1];
                                        [r12+0x0] = malloc();
                                        t6 = rbx + 8;
                                        memcpy();
                                        /* compare rdi vs t6 */
                                        t7 = rdi + r12;
                                        [rdi+0x0] = 0;
                                        *(DWORD*)0x14000C019 = r12;
                                        __main();
                                        t13 = *(DWORD*)0x14000C011;
                                        t4 = [rax+0x0];
                                        [rax+0x0] = t13;
                                        main();
                                        t10 = *(DWORD*)0x14000C006;
                                        *(DWORD*)0x14000C00A = t4;
                                        /* compare t10 vs t10 */
                                        do {
                                            t3 = rdi;
                                            [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                            if (t3 != 0) {
                                            }
                                            t3 = [rsi+0x0];
                                            if (t3 == 1) {
                                            }
                                            if (rdi == 0) {
                                            }
                                            t4 = [rax+0x0];
                                            if (t4 == 0) {
                                            }
                                            t7 = rdi - 8;
                                            strlen();
                                            t11 = &[rax+0x1];
                                            [r12+0x0] = malloc();
                                            t12 = 0 + 8;
                                            memcpy();
                                            /* compare t7 vs t12 */
                                            strlen();
                                            t11 = &[rax+0x1];
                                            [r12+0x0] = malloc();
                                            t6 = rbx + 8;
                                            memcpy();
                                            /* compare rdi vs t6 */
                                            t7 = rdi + r12;
                                            [rdi+0x0] = 0;
                                            *(DWORD*)0x14000C019 = r12;
                                            __main();
                                            t13 = *(DWORD*)0x14000C011;
                                            t4 = [rax+0x0];
                                            [rax+0x0] = t13;
                                            main();
                                            t10 = *(DWORD*)0x14000C006;
                                            *(DWORD*)0x14000C00A = t4;
                                            /* compare t10 vs t10 */
                                            do {
                                                t3 = rdi;
                                                [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                                if (t3 != 0) {
                                                }
                                                t3 = [rsi+0x0];
                                                if (t3 == 1) {
                                                }
                                                if (rdi == 0) {
                                                }
                                                t4 = [rax+0x0];
                                                if (t4 == 0) {
                                                }
                                                t7 = rdi - 8;
                                                strlen();
                                                t11 = &[rax+0x1];
                                                [r12+0x0] = malloc();
                                                t12 = 0 + 8;
                                                memcpy();
                                                /* compare t7 vs t12 */
                                                strlen();
                                                t11 = &[rax+0x1];
                                                [r12+0x0] = malloc();
                                                t6 = rbx + 8;
                                                memcpy();
                                                /* compare rdi vs t6 */
                                                t7 = rdi + r12;
                                                [rdi+0x0] = 0;
                                                *(DWORD*)0x14000C019 = r12;
                                                __main();
                                                t13 = *(DWORD*)0x14000C011;
                                                t4 = [rax+0x0];
                                                [rax+0x0] = t13;
                                                main();
                                                t10 = *(DWORD*)0x14000C006;
                                                *(DWORD*)0x14000C00A = t4;
                                                /* compare t10 vs t10 */
                                                do {
                                                    t3 = rdi;
                                                    [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                                    /* compare t3 vs t3 */
                                                    /* compare rsi vs rax */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    /* compare rsi vs rax */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    r12();
                                                    t3 = rdi;
                                                    [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                                    /* compare t3 vs t3 */
                                                    r12();
                                                    t3 = rdi;
                                                    [rbx+0x0] = cmpxchg([rbx+0x0], rsi);
                                                    /* compare t3 vs t3 */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    _amsg_exit();
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs t3 */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs t3 */
                                                    _amsg_exit();
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    _amsg_exit();
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    /* compare rdi vs rdi */
                                                    _initterm();
                                                    [rsi+0x0] = 2;
                                                    /* compare rdi vs rdi */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs t3 */
                                                    [rsi+0x0] = 1;
                                                    _initterm();
                                                    *(DWORD*)0x14000BFFE = 1;
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    *(DWORD*)0x14000BFFE = 1;
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    _initterm();
                                                    [rsi+0x0] = 2;
                                                    /* compare rdi vs rdi */
                                                    /* compare rdi vs rdi */
                                                    [rsi+0x0] = 1;
                                                    _initterm();
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    t3 = [rsi+0x0];
                                                    /* compare t3 vs 1 */
                                                    _initterm();
                                                    [rsi+0x0] = 2;
                                                    /* compare rdi vs rdi */
                                                    /* compare rdi vs rdi */
                                                    /* compare rdi vs rdi */
                                                    [rbx+0x0] = xchg([rbx+0x0], rax);
                                                    t4 = [rax+0x0];
                                                    /* compare t4 vs t4 */
                                                    _initterm();
                                                    [rsi+0x0] = 2;
                                                    /* compare rdi vs rdi */
                                                    t4 = [rax+0x0];
                                                    /* compare t4 vs t4 */
                                                    [rbx+0x0] = xchg([rbx+0x0], rax);
                                                    [rbx+0x0] = xchg([rbx+0x0], rax);
                                                    t4 = [rax+0x0];
                                                    /* compare t4 vs t4 */
                                                    _pei386_runtime_relocator();
                                                    ___FARPROC__gvar_14000D1FA_();
                                                    t10 = &*(DWORD*)0x140000FF9;
                                                    [rdx+0x0] = rax;
                                                    mingw_set_invalid_parameter_handler();
                                                    _fpreset();
                                                    t6 = *(DWORD*)0x14000C022;
                                                    t7 = &[rbx+0x1];
                                                    t8 = (signed)t7;
                                                    t9 = t8 << 0x3;
                                                    malloc();
                                                    /* compare t6 vs t6 */
                                                    rax();
                                                    _pei386_runtime_relocator();
                                                    ___FARPROC__gvar_14000D1FA_();
                                                    t5 = &*(DWORD*)0x140000FF9;
                                                    [rdx+0x0] = rax;
                                                    mingw_set_invalid_parameter_handler();
                                                    _fpreset();
                                                    t6 = *(DWORD*)0x14000C022;
                                                    t7 = &[rbx+0x1];
                                                    t8 = (signed)t7;
                                                    t9 = t8 << 0x3;
                                                    malloc();
                                                    /* compare t6 vs t6 */
                                                    rax();
                                                    _pei386_runtime_relocator();
                                                    ___FARPROC__gvar_14000D1FA_();
                                                    t5 = &*(DWORD*)0x140000FF9;
                                                    [rdx+0x0] = rax;
                                                    mingw_set_invalid_parameter_handler();
                                                    _fpreset();
                                                    t6 = *(DWORD*)0x14000C022;
                                                    t7 = &[rbx+0x1];
                                                    t8 = (signed)t7;
                                                    t9 = t8 << 0x3;
                                                    malloc();
                                                    /* compare t6 vs t6 */
                                                    t7 = rdi - 8;
                                                    strlen();
                                                    t11 = &[rax+0x1];
                                                    [r12+0x0] = malloc();
                                                    t12 = 0 + 8;
                                                    memcpy();
                                                    /* compare t7 vs t12 */
                                                    _pei386_runtime_relocator();
                                                    ___FARPROC__gvar_14000D1FA_();
                                                    t10 = &*(DWORD*)0x140000FF9;
                                                    [rdx+0x0] = rax;
                                                    mingw_set_invalid_parameter_handler();
                                                    _fpreset();
                                                    t6 = *(DWORD*)0x14000C022;
                                                    t7 = &[rbx+0x1];
                                                    t8 = (signed)t7;
                                                    t9 = t8 << 0x3;
                                                    malloc();
                                                    /* compare t6 vs t6 */
                                                    t7 = rdi - 8;
                                                    strlen();
                                                    t11 = &[rax+0x1];
                                                    [r12+0x0] = malloc();
                                                    t12 = 0 + 8;
                                                    memcpy();
                                                    /* compare t7 vs t12 */
                                                    t7 = rdi - 8;
                                                    strlen();
                                                    t11 = &[rax+0x1];
                                                    [r12+0x0] = malloc();
                                                    t12 = 0 + 8;
                                                    memcpy();
                                                    /* compare t7 vs t12 */
                                                    strlen();
                                                    t11 = &[rax+0x1];
                                                    [r12+0x0] = malloc();
                                                    t6 = rbx + 8;
                                                    memcpy();
                                                    /* compare rdi vs t6 */
                                                    t7 = rdi + r12;
                                                    [rdi+0x0] = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main();
                                                    t13 = *(DWORD*)0x14000C011;
                                                    t4 = [rax+0x0];
                                                    [rax+0x0] = t13;
                                                    main();
                                                    t10 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t4;
                                                    /* compare t10 vs t10 */
                                                    strlen();
                                                    t11 = &[rax+0x1];
                                                    [r12+0x0] = malloc();
                                                    t6 = rbx + 8;
                                                    memcpy();
                                                    /* compare rdi vs t6 */
                                                    strlen();
                                                    t11 = &[rax+0x1];
                                                    [r12+0x0] = malloc();
                                                    t6 = rbx + 8;
                                                    memcpy();
                                                    /* compare rdi vs t6 */
                                                    t7 = rdi + r12;
                                                    [rdi+0x0] = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main();
                                                    t13 = *(DWORD*)0x14000C011;
                                                    t4 = [rax+0x0];
                                                    [rax+0x0] = t13;
                                                    main();
                                                    t10 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t4;
                                                    /* compare t10 vs t10 */
                                                    t7 = rdi + r12;
                                                    [rdi+0x0] = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main();
                                                    t13 = *(DWORD*)0x14000C011;
                                                    t4 = [rax+0x0];
                                                    [rax+0x0] = t13;
                                                    main();
                                                    t10 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t4;
                                                    /* compare t10 vs t10 */
                                                    exit();
                                                    t1 = rsp - 32;
                                                    [rax+0x0] = 1;
                                                    __tmainCRTStartup();
                                                    t17 = t1 + 32;
                                                    t18 = stack_pop();
                                                    t14 = *(DWORD*)0x14000C002;
                                                    /* compare t14 vs t14 */
                                                    [rdi+0x0] = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main();
                                                    t13 = *(DWORD*)0x14000C011;
                                                    t4 = [rax+0x0];
                                                    [rax+0x0] = t13;
                                                    main();
                                                    t10 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t4;
                                                    /* compare t10 vs t10 */
                                                    exit();
                                                    t1 = rsp - 32;
                                                    [rax+0x0] = 1;
                                                    __tmainCRTStartup();
                                                    t17 = t1 + 32;
                                                    t18 = stack_pop();
                                                    t14 = *(DWORD*)0x14000C002;
                                                    /* compare t14 vs t14 */
                                                    t14 = *(DWORD*)0x14000C002;
                                                    /* compare t14 vs t14 */
                                                    _cexit();
                                                    t1 = rsp + 40;
                                                    t6 = stack_pop();
                                                    t11 = stack_pop();
                                                    t7 = stack_pop();
                                                    t15 = stack_pop();
                                                    t16 = stack_pop();
                                                    t2 = stack_pop();
                                                    t1 = rsp + 40;
                                                    t6 = stack_pop();
                                                    t11 = stack_pop();
                                                    t7 = stack_pop();
                                                    t15 = stack_pop();
                                                    t16 = stack_pop();
                                                    t2 = stack_pop();
                                                    t1 = rsp + 40;
                                                    t6 = stack_pop();
                                                    t11 = stack_pop();
                                                    t7 = stack_pop();
                                                    t15 = stack_pop();
                                                    t16 = stack_pop();
                                                    t2 = stack_pop();
                                                    _cexit();
                                                    t1 = rsp + 40;
                                                    t6 = stack_pop();
                                                    t11 = stack_pop();
                                                    t7 = stack_pop();
                                                    t15 = stack_pop();
                                                    t16 = stack_pop();
                                                    t2 = stack_pop();
                                                    exit();
                                                    t1 = rsp - 32;
                                                    [rax+0x0] = 1;
                                                    __tmainCRTStartup();
                                                    t17 = t1 + 32;
                                                    t18 = stack_pop();
                                                } while (1 != 0);
                                                t14 = *(DWORD*)0x14000C002;
                                                if (t14 == 0) {
                                                }
                                                t3 = [rsi+0x0];
                                                if (t3 != 1) {
                                                }
                                                _initterm();
                                                [rsi+0x0] = 2;
                                                /* compare rdi vs rdi */
                                                rax();
                                                _pei386_runtime_relocator();
                                                ___FARPROC__gvar_14000D1FA_();
                                                t5 = &*(DWORD*)0x140000FF9;
                                                [rdx+0x0] = rax;
                                                mingw_set_invalid_parameter_handler();
                                                _fpreset();
                                                t6 = *(DWORD*)0x14000C022;
                                                t7 = &[rbx+0x1];
                                                t8 = (signed)t7;
                                                t9 = t8 << 0x3;
                                                malloc();
                                                /* compare t6 vs t6 */
                                                [rdi+0x0] = 0;
                                                *(DWORD*)0x14000C019 = r12;
                                                __main();
                                                t13 = *(DWORD*)0x14000C011;
                                                t4 = [rax+0x0];
                                                [rax+0x0] = t13;
                                                main();
                                                t10 = *(DWORD*)0x14000C006;
                                                *(DWORD*)0x14000C00A = t4;
                                                /* compare t10 vs t10 */
                                                t1 = rsp + 40;
                                                t6 = stack_pop();
                                                t11 = stack_pop();
                                                t7 = stack_pop();
                                                t15 = stack_pop();
                                                t16 = stack_pop();
                                                t2 = stack_pop();
                                                exit();
                                                t1 = rsp - 32;
                                                [rax+0x0] = 1;
                                                __tmainCRTStartup();
                                                t17 = t1 + 32;
                                                t18 = stack_pop();
                                            } while (1 != 0);
                                            t14 = *(DWORD*)0x14000C002;
                                            if (t14 == 0) {
                                            }
                                            t3 = [rsi+0x0];
                                            if (t3 != 1) {
                                            }
                                            _initterm();
                                            [rsi+0x0] = 2;
                                            /* compare rdi vs rdi */
                                            rax();
                                            _pei386_runtime_relocator();
                                            ___FARPROC__gvar_14000D1FA_();
                                            t5 = &*(DWORD*)0x140000FF9;
                                            [rdx+0x0] = rax;
                                            mingw_set_invalid_parameter_handler();
                                            _fpreset();
                                            t6 = *(DWORD*)0x14000C022;
                                            t7 = &[rbx+0x1];
                                            t8 = (signed)t7;
                                            t9 = t8 << 0x3;
                                            malloc();
                                            /* compare t6 vs t6 */
                                            [rdi+0x0] = 0;
                                            *(DWORD*)0x14000C019 = r12;
                                            __main();
                                            t13 = *(DWORD*)0x14000C011;
                                            t4 = [rax+0x0];
                                            [rax+0x0] = t13;
                                            main();
                                            t10 = *(DWORD*)0x14000C006;
                                            *(DWORD*)0x14000C00A = t4;
                                            /* compare t10 vs t10 */
                                            t1 = rsp + 40;
                                            t6 = stack_pop();
                                            t11 = stack_pop();
                                            t7 = stack_pop();
                                            t15 = stack_pop();
                                            t16 = stack_pop();
                                            t2 = stack_pop();
                                            exit();
                                            t1 = rsp - 32;
                                            [rax+0x0] = 1;
                                            __tmainCRTStartup();
                                            t17 = t1 + 32;
                                            t18 = stack_pop();
                                        } while (1 != 0);
                                        t14 = *(DWORD*)0x14000C002;
                                        if (t14 == 0) {
                                        }
                                        t3 = [rsi+0x0];
                                        if (t3 != 1) {
                                        }
                                        _initterm();
                                        [rsi+0x0] = 2;
                                        /* compare rdi vs rdi */
                                        rax();
                                        _pei386_runtime_relocator();
                                        ___FARPROC__gvar_14000D1FA_();
                                        t5 = &*(DWORD*)0x140000FF9;
                                        [rdx+0x0] = rax;
                                        mingw_set_invalid_parameter_handler();
                                        _fpreset();
                                        t6 = *(DWORD*)0x14000C022;
                                        t7 = &[rbx+0x1];
                                        t8 = (signed)t7;
                                        t9 = t8 << 0x3;
                                        malloc();
                                        /* compare t6 vs t6 */
                                        [rdi+0x0] = 0;
                                        *(DWORD*)0x14000C019 = r12;
                                        __main();
                                        t13 = *(DWORD*)0x14000C011;
                                        t4 = [rax+0x0];
                                        [rax+0x0] = t13;
                                        main();
                                        t10 = *(DWORD*)0x14000C006;
                                        *(DWORD*)0x14000C00A = t4;
                                        /* compare t10 vs t10 */
                                        t1 = rsp + 40;
                                        t6 = stack_pop();
                                        t11 = stack_pop();
                                        t7 = stack_pop();
                                        t15 = stack_pop();
                                        t16 = stack_pop();
                                        t2 = stack_pop();
                                        exit();
                                        t1 = rsp - 32;
                                        [rax+0x0] = 1;
                                        __tmainCRTStartup();
                                        t17 = t1 + 32;
                                        t18 = stack_pop();
                                    } while (1 != 0);
                                    t14 = *(DWORD*)0x14000C002;
                                    if (t14 == 0) {
                                    }
                                    t3 = [rsi+0x0];
                                    if (t3 != 1) {
                                    }
                                    _initterm();
                                    [rsi+0x0] = 2;
                                    /* compare rdi vs rdi */
                                    rax();
                                    _pei386_runtime_relocator();
                                    ___FARPROC__gvar_14000D1FA_();
                                    t5 = &*(DWORD*)0x140000FF9;
                                    [rdx+0x0] = rax;
                                    mingw_set_invalid_parameter_handler();
                                    _fpreset();
                                    t6 = *(DWORD*)0x14000C022;
                                    t7 = &[rbx+0x1];
                                    t8 = (signed)t7;
                                    t9 = t8 << 0x3;
                                    malloc();
                                    /* compare t6 vs t6 */
                                    [rdi+0x0] = 0;
                                    *(DWORD*)0x14000C019 = r12;
                                    __main();
                                    t13 = *(DWORD*)0x14000C011;
                                    t4 = [rax+0x0];
                                    [rax+0x0] = t13;
                                    main();
                                    t10 = *(DWORD*)0x14000C006;
                                    *(DWORD*)0x14000C00A = t4;
                                    /* compare t10 vs t10 */
                                    t1 = rsp + 40;
                                    t6 = stack_pop();
                                    t11 = stack_pop();
                                    t7 = stack_pop();
                                    t15 = stack_pop();
                                    t16 = stack_pop();
                                    t2 = stack_pop();
                                    exit();
                                    t1 = rsp - 32;
                                    [rax+0x0] = 1;
                                    __tmainCRTStartup();
                                    t17 = t1 + 32;
                                    t18 = stack_pop();
                                } while (1 != 0);
                                t14 = *(DWORD*)0x14000C002;
                                if (t14 == 0) {
                                }
                                t3 = [rsi+0x0];
                                if (t3 != 1) {
                                }
                                _initterm();
                                [rsi+0x0] = 2;
                                /* compare rdi vs rdi */
                                rax();
                                _pei386_runtime_relocator();
                                ___FARPROC__gvar_14000D1FA_();
                                t5 = &*(DWORD*)0x140000FF9;
                                [rdx+0x0] = rax;
                                mingw_set_invalid_parameter_handler();
                                _fpreset();
                                t6 = *(DWORD*)0x14000C022;
                                t7 = &[rbx+0x1];
                                t8 = (signed)t7;
                                t9 = t8 << 0x3;
                                malloc();
                                /* compare t6 vs t6 */
                                [rdi+0x0] = 0;
                                *(DWORD*)0x14000C019 = r12;
                                __main();
                                t13 = *(DWORD*)0x14000C011;
                                t4 = [rax+0x0];
                                [rax+0x0] = t13;
                                main();
                                t10 = *(DWORD*)0x14000C006;
                                *(DWORD*)0x14000C00A = t4;
                                /* compare t10 vs t10 */
                                t1 = rsp + 40;
                                t6 = stack_pop();
                                t11 = stack_pop();
                                t7 = stack_pop();
                                t15 = stack_pop();
                                t16 = stack_pop();
                                t2 = stack_pop();
                                exit();
                                t1 = rsp - 32;
                                [rax+0x0] = 1;
                                __tmainCRTStartup();
                                t17 = t1 + 32;
                                t18 = stack_pop();
                            } while (1 != 0);
                            t14 = *(DWORD*)0x14000C002;
                            if (t14 == 0) {
                            }
                            t3 = [rsi+0x0];
                            if (t3 != 1) {
                            }
                            _initterm();
                            [rsi+0x0] = 2;
                            /* compare rdi vs rdi */
                            rax();
                            _pei386_runtime_relocator();
                            ___FARPROC__gvar_14000D1FA_();
                            t5 = &*(DWORD*)0x140000FF9;
                            [rdx+0x0] = rax;
                            mingw_set_invalid_parameter_handler();
                            _fpreset();
                            t6 = *(DWORD*)0x14000C022;
                            t7 = &[rbx+0x1];
                            t8 = (signed)t7;
                            t9 = t8 << 0x3;
                            malloc();
                            /* compare t6 vs t6 */
                            [rdi+0x0] = 0;
                            *(DWORD*)0x14000C019 = r12;
                            __main();
                            t13 = *(DWORD*)0x14000C011;
                            t4 = [rax+0x0];
                            [rax+0x0] = t13;
                            main();
                            t10 = *(DWORD*)0x14000C006;
                            *(DWORD*)0x14000C00A = t4;
                            /* compare t10 vs t10 */
                            t1 = rsp + 40;
                            t6 = stack_pop();
                            t11 = stack_pop();
                            t7 = stack_pop();
                            t15 = stack_pop();
                            t16 = stack_pop();
                            t2 = stack_pop();
                            exit();
                            t1 = rsp - 32;
                            [rax+0x0] = 1;
                            __tmainCRTStartup();
                            t17 = t1 + 32;
                            t18 = stack_pop();
                        } while (1 != 0);
                        t14 = *(DWORD*)0x14000C002;
                        if (t14 == 0) {
                        }
                        t3 = [rsi+0x0];
                        if (t3 != 1) {
                        }
                        _initterm();
                        [rsi+0x0] = 2;
                        /* compare rdi vs rdi */
                        rax();
                        _pei386_runtime_relocator();
                        ___FARPROC__gvar_14000D1FA_();
                        t5 = &*(DWORD*)0x140000FF9;
                        [rdx+0x0] = rax;
                        mingw_set_invalid_parameter_handler();
                        _fpreset();
                        t6 = *(DWORD*)0x14000C022;
                        t7 = &[rbx+0x1];
                        t8 = (signed)t7;
                        t9 = t8 << 0x3;
                        malloc();
                        /* compare t6 vs t6 */
                        [rdi+0x0] = 0;
                        *(DWORD*)0x14000C019 = r12;
                        __main();
                        t13 = *(DWORD*)0x14000C011;
                        t4 = [rax+0x0];
                        [rax+0x0] = t13;
                        main();
                        t10 = *(DWORD*)0x14000C006;
                        *(DWORD*)0x14000C00A = t4;
                        /* compare t10 vs t10 */
                        t1 = rsp + 40;
                        t6 = stack_pop();
                        t11 = stack_pop();
                        t7 = stack_pop();
                        t15 = stack_pop();
                        t16 = stack_pop();
                        t2 = stack_pop();
                        exit();
                        t1 = rsp - 32;
                        [rax+0x0] = 1;
                        __tmainCRTStartup();
                        t17 = t1 + 32;
                        t18 = stack_pop();
                    } while (1 != 0);
                    t14 = *(DWORD*)0x14000C002;
                    if (t14 == 0) {
                    }
                    t3 = [rsi+0x0];
                    if (t3 != 1) {
                    }
                    _initterm();
                    [rsi+0x0] = 2;
                    /* compare rdi vs rdi */
                    rax();
                    _pei386_runtime_relocator();
                    ___FARPROC__gvar_14000D1FA_();
                    t5 = &*(DWORD*)0x140000FF9;
                    [rdx+0x0] = rax;
                    mingw_set_invalid_parameter_handler();
                    _fpreset();
                    t6 = *(DWORD*)0x14000C022;
                    t7 = &[rbx+0x1];
                    t8 = (signed)t7;
                    t9 = t8 << 0x3;
                    malloc();
                    /* compare t6 vs t6 */
                    [rdi+0x0] = 0;
                    *(DWORD*)0x14000C019 = r12;
                    __main();
                    t13 = *(DWORD*)0x14000C011;
                    t4 = [rax+0x0];
                    [rax+0x0] = t13;
                    main();
                    t10 = *(DWORD*)0x14000C006;
                    *(DWORD*)0x14000C00A = t4;
                    /* compare t10 vs t10 */
                    t1 = rsp + 40;
                    t6 = stack_pop();
                    t11 = stack_pop();
                    t7 = stack_pop();
                    t15 = stack_pop();
                    t16 = stack_pop();
                    t2 = stack_pop();
                    exit();
                    t1 = rsp - 32;
                    [rax+0x0] = 1;
                    __tmainCRTStartup();
                    t17 = t1 + 32;
                    t18 = stack_pop();
                } while (1 != 0);
                t14 = *(DWORD*)0x14000C002;
                if (t14 == 0) {
                }
                t3 = [rsi+0x0];
                if (t3 != 1) {
                }
                _initterm();
                [rsi+0x0] = 2;
                /* compare rdi vs rdi */
                rax();
                _pei386_runtime_relocator();
                ___FARPROC__gvar_14000D1FA_();
                t5 = &*(DWORD*)0x140000FF9;
                [rdx+0x0] = rax;
                mingw_set_invalid_parameter_handler();
                _fpreset();
                t6 = *(DWORD*)0x14000C022;
                t7 = &[rbx+0x1];
                t8 = (signed)t7;
                t9 = t8 << 0x3;
                malloc();
                /* compare t6 vs t6 */
                [rdi+0x0] = 0;
                *(DWORD*)0x14000C019 = r12;
                __main();
                t13 = *(DWORD*)0x14000C011;
                t4 = [rax+0x0];
                [rax+0x0] = t13;
                main();
                t10 = *(DWORD*)0x14000C006;
                *(DWORD*)0x14000C00A = t4;
                /* compare t10 vs t10 */
                t1 = rsp + 40;
                t6 = stack_pop();
                t11 = stack_pop();
                t7 = stack_pop();
                t15 = stack_pop();
                t16 = stack_pop();
                t2 = stack_pop();
                exit();
                t1 = rsp - 32;
                [rax+0x0] = 1;
                __tmainCRTStartup();
                t17 = t1 + 32;
                t18 = stack_pop();
            } while (1 != 0);
            t14 = *(DWORD*)0x14000C002;
            if (t14 == 0) {
            }
            t3 = [rsi+0x0];
            if (t3 != 1) {
            }
            _initterm();
            [rsi+0x0] = 2;
            /* compare rdi vs rdi */
            rax();
            _pei386_runtime_relocator();
            ___FARPROC__gvar_14000D1FA_();
            t5 = &*(DWORD*)0x140000FF9;
            [rdx+0x0] = rax;
            mingw_set_invalid_parameter_handler();
            _fpreset();
            t6 = *(DWORD*)0x14000C022;
            t7 = &[rbx+0x1];
            t8 = (signed)t7;
            t9 = t8 << 0x3;
            malloc();
            /* compare t6 vs t6 */
            [rdi+0x0] = 0;
            *(DWORD*)0x14000C019 = r12;
            __main();
            t13 = *(DWORD*)0x14000C011;
            t4 = [rax+0x0];
            [rax+0x0] = t13;
            main();
            t10 = *(DWORD*)0x14000C006;
            *(DWORD*)0x14000C00A = t4;
            /* compare t10 vs t10 */
            t1 = rsp + 40;
            t6 = stack_pop();
            t11 = stack_pop();
            t7 = stack_pop();
            t15 = stack_pop();
            t16 = stack_pop();
            t2 = stack_pop();
            exit();
            t1 = rsp - 32;
            [rax+0x0] = 1;
            __tmainCRTStartup();
            t17 = t1 + 32;
            t18 = stack_pop();
        } while (1 != 0);
        t14 = *(DWORD*)0x14000C002;
        if (t14 == 0) {
        }
        t3 = [rsi+0x0];
        if (t3 != 1) {
        }
        _initterm();
        [rsi+0x0] = 2;
        /* compare rdi vs rdi */
        rax();
        _pei386_runtime_relocator();
        ___FARPROC__gvar_14000D1FA_();
        t5 = &*(DWORD*)0x140000FF9;
        [rdx+0x0] = rax;
        mingw_set_invalid_parameter_handler();
        _fpreset();
        t6 = *(DWORD*)0x14000C022;
        t7 = &[rbx+0x1];
        t8 = (signed)t7;
        t9 = t8 << 0x3;
        malloc();
        /* compare t6 vs t6 */
        [rdi+0x0] = 0;
        *(DWORD*)0x14000C019 = r12;
        __main();
        t13 = *(DWORD*)0x14000C011;
        t4 = [rax+0x0];
        [rax+0x0] = t13;
        main();
        t10 = *(DWORD*)0x14000C006;
        *(DWORD*)0x14000C00A = t4;
        /* compare t10 vs t10 */
        t1 = rsp + 40;
        t6 = stack_pop();
        t11 = stack_pop();
        t7 = stack_pop();
        t15 = stack_pop();
        t16 = stack_pop();
        t2 = stack_pop();
        exit();
        t1 = rsp - 32;
        [rax+0x0] = 1;
        __tmainCRTStartup();
        t17 = t1 + 32;
        t18 = stack_pop();
    } while (1 != 0);
    t14 = *(DWORD*)0x14000C002;
    if (t14 == 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * mainCRTStartup @ 0x140001410 (ENTRY_POINT)
 * Blocks: 1 | SSA vars: 5
 * ═══════════════════════════════════════════════════ */
void mainCRTStartup(void) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t rax;

    t1 = rsp - 32;
    _onexit();
    /* compare rax vs 1 */
    t2 = t1 + 32;
    t3 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * atexit @ 0x140001440 (USER)
 * Blocks: 5 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
void atexit(int param_1, int param_2, int param_3) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t rax;
    int32_t rcx;
    int32_t rbx;
    uint64_t r8;
    int32_t rdx;
    int32_t var_4;

    t1 = rsp - 32;
    _onexit();
    /* compare rax vs 1 */
    t2 = t1 + 32;
    t3 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * printf @ 0x140001480 (USER)
 * Blocks: 1 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
void printf(int param_1, int param_2, int param_3) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rbx;
    int32_t rcx;
    uint64_t r8;
    int32_t rdx;
    int32_t var_4;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    arg_20 = rcx;
    arg_30 = r8;
    arg_38 = r9;
    t3 = &(rdx);
    t4 = (t3);
    t5 = *(DWORD*)0x1400080A9;
    t6 = t5();
    __mingw_vfprintf();
    var_4 = t6;
    t7 = t1 + 56;
    t8 = stack_pop();
    t9 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * add @ 0x1400014D4 (USER)
 * Blocks: 1 | SSA vars: 5
 * ═══════════════════════════════════════════════════ */
void add(void) {
    /* local variables */
    int32_t rbp;
    int32_t rdx;
    int32_t rax;

    t1 = (rcx);
    t2 = (rdx);
    t3 = t2 + t1;
    t4 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * main @ 0x1400014E8 (USER)
 * Blocks: 16 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
int __cdecl main(void) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t rdx;
    int32_t rcx;
    int32_t rax;
    int32_t rbx;
    int32_t rsi;
    int32_t invalid;

    t1 = rsp - 32;
    __main();
    add();
    t2 = &*(DWORD*)0x140008FF9;
    printf();
    t3 = t1 + 32;
    t4 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __main @ 0x1400015F0 (USER)
 * Blocks: 5 | SSA vars: 1
 * ═══════════════════════════════════════════════════ */
void __main(void) {
    /* local variables */
    int32_t rax;

    t1 = *(DWORD*)0x14000C02A;
    if (t1 == 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * _setargv @ 0x140001610 (USER)
 * Blocks: 31 | SSA vars: 20
 * ═══════════════════════════════════════════════════ */
void _setargv(int param_1, int param_2) {
    /* local variables */
    int32_t rax;
    int32_t rbp;
    int32_t rsp;
    int32_t rbx;
    int32_t rsi;
    int32_t rdx;
    int32_t invalid;
    double xmm7;
    double xmm6;
    int32_t rcx;
    uint64_t r8;
    uint64_t r9;

}

/* ═══════════════════════════════════════════════════
 * _fpreset @ 0x1400017F0 (USER)
 * Blocks: 2 | SSA vars: 18
 * ═══════════════════════════════════════════════════ */
void _fpreset(int param_1, int param_2, int param_3) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rax;
    int32_t rcx;
    int32_t invalid;
    int32_t rdx;
    uint64_t r9;
    int32_t rsi;
    uint64_t r8;
    int32_t var_8;

    /* asm: fninit */;
}

/* ═══════════════════════════════════════════════════
 * __report_error @ 0x140001800 (USER)
 * Blocks: 1 | SSA vars: 18
 * ═══════════════════════════════════════════════════ */
void __report_error(int param_1, int param_2, int param_3) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rax;
    int32_t rcx;
    int32_t invalid;
    int32_t rdx;
    uint64_t r9;
    int32_t rsi;
    uint64_t r8;
    int32_t var_8;

    t1 = rsp - 48;
    t2 = &[rsp+0x30];
    t3 = rcx;
    t4 = &arg_28;
    arg_28 = rdx;
    arg_30 = r8;
    arg_38 = r9;
    var_8 = t4;
    __acrt_iob_func();
    t5 = &*(DWORD*)0x1400091B9;
    t6 = fwrite();
    __acrt_iob_func();
    vfprintf();
    abort();
    t7 = t1 - 88;
    t8 = &[rsp+0x50];
    t9 = (signed)*(DWORD*)0x14000C09D;
    /* compare t9 vs t9 */
    return;
}

/* ═══════════════════════════════════════════════════
 * mark_section_writable @ 0x140001870 (USER)
 * Blocks: 17 | SSA vars: 17
 * ═══════════════════════════════════════════════════ */
void mark_section_writable(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rsi;
    int32_t rbx;
    int32_t rax;
    int32_t invalid;
    uint64_t r8;
    int32_t rdx;
    int32_t rcx;
    int32_t rdi;
    uint64_t r9;
    int32_t var_30;
    int32_t var_18;

    t1 = rsp - 88;
    t2 = &[rsp+0x50];
    t3 = (signed)*(DWORD*)0x14000C09D;
    if (t3 != 0) {
    }
    __mingw_GetSectionForAddress();
    /* compare rax vs rax */
    t11 = &*(DWORD*)0x1400091D9;
    __report_error();
    t1 = rsp - 72;
    t2 = &[rsp+0x40];
    t8 = *(DWORD*)0x14000C099;
    /* compare t8 vs t8 */
    t4 = *(DWORD*)0x14000C0A1;
    t9 = &[rsi+0x0];
    t10 = t9 << 0x3;
    t5 = t4 + t10;
    [rax+0x20] = rdi;
    [rax+0x0] = 0;
    _GetPEImageBase();
    t11 = &[rax+0x0];
    t12 = *(DWORD*)0x14000C0A1;
    t7 = &var_30;
    [rax+0x18] = t11;
    ___FARPROC__gvar_14000D21A_();
    /* compare t12 vs t12 */
    t11 = &*(DWORD*)0x1400091F9;
    __report_error();
    t15 = &*(DWORD*)0x1400091D9;
    __report_error();
    t1 = rsp - 72;
    t2 = &[rsp+0x40];
    t8 = *(DWORD*)0x14000C099;
    /* compare t8 vs t8 */
    t13 = &[rax-0x4];
    t7 = t13 & -5;
    if ( == ) {
    }
    *(DWORD*)0x14000C09D = *(DWORD*)0x14000C09D + 1;
    t1 = rsp + 88;
    t9 = stack_pop();
    t3 = stack_pop();
    t14 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * _pei386_runtime_relocator @ 0x1400019E0 (USER)
 * Blocks: 68 | SSA vars: 28
 * ═══════════════════════════════════════════════════ */
void _pei386_runtime_relocator(int param_1, int param_2) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    int32_t rbx;
    int32_t rsi;
    int32_t rdi;
    int32_t r12;
    int32_t r13;
    int32_t r14;
    int32_t r15;
    int32_t rax;
    int32_t rdx;
    int32_t rcx;
    uint64_t r9;
    uint64_t r8;
    int32_t r11;
    double xmm0;
    int32_t var_4;
    int32_t var_28;
    int32_t var_20;
    int32_t var_10;

    t1 = rsp - 72;
    t2 = &[rsp+0x40];
    t3 = *(DWORD*)0x14000C099;
    if (t3 == 0) {
    }
    t1 = &arg_8;
    t4 = stack_pop();
    t5 = stack_pop();
    t6 = stack_pop();
    t7 = stack_pop();
    t8 = stack_pop();
    t9 = stack_pop();
    t10 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __mingw_setusermatherr @ 0x140001D80 (USER)
 * Blocks: 40 | SSA vars: 9
 * ═══════════════════════════════════════════════════ */
void __mingw_setusermatherr(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rdx;
    int32_t rax;
    int32_t rbx;
    int32_t rcx;
    int32_t r13;

    *(DWORD*)0x14000C0A9 = rcx;
}

/* ═══════════════════════════════════════════════════
 * __mingwthr_run_key_dtors_part_0 @ 0x140001F50 (USER)
 * Blocks: 30 | SSA vars: 12
 * ═══════════════════════════════════════════════════ */
void __mingwthr_run_key_dtors_part_0(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t r13;
    int32_t rcx;
    int32_t rbx;
    int32_t r12;
    int32_t rdi;
    int32_t rsi;
    int32_t rax;
    int32_t rdx;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = &*(DWORD*)0x14000C0F9;
    ___FARPROC__gvar_14000D1CA_();
    t4 = *(DWORD*)0x14000C0D9;
    if (t4 == 0) {
    }
    t1 = rsp + 40;
    t4 = stack_pop();
    t7 = stack_pop();
    t6 = stack_pop();
    t5 = stack_pop();
    t3 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __mingw_TLScallback @ 0x1400020F0 (USER)
 * Blocks: 47 | SSA vars: 16
 * ═══════════════════════════════════════════════════ */
void __mingw_TLScallback(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rbx;
    int32_t rcx;
    int32_t rdx;
    int32_t invalid;
    uint64_t r9;
    int32_t rsi;
    int32_t rdi;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    if (rdx == 2) {
    }
}

/* ═══════════════════════════════════════════════════
 * __mingw_GetSectionForAddress @ 0x140002320 (USER)
 * Blocks: 11 | SSA vars: 10
 * ═══════════════════════════════════════════════════ */
void __mingw_GetSectionForAddress(void) {
    /* local variables */
    int32_t rdx;
    int32_t rax;
    uint64_t r8;
    int32_t rcx;
    int32_t invalid;
    uint64_t r9;

    if ([rdx+0x0] != 23117) {
    }
}

/* ═══════════════════════════════════════════════════
 * __mingw_GetSectionCount @ 0x1400023A0 (USER)
 * Blocks: 19 | SSA vars: 8
 * ═══════════════════════════════════════════════════ */
int __mingw_GetSectionCount(void) {
    /* local variables */
    int32_t rax;
    int32_t rcx;
    int32_t rdx;
    uint64_t r8;
    int32_t invalid;

    if ([rax+0x0] != 23117) {
    }
}

/* ═══════════════════════════════════════════════════
 * _GetPEImageBase @ 0x140002460 (USER)
 * Blocks: 38 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
void _GetPEImageBase(void) {
    /* local variables */
    int32_t rax;
    int32_t rdx;
    int32_t rcx;
    uint64_t r8;
    int32_t invalid;
    uint64_t r9;
    int32_t r11;

    if ([rax+0x0] != 23117) {
    }
}

/* ═══════════════════════════════════════════════════
 * ___chkstk_ms @ 0x1400025F0 (USER)
 * Blocks: 4 | SSA vars: 17
 * ═══════════════════════════════════════════════════ */
void ___chkstk_ms(void) {
    /* local variables */
    int32_t rcx;
    int32_t rax;
    int32_t rsp;
    int32_t rbp;
    int32_t rdi;
    int32_t rbx;
    int32_t rsi;
    uint64_t r9;
    int32_t invalid;
    int32_t rdx;

    t1 = &[rsp+0x18];
    if ((unsigned)rax < (unsigned)4096) {
    }
    t1 = rcx - rax;
    [rcx+0x0] = [rcx+0x0] | 0;
    t2 = stack_pop();
    t3 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __mingw_vfprintf @ 0x140002630 (USER)
 * Blocks: 2 | SSA vars: 19
 * ═══════════════════════════════════════════════════ */
void __mingw_vfprintf(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rdi;
    int32_t rbx;
    int32_t rsi;
    uint64_t r9;
    int32_t invalid;
    int32_t rdx;
    int32_t rcx;
    int32_t rax;
    int32_t var_10;
    int32_t var_8;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    t3 = rcx;
    _lock_file();
    [rsp+0x20] = r8;
    __mingw_pformat();
    _unlock_file();
    t4 = t1 + 56;
    t5 = stack_pop();
    t6 = stack_pop();
    t7 = stack_pop();
    t8 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __pformat_cvt @ 0x140002680 (USER)
 * Blocks: 17 | SSA vars: 17
 * ═══════════════════════════════════════════════════ */
void __pformat_cvt(void) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t rax;
    int32_t rdx;
    int32_t invalid;
    int32_t rcx;
    uint64_t r9;
    uint64_t r8;
    int32_t rbx;
    int32_t var_10;
    int32_t var_8;
    int32_t var_1C;
    int32_t var_18;

    t1 = rsp - 96;
    t2 = [rdx+0x0];
    t3 = [rdx+0x8];
    var_10 = t2;
    var_8 = t3;
    t4 = rcx & 32767;
    if ( != ) {
    }
    var_1C = rax;
    t6 = rcx & 32768;
    [rax+0x0] = t6;
    t12 = &var_18;
    t8 = &*(DWORD*)0x140008039;
    [rsp+0x30] = r9;
    t9 = &var_1C;
    [rsp+0x28] = invalid;
    t10 = &var_10;
    [rsp+0x38] = t12;
    [rsp+0x20] = invalid;
    __gdtoa();
    t1 = rsp + 96;
    t11 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __pformat_putc @ 0x140002770 (USER)
 * Blocks: 8 | SSA vars: 15
 * ═══════════════════════════════════════════════════ */
void __pformat_putc(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rdx;
    int32_t rax;
    int32_t rdi;
    int32_t rsi;
    int32_t r12;
    uint64_t r8;
    int32_t rcx;
    int32_t var_18;
    int32_t var_10;
    int32_t var_28;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = [rdx+0x8];
    if (t3 != 0) {
    }
    t3 = rdx & 32;
    if ( != ) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_wputchars @ 0x1400027D0 (USER)
 * Blocks: 28 | SSA vars: 20
 * ═══════════════════════════════════════════════════ */
void __pformat_wputchars(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rdi;
    int32_t rsi;
    int32_t rbx;
    int32_t rdx;
    int32_t r12;
    uint64_t r8;
    int32_t rcx;
    int32_t invalid;
    int32_t r15;
    int32_t r14;
    int32_t r13;
    int32_t var_18;
    int32_t var_10;
    int32_t var_28;

    t1 = rsp - 88;
    t2 = &[rsp+0x50];
    t3 = &var_18;
    t4 = &var_10;
    t5 = rdx;
    var_28 = t3;
    wcrtomb();
    t6 = [rbx+0x10];
    /* compare t5 vs t6 */
    /* compare t6 vs t6 */
    t7 = [rbx+0xC];
    t8 = t5;
    /* compare t7 vs t8 */
    t3 = rax - rsi;
    [rbx+0xC] = t3;
    if ([rbx+0x9] != 0) {
    }
    t9 = invalid + 1;
    t10 = (unsigned)[r12+0x0];
    wcrtomb();
    /* compare rax vs rax */
    t3 = [rbx+0xC];
    t10 = &[rax-0x1];
    [rbx+0xC] = t10;
    if (t3 != 0) {
    }
    t1 = rsp + 88;
    t15 = stack_pop();
    t5 = stack_pop();
    t4 = stack_pop();
    t16 = stack_pop();
    t17 = stack_pop();
    t11 = stack_pop();
    t12 = stack_pop();
    t2 = stack_pop();
    t3 = rax - 1;
    t11 = &[rdi+0x1];
    t10 = [rbx+0x8];
    t12 = r15 + 1;
    if (t10 != 0) {
    }
    t13 = (signed)[r15-0x1];
    t10 = rdx & 32;
    if ( == ) {
    }
    t5 = rsi + 1;
    t6 = invalid - t5;
    if (t6 != 0) {
    }
    [rbx+0xC] = -1;
    t9 = &[rsi-0x1];
    if (rsi != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_putchars @ 0x140002970 (USER)
 * Blocks: 33 | SSA vars: 13
 * ═══════════════════════════════════════════════════ */
void __pformat_putchars(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rdi;
    int32_t rdx;
    int32_t rsi;
    int32_t rbx;
    int32_t rcx;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = [r8+0x10];
    t4 = rdx;
    /* compare rdx vs t3 */
    /* compare t3 vs t3 */
    t5 = [r8+0xC];
    t6 = t4;
    if (t5 > t6) {
    }
    t4 = &[rdx+0x1];
    t6 = t4 + rsi;
    t9 = rsi + 1;
    if (rax != 0) {
    }
    t10 = (signed)[rsi-0x1];
    if (rax == 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_puts @ 0x140002AC0 (USER)
 * Blocks: 6 | SSA vars: 10
 * ═══════════════════════════════════════════════════ */
void __pformat_puts(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rbx;
    int32_t rsi;
    int32_t rdx;
    int32_t rcx;
    uint64_t r8;
    int32_t invalid;

    t1 = rsp - 32;
    t2 = &[rsp+0x20];
    t3 = &*(DWORD*)0x140009349;
    /* compare rcx vs rcx */
    t4 = (signed)[rdx+0x10];
    if (t4 < 0) {
    }
    return;
}

/* ═══════════════════════════════════════════════════
 * __pformat_emit_inf_or_nan @ 0x140002B10 (USER)
 * Blocks: 12 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
void __pformat_emit_inf_or_nan(void) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t invalid;
    int32_t rax;
    uint64_t r9;
    int32_t r11;
    int32_t rcx;
    int32_t rdx;
    int32_t rbx;
    int32_t var_3;
    int32_t var_4;

    t1 = rsp - 48;
    [r8+0x10] = -1;
    if (rcx != 0) {
    }
    t4 = invalid & 32;
    t9 = (unsigned)[rdx+0x0];
    t5 = t9 & -33;
    t6 = t5 | t4;
    [r9+0x0] = t6;
    t8 = 0 + 1;
    if (t8 != 3) {
    }
    t11 = &[r9+0x3];
    t12 = t11 - invalid;
    __pformat_putchars();
    t1 = rsp + 48;
    t13 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __pformat_xint_isra_0 @ 0x140002BB0 (USER)
 * Blocks: 98 | SSA vars: 29
 * ═══════════════════════════════════════════════════ */
void __pformat_xint_isra_0(int param_1) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    int32_t rbx;
    int32_t rax;
    int32_t rdi;
    int32_t rcx;
    uint64_t r8;
    int32_t r12;
    int32_t rsi;
    int32_t rdx;
    int32_t r11;
    int32_t r13;
    int32_t r14;
    int32_t r15;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    if (rcx == 111) {
    }
    t6 = r8 * r9;
    t7 = (unsigned)t6 >> 0x21;
    t8 = rax + -1431655765;
    t9 = [rbx+0xC];
    /* compare t9 vs t8 */
    t5 = (signed)t9;
    t10 = t5 + 15;
    t11 = t10 & -16;
    ___chkstk_ms();
    t1 = rsp - t11;
    /* compare 0 vs 111 */
    t12 = (flags_ZF == 0);
    t13 = &[rsp+0x20];
    t14 = &[invalid+0x7];
    /* compare rdx vs rdx */
    t17 = r12;
    t21 = invalid & 32;
    t20 = t17 + 1;
    t15 = t21 & rdx;
    t9 = &[rax+0x30];
    t5 = t15 + 55;
    t10 = t5 | t9;
    t16 = t9;
    /* compare t16 vs 57 */
    t22 = (unsigned)rdx >> rcx;
    [rsi-0x1] = t16;
    if (t22 != 0) {
    }
    t13 = (r12);
    if (rsi == t13) {
    }
    if (invalid == 0) {
    }
    [rbx+0xC] = -1;
    if (invalid != 111) {
    }
    t17 = rsi - 1;
    if (rdi != 0) {
    }
    t4 = rdi & 8192;
    t24 = (signed)[rsi+0x0];
    if ( == ) {
    }
    t4 = rdi & -2049;
    [rbx+0x8] = t4;
    if (invalid != 0) {
    }
    t22 = &[rsi+0x1];
    [rsi+0x0] = 48;
    t15 = t22 - r12;
    if (t15 >= invalid) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_int_isra_0 @ 0x1400030D0 (USER)
 * Blocks: 79 | SSA vars: 24
 * ═══════════════════════════════════════════════════ */
void __pformat_int_isra_0(int param_1) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t invalid;
    int32_t rdi;
    int32_t rbx;
    int32_t rsi;
    int32_t r12;
    int32_t r11;
    uint64_t r8;
    uint64_t r9;
    int32_t r13;
    int32_t rdx;
    int32_t r15;
    int32_t rcx;
    int32_t r14;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = [rdx+0x10];
    t4 = [rdx+0x8];
    /* compare t3 vs t3 */
    t5 = t3 + 23;
    if (t4 == 0) {
    }
    t6 = [rbx+0xC];
    /* compare t6 vs rax */
    t7 = (signed)t6;
    t5 = t7 + 15;
    t8 = t5 & -16;
    ___chkstk_ms();
    t1 = rsp - t8;
    t9 = &[rsp+0x20];
    /* compare invalid vs -128 */
    if (rcx == 0) {
    }
    t14 = (signed)invalid;
    t12 = r13 + t14;
    memset();
    /* compare r12 vs t12 */
    t17 = (flags_ZF != 0);
    /* compare invalid vs invalid */
    if (rsi != 0) {
    }
    if (invalid == 0) {
    }
    t13 = rax;
    t17 = rax - 1;
    [rbx+0xC] = t17;
    if (t13 != 0) {
    }
    t1 = &arg_8;
    t21 = stack_pop();
    t6 = stack_pop();
    t4 = stack_pop();
    t9 = stack_pop();
    t12 = stack_pop();
    t22 = stack_pop();
    t14 = stack_pop();
    t2 = stack_pop();
    if (rax != 0) {
    }
    if (rcx < 0) {
    }
    t10 = r12;
    t11 = rdi & 4096;
    if (r12 == t10) {
    }
    t12 = &[r8+0x1];
    t7 = rcx / r9;
    t13 = (unsigned)rdx >> 0x3;
    t14 = &[rdx+0x0];
    t15 = t14 + t14;
    t8 = rcx - t15;
    t16 = t8 + 48;
    [r8+0x0] = t16;
    if ((unsigned)rcx <= (unsigned)9) {
    }
    if (invalid != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_emit_radix_point @ 0x140003480 (USER)
 * Blocks: 25 | SSA vars: 15
 * ═══════════════════════════════════════════════════ */
void __pformat_emit_radix_point(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rdx;
    int32_t rax;
    int32_t rdi;
    uint64_t r8;
    int32_t rsi;
    int32_t rcx;
    int32_t r12;
    uint64_t r9;
    int32_t invalid;
    int32_t var_8;
    int32_t var_A;

    t1 = rsp - 48;
    t2 = &[rsp+0x30];
    if ([rcx+0x14] == -3) {
    }
    t4 = (signed)[rbx+0x14];
    t5 = t4 + 15;
    t6 = t5 & -16;
    ___chkstk_ms();
    t1 = rsp - t6;
    t7 = &var_8;
    var_8 = 0;
    t8 = &[rsp+0x20];
    wcrtomb();
    /* compare t6 vs t6 */
    __pformat_putc();
    if (? != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_emit_float @ 0x1400035D0 (USER)
 * Blocks: 99 | SSA vars: 19
 * ═══════════════════════════════════════════════════ */
void __pformat_emit_float(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t invalid;
    int32_t rdi;
    int32_t rsi;
    int32_t rbx;
    int32_t rdx;
    int32_t rcx;
    uint64_t r8;
    int32_t r12;

    t1 = rsp - 32;
    t2 = &[rsp+0x20];
    t3 = rcx;
    if (t3 != 0) {
    }
    t5 = rax - rdx;
    [rbx+0xC] = t5;
    if (rdx != 0) {
    }
    t5 = rax - 1;
    [rbx+0xC] = t5;
    if (rsi != 0) {
    }
    if (rax != 0) {
    }
    if (invalid != 0) {
    }
    t5 = [rbx+0xC];
    if (t5 != 0) {
    }
    if (rsi != 0) {
    }
    t5 = rax - 1;
    [rbx+0x10] = t5;
    t1 = rsp + 32;
    t10 = stack_pop();
    t9 = stack_pop();
    t8 = stack_pop();
    t11 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __pformat_emit_efloat @ 0x1400039B0 (USER)
 * Blocks: 7 | SSA vars: 28
 * ═══════════════════════════════════════════════════ */
void __pformat_emit_efloat(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    int32_t rbx;
    int32_t rsi;
    int32_t rcx;
    int32_t rax;
    uint64_t r9;
    int32_t rdi;
    int32_t rdx;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = 1 - 1;
    t4 = rcx;
    t5 = (signed)t4;
    t6 = (signed)t4 >> 0x1F;
    t7 = rcx * 1717986919;
    t8 = (signed)t7 >> 0x22;
    t9 = t8 - t6;
    if ( == ) {
    }
    t10 = [rbx+0x2C];
    if (t10 != -1) {
    }
    return;
}

/* ═══════════════════════════════════════════════════
 * __pformat_efloat @ 0x140003A90 (USER)
 * Blocks: 9 | SSA vars: 12
 * ═══════════════════════════════════════════════════ */
void __pformat_efloat(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    int32_t rbx;
    int32_t rax;
    int32_t rdx;
    int32_t rcx;
    uint64_t r9;
    int32_t rsi;
    uint64_t r8;
    int32_t var_8;
    int32_t var_20;
    int32_t var_4;

    t1 = rsp - 80;
    t2 = &[rsp+0x50];
    t3 = [rdx+0x10];
    /* asm: fld [rcx+0x0] */;
    if (t3 < 0) {
    }
    __pformat_emit_efloat();
    __freedtoa();
    t1 = rsp + 80;
    t9 = stack_pop();
    t10 = stack_pop();
    t2 = stack_pop();
    return;
    if (? != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_float @ 0x140003B30 (USER)
 * Blocks: 16 | SSA vars: 16
 * ═══════════════════════════════════════════════════ */
void __pformat_float(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    int32_t rbx;
    int32_t rax;
    int32_t rdx;
    int32_t rcx;
    uint64_t r9;
    int32_t rsi;
    uint64_t r8;
    int32_t var_8;
    int32_t var_20;
    int32_t var_4;

    t1 = rsp - 80;
    t2 = &[rsp+0x50];
    t3 = [rdx+0x10];
    /* asm: fld [rcx+0x0] */;
    if (t3 >= 0) {
    }
    __pformat_emit_float();
    if (? != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_gfloat @ 0x140003C10 (USER)
 * Blocks: 28 | SSA vars: 15
 * ═══════════════════════════════════════════════════ */
void __pformat_gfloat(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    int32_t rbx;
    int32_t rax;
    int32_t rdx;
    int32_t rcx;
    uint64_t r9;
    int32_t rdi;
    int32_t rsi;
    uint64_t r8;
    int32_t var_8;
    int32_t var_20;
    int32_t var_4;

    t1 = rsp - 88;
    t2 = &[rsp+0x50];
    t3 = [rdx+0x10];
    /* asm: fld [rcx+0x0] */;
    if (t3 < 0) {
    }
    t4 = &var_8;
    t5 = &var_20;
    /* asm: t6 */;
    t7 = &var_4;
    [rsp+0x20] = t4;
    t8 = __pformat_cvt();
    /* compare t8 vs -32768 */
    __pformat_emit_inf_or_nan();
    if (? != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __pformat_emit_xfloat_isra_0 @ 0x140003D70 (USER)
 * Blocks: 97 | SSA vars: 33
 * ═══════════════════════════════════════════════════ */
void __pformat_emit_xfloat_isra_0(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t invalid;
    uint64_t r9;
    int32_t rax;
    int32_t rbx;
    int32_t r12;
    int32_t rdx;
    int32_t rdi;
    int32_t rsi;
    int32_t rcx;
    int32_t r14;
    uint64_t r8;
    int32_t r13;
    int32_t var_20;
    int32_t var_1F;
    int32_t var_8;
    int32_t var_18;
    int32_t var_10;
    int32_t var_30;
    int32_t var_28;
    int32_t var_24;
    int32_t var_14;
    int32_t var_C;
    int32_t var_4;

    t1 = rsp - 80;
    t2 = &[rsp+0x50];
    if (rdx != 0) {
    }
    t3 = &[rax-0x3];
    if ((unsigned)t3 <= (unsigned)14) {
    }
    t3 = [rbx+0x8];
    t5 = &var_20;
    if (t3 == 0) {
    }
    t12 = [rbx+0x10];
    t10 = (signed)invalid;
    t24 = (signed)invalid;
    t15 = rsi - rdi;
    t3 = &[rdx+0x0];
    /* compare t12 vs t12 */
    t18 = t3 & 448;
    t22 = sbb(ecx, -6);
    t25 = t24 * 1717986919;
    t13 = (signed)t10 >> 0x1F;
    t26 = (signed)t25 >> 0x22;
    t27 = t22 - t13;
    if (t18 == 1) {
    }
    t3 = invalid - invalid;
    if (t3 != 0) {
    }
    if (invalid != 0) {
    }
    __pformat_putc();
    t15 = [rbx+0x8];
    t16 = t15 & 32;
    t22 = t16 | 88;
    __pformat_putc();
    t10 = [rbx+0xC];
    /* compare t10 vs t10 */
    t23 = &(t10);
    if ((unsigned)rdi < (unsigned)rsi) {
    }
    t10 = [rbx+0x10];
    t12 = &[rax-0x1];
    [rbx+0x10] = t12;
    if (t10 != 0) {
    }
    t14 = [rbx+0x8];
    t15 = t14 & 32;
    t16 = t15 | 80;
    __pformat_putc();
    [rbx+0xC] = [rbx+0xC] + invalid;
    [rbx+0x8] = [rbx+0x8] | 448;
    t1 = rsp + 80;
    t30 = stack_pop();
    t9 = stack_pop();
    t5 = stack_pop();
    t4 = stack_pop();
    t31 = stack_pop();
    t23 = stack_pop();
    t2 = stack_pop();
    if (? != 0) {
    }
    return;
}

/* ═══════════════════════════════════════════════════
 * __mingw_pformat @ 0x140004230 (USER)
 * Blocks: 157 | SSA vars: 37
 * ═══════════════════════════════════════════════════ */
void __mingw_pformat(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t r14;
    int32_t rdi;
    int32_t r12;
    int32_t rbx;
    int32_t rsi;
    int32_t rdx;
    int32_t rcx;
    int32_t rax;
    int32_t r13;
    int32_t r15;
    uint64_t r8;
    int32_t r10;
    int32_t invalid;
    uint64_t r9;
    int32_t var_18;
    int32_t var_20;
    int32_t var_10;
    int32_t var_30;
    int32_t var_28;
    int32_t var_24;
    int32_t var_14;
    int32_t var_C;
    int32_t var_4;
    int32_t var_6C;
    int32_t var_68;
    int32_t var_40;
    int32_t var_60;
    int32_t var_80;
    int32_t var_78;
    int32_t var_88;
    int32_t var_70;
    int32_t var_42;

    t1 = rsp - 184;
    t2 = &[rsp+0xB0];
    _errno();
    t3 = rcx & 24576;
    var_18 = 0;
    t4 = &[rsi+0x1];
    var_20 = -8589934593;
    var_10 = 0;
    t5 = (signed)[rsi+0x0];
    var_30 = rdx;
    var_28 = t3;
    var_24 = -1;
    var_14 = 0;
    var_C = 0;
    var_4 = -1;
    /* compare t5 vs t5 */
    t1 = rsp + 184;
    t15 = stack_pop();
    t6 = stack_pop();
    t16 = stack_pop();
    t12 = stack_pop();
    t7 = stack_pop();
    t17 = stack_pop();
    t10 = stack_pop();
    t2 = stack_pop();
    t6 = &var_24;
    var_6C = rax;
    t7 = &*(DWORD*)0x140009369;
    var_68 = t6;
    if (rcx != 37) {
    }
    t11 = var_C;
    t1 = rsp + 184;
    t15 = stack_pop();
    t6 = stack_pop();
    t16 = stack_pop();
    t12 = stack_pop();
    t7 = stack_pop();
    t17 = stack_pop();
    t10 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __rv_alloc_D2A @ 0x140004C40 (USER)
 * Blocks: 4 | SSA vars: 7
 * ═══════════════════════════════════════════════════ */
void __rv_alloc_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rax;
    int32_t rdx;
    int32_t rcx;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    if (rcx <= 27) {
    }
    __Balloc_D2A();
    [rax+0x0] = rbx;
    t6 = rax + 4;
    t1 = rsp + 40;
    t4 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __nrv_alloc_D2A @ 0x140004C80 (USER)
 * Blocks: 12 | SSA vars: 15
 * ═══════════════════════════════════════════════════ */
void __nrv_alloc_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rdi;
    int32_t rsi;
    int32_t rax;
    int32_t rbx;
    int32_t rdx;
    int32_t rcx;
    uint64_t r8;
    double xmm0;
    double xmm1;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    if (invalid <= 27) {
    }
    __Balloc_D2A();
    t5 = &[rdi+0x1];
    [rax+0x0] = rbx;
    t8 = (unsigned)[rdi+0x0];
    t9 = &[rax+0x4];
    [rax+0x4] = t8;
    /* compare t8 vs t8 */
    if (rsi == 0) {
    }
    t10 = (unsigned)[rdx+0x0];
    t6 = rax + 1;
    t5 = rdx + 1;
    [rax+0x0] = t10;
    if (t10 != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __freedtoa @ 0x140004D00 (USER)
 * Blocks: 2 | SSA vars: 12
 * ═══════════════════════════════════════════════════ */
void __freedtoa(void) {
    /* local variables */
    int32_t rdx;
    int32_t rax;
    int32_t rcx;
    double xmm0;
    double xmm1;
    int32_t rsp;
    int32_t rbp;
    int32_t rsi;
    int32_t r13;
    int32_t r11;

    t1 = [rcx-0x4];
    t2 = 1 << t1;
    t3 = &[rax-0x4];
    /* asm: punpckldq xmm0 xmm1 */;
    [rax+0x4] = t1;
    return;
}

/* ═══════════════════════════════════════════════════
 * __quorem_D2A @ 0x140004D30 (USER)
 * Blocks: 24 | SSA vars: 36
 * ═══════════════════════════════════════════════════ */
void __quorem_D2A(int param_1, int param_2, int param_3, int param_4) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rsi;
    int32_t r13;
    int32_t r11;
    int32_t rbx;
    int32_t r12;
    int32_t rdx;
    int32_t r10;
    int32_t rdi;
    int32_t invalid;
    int32_t rcx;
    uint64_t r9;
    uint64_t r8;
    int32_t r14;
    int32_t r15;
    int32_t var_8;
    int32_t var_4;
    int32_t var_28;
    int32_t var_30;
    int32_t var_34;
    int32_t var_18;
    int32_t var_20;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    t3 = [rdx+0x14];
    if ([rcx+0x14] < t3) {
    }
}

/* ═══════════════════════════════════════════════════
 * __gdtoa @ 0x140004EB0 (USER)
 * Blocks: 306 | SSA vars: 56
 * ═══════════════════════════════════════════════════ */
void __gdtoa(int param_1, int param_2, int param_3, int param_4) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rdi;
    int32_t r12;
    int32_t rsi;
    int32_t r15;
    int32_t rbx;
    int32_t invalid;
    int32_t rcx;
    int32_t rdx;
    uint64_t r8;
    int32_t r14;
    int32_t r10;
    double xmm1;
    uint64_t r9;
    double xmm0;
    double xmm5;
    int32_t r13;
    double xmm4;
    double xmm2;
    double xmm3;
    int32_t var_28;
    int32_t var_30;
    int32_t var_34;
    int32_t var_20;
    int32_t var_40;
    int32_t var_4;
    int32_t var_58;
    int32_t var_98;
    int32_t var_50;
    int32_t var_7C;
    int32_t var_68;
    int32_t var_70;
    int32_t var_74;
    int32_t var_8C;
    int32_t var_78;
    int32_t var_90;
    int32_t var_48;
    int32_t var_88;
    int32_t var_80;
    int32_t var_60;
    int32_t var_38;

    t1 = rsp - 200;
    t2 = &[rsp+0xC0];
    t3 = arg_70;
    t4 = [r9+0x0];
    var_28 = t3;
    t5 = arg_78;
    var_30 = rdx;
    var_34 = t5;
    t6 = arg_80;
    t7 = arg_88;
    var_20 = t7;
    t8 = t4 & -49;
    [r9+0x0] = t8;
    t9 = t4 & 7;
    if (t9 == 3) {
    }
}

/* ═══════════════════════════════════════════════════
 * __rshift_D2A @ 0x1400064D0 (USER)
 * Blocks: 21 | SSA vars: 20
 * ═══════════════════════════════════════════════════ */
void __rshift_D2A(void) {
    /* local variables */
    int32_t rbp;
    int32_t rbx;
    int32_t invalid;
    int32_t r10;
    int32_t rsi;
    int32_t rdi;
    int32_t r12;
    int32_t r13;
    int32_t r11;
    int32_t rdx;
    int32_t rcx;
    uint64_t r8;
    int32_t rax;

    t1 = &[rsp+0x0];
    t2 = (signed)[rcx+0x14];
    t3 = (signed)rdx >> 0x5;
    if (t2 > t3) {
    }
    [r10+0x14] = 0;
    [r10+0x18] = 0;
    t2 = stack_pop();
    t4 = stack_pop();
    t5 = stack_pop();
    t6 = stack_pop();
    t7 = stack_pop();
    t1 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __trailz_D2A @ 0x1400065E0 (USER)
 * Blocks: 9 | SSA vars: 9
 * ═══════════════════════════════════════════════════ */
void __trailz_D2A(void) {
    /* local variables */
    int32_t rdx;
    int32_t rax;
    int32_t rcx;
    int32_t invalid;
    int32_t rsp;
    int32_t rbp;
    int32_t rsi;

    t1 = (signed)[rcx+0x14];
    t2 = &[rcx+0x18];
    t3 = &[rax+0x0];
    if ((unsigned)t2 < (unsigned)t3) {
    }
}

/* ═══════════════════════════════════════════════════
 * dtoa_lock @ 0x140006620 (USER)
 * Blocks: 23 | SSA vars: 15
 * ═══════════════════════════════════════════════════ */
void dtoa_lock(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rsi;
    int32_t rbx;
    int32_t rcx;
    int32_t rdi;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = *(DWORD*)0x14000CAEA;
    if (t3 == 2) {
    }
    t4 = &*(DWORD*)0x14000CAF9;
    t8 = 0 - rsi;
    t9 = t8 & 40;
    t15 = t9 + rbx;
    t1 = rsp + 40;
    t4 = stack_pop();
    t5 = stack_pop();
    t6 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __Balloc_D2A @ 0x140006760 (USER)
 * Blocks: 14 | SSA vars: 18
 * ═══════════════════════════════════════════════════ */
void __Balloc_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rdx;
    int32_t rax;
    uint64_t r8;
    int32_t rsi;
    int32_t var_8;

    t1 = rsp - 48;
    t2 = &[rsp+0x30];
    t3 = rcx;
    dtoa_lock();
    /* compare t3 vs 9 */
    t8 = 1 << rbx;
    t6 = &[rsi-0x1];
    t9 = (signed)t6;
    t10 = &[invalid+0x27];
    t11 = (unsigned)t10 >> 0x3;
    t12 = t11 << 0x3;
    malloc();
    /* compare t9 vs t9 */
    t1 = rsp + 48;
    t3 = stack_pop();
    t13 = stack_pop();
    t2 = stack_pop();
    [rax+0x8] = rbx;
    [rax+0xC] = rsi;
    if (gvar_14000CAE9 == 2) {
    }
    [rax+0x10] = 0;
    t1 = rsp + 48;
    t3 = stack_pop();
    t13 = stack_pop();
    t2 = stack_pop();
    t4 = &*(DWORD*)0x14000CA99;
    t5 = (signed)rbx;
    t6 = [rdx+0x0];
    if (t6 == 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __Bfree_D2A @ 0x140006860 (USER)
 * Blocks: 9 | SSA vars: 13
 * ═══════════════════════════════════════════════════ */
void __Bfree_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rdx;
    int32_t rax;
    int32_t rdi;
    int32_t rsi;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    if (rcx == 0) {
    }
    t1 = rsp + 40;
    t3 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __multadd_D2A @ 0x1400068D0 (USER)
 * Blocks: 10 | SSA vars: 17
 * ═══════════════════════════════════════════════════ */
void __multadd_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rdi;
    int32_t rbx;
    int32_t rsi;
    int32_t rdx;
    int32_t rcx;
    int32_t rax;
    int32_t r12;
    uint64_t r8;

    t1 = rsp - 32;
    t2 = &[rsp+0x20];
    t3 = [rcx+0x14];
    t4 = (signed)invalid;
    t5 = (signed)rdx;
    t6 = [rbx+0x18];
    t7 = t6 * t5;
    t8 = t7 + t4;
    [rbx+0x18] = t8;
    t9 = 0 + 1;
    t10 = (unsigned)t8 >> 0x20;
    if (t3 > t9) {
    }
    if (rsi == 0) {
    }
    t1 = rsp + 32;
    t13 = stack_pop();
    t4 = stack_pop();
    t3 = stack_pop();
    t16 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __i2b_D2A @ 0x140006990 (USER)
 * Blocks: 12 | SSA vars: 13
 * ═══════════════════════════════════════════════════ */
void __i2b_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rax;
    int32_t rdx;
    int32_t r14;
    int32_t r13;
    uint64_t r9;
    int32_t r15;
    int32_t var_8;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    dtoa_lock();
    t3 = (t4);
    /* compare t3 vs t3 */
    t3 = *(DWORD*)0x140008059;
    t6 = &*(DWORD*)0x14000C199;
    t7 = t3 - t6;
    t8 = (signed)t7 >> 0x3;
    t9 = t8 + 5;
    if ((unsigned)t9 <= (unsigned)288) {
    }
    t4 = *(DWORD*)0x1400096C1;
    [rax+0x8] = t4;
    if (gvar_14000CAE9 != 2) {
    }
    t4 = *(DWORD*)0x1400096C9;
    [rax+0x18] = rbx;
    [rax+0x10] = t4;
    t1 = rsp + 56;
    t5 = stack_pop();
    t2 = stack_pop();
    t4 = [rax+0x0];
    if (gvar_14000CAE9 == 2) {
    }
}

/* ═══════════════════════════════════════════════════
 * __mult_D2A @ 0x140006A50 (USER)
 * Blocks: 23 | SSA vars: 27
 * ═══════════════════════════════════════════════════ */
void __mult_D2A(int param_1) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t r14;
    int32_t r13;
    uint64_t r9;
    int32_t r15;
    int32_t rax;
    int32_t rcx;
    int32_t rbx;
    int32_t rdi;
    int32_t r12;
    int32_t rsi;
    int32_t rdx;
    uint64_t r8;
    int32_t r11;
    int32_t r10;
    int32_t invalid;
    int32_t var_8;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    t3 = (signed)[rcx+0x14];
    t4 = (signed)[rdx+0x14];
    if (invalid < invalid) {
    }
    t6 = rcx + 1;
    arg_50 = r9;
    __Balloc_D2A();
    /* compare rax vs rax */
    t1 = rsp + 56;
    t5 = stack_pop();
    t9 = stack_pop();
    t23 = stack_pop();
    t7 = stack_pop();
    t4 = stack_pop();
    t3 = stack_pop();
    t24 = stack_pop();
    t2 = stack_pop();
    t7 = &[rax+0x18];
    t8 = (signed)rbx;
    t9 = &[r12+0x0];
    if ((unsigned)t7 >= (unsigned)t9) {
    }
    t17 = &[r15+0x19];
    t10 = r13 - r15;
    t11 = t10 - 25;
    t12 = (unsigned)t11 >> 0x2;
    /* compare r13 vs t17 */
    t18 = &[invalid+0x4];
    var_8 = t18;
    t19 = [r9+0x0];
    t14 = r9 + 4;
    if (t19 == 0) {
    }
    if (rbx != 0) {
    }
    [rdi+0x14] = rbx;
    t1 = rsp + 56;
    t5 = stack_pop();
    t9 = stack_pop();
    t23 = stack_pop();
    t7 = stack_pop();
    t4 = stack_pop();
    t3 = stack_pop();
    t24 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __pow5mult_D2A @ 0x140006BC0 (USER)
 * Blocks: 30 | SSA vars: 16
 * ═══════════════════════════════════════════════════ */
void __pow5mult_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rsi;
    int32_t rbx;
    int32_t r12;
    int32_t rdi;
    int32_t rdx;
    int32_t rcx;
    int32_t invalid;
    int32_t r13;

    t1 = rsp - 32;
    t2 = &[rsp+0x20];
    t3 = rdx & 3;
    if ( != ) {
    }
    t4 = (signed)rbx >> 0x2;
    if ( == ) {
    }
    t1 = rsp + 32;
    t4 = stack_pop();
    t6 = stack_pop();
    t5 = stack_pop();
    t7 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __lshift_D2A @ 0x140006D50 (USER)
 * Blocks: 18 | SSA vars: 28
 * ═══════════════════════════════════════════════════ */
void __lshift_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t r13;
    int32_t rsi;
    int32_t rcx;
    int32_t invalid;
    int32_t rbx;
    int32_t rax;
    int32_t r15;
    int32_t rdi;
    int32_t rdx;
    uint64_t r8;
    uint64_t r9;
    int32_t r12;
    int32_t r14;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = [r13+0x14];
    t4 = (signed)rdx >> 0x5;
    t5 = [r13+0xC];
    t6 = t3 + t4;
    t7 = &[rbx+0x1];
    if (t7 <= t5) {
    }
    __Balloc_D2A();
    /* compare rax vs rax */
    t1 = rsp + 40;
    t3 = stack_pop();
    t10 = stack_pop();
    t9 = stack_pop();
    t23 = stack_pop();
    t24 = stack_pop();
    t25 = stack_pop();
    t26 = stack_pop();
    t2 = stack_pop();
    t9 = &[rax+0x18];
    if (rsi != 0) {
    }
    t7 = 32 - 32;
    t5 = [rsi+0x0];
    t14 = rdi + 4;
    t10 = rsi + 4;
    t15 = t5 << t7;
    t16 = t15 | 0;
    [r9-0x4] = t16;
    t17 = [rsi-0x4];
    t18 = (unsigned)t17 >> t7;
    if ((unsigned)t10 < (unsigned)r8) {
    }
    t8 = &[r13+0x19];
    t15 = r8 - r13;
    t16 = t15 - 25;
    t21 = (unsigned)t16 >> 0x2;
    /* compare r8 vs t8 */
    t22 = &[invalid+0x4];
    [rdi+0x0] = rdx;
    if (rdx != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __cmp_D2A @ 0x140006E80 (USER)
 * Blocks: 8 | SSA vars: 10
 * ═══════════════════════════════════════════════════ */
void __cmp_D2A(void) {
    /* local variables */
    int32_t rax;
    int32_t invalid;
    uint64_t r8;
    int32_t rcx;
    int32_t rdx;
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rsi;

    t1 = (signed)[rdx+0x14];
    t2 = [rcx+0x14];
    t3 = t2 - t1;
    if ( != ) {
    }
}

/* ═══════════════════════════════════════════════════
 * __diff_D2A @ 0x140006ED0 (USER)
 * Blocks: 28 | SSA vars: 32
 * ═══════════════════════════════════════════════════ */
void __diff_D2A(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rbx;
    int32_t rsi;
    int32_t rdx;
    int32_t rcx;
    int32_t rdi;
    uint64_t r9;
    int32_t r13;
    int32_t r12;
    int32_t r10;
    int32_t r11;
    uint64_t r8;
    int32_t invalid;
    int32_t r14;

    t1 = rsp - 32;
    t2 = &[rsp+0x20];
    t3 = (signed)[rdx+0x14];
    if ([rcx+0x14] != t3) {
    }
    __Balloc_D2A();
    /* compare rax vs rax */
    t1 = rsp + 32;
    t24 = stack_pop();
    t27 = stack_pop();
    t7 = stack_pop();
    t9 = stack_pop();
    t8 = stack_pop();
    t21 = stack_pop();
    t2 = stack_pop();
    [rax+0x10] = rdi;
    t3 = (signed)[rsi+0x14];
    t8 = &[rsi+0x18];
    t9 = &[r9+0x18];
    t10 = &[r13+0x0];
    t11 = (signed)[rbx+0x14];
    t12 = &[rbx+0x18];
    t7 = [rbx+0x0];
    t13 = [rsi+0x0];
    t14 = t13 - t7;
    t15 = t14 - 0;
    [r9+0x0] = t15;
    t16 = 24 + 4;
    t17 = (unsigned)t15 >> 0x20;
    t18 = &[rcx+0x0];
    t19 = t17 & 1;
    if ((unsigned)t18 < (unsigned)t12) {
    }
    t3 = &[rbx+0x19];
    t5 = 4;
    /* compare r8 vs t3 */
    t20 = (flags_CF == 0);
    t12 = r8 - rbx;
    t21 = &[r8-0x19];
    t22 = (unsigned)t21 >> 0x2;
    /* compare t20 vs t20 */
    t11 = &[invalid+0x4];
    t8 = r13 + t5;
    t23 = &[r12+0x0];
    if ((unsigned)t8 >= (unsigned)r11) {
    }
    t4 = [rax-0x4];
    t3 = rax - 4;
    t20 = invalid - 1;
    if (t4 == 0) {
    }
    [r9+0x14] = invalid;
    t1 = rsp + 32;
    t24 = stack_pop();
    t27 = stack_pop();
    t7 = stack_pop();
    t9 = stack_pop();
    t8 = stack_pop();
    t21 = stack_pop();
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __b2d_D2A @ 0x1400070A0 (USER)
 * Blocks: 28 | SSA vars: 30
 * ═══════════════════════════════════════════════════ */
void __b2d_D2A(void) {
    /* local variables */
    int32_t rbp;
    int32_t rax;
    int32_t r11;
    int32_t r10;
    int32_t invalid;
    int32_t rsi;
    int32_t rcx;
    int32_t rdi;
    int32_t rbx;
    int32_t rdx;
    double xmm0;
    int32_t rsp;
    double xmm6;

    t1 = &[rsp+0x0];
    t2 = (signed)[rcx+0x14];
    t3 = &[rcx+0x18];
    t4 = &[r11+0x0];
    t5 = &[r10-0x4];
    t6 = bsr(invalid);
    t7 = 32;
    t8 = t6 ^ 31;
    t9 = t7 - t8;
    [rdx+0x0] = t9;
    if (t8 <= 10) {
    }
}

/* ═══════════════════════════════════════════════════
 * strnlen @ 0x140007300 (USER)
 * Blocks: 7 | SSA vars: 4
 * ═══════════════════════════════════════════════════ */
char* strnlen(void) {
    /* local variables */
    int32_t invalid;
    int32_t rax;
    uint64_t r8;

    if (rdx != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * wcsnlen @ 0x140007330 (USER)
 * Blocks: 8 | SSA vars: 4
 * ═══════════════════════════════════════════════════ */
void wcsnlen(void) {
    /* local variables */
    int32_t invalid;
    int32_t rax;
    uint64_t r8;

    if (rdx != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * __p__fmode @ 0x140007360 (USER)
 * Blocks: 2 | SSA vars: 2
 * ═══════════════════════════════════════════════════ */
void __p__fmode(void) {
    /* local variables */
    int32_t rax;

}

/* ═══════════════════════════════════════════════════
 * __p__commode @ 0x140007370 (USER)
 * Blocks: 2 | SSA vars: 6
 * ═══════════════════════════════════════════════════ */
void __p__commode(void) {
    /* local variables */
    int32_t rax;
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;

}

/* ═══════════════════════════════════════════════════
 * _lock_file @ 0x140007380 (USER)
 * Blocks: 5 | SSA vars: 10
 * ═══════════════════════════════════════════════════ */
void _lock_file(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rdx;
    int32_t rax;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = rcx;
    __acrt_iob_func();
    /* compare t3 vs rax */
    t4 = &[rbx+0x30];
    t1 = rsp + 40;
    t3 = stack_pop();
    t2 = stack_pop();
    __acrt_iob_func();
    /* compare rbx vs rax */
    __acrt_iob_func();
    t5 = rbx - rax;
    t6 = (signed)t5 >> 0x4;
    t7 = t6 * -1431655765;
    t8 = &[rax+0x10];
    _lock();
    [rbx+0x18] = [rbx+0x18] | 32768;
    t1 = rsp + 40;
    t3 = stack_pop();
    t2 = stack_pop();
    return;
    if (? != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * _unlock_file @ 0x1400073F0 (USER)
 * Blocks: 7 | SSA vars: 9
 * ═══════════════════════════════════════════════════ */
void _unlock_file(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rax;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    t3 = rcx;
    __acrt_iob_func();
    /* compare t3 vs rax */
    t4 = &[rbx+0x30];
    t1 = rsp + 40;
    t3 = stack_pop();
    t2 = stack_pop();
    __acrt_iob_func();
    /* compare rbx vs rax */
    [rbx+0x18] = [rbx+0x18] & -32769;
    __acrt_iob_func();
    t3 = rbx - rax;
    t5 = (signed)t3 >> 0x4;
    t6 = t5 * -1431655765;
    t7 = &[rbx+0x10];
    t1 = rsp + 40;
    t8 = stack_pop();
    t2 = stack_pop();
    if (? != 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * mingw_set_invalid_parameter_handler @ 0x140007470 (USER)
 * Blocks: 2 | SSA vars: 10
 * ═══════════════════════════════════════════════════ */
HANDLE mingw_set_invalid_parameter_handler(void) {
    /* local variables */
    int32_t rax;
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rdx;

    *(DWORD*)0x14000CB59 = t1;
}

/* ═══════════════════════════════════════════════════
 * __acrt_iob_func @ 0x140007480 (USER)
 * Blocks: 2 | SSA vars: 10
 * ═══════════════════════════════════════════════════ */
void __acrt_iob_func(int param_1) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rcx;
    int32_t rdx;
    int32_t rax;

    t1 = rsp - 40;
    t2 = &[rsp+0x20];
    __iob_func();
    t3 = &[rcx+0x0];
    t4 = t3 << 0x4;
    t5 = rax + t4;
    t6 = t1 + 40;
    t7 = stack_pop();
    t8 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __wcrtomb_cp @ 0x1400074B0 (USER)
 * Blocks: 9 | SSA vars: 19
 * ═══════════════════════════════════════════════════ */
void __wcrtomb_cp(int param_1) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t rax;
    int32_t rcx;
    int32_t rdx;
    uint64_t r8;
    int32_t invalid;
    int32_t rbx;
    int32_t rsi;
    int32_t rdi;
    int32_t var_4;
    int32_t var_5;

    t1 = rsp - 80;
    arg_18 = rdx;
    if (invalid != 0) {
    }
    _errno();
    [rax+0x0] = 42;
    t1 = rsp + 80;
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * wcrtomb @ 0x140007540 (USER)
 * Blocks: 25 | SSA vars: 22
 * ═══════════════════════════════════════════════════ */
void wcrtomb(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rbx;
    int32_t rax;
    int32_t rsi;
    int32_t rdi;
    int32_t rdx;
    int32_t invalid;
    int32_t rcx;
    int32_t r12;
    int32_t r15;
    int32_t r13;
    int32_t r14;
    int32_t var_5;

    t1 = rsp - 56;
    t2 = &[rsp+0x30];
    /* compare rcx vs rcx */
    t3 = &var_5;
    ___mb_cur_max_func();
    ___lc_codepage_func();
    t4 = (unsigned)rdx;
    __wcrtomb_cp();
    t5 = (signed)t3;
    t6 = t1 + 56;
    t7 = stack_pop();
    t8 = stack_pop();
    t9 = stack_pop();
    t10 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __mbrtowc_cp @ 0x1400076A0 (USER)
 * Blocks: 26 | SSA vars: 23
 * ═══════════════════════════════════════════════════ */
void __mbrtowc_cp(int param_1, int param_2, int param_3) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rdi;
    int32_t rbx;
    int32_t rax;
    int32_t rdx;
    int32_t rcx;
    uint64_t r8;
    uint64_t r9;
    int32_t invalid;
    int32_t rsi;
    int32_t r12;
    int32_t r13;
    int32_t var_4;
    int32_t var_3;

    t1 = rsp - 64;
    t2 = &[rsp+0x40];
    if (rdx == 0) {
    }
}

/* ═══════════════════════════════════════════════════
 * mbrtowc @ 0x1400077F0 (USER)
 * Blocks: 24 | SSA vars: 28
 * ═══════════════════════════════════════════════════ */
void mbrtowc(void) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rbx;
    int32_t rsi;
    int32_t rdi;
    int32_t r12;
    int32_t invalid;
    uint64_t r8;
    uint64_t r9;
    int32_t rdx;
    int32_t rcx;
    int32_t r13;
    int32_t r15;
    int32_t r14;
    int32_t var_2;

    t1 = rsp - 72;
    t2 = &[rsp+0x40];
    /* compare rcx vs rcx */
    var_2 = 0;
    t3 = &var_2;
    t4 = r9;
    ___mb_cur_max_func();
    ___lc_codepage_func();
    /* compare t4 vs t4 */
    [rsp+0x28] = t3;
    [rsp+0x20] = t3;
    t5 = &*(DWORD*)0x14000CB71;
    __mbrtowc_cp();
    t6 = (signed)t3;
    t7 = t1 + 72;
    t8 = stack_pop();
    t9 = stack_pop();
    t10 = stack_pop();
    t11 = stack_pop();
    t12 = stack_pop();
    t13 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * ___lc_codepage_func @ 0x1400079F8 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void ___lc_codepage_func(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * ___mb_cur_max_func @ 0x140007A00 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void ___mb_cur_max_func(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * __getmainargs @ 0x140007A08 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void __getmainargs(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * __iob_func @ 0x140007A10 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void __iob_func(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * __set_app_type @ 0x140007A18 (USER)
 * Blocks: 4 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void __set_app_type(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * _amsg_exit @ 0x140007A28 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void _amsg_exit(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * _cexit @ 0x140007A30 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void _cexit(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * _errno @ 0x140007A38 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void _errno(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * _initterm @ 0x140007A40 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void _initterm(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * _lock @ 0x140007A48 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void _lock(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * _onexit @ 0x140007A50 (USER)
 * Blocks: 4 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void _onexit(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * abort @ 0x140007A60 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void abort(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * calloc @ 0x140007A68 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void calloc(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * exit @ 0x140007A70 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void exit(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * fprintf @ 0x140007A78 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void fprintf(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * fputc @ 0x140007A80 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void fputc(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * free @ 0x140007A88 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void free(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * fwrite @ 0x140007A90 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void fwrite(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * localeconv @ 0x140007A98 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void localeconv(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * malloc @ 0x140007AA0 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void malloc(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * memcpy @ 0x140007AA8 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void memcpy(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * memset @ 0x140007AB0 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void memset(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * signal @ 0x140007AB8 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void signal(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * strerror @ 0x140007AC0 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
char* strerror(void) {
    return 0;
}

/* ═══════════════════════════════════════════════════
 * strlen @ 0x140007AC8 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
char* strlen(void) {
    return 0;
}

/* ═══════════════════════════════════════════════════
 * strncmp @ 0x140007AD0 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
char* strncmp(void) {
    return 0;
}

/* ═══════════════════════════════════════════════════
 * vfprintf @ 0x140007AD8 (USER)
 * Blocks: 2 | SSA vars: 0
 * ═══════════════════════════════════════════════════ */
void vfprintf(void) {
    return;
}

/* ═══════════════════════════════════════════════════
 * wcslen @ 0x140007AE0 (USER)
 * Blocks: 17 | SSA vars: 1
 * ═══════════════════════════════════════════════════ */
void wcslen(void) {
    /* local variables */
    int32_t rbx;

    return;
}

