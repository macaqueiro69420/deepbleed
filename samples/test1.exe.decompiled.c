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
void __pformat_cvt(int param_1); /* USER @ 0x140002680 */
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = 0;
    t3 = *(DWORD*)0x30;
    t4 = *(uintptr_t*)(rax+0x8);
    t3 = rdi;
    *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
    if (t3 != 0) {
    }
    t4 = *(DWORD*)0x1400097D9;
    t2 = 0;
    t3 = *(uintptr_t*)(rsi+0x0);
    if (t3 == 1) {
    }
    if (rdi == 0) {
    }
    t3 = *(DWORD*)0x140009729;
    t6 = *(uintptr_t*)(rax+0x0);
    if (t6 == 0) {
    }
    t2 = rdi - 8;
    t5 = *(uintptr_t*)(r13+0x0);
    strlen(*(uintptr_t*)(r13+0x0));
    t4 = &*(uintptr_t*)(rax+0x1);
    t8 = t4;
    malloc(rsi_0);
    t16 = t4;
    *(uintptr_t*)(r12+0x0) = rax;
    t7 = *(uintptr_t*)(r13+0x0);
    t10 = rax;
    t17 = 0 + 8;
    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
    t5 = *(uintptr_t*)(r13+0x0);
    strlen(*(uintptr_t*)(r13+0x0));
    t4 = &*(uintptr_t*)(rax+0x1);
    t8 = t4;
    malloc(rsi_0);
    t16 = t4;
    *(uintptr_t*)(r12+0x0) = rax;
    t7 = *(uintptr_t*)(r13+0x0);
    t10 = rax;
    t11 = rbx + 8;
    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
    t2 = rdi + r12;
    *(uintptr_t*)(rdi+0x0) = 0;
    *(DWORD*)0x14000C019 = r12;
    __main(*(DWORD*)0x14000C006);
    t3 = *(DWORD*)0x140009749;
    t16 = *(DWORD*)0x14000C011;
    t5 = *(DWORD*)0x14000C022;
    t6 = *(uintptr_t*)(rax+0x0);
    *(uintptr_t*)(rax+0x0) = t16;
    t7 = r12;
    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
    t8 = *(DWORD*)0x14000C006;
    *(DWORD*)0x14000C00A = t6;
    do {
        t3 = rdi;
        *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
        if (t3 != 0) {
        }
        t4 = *(DWORD*)0x1400097D9;
        t2 = 0;
        t3 = *(uintptr_t*)(rsi+0x0);
        if (t3 == 1) {
        }
        if (rdi == 0) {
        }
        t3 = *(DWORD*)0x140009729;
        t6 = *(uintptr_t*)(rax+0x0);
        if (t6 == 0) {
        }
        t2 = rdi - 8;
        t5 = *(uintptr_t*)(r13+0x0);
        strlen(*(uintptr_t*)(r13+0x0));
        t4 = &*(uintptr_t*)(rax+0x1);
        t8 = t4;
        malloc(rsi_0);
        t16 = t4;
        *(uintptr_t*)(r12+0x0) = rax;
        t7 = *(uintptr_t*)(r13+0x0);
        t10 = rax;
        t17 = 0 + 8;
        memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
        t5 = *(uintptr_t*)(r13+0x0);
        strlen(*(uintptr_t*)(r13+0x0));
        t4 = &*(uintptr_t*)(rax+0x1);
        t8 = t4;
        malloc(rsi_0);
        t16 = t4;
        *(uintptr_t*)(r12+0x0) = rax;
        t7 = *(uintptr_t*)(r13+0x0);
        t10 = rax;
        t11 = rbx + 8;
        memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
        t2 = rdi + r12;
        *(uintptr_t*)(rdi+0x0) = 0;
        *(DWORD*)0x14000C019 = r12;
        __main(*(DWORD*)0x14000C006);
        t3 = *(DWORD*)0x140009749;
        t16 = *(DWORD*)0x14000C011;
        t5 = *(DWORD*)0x14000C022;
        t6 = *(uintptr_t*)(rax+0x0);
        *(uintptr_t*)(rax+0x0) = t16;
        t7 = r12;
        main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
        t8 = *(DWORD*)0x14000C006;
        *(DWORD*)0x14000C00A = t6;
        do {
            t3 = rdi;
            *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
            if (t3 != 0) {
            }
            t4 = *(DWORD*)0x1400097D9;
            t2 = 0;
            t3 = *(uintptr_t*)(rsi+0x0);
            if (t3 == 1) {
            }
            if (rdi == 0) {
            }
            t3 = *(DWORD*)0x140009729;
            t6 = *(uintptr_t*)(rax+0x0);
            if (t6 == 0) {
            }
            t2 = rdi - 8;
            t5 = *(uintptr_t*)(r13+0x0);
            strlen(*(uintptr_t*)(r13+0x0));
            t4 = &*(uintptr_t*)(rax+0x1);
            t8 = t4;
            malloc(rsi_0);
            t16 = t4;
            *(uintptr_t*)(r12+0x0) = rax;
            t7 = *(uintptr_t*)(r13+0x0);
            t10 = rax;
            t17 = 0 + 8;
            memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
            t5 = *(uintptr_t*)(r13+0x0);
            strlen(*(uintptr_t*)(r13+0x0));
            t4 = &*(uintptr_t*)(rax+0x1);
            t8 = t4;
            malloc(rsi_0);
            t16 = t4;
            *(uintptr_t*)(r12+0x0) = rax;
            t7 = *(uintptr_t*)(r13+0x0);
            t10 = rax;
            t11 = rbx + 8;
            memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
            t2 = rdi + r12;
            *(uintptr_t*)(rdi+0x0) = 0;
            *(DWORD*)0x14000C019 = r12;
            __main(*(DWORD*)0x14000C006);
            t3 = *(DWORD*)0x140009749;
            t16 = *(DWORD*)0x14000C011;
            t5 = *(DWORD*)0x14000C022;
            t6 = *(uintptr_t*)(rax+0x0);
            *(uintptr_t*)(rax+0x0) = t16;
            t7 = r12;
            main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
            t8 = *(DWORD*)0x14000C006;
            *(DWORD*)0x14000C00A = t6;
            do {
                t3 = rdi;
                *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                if (t3 != 0) {
                }
                t4 = *(DWORD*)0x1400097D9;
                t2 = 0;
                t3 = *(uintptr_t*)(rsi+0x0);
                if (t3 == 1) {
                }
                if (rdi == 0) {
                }
                t3 = *(DWORD*)0x140009729;
                t6 = *(uintptr_t*)(rax+0x0);
                if (t6 == 0) {
                }
                t2 = rdi - 8;
                t5 = *(uintptr_t*)(r13+0x0);
                strlen(*(uintptr_t*)(r13+0x0));
                t4 = &*(uintptr_t*)(rax+0x1);
                t8 = t4;
                malloc(rsi_0);
                t16 = t4;
                *(uintptr_t*)(r12+0x0) = rax;
                t7 = *(uintptr_t*)(r13+0x0);
                t10 = rax;
                t17 = 0 + 8;
                memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                t5 = *(uintptr_t*)(r13+0x0);
                strlen(*(uintptr_t*)(r13+0x0));
                t4 = &*(uintptr_t*)(rax+0x1);
                t8 = t4;
                malloc(rsi_0);
                t16 = t4;
                *(uintptr_t*)(r12+0x0) = rax;
                t7 = *(uintptr_t*)(r13+0x0);
                t10 = rax;
                t11 = rbx + 8;
                memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                t2 = rdi + r12;
                *(uintptr_t*)(rdi+0x0) = 0;
                *(DWORD*)0x14000C019 = r12;
                __main(*(DWORD*)0x14000C006);
                t3 = *(DWORD*)0x140009749;
                t16 = *(DWORD*)0x14000C011;
                t5 = *(DWORD*)0x14000C022;
                t6 = *(uintptr_t*)(rax+0x0);
                *(uintptr_t*)(rax+0x0) = t16;
                t7 = r12;
                main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                t8 = *(DWORD*)0x14000C006;
                *(DWORD*)0x14000C00A = t6;
                do {
                    t3 = rdi;
                    *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                    if (t3 != 0) {
                    }
                    t4 = *(DWORD*)0x1400097D9;
                    t2 = 0;
                    t3 = *(uintptr_t*)(rsi+0x0);
                    if (t3 == 1) {
                    }
                    if (rdi == 0) {
                    }
                    t3 = *(DWORD*)0x140009729;
                    t6 = *(uintptr_t*)(rax+0x0);
                    if (t6 == 0) {
                    }
                    t2 = rdi - 8;
                    t5 = *(uintptr_t*)(r13+0x0);
                    strlen(*(uintptr_t*)(r13+0x0));
                    t4 = &*(uintptr_t*)(rax+0x1);
                    t8 = t4;
                    malloc(rsi_0);
                    t16 = t4;
                    *(uintptr_t*)(r12+0x0) = rax;
                    t7 = *(uintptr_t*)(r13+0x0);
                    t10 = rax;
                    t17 = 0 + 8;
                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                    t5 = *(uintptr_t*)(r13+0x0);
                    strlen(*(uintptr_t*)(r13+0x0));
                    t4 = &*(uintptr_t*)(rax+0x1);
                    t8 = t4;
                    malloc(rsi_0);
                    t16 = t4;
                    *(uintptr_t*)(r12+0x0) = rax;
                    t7 = *(uintptr_t*)(r13+0x0);
                    t10 = rax;
                    t11 = rbx + 8;
                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                    t2 = rdi + r12;
                    *(uintptr_t*)(rdi+0x0) = 0;
                    *(DWORD*)0x14000C019 = r12;
                    __main(*(DWORD*)0x14000C006);
                    t3 = *(DWORD*)0x140009749;
                    t16 = *(DWORD*)0x14000C011;
                    t5 = *(DWORD*)0x14000C022;
                    t6 = *(uintptr_t*)(rax+0x0);
                    *(uintptr_t*)(rax+0x0) = t16;
                    t7 = r12;
                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                    t8 = *(DWORD*)0x14000C006;
                    *(DWORD*)0x14000C00A = t6;
                    do {
                        t3 = rdi;
                        *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                        if (t3 != 0) {
                        }
                        t4 = *(DWORD*)0x1400097D9;
                        t2 = 0;
                        t3 = *(uintptr_t*)(rsi+0x0);
                        if (t3 == 1) {
                        }
                        if (rdi == 0) {
                        }
                        t3 = *(DWORD*)0x140009729;
                        t6 = *(uintptr_t*)(rax+0x0);
                        if (t6 == 0) {
                        }
                        t2 = rdi - 8;
                        t5 = *(uintptr_t*)(r13+0x0);
                        strlen(*(uintptr_t*)(r13+0x0));
                        t4 = &*(uintptr_t*)(rax+0x1);
                        t8 = t4;
                        malloc(rsi_0);
                        t16 = t4;
                        *(uintptr_t*)(r12+0x0) = rax;
                        t7 = *(uintptr_t*)(r13+0x0);
                        t10 = rax;
                        t17 = 0 + 8;
                        memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                        t5 = *(uintptr_t*)(r13+0x0);
                        strlen(*(uintptr_t*)(r13+0x0));
                        t4 = &*(uintptr_t*)(rax+0x1);
                        t8 = t4;
                        malloc(rsi_0);
                        t16 = t4;
                        *(uintptr_t*)(r12+0x0) = rax;
                        t7 = *(uintptr_t*)(r13+0x0);
                        t10 = rax;
                        t11 = rbx + 8;
                        memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                        t2 = rdi + r12;
                        *(uintptr_t*)(rdi+0x0) = 0;
                        *(DWORD*)0x14000C019 = r12;
                        __main(*(DWORD*)0x14000C006);
                        t3 = *(DWORD*)0x140009749;
                        t16 = *(DWORD*)0x14000C011;
                        t5 = *(DWORD*)0x14000C022;
                        t6 = *(uintptr_t*)(rax+0x0);
                        *(uintptr_t*)(rax+0x0) = t16;
                        t7 = r12;
                        main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                        t8 = *(DWORD*)0x14000C006;
                        *(DWORD*)0x14000C00A = t6;
                        do {
                            t3 = rdi;
                            *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                            if (t3 != 0) {
                            }
                            t4 = *(DWORD*)0x1400097D9;
                            t2 = 0;
                            t3 = *(uintptr_t*)(rsi+0x0);
                            if (t3 == 1) {
                            }
                            if (rdi == 0) {
                            }
                            t3 = *(DWORD*)0x140009729;
                            t6 = *(uintptr_t*)(rax+0x0);
                            if (t6 == 0) {
                            }
                            t2 = rdi - 8;
                            t5 = *(uintptr_t*)(r13+0x0);
                            strlen(*(uintptr_t*)(r13+0x0));
                            t4 = &*(uintptr_t*)(rax+0x1);
                            t8 = t4;
                            malloc(rsi_0);
                            t16 = t4;
                            *(uintptr_t*)(r12+0x0) = rax;
                            t7 = *(uintptr_t*)(r13+0x0);
                            t10 = rax;
                            t17 = 0 + 8;
                            memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                            t5 = *(uintptr_t*)(r13+0x0);
                            strlen(*(uintptr_t*)(r13+0x0));
                            t4 = &*(uintptr_t*)(rax+0x1);
                            t8 = t4;
                            malloc(rsi_0);
                            t16 = t4;
                            *(uintptr_t*)(r12+0x0) = rax;
                            t7 = *(uintptr_t*)(r13+0x0);
                            t10 = rax;
                            t11 = rbx + 8;
                            memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                            t2 = rdi + r12;
                            *(uintptr_t*)(rdi+0x0) = 0;
                            *(DWORD*)0x14000C019 = r12;
                            __main(*(DWORD*)0x14000C006);
                            t3 = *(DWORD*)0x140009749;
                            t16 = *(DWORD*)0x14000C011;
                            t5 = *(DWORD*)0x14000C022;
                            t6 = *(uintptr_t*)(rax+0x0);
                            *(uintptr_t*)(rax+0x0) = t16;
                            t7 = r12;
                            main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                            t8 = *(DWORD*)0x14000C006;
                            *(DWORD*)0x14000C00A = t6;
                            do {
                                t3 = rdi;
                                *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                if (t3 != 0) {
                                }
                                t4 = *(DWORD*)0x1400097D9;
                                t2 = 0;
                                t3 = *(uintptr_t*)(rsi+0x0);
                                if (t3 == 1) {
                                }
                                if (rdi == 0) {
                                }
                                t3 = *(DWORD*)0x140009729;
                                t6 = *(uintptr_t*)(rax+0x0);
                                if (t6 == 0) {
                                }
                                t2 = rdi - 8;
                                t5 = *(uintptr_t*)(r13+0x0);
                                strlen(*(uintptr_t*)(r13+0x0));
                                t4 = &*(uintptr_t*)(rax+0x1);
                                t8 = t4;
                                malloc(rsi_0);
                                t16 = t4;
                                *(uintptr_t*)(r12+0x0) = rax;
                                t7 = *(uintptr_t*)(r13+0x0);
                                t10 = rax;
                                t17 = 0 + 8;
                                memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                t5 = *(uintptr_t*)(r13+0x0);
                                strlen(*(uintptr_t*)(r13+0x0));
                                t4 = &*(uintptr_t*)(rax+0x1);
                                t8 = t4;
                                malloc(rsi_0);
                                t16 = t4;
                                *(uintptr_t*)(r12+0x0) = rax;
                                t7 = *(uintptr_t*)(r13+0x0);
                                t10 = rax;
                                t11 = rbx + 8;
                                memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                t2 = rdi + r12;
                                *(uintptr_t*)(rdi+0x0) = 0;
                                *(DWORD*)0x14000C019 = r12;
                                __main(*(DWORD*)0x14000C006);
                                t3 = *(DWORD*)0x140009749;
                                t16 = *(DWORD*)0x14000C011;
                                t5 = *(DWORD*)0x14000C022;
                                t6 = *(uintptr_t*)(rax+0x0);
                                *(uintptr_t*)(rax+0x0) = t16;
                                t7 = r12;
                                main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                t8 = *(DWORD*)0x14000C006;
                                *(DWORD*)0x14000C00A = t6;
                                do {
                                    t3 = rdi;
                                    *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                    if (t3 != 0) {
                                    }
                                    t4 = *(DWORD*)0x1400097D9;
                                    t2 = 0;
                                    t3 = *(uintptr_t*)(rsi+0x0);
                                    if (t3 == 1) {
                                    }
                                    if (rdi == 0) {
                                    }
                                    t3 = *(DWORD*)0x140009729;
                                    t6 = *(uintptr_t*)(rax+0x0);
                                    if (t6 == 0) {
                                    }
                                    t2 = rdi - 8;
                                    t5 = *(uintptr_t*)(r13+0x0);
                                    strlen(*(uintptr_t*)(r13+0x0));
                                    t4 = &*(uintptr_t*)(rax+0x1);
                                    t8 = t4;
                                    malloc(rsi_0);
                                    t16 = t4;
                                    *(uintptr_t*)(r12+0x0) = rax;
                                    t7 = *(uintptr_t*)(r13+0x0);
                                    t10 = rax;
                                    t17 = 0 + 8;
                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                    t5 = *(uintptr_t*)(r13+0x0);
                                    strlen(*(uintptr_t*)(r13+0x0));
                                    t4 = &*(uintptr_t*)(rax+0x1);
                                    t8 = t4;
                                    malloc(rsi_0);
                                    t16 = t4;
                                    *(uintptr_t*)(r12+0x0) = rax;
                                    t7 = *(uintptr_t*)(r13+0x0);
                                    t10 = rax;
                                    t11 = rbx + 8;
                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                    t2 = rdi + r12;
                                    *(uintptr_t*)(rdi+0x0) = 0;
                                    *(DWORD*)0x14000C019 = r12;
                                    __main(*(DWORD*)0x14000C006);
                                    t3 = *(DWORD*)0x140009749;
                                    t16 = *(DWORD*)0x14000C011;
                                    t5 = *(DWORD*)0x14000C022;
                                    t6 = *(uintptr_t*)(rax+0x0);
                                    *(uintptr_t*)(rax+0x0) = t16;
                                    t7 = r12;
                                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                    t8 = *(DWORD*)0x14000C006;
                                    *(DWORD*)0x14000C00A = t6;
                                    do {
                                        t3 = rdi;
                                        *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                        if (t3 != 0) {
                                        }
                                        t4 = *(DWORD*)0x1400097D9;
                                        t2 = 0;
                                        t3 = *(uintptr_t*)(rsi+0x0);
                                        if (t3 == 1) {
                                        }
                                        if (rdi == 0) {
                                        }
                                        t3 = *(DWORD*)0x140009729;
                                        t6 = *(uintptr_t*)(rax+0x0);
                                        if (t6 == 0) {
                                        }
                                        t2 = rdi - 8;
                                        t5 = *(uintptr_t*)(r13+0x0);
                                        strlen(*(uintptr_t*)(r13+0x0));
                                        t4 = &*(uintptr_t*)(rax+0x1);
                                        t8 = t4;
                                        malloc(rsi_0);
                                        t16 = t4;
                                        *(uintptr_t*)(r12+0x0) = rax;
                                        t7 = *(uintptr_t*)(r13+0x0);
                                        t10 = rax;
                                        t17 = 0 + 8;
                                        memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                        t5 = *(uintptr_t*)(r13+0x0);
                                        strlen(*(uintptr_t*)(r13+0x0));
                                        t4 = &*(uintptr_t*)(rax+0x1);
                                        t8 = t4;
                                        malloc(rsi_0);
                                        t16 = t4;
                                        *(uintptr_t*)(r12+0x0) = rax;
                                        t7 = *(uintptr_t*)(r13+0x0);
                                        t10 = rax;
                                        t11 = rbx + 8;
                                        memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                        t2 = rdi + r12;
                                        *(uintptr_t*)(rdi+0x0) = 0;
                                        *(DWORD*)0x14000C019 = r12;
                                        __main(*(DWORD*)0x14000C006);
                                        t3 = *(DWORD*)0x140009749;
                                        t16 = *(DWORD*)0x14000C011;
                                        t5 = *(DWORD*)0x14000C022;
                                        t6 = *(uintptr_t*)(rax+0x0);
                                        *(uintptr_t*)(rax+0x0) = t16;
                                        t7 = r12;
                                        main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                        t8 = *(DWORD*)0x14000C006;
                                        *(DWORD*)0x14000C00A = t6;
                                        do {
                                            t3 = rdi;
                                            *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                            if (t3 != 0) {
                                            }
                                            t4 = *(DWORD*)0x1400097D9;
                                            t2 = 0;
                                            t3 = *(uintptr_t*)(rsi+0x0);
                                            if (t3 == 1) {
                                            }
                                            if (rdi == 0) {
                                            }
                                            t3 = *(DWORD*)0x140009729;
                                            t6 = *(uintptr_t*)(rax+0x0);
                                            if (t6 == 0) {
                                            }
                                            t2 = rdi - 8;
                                            t5 = *(uintptr_t*)(r13+0x0);
                                            strlen(*(uintptr_t*)(r13+0x0));
                                            t4 = &*(uintptr_t*)(rax+0x1);
                                            t8 = t4;
                                            malloc(rsi_0);
                                            t16 = t4;
                                            *(uintptr_t*)(r12+0x0) = rax;
                                            t7 = *(uintptr_t*)(r13+0x0);
                                            t10 = rax;
                                            t17 = 0 + 8;
                                            memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                            t5 = *(uintptr_t*)(r13+0x0);
                                            strlen(*(uintptr_t*)(r13+0x0));
                                            t4 = &*(uintptr_t*)(rax+0x1);
                                            t8 = t4;
                                            malloc(rsi_0);
                                            t16 = t4;
                                            *(uintptr_t*)(r12+0x0) = rax;
                                            t7 = *(uintptr_t*)(r13+0x0);
                                            t10 = rax;
                                            t11 = rbx + 8;
                                            memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                            t2 = rdi + r12;
                                            *(uintptr_t*)(rdi+0x0) = 0;
                                            *(DWORD*)0x14000C019 = r12;
                                            __main(*(DWORD*)0x14000C006);
                                            t3 = *(DWORD*)0x140009749;
                                            t16 = *(DWORD*)0x14000C011;
                                            t5 = *(DWORD*)0x14000C022;
                                            t6 = *(uintptr_t*)(rax+0x0);
                                            *(uintptr_t*)(rax+0x0) = t16;
                                            t7 = r12;
                                            main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                            t8 = *(DWORD*)0x14000C006;
                                            *(DWORD*)0x14000C00A = t6;
                                            do {
                                                t3 = rdi;
                                                *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                                if (t3 != 0) {
                                                }
                                                t4 = *(DWORD*)0x1400097D9;
                                                t2 = 0;
                                                t3 = *(uintptr_t*)(rsi+0x0);
                                                if (t3 == 1) {
                                                }
                                                if (rdi == 0) {
                                                }
                                                t3 = *(DWORD*)0x140009729;
                                                t6 = *(uintptr_t*)(rax+0x0);
                                                if (t6 == 0) {
                                                }
                                                t2 = rdi - 8;
                                                t5 = *(uintptr_t*)(r13+0x0);
                                                strlen(*(uintptr_t*)(r13+0x0));
                                                t4 = &*(uintptr_t*)(rax+0x1);
                                                t8 = t4;
                                                malloc(rsi_0);
                                                t16 = t4;
                                                *(uintptr_t*)(r12+0x0) = rax;
                                                t7 = *(uintptr_t*)(r13+0x0);
                                                t10 = rax;
                                                t17 = 0 + 8;
                                                memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                t5 = *(uintptr_t*)(r13+0x0);
                                                strlen(*(uintptr_t*)(r13+0x0));
                                                t4 = &*(uintptr_t*)(rax+0x1);
                                                t8 = t4;
                                                malloc(rsi_0);
                                                t16 = t4;
                                                *(uintptr_t*)(r12+0x0) = rax;
                                                t7 = *(uintptr_t*)(r13+0x0);
                                                t10 = rax;
                                                t11 = rbx + 8;
                                                memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                t2 = rdi + r12;
                                                *(uintptr_t*)(rdi+0x0) = 0;
                                                *(DWORD*)0x14000C019 = r12;
                                                __main(*(DWORD*)0x14000C006);
                                                t3 = *(DWORD*)0x140009749;
                                                t16 = *(DWORD*)0x14000C011;
                                                t5 = *(DWORD*)0x14000C022;
                                                t6 = *(uintptr_t*)(rax+0x0);
                                                *(uintptr_t*)(rax+0x0) = t16;
                                                t7 = r12;
                                                main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                                t8 = *(DWORD*)0x14000C006;
                                                *(DWORD*)0x14000C00A = t6;
                                                do {
                                                    t3 = rdi;
                                                    *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                                    t4 = *(DWORD*)0x1400097D9;
                                                    t2 = 0;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t4 = *(DWORD*)0x1400097D9;
                                                    t2 = 1;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t5 = 1000;
                                                    r12(1000);
                                                    t3 = rdi;
                                                    *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                                    t5 = 1000;
                                                    r12(1000);
                                                    t3 = rdi;
                                                    *(uintptr_t*)(rbx+0x0) = cmpxchg(*(uintptr_t*)(rbx+0x0), rsi);
                                                    t4 = *(DWORD*)0x1400097D9;
                                                    t2 = 0;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t5 = 31;
                                                    _amsg_exit(31);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t4 = *(DWORD*)0x1400097D9;
                                                    t2 = 1;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t5 = 31;
                                                    _amsg_exit(31);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t5 = 31;
                                                    _amsg_exit(31);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t7 = *(DWORD*)0x140009809;
                                                    t5 = *(DWORD*)0x1400097F9;
                                                    _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                                    *(uintptr_t*)(rsi+0x0) = 2;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t7 = *(DWORD*)0x140009829;
                                                    t5 = *(DWORD*)0x140009819;
                                                    *(uintptr_t*)(rsi+0x0) = 1;
                                                    _initterm(*(DWORD*)0x140009819, *(DWORD*)0x140009829);
                                                    *(DWORD*)0x14000BFFE = 1;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    *(DWORD*)0x14000BFFE = 1;
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t7 = *(DWORD*)0x140009809;
                                                    t5 = *(DWORD*)0x1400097F9;
                                                    _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                                    *(uintptr_t*)(rsi+0x0) = 2;
                                                    t7 = *(DWORD*)0x140009829;
                                                    t5 = *(DWORD*)0x140009819;
                                                    *(uintptr_t*)(rsi+0x0) = 1;
                                                    _initterm(*(DWORD*)0x140009819, *(DWORD*)0x140009829);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t3 = *(uintptr_t*)(rsi+0x0);
                                                    t7 = *(DWORD*)0x140009809;
                                                    t5 = *(DWORD*)0x1400097F9;
                                                    _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                                    *(uintptr_t*)(rsi+0x0) = 2;
                                                    t3 = 0;
                                                    *(uintptr_t*)(rbx+0x0) = xchg(*(uintptr_t*)(rbx+0x0), rax);
                                                    t3 = *(DWORD*)0x140009729;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    t7 = *(DWORD*)0x140009809;
                                                    t5 = *(DWORD*)0x1400097F9;
                                                    _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                                    *(uintptr_t*)(rsi+0x0) = 2;
                                                    t3 = *(DWORD*)0x140009729;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    t3 = 0;
                                                    *(uintptr_t*)(rbx+0x0) = xchg(*(uintptr_t*)(rbx+0x0), rax);
                                                    t3 = 0;
                                                    *(uintptr_t*)(rbx+0x0) = xchg(*(uintptr_t*)(rbx+0x0), rax);
                                                    t3 = *(DWORD*)0x140009729;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                                    t5 = *(DWORD*)0x140009869;
                                                    ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                                    t7 = *(DWORD*)0x1400097B9;
                                                    t8 = &*(DWORD*)0x140000FF9;
                                                    *(uintptr_t*)(rdx+0x0) = rax;
                                                    mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                                    _fpreset(*(DWORD*)0x14000C006);
                                                    t11 = *(DWORD*)0x14000C022;
                                                    t2 = &*(uintptr_t*)(rbx+0x1);
                                                    t12 = (signed)t2;
                                                    t13 = t12 << 0x3;
                                                    t10 = t13;
                                                    malloc(rdi_2);
                                                    t7 = 2;
                                                    t5 = 0;
                                                    rax(0, 2);
                                                    _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                                    t8 = *(DWORD*)0x140009869;
                                                    ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                                    t9 = *(DWORD*)0x1400097B9;
                                                    t10 = &*(DWORD*)0x140000FF9;
                                                    *(uintptr_t*)(rdx+0x0) = rax;
                                                    mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                                    _fpreset(*(DWORD*)0x14000C006);
                                                    t11 = *(DWORD*)0x14000C022;
                                                    t2 = &*(uintptr_t*)(rbx+0x1);
                                                    t12 = (signed)t2;
                                                    t13 = t12 << 0x3;
                                                    t14 = t13;
                                                    malloc(rdi_2);
                                                    t7 = 2;
                                                    t5 = 0;
                                                    rax(0, 2);
                                                    _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                                    t8 = *(DWORD*)0x140009869;
                                                    ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                                    t9 = *(DWORD*)0x1400097B9;
                                                    t10 = &*(DWORD*)0x140000FF9;
                                                    *(uintptr_t*)(rdx+0x0) = rax;
                                                    mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                                    _fpreset(*(DWORD*)0x14000C006);
                                                    t11 = *(DWORD*)0x14000C022;
                                                    t2 = &*(uintptr_t*)(rbx+0x1);
                                                    t12 = (signed)t2;
                                                    t13 = t12 << 0x3;
                                                    t14 = t13;
                                                    malloc(rdi_2);
                                                    t2 = rax;
                                                    t2 = rdi - 8;
                                                    t5 = *(uintptr_t*)(r13+0x0);
                                                    strlen(*(uintptr_t*)(r13+0x0));
                                                    t4 = &*(uintptr_t*)(rax+0x1);
                                                    t8 = t4;
                                                    malloc(rsi_0);
                                                    t16 = t4;
                                                    *(uintptr_t*)(r12+0x0) = rax;
                                                    t7 = *(uintptr_t*)(r13+0x0);
                                                    t10 = rax;
                                                    t17 = 0 + 8;
                                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                    _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                                    t5 = *(DWORD*)0x140009869;
                                                    ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                                    t7 = *(DWORD*)0x1400097B9;
                                                    t8 = &*(DWORD*)0x140000FF9;
                                                    *(uintptr_t*)(rdx+0x0) = rax;
                                                    mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                                    _fpreset(*(DWORD*)0x14000C006);
                                                    t11 = *(DWORD*)0x14000C022;
                                                    t2 = &*(uintptr_t*)(rbx+0x1);
                                                    t12 = (signed)t2;
                                                    t13 = t12 << 0x3;
                                                    t10 = t13;
                                                    malloc(rdi_2);
                                                    t2 = rax;
                                                    t2 = rdi - 8;
                                                    t5 = *(uintptr_t*)(r13+0x0);
                                                    strlen(*(uintptr_t*)(r13+0x0));
                                                    t4 = &*(uintptr_t*)(rax+0x1);
                                                    t8 = t4;
                                                    malloc(rsi_0);
                                                    t16 = t4;
                                                    *(uintptr_t*)(r12+0x0) = rax;
                                                    t7 = *(uintptr_t*)(r13+0x0);
                                                    t10 = rax;
                                                    t17 = 0 + 8;
                                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                    t2 = rdi - 8;
                                                    t5 = *(uintptr_t*)(r13+0x0);
                                                    strlen(*(uintptr_t*)(r13+0x0));
                                                    t4 = &*(uintptr_t*)(rax+0x1);
                                                    t8 = t4;
                                                    malloc(rsi_0);
                                                    t16 = t4;
                                                    *(uintptr_t*)(r12+0x0) = rax;
                                                    t7 = *(uintptr_t*)(r13+0x0);
                                                    t10 = rax;
                                                    t17 = 0 + 8;
                                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                    t5 = *(uintptr_t*)(r13+0x0);
                                                    strlen(*(uintptr_t*)(r13+0x0));
                                                    t4 = &*(uintptr_t*)(rax+0x1);
                                                    t8 = t4;
                                                    malloc(rsi_0);
                                                    t16 = t4;
                                                    *(uintptr_t*)(r12+0x0) = rax;
                                                    t7 = *(uintptr_t*)(r13+0x0);
                                                    t10 = rax;
                                                    t11 = rbx + 8;
                                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                    t2 = rdi + r12;
                                                    *(uintptr_t*)(rdi+0x0) = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main(*(DWORD*)0x14000C006);
                                                    t3 = *(DWORD*)0x140009749;
                                                    t16 = *(DWORD*)0x14000C011;
                                                    t5 = *(DWORD*)0x14000C022;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    *(uintptr_t*)(rax+0x0) = t16;
                                                    t7 = r12;
                                                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                                    t8 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t6;
                                                    t5 = *(uintptr_t*)(r13+0x0);
                                                    strlen(*(uintptr_t*)(r13+0x0));
                                                    t4 = &*(uintptr_t*)(rax+0x1);
                                                    t8 = t4;
                                                    malloc(rsi_0);
                                                    t16 = t4;
                                                    *(uintptr_t*)(r12+0x0) = rax;
                                                    t7 = *(uintptr_t*)(r13+0x0);
                                                    t10 = rax;
                                                    t11 = rbx + 8;
                                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                    t5 = *(uintptr_t*)(r13+0x0);
                                                    strlen(*(uintptr_t*)(r13+0x0));
                                                    t4 = &*(uintptr_t*)(rax+0x1);
                                                    t8 = t4;
                                                    malloc(rsi_0);
                                                    t16 = t4;
                                                    *(uintptr_t*)(r12+0x0) = rax;
                                                    t7 = *(uintptr_t*)(r13+0x0);
                                                    t10 = rax;
                                                    t11 = rbx + 8;
                                                    memcpy(rax, *(uintptr_t*)(r13+0x0), rsi_0);
                                                    t2 = rdi + r12;
                                                    *(uintptr_t*)(rdi+0x0) = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main(*(DWORD*)0x14000C006);
                                                    t3 = *(DWORD*)0x140009749;
                                                    t16 = *(DWORD*)0x14000C011;
                                                    t5 = *(DWORD*)0x14000C022;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    *(uintptr_t*)(rax+0x0) = t16;
                                                    t7 = r12;
                                                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                                    t8 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t6;
                                                    t2 = rdi + r12;
                                                    *(uintptr_t*)(rdi+0x0) = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main(*(DWORD*)0x14000C006);
                                                    t3 = *(DWORD*)0x140009749;
                                                    t16 = *(DWORD*)0x14000C011;
                                                    t5 = *(DWORD*)0x14000C022;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    *(uintptr_t*)(rax+0x0) = t16;
                                                    t7 = r12;
                                                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                                    t8 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t6;
                                                    t5 = rax;
                                                    exit(rax);
                                                    t3 = *(DWORD*)0x140009779;
                                                    *(uintptr_t*)(rax+0x0) = 1;
                                                    __tmainCRTStartup(*(DWORD*)0x14000C006);
                                                    t20 = stack_pop();
                                                    t7 = *(DWORD*)0x14000C002;
                                                    t2 = rax;
                                                    *(uintptr_t*)(rdi+0x0) = 0;
                                                    *(DWORD*)0x14000C019 = r12;
                                                    __main(*(DWORD*)0x14000C006);
                                                    t3 = *(DWORD*)0x140009749;
                                                    t16 = *(DWORD*)0x14000C011;
                                                    t5 = *(DWORD*)0x14000C022;
                                                    t6 = *(uintptr_t*)(rax+0x0);
                                                    *(uintptr_t*)(rax+0x0) = t16;
                                                    t7 = r12;
                                                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                                    t8 = *(DWORD*)0x14000C006;
                                                    *(DWORD*)0x14000C00A = t6;
                                                    t5 = rax;
                                                    exit(rax);
                                                    t3 = *(DWORD*)0x140009779;
                                                    *(uintptr_t*)(rax+0x0) = 1;
                                                    __tmainCRTStartup(*(DWORD*)0x14000C006);
                                                    t20 = stack_pop();
                                                    t7 = *(DWORD*)0x14000C002;
                                                    t7 = *(DWORD*)0x14000C002;
                                                    _cexit(*(DWORD*)0x14000C006, *(DWORD*)0x14000C002);
                                                    t3 = t6;
                                                    t11 = stack_pop();
                                                    t4 = stack_pop();
                                                    t2 = stack_pop();
                                                    t18 = stack_pop();
                                                    t19 = stack_pop();
                                                    t11 = stack_pop();
                                                    t4 = stack_pop();
                                                    t2 = stack_pop();
                                                    t18 = stack_pop();
                                                    t19 = stack_pop();
                                                    t11 = stack_pop();
                                                    t4 = stack_pop();
                                                    t2 = stack_pop();
                                                    t18 = stack_pop();
                                                    t19 = stack_pop();
                                                    _cexit(*(DWORD*)0x14000C006, *(DWORD*)0x14000C002);
                                                    t3 = t6;
                                                    t11 = stack_pop();
                                                    t4 = stack_pop();
                                                    t2 = stack_pop();
                                                    t18 = stack_pop();
                                                    t19 = stack_pop();
                                                    t5 = rax;
                                                    exit(rax);
                                                    t3 = *(DWORD*)0x140009779;
                                                    *(uintptr_t*)(rax+0x0) = 1;
                                                    __tmainCRTStartup(*(DWORD*)0x14000C006);
                                                    t20 = stack_pop();
                                                } while (1 != 0);
                                                t7 = *(DWORD*)0x14000C002;
                                                if (t7 == 0) {
                                                }
                                                t4 = *(DWORD*)0x1400097D9;
                                                t2 = 1;
                                                t3 = *(uintptr_t*)(rsi+0x0);
                                                if (t3 != 1) {
                                                }
                                                t7 = *(DWORD*)0x140009809;
                                                t5 = *(DWORD*)0x1400097F9;
                                                _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                                *(uintptr_t*)(rsi+0x0) = 2;
                                                t7 = 2;
                                                t5 = 0;
                                                rax(0, 2);
                                                _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                                t8 = *(DWORD*)0x140009869;
                                                ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                                t9 = *(DWORD*)0x1400097B9;
                                                t10 = &*(DWORD*)0x140000FF9;
                                                *(uintptr_t*)(rdx+0x0) = rax;
                                                mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                                _fpreset(*(DWORD*)0x14000C006);
                                                t11 = *(DWORD*)0x14000C022;
                                                t2 = &*(uintptr_t*)(rbx+0x1);
                                                t12 = (signed)t2;
                                                t13 = t12 << 0x3;
                                                t14 = t13;
                                                malloc(rdi_2);
                                                t2 = rax;
                                                *(uintptr_t*)(rdi+0x0) = 0;
                                                *(DWORD*)0x14000C019 = r12;
                                                __main(*(DWORD*)0x14000C006);
                                                t3 = *(DWORD*)0x140009749;
                                                t16 = *(DWORD*)0x14000C011;
                                                t5 = *(DWORD*)0x14000C022;
                                                t6 = *(uintptr_t*)(rax+0x0);
                                                *(uintptr_t*)(rax+0x0) = t16;
                                                t7 = r12;
                                                main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                                t8 = *(DWORD*)0x14000C006;
                                                *(DWORD*)0x14000C00A = t6;
                                                t11 = stack_pop();
                                                t4 = stack_pop();
                                                t2 = stack_pop();
                                                t18 = stack_pop();
                                                t19 = stack_pop();
                                                t5 = rax;
                                                exit(rax);
                                                t3 = *(DWORD*)0x140009779;
                                                *(uintptr_t*)(rax+0x0) = 1;
                                                __tmainCRTStartup(*(DWORD*)0x14000C006);
                                                t20 = stack_pop();
                                            } while (1 != 0);
                                            t7 = *(DWORD*)0x14000C002;
                                            if (t7 == 0) {
                                            }
                                            t4 = *(DWORD*)0x1400097D9;
                                            t2 = 1;
                                            t3 = *(uintptr_t*)(rsi+0x0);
                                            if (t3 != 1) {
                                            }
                                            t7 = *(DWORD*)0x140009809;
                                            t5 = *(DWORD*)0x1400097F9;
                                            _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                            *(uintptr_t*)(rsi+0x0) = 2;
                                            t7 = 2;
                                            t5 = 0;
                                            rax(0, 2);
                                            _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                            t8 = *(DWORD*)0x140009869;
                                            ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                            t9 = *(DWORD*)0x1400097B9;
                                            t10 = &*(DWORD*)0x140000FF9;
                                            *(uintptr_t*)(rdx+0x0) = rax;
                                            mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                            _fpreset(*(DWORD*)0x14000C006);
                                            t11 = *(DWORD*)0x14000C022;
                                            t2 = &*(uintptr_t*)(rbx+0x1);
                                            t12 = (signed)t2;
                                            t13 = t12 << 0x3;
                                            t14 = t13;
                                            malloc(rdi_2);
                                            t2 = rax;
                                            *(uintptr_t*)(rdi+0x0) = 0;
                                            *(DWORD*)0x14000C019 = r12;
                                            __main(*(DWORD*)0x14000C006);
                                            t3 = *(DWORD*)0x140009749;
                                            t16 = *(DWORD*)0x14000C011;
                                            t5 = *(DWORD*)0x14000C022;
                                            t6 = *(uintptr_t*)(rax+0x0);
                                            *(uintptr_t*)(rax+0x0) = t16;
                                            t7 = r12;
                                            main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                            t8 = *(DWORD*)0x14000C006;
                                            *(DWORD*)0x14000C00A = t6;
                                            t11 = stack_pop();
                                            t4 = stack_pop();
                                            t2 = stack_pop();
                                            t18 = stack_pop();
                                            t19 = stack_pop();
                                            t5 = rax;
                                            exit(rax);
                                            t3 = *(DWORD*)0x140009779;
                                            *(uintptr_t*)(rax+0x0) = 1;
                                            __tmainCRTStartup(*(DWORD*)0x14000C006);
                                            t20 = stack_pop();
                                        } while (1 != 0);
                                        t7 = *(DWORD*)0x14000C002;
                                        if (t7 == 0) {
                                        }
                                        t4 = *(DWORD*)0x1400097D9;
                                        t2 = 1;
                                        t3 = *(uintptr_t*)(rsi+0x0);
                                        if (t3 != 1) {
                                        }
                                        t7 = *(DWORD*)0x140009809;
                                        t5 = *(DWORD*)0x1400097F9;
                                        _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                        *(uintptr_t*)(rsi+0x0) = 2;
                                        t7 = 2;
                                        t5 = 0;
                                        rax(0, 2);
                                        _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                        t8 = *(DWORD*)0x140009869;
                                        ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                        t9 = *(DWORD*)0x1400097B9;
                                        t10 = &*(DWORD*)0x140000FF9;
                                        *(uintptr_t*)(rdx+0x0) = rax;
                                        mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                        _fpreset(*(DWORD*)0x14000C006);
                                        t11 = *(DWORD*)0x14000C022;
                                        t2 = &*(uintptr_t*)(rbx+0x1);
                                        t12 = (signed)t2;
                                        t13 = t12 << 0x3;
                                        t14 = t13;
                                        malloc(rdi_2);
                                        t2 = rax;
                                        *(uintptr_t*)(rdi+0x0) = 0;
                                        *(DWORD*)0x14000C019 = r12;
                                        __main(*(DWORD*)0x14000C006);
                                        t3 = *(DWORD*)0x140009749;
                                        t16 = *(DWORD*)0x14000C011;
                                        t5 = *(DWORD*)0x14000C022;
                                        t6 = *(uintptr_t*)(rax+0x0);
                                        *(uintptr_t*)(rax+0x0) = t16;
                                        t7 = r12;
                                        main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                        t8 = *(DWORD*)0x14000C006;
                                        *(DWORD*)0x14000C00A = t6;
                                        t11 = stack_pop();
                                        t4 = stack_pop();
                                        t2 = stack_pop();
                                        t18 = stack_pop();
                                        t19 = stack_pop();
                                        t5 = rax;
                                        exit(rax);
                                        t3 = *(DWORD*)0x140009779;
                                        *(uintptr_t*)(rax+0x0) = 1;
                                        __tmainCRTStartup(*(DWORD*)0x14000C006);
                                        t20 = stack_pop();
                                    } while (1 != 0);
                                    t7 = *(DWORD*)0x14000C002;
                                    if (t7 == 0) {
                                    }
                                    t4 = *(DWORD*)0x1400097D9;
                                    t2 = 1;
                                    t3 = *(uintptr_t*)(rsi+0x0);
                                    if (t3 != 1) {
                                    }
                                    t7 = *(DWORD*)0x140009809;
                                    t5 = *(DWORD*)0x1400097F9;
                                    _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                    *(uintptr_t*)(rsi+0x0) = 2;
                                    t7 = 2;
                                    t5 = 0;
                                    rax(0, 2);
                                    _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                    t8 = *(DWORD*)0x140009869;
                                    ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                    t9 = *(DWORD*)0x1400097B9;
                                    t10 = &*(DWORD*)0x140000FF9;
                                    *(uintptr_t*)(rdx+0x0) = rax;
                                    mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                    _fpreset(*(DWORD*)0x14000C006);
                                    t11 = *(DWORD*)0x14000C022;
                                    t2 = &*(uintptr_t*)(rbx+0x1);
                                    t12 = (signed)t2;
                                    t13 = t12 << 0x3;
                                    t14 = t13;
                                    malloc(rdi_2);
                                    t2 = rax;
                                    *(uintptr_t*)(rdi+0x0) = 0;
                                    *(DWORD*)0x14000C019 = r12;
                                    __main(*(DWORD*)0x14000C006);
                                    t3 = *(DWORD*)0x140009749;
                                    t16 = *(DWORD*)0x14000C011;
                                    t5 = *(DWORD*)0x14000C022;
                                    t6 = *(uintptr_t*)(rax+0x0);
                                    *(uintptr_t*)(rax+0x0) = t16;
                                    t7 = r12;
                                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                    t8 = *(DWORD*)0x14000C006;
                                    *(DWORD*)0x14000C00A = t6;
                                    t11 = stack_pop();
                                    t4 = stack_pop();
                                    t2 = stack_pop();
                                    t18 = stack_pop();
                                    t19 = stack_pop();
                                    t5 = rax;
                                    exit(rax);
                                    t3 = *(DWORD*)0x140009779;
                                    *(uintptr_t*)(rax+0x0) = 1;
                                    __tmainCRTStartup(*(DWORD*)0x14000C006);
                                    t20 = stack_pop();
                                } while (1 != 0);
                                t7 = *(DWORD*)0x14000C002;
                                if (t7 == 0) {
                                }
                                t4 = *(DWORD*)0x1400097D9;
                                t2 = 1;
                                t3 = *(uintptr_t*)(rsi+0x0);
                                if (t3 != 1) {
                                }
                                t7 = *(DWORD*)0x140009809;
                                t5 = *(DWORD*)0x1400097F9;
                                _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                                *(uintptr_t*)(rsi+0x0) = 2;
                                t7 = 2;
                                t5 = 0;
                                rax(0, 2);
                                _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                                t8 = *(DWORD*)0x140009869;
                                ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                                t9 = *(DWORD*)0x1400097B9;
                                t10 = &*(DWORD*)0x140000FF9;
                                *(uintptr_t*)(rdx+0x0) = rax;
                                mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                                _fpreset(*(DWORD*)0x14000C006);
                                t11 = *(DWORD*)0x14000C022;
                                t2 = &*(uintptr_t*)(rbx+0x1);
                                t12 = (signed)t2;
                                t13 = t12 << 0x3;
                                t14 = t13;
                                malloc(rdi_2);
                                t2 = rax;
                                *(uintptr_t*)(rdi+0x0) = 0;
                                *(DWORD*)0x14000C019 = r12;
                                __main(*(DWORD*)0x14000C006);
                                t3 = *(DWORD*)0x140009749;
                                t16 = *(DWORD*)0x14000C011;
                                t5 = *(DWORD*)0x14000C022;
                                t6 = *(uintptr_t*)(rax+0x0);
                                *(uintptr_t*)(rax+0x0) = t16;
                                t7 = r12;
                                main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                                t8 = *(DWORD*)0x14000C006;
                                *(DWORD*)0x14000C00A = t6;
                                t11 = stack_pop();
                                t4 = stack_pop();
                                t2 = stack_pop();
                                t18 = stack_pop();
                                t19 = stack_pop();
                                t5 = rax;
                                exit(rax);
                                t3 = *(DWORD*)0x140009779;
                                *(uintptr_t*)(rax+0x0) = 1;
                                __tmainCRTStartup(*(DWORD*)0x14000C006);
                                t20 = stack_pop();
                            } while (1 != 0);
                            t7 = *(DWORD*)0x14000C002;
                            if (t7 == 0) {
                            }
                            t4 = *(DWORD*)0x1400097D9;
                            t2 = 1;
                            t3 = *(uintptr_t*)(rsi+0x0);
                            if (t3 != 1) {
                            }
                            t7 = *(DWORD*)0x140009809;
                            t5 = *(DWORD*)0x1400097F9;
                            _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                            *(uintptr_t*)(rsi+0x0) = 2;
                            t7 = 2;
                            t5 = 0;
                            rax(0, 2);
                            _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                            t8 = *(DWORD*)0x140009869;
                            ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                            t9 = *(DWORD*)0x1400097B9;
                            t10 = &*(DWORD*)0x140000FF9;
                            *(uintptr_t*)(rdx+0x0) = rax;
                            mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                            _fpreset(*(DWORD*)0x14000C006);
                            t11 = *(DWORD*)0x14000C022;
                            t2 = &*(uintptr_t*)(rbx+0x1);
                            t12 = (signed)t2;
                            t13 = t12 << 0x3;
                            t14 = t13;
                            malloc(rdi_2);
                            t2 = rax;
                            *(uintptr_t*)(rdi+0x0) = 0;
                            *(DWORD*)0x14000C019 = r12;
                            __main(*(DWORD*)0x14000C006);
                            t3 = *(DWORD*)0x140009749;
                            t16 = *(DWORD*)0x14000C011;
                            t5 = *(DWORD*)0x14000C022;
                            t6 = *(uintptr_t*)(rax+0x0);
                            *(uintptr_t*)(rax+0x0) = t16;
                            t7 = r12;
                            main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                            t8 = *(DWORD*)0x14000C006;
                            *(DWORD*)0x14000C00A = t6;
                            t11 = stack_pop();
                            t4 = stack_pop();
                            t2 = stack_pop();
                            t18 = stack_pop();
                            t19 = stack_pop();
                            t5 = rax;
                            exit(rax);
                            t3 = *(DWORD*)0x140009779;
                            *(uintptr_t*)(rax+0x0) = 1;
                            __tmainCRTStartup(*(DWORD*)0x14000C006);
                            t20 = stack_pop();
                        } while (1 != 0);
                        t7 = *(DWORD*)0x14000C002;
                        if (t7 == 0) {
                        }
                        t4 = *(DWORD*)0x1400097D9;
                        t2 = 1;
                        t3 = *(uintptr_t*)(rsi+0x0);
                        if (t3 != 1) {
                        }
                        t7 = *(DWORD*)0x140009809;
                        t5 = *(DWORD*)0x1400097F9;
                        _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                        *(uintptr_t*)(rsi+0x0) = 2;
                        t7 = 2;
                        t5 = 0;
                        rax(0, 2);
                        _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                        t8 = *(DWORD*)0x140009869;
                        ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                        t9 = *(DWORD*)0x1400097B9;
                        t10 = &*(DWORD*)0x140000FF9;
                        *(uintptr_t*)(rdx+0x0) = rax;
                        mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                        _fpreset(*(DWORD*)0x14000C006);
                        t11 = *(DWORD*)0x14000C022;
                        t2 = &*(uintptr_t*)(rbx+0x1);
                        t12 = (signed)t2;
                        t13 = t12 << 0x3;
                        t14 = t13;
                        malloc(rdi_2);
                        t2 = rax;
                        *(uintptr_t*)(rdi+0x0) = 0;
                        *(DWORD*)0x14000C019 = r12;
                        __main(*(DWORD*)0x14000C006);
                        t3 = *(DWORD*)0x140009749;
                        t16 = *(DWORD*)0x14000C011;
                        t5 = *(DWORD*)0x14000C022;
                        t6 = *(uintptr_t*)(rax+0x0);
                        *(uintptr_t*)(rax+0x0) = t16;
                        t7 = r12;
                        main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                        t8 = *(DWORD*)0x14000C006;
                        *(DWORD*)0x14000C00A = t6;
                        t11 = stack_pop();
                        t4 = stack_pop();
                        t2 = stack_pop();
                        t18 = stack_pop();
                        t19 = stack_pop();
                        t5 = rax;
                        exit(rax);
                        t3 = *(DWORD*)0x140009779;
                        *(uintptr_t*)(rax+0x0) = 1;
                        __tmainCRTStartup(*(DWORD*)0x14000C006);
                        t20 = stack_pop();
                    } while (1 != 0);
                    t7 = *(DWORD*)0x14000C002;
                    if (t7 == 0) {
                    }
                    t4 = *(DWORD*)0x1400097D9;
                    t2 = 1;
                    t3 = *(uintptr_t*)(rsi+0x0);
                    if (t3 != 1) {
                    }
                    t7 = *(DWORD*)0x140009809;
                    t5 = *(DWORD*)0x1400097F9;
                    _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                    *(uintptr_t*)(rsi+0x0) = 2;
                    t7 = 2;
                    t5 = 0;
                    rax(0, 2);
                    _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                    t8 = *(DWORD*)0x140009869;
                    ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                    t9 = *(DWORD*)0x1400097B9;
                    t10 = &*(DWORD*)0x140000FF9;
                    *(uintptr_t*)(rdx+0x0) = rax;
                    mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                    _fpreset(*(DWORD*)0x14000C006);
                    t11 = *(DWORD*)0x14000C022;
                    t2 = &*(uintptr_t*)(rbx+0x1);
                    t12 = (signed)t2;
                    t13 = t12 << 0x3;
                    t14 = t13;
                    malloc(rdi_2);
                    t2 = rax;
                    *(uintptr_t*)(rdi+0x0) = 0;
                    *(DWORD*)0x14000C019 = r12;
                    __main(*(DWORD*)0x14000C006);
                    t3 = *(DWORD*)0x140009749;
                    t16 = *(DWORD*)0x14000C011;
                    t5 = *(DWORD*)0x14000C022;
                    t6 = *(uintptr_t*)(rax+0x0);
                    *(uintptr_t*)(rax+0x0) = t16;
                    t7 = r12;
                    main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                    t8 = *(DWORD*)0x14000C006;
                    *(DWORD*)0x14000C00A = t6;
                    t11 = stack_pop();
                    t4 = stack_pop();
                    t2 = stack_pop();
                    t18 = stack_pop();
                    t19 = stack_pop();
                    t5 = rax;
                    exit(rax);
                    t3 = *(DWORD*)0x140009779;
                    *(uintptr_t*)(rax+0x0) = 1;
                    __tmainCRTStartup(*(DWORD*)0x14000C006);
                    t20 = stack_pop();
                } while (1 != 0);
                t7 = *(DWORD*)0x14000C002;
                if (t7 == 0) {
                }
                t4 = *(DWORD*)0x1400097D9;
                t2 = 1;
                t3 = *(uintptr_t*)(rsi+0x0);
                if (t3 != 1) {
                }
                t7 = *(DWORD*)0x140009809;
                t5 = *(DWORD*)0x1400097F9;
                _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
                *(uintptr_t*)(rsi+0x0) = 2;
                t7 = 2;
                t5 = 0;
                rax(0, 2);
                _pei386_runtime_relocator(*(DWORD*)0x14000C006);
                t8 = *(DWORD*)0x140009869;
                ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
                t9 = *(DWORD*)0x1400097B9;
                t10 = &*(DWORD*)0x140000FF9;
                *(uintptr_t*)(rdx+0x0) = rax;
                mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
                _fpreset(*(DWORD*)0x14000C006);
                t11 = *(DWORD*)0x14000C022;
                t2 = &*(uintptr_t*)(rbx+0x1);
                t12 = (signed)t2;
                t13 = t12 << 0x3;
                t14 = t13;
                malloc(rdi_2);
                t2 = rax;
                *(uintptr_t*)(rdi+0x0) = 0;
                *(DWORD*)0x14000C019 = r12;
                __main(*(DWORD*)0x14000C006);
                t3 = *(DWORD*)0x140009749;
                t16 = *(DWORD*)0x14000C011;
                t5 = *(DWORD*)0x14000C022;
                t6 = *(uintptr_t*)(rax+0x0);
                *(uintptr_t*)(rax+0x0) = t16;
                t7 = r12;
                main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
                t8 = *(DWORD*)0x14000C006;
                *(DWORD*)0x14000C00A = t6;
                t11 = stack_pop();
                t4 = stack_pop();
                t2 = stack_pop();
                t18 = stack_pop();
                t19 = stack_pop();
                t5 = rax;
                exit(rax);
                t3 = *(DWORD*)0x140009779;
                *(uintptr_t*)(rax+0x0) = 1;
                __tmainCRTStartup(*(DWORD*)0x14000C006);
                t20 = stack_pop();
            } while (1 != 0);
            t7 = *(DWORD*)0x14000C002;
            if (t7 == 0) {
            }
            t4 = *(DWORD*)0x1400097D9;
            t2 = 1;
            t3 = *(uintptr_t*)(rsi+0x0);
            if (t3 != 1) {
            }
            t7 = *(DWORD*)0x140009809;
            t5 = *(DWORD*)0x1400097F9;
            _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
            *(uintptr_t*)(rsi+0x0) = 2;
            t7 = 2;
            t5 = 0;
            rax(0, 2);
            _pei386_runtime_relocator(*(DWORD*)0x14000C006);
            t8 = *(DWORD*)0x140009869;
            ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
            t9 = *(DWORD*)0x1400097B9;
            t10 = &*(DWORD*)0x140000FF9;
            *(uintptr_t*)(rdx+0x0) = rax;
            mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
            _fpreset(*(DWORD*)0x14000C006);
            t11 = *(DWORD*)0x14000C022;
            t2 = &*(uintptr_t*)(rbx+0x1);
            t12 = (signed)t2;
            t13 = t12 << 0x3;
            t14 = t13;
            malloc(rdi_2);
            t2 = rax;
            *(uintptr_t*)(rdi+0x0) = 0;
            *(DWORD*)0x14000C019 = r12;
            __main(*(DWORD*)0x14000C006);
            t3 = *(DWORD*)0x140009749;
            t16 = *(DWORD*)0x14000C011;
            t5 = *(DWORD*)0x14000C022;
            t6 = *(uintptr_t*)(rax+0x0);
            *(uintptr_t*)(rax+0x0) = t16;
            t7 = r12;
            main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
            t8 = *(DWORD*)0x14000C006;
            *(DWORD*)0x14000C00A = t6;
            t11 = stack_pop();
            t4 = stack_pop();
            t2 = stack_pop();
            t18 = stack_pop();
            t19 = stack_pop();
            t5 = rax;
            exit(rax);
            t3 = *(DWORD*)0x140009779;
            *(uintptr_t*)(rax+0x0) = 1;
            __tmainCRTStartup(*(DWORD*)0x14000C006);
            t20 = stack_pop();
        } while (1 != 0);
        t7 = *(DWORD*)0x14000C002;
        if (t7 == 0) {
        }
        t4 = *(DWORD*)0x1400097D9;
        t2 = 1;
        t3 = *(uintptr_t*)(rsi+0x0);
        if (t3 != 1) {
        }
        t7 = *(DWORD*)0x140009809;
        t5 = *(DWORD*)0x1400097F9;
        _initterm(*(DWORD*)0x1400097F9, *(DWORD*)0x140009809);
        *(uintptr_t*)(rsi+0x0) = 2;
        t7 = 2;
        t5 = 0;
        rax(0, 2);
        _pei386_runtime_relocator(*(DWORD*)0x14000C006);
        t8 = *(DWORD*)0x140009869;
        ___FARPROC__gvar_14000D1FA_(*(DWORD*)0x140009869);
        t9 = *(DWORD*)0x1400097B9;
        t10 = &*(DWORD*)0x140000FF9;
        *(uintptr_t*)(rdx+0x0) = rax;
        mingw_set_invalid_parameter_handler(*(DWORD*)0x140000FF9, rax);
        _fpreset(*(DWORD*)0x14000C006);
        t11 = *(DWORD*)0x14000C022;
        t2 = &*(uintptr_t*)(rbx+0x1);
        t12 = (signed)t2;
        t13 = t12 << 0x3;
        t14 = t13;
        malloc(rdi_2);
        t2 = rax;
        *(uintptr_t*)(rdi+0x0) = 0;
        *(DWORD*)0x14000C019 = r12;
        __main(*(DWORD*)0x14000C006);
        t3 = *(DWORD*)0x140009749;
        t16 = *(DWORD*)0x14000C011;
        t5 = *(DWORD*)0x14000C022;
        t6 = *(uintptr_t*)(rax+0x0);
        *(uintptr_t*)(rax+0x0) = t16;
        t7 = r12;
        main(*(DWORD*)0x14000C022, *(DWORD*)0x14000C019, *(DWORD*)0x14000C011);
        t8 = *(DWORD*)0x14000C006;
        *(DWORD*)0x14000C00A = t6;
        t11 = stack_pop();
        t4 = stack_pop();
        t2 = stack_pop();
        t18 = stack_pop();
        t19 = stack_pop();
        t5 = rax;
        exit(rax);
        t3 = *(DWORD*)0x140009779;
        *(uintptr_t*)(rax+0x0) = 1;
        __tmainCRTStartup(*(DWORD*)0x14000C006);
        t20 = stack_pop();
    } while (1 != 0);
    t7 = *(DWORD*)0x14000C002;
    if (t7 == 0) {
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

    _onexit();
    t1 = sbb(eax, eax);
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * atexit @ 0x140001440 (USER)
 * Blocks: 5 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
void atexit(int param_1, int param_2) {
    /* local variables */
    int32_t rbp;
    int32_t rsp;
    int32_t rax;
    int32_t rcx;
    int32_t rbx;
    uint64_t r8;
    int32_t rdx;

    _onexit(*(DWORD*)0x140001469);
    t1 = sbb(eax, eax);
    t2 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * printf @ 0x140001480 (USER)
 * Blocks: 1 | SSA vars: 14
 * ═══════════════════════════════════════════════════ */
void printf(int param_1, int param_2) {
    /* local variables */
    int32_t rsp;
    int32_t rbp;
    int32_t rax;
    int32_t rbx;
    int32_t rcx;
    uint64_t r8;
    int32_t rdx;

    t1 = &*(uintptr_t*)(rsp+0x30);
    arg_30 = r8;
    arg_38 = r9;
    t2 = &rdx;
    t3 = t2;
    t4 = 1;
    t5 = *(DWORD*)0x1400080A9;
    t6 = ___FARPROC__rax_1_(1);
    t7 = rcx;
    t8 = t3;
    t9 = t7;
    t10 = (__mingw_vfprintf(rcx_1, rax_2, rbx_0));
    t11 = stack_pop();
    t12 = stack_pop();
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

    t1 = rcx;
    t2 = rdx;
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

    __main();
    t1 = 20;
    t2 = 10;
    t3 = add(10, 20);
    t4 = &*(DWORD*)0x140008FF9;
    t5 = t4;
    printf(rax_0, rdx_1);
    t6 = 0;
    t7 = stack_pop();
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

    t1 = 0;
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = rcx;
    t3 = &arg_28;
    t4 = 2;
    arg_28 = rdx;
    arg_30 = r8;
    arg_38 = r9;
    var_8 = t3;
    __acrt_iob_func(2);
    t5 = 1;
    t6 = &*(DWORD*)0x1400091B9;
    t7 = t3;
    t8 = fwrite(*(DWORD*)0x1400091B9, 1);
    t9 = 2;
    __acrt_iob_func(2);
    t10 = t2;
    t11 = t3;
    t12 = t8;
    vfprintf(rax_0, rbx_0, rsi_0);
    abort();
    t13 = &*(uintptr_t*)(rsp+0x50);
    t14 = (signed)*(DWORD*)0x14000C09D;
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
    int32_t var_C;
    int32_t var_18;

    t1 = &*(uintptr_t*)(rsp+0x50);
    t2 = (signed)*(DWORD*)0x14000C09D;
    if (t2 != 0) {
    }
    t9 = rbx;
    t10 = __mingw_GetSectionForAddress(rbx, *(uintptr_t*)(rdx+0x8), *(uintptr_t*)(rax+0x0));
    t6 = rbx;
    t9 = &*(DWORD*)0x1400091D9;
    __report_error(*(DWORD*)0x1400091D9, rbx, *(uintptr_t*)(rax+0x0));
    t1 = &*(uintptr_t*)(rsp+0x40);
    t8 = *(DWORD*)0x14000C099;
    t3 = *(DWORD*)0x14000C0A1;
    t13 = &*(uintptr_t*)(rsi+0x0);
    t14 = t13 << 0x3;
    t4 = t3 + t14;
    *(uintptr_t*)(rax+0x20) = rdi;
    *(uintptr_t*)(rax+0x0) = 0;
    _GetPEImageBase();
    t6 = *(uintptr_t*)(rdi+0xC);
    t9 = &*(uintptr_t*)(rax+0x0);
    t15 = *(DWORD*)0x14000C0A1;
    t7 = &var_30;
    *(uintptr_t*)(rax+0x18) = t9;
    ___FARPROC__gvar_14000D21A_(*(uintptr_t*)(rax+0x0), var_30, *(uintptr_t*)(rax+0x0));
    t3 = *(DWORD*)0x14000C0A1;
    t6 = *(uintptr_t*)(rdi+0x8);
    t9 = &*(DWORD*)0x1400091F9;
    t5 = *(uintptr_t*)(rax+0x18);
    __report_error(*(DWORD*)0x1400091F9, *(uintptr_t*)(rdi+0x8), *(uintptr_t*)(rax+0x18));
    t7 = rbx;
    t19 = &*(DWORD*)0x1400091D9;
    __report_error(*(DWORD*)0x1400091D9, rbx, *(uintptr_t*)(rax+0x0));
    t1 = &*(uintptr_t*)(rsp+0x40);
    t8 = *(DWORD*)0x14000C099;
    t3 = var_C;
    t6 = &*(uintptr_t*)(rax-0x4);
    t7 = t6 & -5;
    if ( == ) {
    }
    *(DWORD*)0x14000C09D = *(DWORD*)0x14000C09D + 1;
    t13 = stack_pop();
    t2 = stack_pop();
    t10 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x40);
    t2 = *(DWORD*)0x14000C099;
    if (t2 == 0) {
    }
    t3 = &arg_8;
    t4 = stack_pop();
    t5 = stack_pop();
    t6 = stack_pop();
    t7 = stack_pop();
    t8 = stack_pop();
    t9 = stack_pop();
    t10 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = &*(DWORD*)0x14000C0F9;
    t3 = t2;
    ___FARPROC__gvar_14000D1CA_(r13_0);
    t4 = rax;
    if (t4 == 0) {
    }
    t3 = r13;
    t4 = stack_pop();
    t7 = stack_pop();
    t6 = stack_pop();
    t5 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
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

    t1 = *(DWORD*)0x140009739;
    t2 = 0;
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

    t1 = *(DWORD*)0x140009739;
    t2 = 0;
    if ([rax+0x0] != 23117) {
    }
    t1 = rcx;
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

    t1 = *(DWORD*)0x140009739;
    t2 = 0;
    if ([rax+0x0] != 23117) {
    }
    t1 = rdx;
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

    t1 = &*(uintptr_t*)(rsp+0x18);
    if ((unsigned)rax < (unsigned)4096) {
    }
    t1 = rcx - rax;
    *(uintptr_t*)(rcx+0x0) = *(uintptr_t*)(rcx+0x0) | 0;
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = r8;
    t3 = rcx;
    t4 = rdx;
    _lock_file();
    *(uintptr_t*)(rsp+0x20) = r8;
    t5 = rdx;
    t6 = t3;
    t7 = 24576;
    __mingw_pformat(24576, rbx_0);
    t8 = t3;
    t9 = rax;
    t10 = _unlock_file(rbx_0);
    t11 = stack_pop();
    t12 = stack_pop();
    t13 = stack_pop();
    t14 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __pformat_cvt @ 0x140002680 (USER)
 * Blocks: 17 | SSA vars: 17
 * ═══════════════════════════════════════════════════ */
void __pformat_cvt(int param_1) {
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

    t1 = *(uintptr_t*)(rdx+0x0);
    t2 = *(uintptr_t*)(rdx+0x8);
    var_10 = t1;
    t3 = t2;
    var_8 = t2;
    t4 = rcx & 32767;
    if ( != ) {
    }
    var_1C = rax;
    t3 = rcx & 32768;
    t1 = arg_30;
    *(uintptr_t*)(rax+0x0) = t3;
    t6 = &var_18;
    t8 = &*(DWORD*)0x140008039;
    *(uintptr_t*)(rsp+0x30) = r9;
    t9 = &4;
    *(uintptr_t*)(rsp+0x28) = invalid;
    t10 = &t1;
    *(uintptr_t*)(rsp+0x38) = t6;
    *(uintptr_t*)(rsp+0x20) = invalid;
    __gdtoa(*(DWORD*)0x140008039, 0, var_10, var_1C);
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = *(uintptr_t*)(rdx+0x8);
    if (t2 != 0) {
    }
    t3 = *(uintptr_t*)(rbx+0x0);
    t2 = rdx & 32;
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

    t1 = &*(uintptr_t*)(rsp+0x50);
    t2 = &var_18;
    t3 = &var_10;
    t4 = rdx;
    t5 = 0;
    t6 = t2;
    t7 = t3;
    var_28 = t2;
    wcrtomb(rdi_0, 0, rax_0);
    t8 = *(uintptr_t*)(rbx+0x10);
    t9 = t8;
    t10 = t4;
    t11 = *(uintptr_t*)(rbx+0xC);
    t12 = t4;
    t2 = rax - rsi;
    *(uintptr_t*)(rbx+0xC) = t2;
    if ([rbx+0x9] != 0) {
    }
    t4 = 0;
    t13 = invalid + 1;
    t5 = (unsigned)*(uintptr_t*)(r12+0x0);
    t6 = t2;
    t7 = rdi;
    wcrtomb(rdi, *(uintptr_t*)(r12+0x0), var_28);
    t2 = *(uintptr_t*)(rbx+0xC);
    t5 = &*(uintptr_t*)(rax-0x1);
    *(uintptr_t*)(rbx+0xC) = t5;
    if (t2 != 0) {
    }
    t18 = stack_pop();
    t4 = stack_pop();
    t3 = stack_pop();
    t19 = stack_pop();
    t20 = stack_pop();
    t15 = stack_pop();
    t16 = stack_pop();
    t2 = rax - 1;
    t15 = &*(uintptr_t*)(rdi+0x1);
    t5 = *(uintptr_t*)(rbx+0x8);
    t16 = r15 + 1;
    if (t5 != 0) {
    }
    t7 = (signed)*(uintptr_t*)(r15-0x1);
    t2 = *(uintptr_t*)(rbx+0x0);
    t5 = rdx & 32;
    if ( == ) {
    }
    t4 = rsi + 1;
    t2 = invalid;
    t8 = invalid - t4;
    if (t8 != 0) {
    }
    *(uintptr_t*)(rbx+0xC) = -1;
    t13 = &*(uintptr_t*)(rsi-0x1);
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = *(uintptr_t*)(r8+0x10);
    t3 = rdx;
    t4 = t2;
    t5 = rcx;
    t6 = rdx;
    t7 = *(uintptr_t*)(r8+0xC);
    t8 = t3;
    if (t7 > t8) {
    }
    t2 = *(uintptr_t*)(rbx+0x8);
    t3 = &*(uintptr_t*)(rdx+0x1);
    t8 = t3 + rsi;
    t5 = rsi + 1;
    if (rax != 0) {
    }
    t9 = (signed)*(uintptr_t*)(rsi-0x1);
    t4 = *(uintptr_t*)(rbx+0x0);
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = &*(DWORD*)0x140009349;
    t3 = rdx;
    t4 = (signed)*(uintptr_t*)(rdx+0x10);
    t5 = t2;
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

    *(uintptr_t*)(r8+0x10) = -1;
    if (rcx != 0) {
    }
    t4 = invalid & 32;
    t5 = 0;
    t1 = (unsigned)*(uintptr_t*)(rdx+0x0);
    t6 = t1 & -33;
    t7 = t6 | t4;
    *(uintptr_t*)(r9+0x0) = t7;
    t9 = 0 + 1;
    if (t9 != 3) {
    }
    t10 = &*(uintptr_t*)(r9+0x3);
    t5 = r11;
    t11 = t10 - invalid;
    __pformat_putchars(r11, rdx_0, -1, rax_3);
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    if (rcx == 111) {
    }
    t8 = r8 * r9;
    t9 = (unsigned)t8 >> 0x21;
    t3 = rax + -1431655765;
    t10 = *(uintptr_t*)(rbx+0xC);
    t5 = t10;
    t6 = (signed)t10;
    t11 = t6 + 15;
    t12 = t11 & -16;
    ___chkstk_ms(4);
    t13 = (flags_ZF == 0);
    t14 = &*(uintptr_t*)(rsp+0x20);
    t15 = &*(uintptr_t*)(invalid+0x7);
    t17 = r12;
    t22 = invalid & 32;
    t3 = t22;
    t21 = t17 + 1;
    t5 = t22 & rdx;
    t10 = &*(uintptr_t*)(rax+0x30);
    t6 = t5 + 55;
    t11 = t6 | t10;
    t16 = t10;
    t12 = t16;
    t19 = (unsigned)rdx >> rcx;
    *(uintptr_t*)(rsi-0x1) = t16;
    if (t19 != 0) {
    }
    t14 = r12;
    if (rsi == t14) {
    }
    if (invalid == 0) {
    }
    *(uintptr_t*)(rbx+0xC) = -1;
    if (invalid != 111) {
    }
    t17 = rsi - 1;
    if (rdi != 0) {
    }
    t4 = rdi & 8192;
    t7 = (signed)*(uintptr_t*)(rsi+0x0);
    t19 = *(uintptr_t*)(rbx+0x0);
    if ( == ) {
    }
    t4 = rdi & -2049;
    *(uintptr_t*)(rbx+0x8) = t4;
    if (invalid != 0) {
    }
    t19 = &*(uintptr_t*)(rsi+0x1);
    *(uintptr_t*)(rsi+0x0) = 48;
    t3 = t19;
    t17 = t19;
    t5 = t19 - r12;
    t23 = t5;
    if (t5 >= invalid) {
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = 0;
    t3 = *(uintptr_t*)(rdx+0x10);
    t4 = *(uintptr_t*)(rdx+0x8);
    t5 = t3;
    t6 = t3 + 23;
    if (t4 == 0) {
    }
    t7 = *(uintptr_t*)(rbx+0xC);
    t2 = t7;
    t5 = (signed)t7;
    t6 = t5 + 15;
    t8 = t6 & -16;
    ___chkstk_ms();
    t9 = &*(uintptr_t*)(rsp+0x20);
    if (rcx == 0) {
    }
    t15 = (signed)invalid;
    t18 = r13;
    t14 = 48;
    t10 = t15;
    t13 = r13 + t15;
    memset(r13, 48, r15_0, -3689348814741910323);
    t2 = (flags_ZF != 0);
    if (rsi != 0) {
    }
    if (invalid == 0) {
    }
    t2 = *(uintptr_t*)(rbx+0xC);
    t14 = rax;
    t2 = rax - 1;
    *(uintptr_t*)(rbx+0xC) = t2;
    if (t14 != 0) {
    }
    t23 = &arg_8;
    t24 = stack_pop();
    t7 = stack_pop();
    t4 = stack_pop();
    t9 = stack_pop();
    t13 = stack_pop();
    t25 = stack_pop();
    t15 = stack_pop();
    if (rax != 0) {
    }
    if (rcx < 0) {
    }
    t10 = r12;
    t11 = -3689348814741910323;
    t12 = rdi & 4096;
    if (r12 == t10) {
    }
    t2 = rcx;
    t13 = &*(uintptr_t*)(r8+0x1);
    t5 = rcx / r9;
    t6 = rcx;
    t14 = (unsigned)rdx >> 0x3;
    t15 = &*(uintptr_t*)(rdx+0x0);
    t16 = t15 + t15;
    t8 = rcx - t16;
    t17 = t8 + 48;
    *(uintptr_t*)(r8+0x0) = t17;
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    if ([rcx+0x14] == -3) {
    }
    t3 = (signed)*(uintptr_t*)(rbx+0x14);
    t4 = rsp;
    t5 = t3 + 15;
    t6 = t5 & -16;
    ___chkstk_ms();
    t7 = &0;
    var_8 = 0;
    t8 = &*(uintptr_t*)(rsp+0x20);
    t9 = t8;
    wcrtomb(rsi_0, *(uintptr_t*)(rcx+0x18), var_8);
    t2 = rbx;
    t9 = 46;
    __pformat_putc(46, rbx);
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = *(uintptr_t*)(r9+0xC);
    t3 = rcx;
    t4 = rdx;
    t5 = t3;
    if (t3 != 0) {
    }
    t2 = rax - rdx;
    *(uintptr_t*)(rbx+0xC) = t2;
    if (rdx != 0) {
    }
    t2 = rax - 1;
    *(uintptr_t*)(rbx+0xC) = t2;
    if (rsi != 0) {
    }
    if (rax != 0) {
    }
    if (invalid != 0) {
    }
    t2 = *(uintptr_t*)(rbx+0xC);
    if (t2 != 0) {
    }
    if (rsi != 0) {
    }
    t2 = rax - 1;
    *(uintptr_t*)(rbx+0x10) = t2;
    t12 = stack_pop();
    t5 = stack_pop();
    t4 = stack_pop();
    t13 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = 1 - 1;
    t3 = rcx;
    t4 = (signed)t3;
    t5 = (signed)t3 >> 0x1F;
    t6 = rcx * 1717986919;
    t7 = (signed)t6 >> 0x22;
    t8 = t7 - t5;
    if ( == ) {
    }
    t9 = *(uintptr_t*)(rbx+0x2C);
    if (t9 != -1) {
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

    t1 = &*(uintptr_t*)(rsp+0x50);
    t2 = *(uintptr_t*)(rdx+0x10);
    /* asm: fld *(uintptr_t*)(rcx+0x0) */;
    if (t2 < 0) {
    }
    t5 = var_8;
    t7 = rbx;
    t4 = rax;
    __pformat_emit_efloat(var_8, rax);
    t10 = rsi;
    __freedtoa(rsi, 6);
    t11 = stack_pop();
    t9 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x50);
    t2 = *(uintptr_t*)(rdx+0x10);
    /* asm: fld *(uintptr_t*)(rcx+0x0) */;
    if (t2 >= 0) {
    }
    t5 = var_8;
    t4 = rax;
    t7 = rbx;
    __pformat_emit_float(var_8, rax);
    t3 = *(uintptr_t*)(rbx+0xC);
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

    t1 = &*(uintptr_t*)(rsp+0x50);
    t2 = *(uintptr_t*)(rdx+0x10);
    /* asm: fld *(uintptr_t*)(rcx+0x0) */;
    if (t2 < 0) {
    }
    t3 = &var_8;
    t4 = &var_20;
    t5 = 2;
    /* asm: t6 */;
    t7 = &var_4;
    *(uintptr_t*)(rsp+0x20) = t3;
    t8 = __pformat_cvt(2, var_20);
    t9 = t3;
    t5 = var_8;
    t17 = rbx;
    t4 = rax;
    __pformat_emit_inf_or_nan(var_8, rax, rbx);
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

    t1 = &*(uintptr_t*)(rsp+0x50);
    t2 = rcx;
    t3 = rdx;
    if (rdx != 0) {
    }
    t4 = &*(uintptr_t*)(rax-0x3);
    if ((unsigned)t4 <= (unsigned)14) {
    }
    t4 = *(uintptr_t*)(rbx+0x8);
    t7 = &-8589934593;
    t3 = t7;
    if (t4 == 0) {
    }
    t6 = *(uintptr_t*)(rbx+0x10);
    t13 = rsi;
    t3 = (signed)invalid;
    t25 = (signed)invalid;
    t14 = rsi - rdi;
    t4 = &*(uintptr_t*)(rdx+0x0);
    t16 = t4;
    t15 = t4;
    t17 = t4 & 448;
    t18 = sbb(ecx, -6);
    t26 = t25 * 1717986919;
    t12 = (signed)t3 >> 0x1F;
    t22 = (signed)t26 >> 0x22;
    t27 = t18 - t12;
    if (t17 == 1) {
    }
    t4 = invalid - invalid;
    if (t4 != 0) {
    }
    if (invalid != 0) {
    }
    t6 = rbx;
    t13 = 48;
    __pformat_putc(48, rbx, r8_2, r9_0);
    t14 = *(uintptr_t*)(rbx+0x8);
    t16 = rbx;
    t15 = t14 & 32;
    t18 = t15 | 88;
    __pformat_putc(rcx_3, rbx, r8_2, r9_0);
    t3 = *(uintptr_t*)(rbx+0xC);
    t23 = &t3;
    if ((unsigned)rdi < (unsigned)rsi) {
    }
    t3 = *(uintptr_t*)(rbx+0x10);
    t6 = &*(uintptr_t*)(rax-0x1);
    *(uintptr_t*)(rbx+0x10) = t6;
    if (t3 != 0) {
    }
    t13 = *(uintptr_t*)(rbx+0x8);
    t6 = rbx;
    t14 = t13 & 32;
    t15 = t14 | 80;
    __pformat_putc(rcx_2, rbx, r8_2, r9_0);
    *(uintptr_t*)(rbx+0xC) = *(uintptr_t*)(rbx+0xC) + invalid;
    t16 = rbx;
    t18 = r12;
    *(uintptr_t*)(rbx+0x8) = *(uintptr_t*)(rbx+0x8) | 448;
    t30 = stack_pop();
    t8 = stack_pop();
    t7 = stack_pop();
    t5 = stack_pop();
    t31 = stack_pop();
    t23 = stack_pop();
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
    int32_t var_68;
    int32_t var_40;
    int32_t var_60;
    int32_t var_80;
    int32_t var_78;
    int32_t var_88;
    int32_t var_70;
    int32_t var_42;

    t1 = &*(uintptr_t*)(rsp+0xB0);
    t2 = rcx;
    t3 = r9;
    _errno();
    t4 = rcx & 24576;
    t5 = 0;
    t6 = -8589934593;
    var_18 = 0;
    t7 = *(uintptr_t*)(rax+0x0);
    t8 = &*(uintptr_t*)(rsi+0x1);
    var_20 = -8589934593;
    t9 = 0;
    var_10 = 0;
    t10 = (signed)*(uintptr_t*)(rsi+0x0);
    var_30 = rdx;
    var_28 = t4;
    t11 = t10;
    var_24 = -1;
    var_14 = 0;
    var_C = 0;
    var_4 = -1;
    t7 = rcx;
    t18 = stack_pop();
    t3 = stack_pop();
    t2 = stack_pop();
    t15 = stack_pop();
    t12 = stack_pop();
    t19 = stack_pop();
    t14 = stack_pop();
    t3 = &var_24;
    t12 = &*(DWORD*)0x140009369;
    var_68 = t3;
    if (rcx != 37) {
    }
    t6 = t3;
    t7 = t6;
    t18 = stack_pop();
    t3 = stack_pop();
    t2 = stack_pop();
    t15 = stack_pop();
    t12 = stack_pop();
    t19 = stack_pop();
    t14 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    if (rcx <= 27) {
    }
    t6 = rbx;
    __Balloc_D2A(rbx, *(uintptr_t*)(rax+0x17));
    *(uintptr_t*)(rax+0x0) = rbx;
    t2 = rax + 4;
    t4 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = rcx;
    t3 = rdx;
    if (invalid <= 27) {
    }
    t9 = rbx;
    __Balloc_D2A(rbx, *(uintptr_t*)(rax+0x17));
    t7 = &*(uintptr_t*)(rdi+0x1);
    *(uintptr_t*)(rax+0x0) = rbx;
    t11 = (unsigned)*(uintptr_t*)(rdi+0x0);
    t12 = &*(uintptr_t*)(rax+0x4);
    *(uintptr_t*)(rax+0x4) = t11;
    t4 = t12;
    if (rsi == 0) {
    }
    t9 = (unsigned)*(uintptr_t*)(rdx+0x0);
    t4 = rax + 1;
    t7 = rdx + 1;
    *(uintptr_t*)(rax+0x0) = t9;
    if (t9 != 0) {
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

    t1 = 1;
    t2 = rcx;
    t3 = *(uintptr_t*)(rcx-0x4);
    t4 = 1 << t3;
    t5 = t3;
    t6 = &*(uintptr_t*)(rax-0x4);
    t7 = t4;
    /* asm: punpckldq xmm0 xmm1 */;
    *(uintptr_t*)(rax+0x4) = t3;
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = 0;
    t3 = *(uintptr_t*)(rdx+0x14);
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
    int32_t var_18;
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

    t1 = &*(uintptr_t*)(rsp+0xC0);
    t2 = arg_70;
    t3 = *(uintptr_t*)(r9+0x0);
    var_28 = t2;
    t4 = arg_78;
    t5 = r8;
    var_30 = rdx;
    var_34 = t4;
    t6 = arg_80;
    var_18 = t6;
    t7 = arg_88;
    var_20 = t7;
    t8 = t3;
    t9 = t3 & -49;
    *(uintptr_t*)(r9+0x0) = t9;
    t10 = t3;
    t11 = t3 & 7;
    if (t11 == 3) {
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

    t1 = &*(uintptr_t*)(rsp+0x0);
    t2 = (signed)*(uintptr_t*)(rcx+0x14);
    t3 = (signed)rdx >> 0x5;
    if (t2 > t3) {
    }
    *(uintptr_t*)(r10+0x14) = 0;
    *(uintptr_t*)(r10+0x18) = 0;
    t2 = stack_pop();
    t4 = stack_pop();
    t5 = stack_pop();
    t6 = stack_pop();
    t7 = stack_pop();
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

    t1 = (signed)*(uintptr_t*)(rcx+0x14);
    t2 = &*(uintptr_t*)(rcx+0x18);
    t3 = &*(uintptr_t*)(rax+0x0);
    t4 = 0;
    if ((unsigned)t2 < (unsigned)t3) {
    }
    t2 = rdx;
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = t7;
    t3 = rcx;
    if (t2 == 2) {
    }
    t4 = &*(DWORD*)0x14000CAF9;
    t5 = rsi;
    t8 = 0 - rsi;
    t10 = t8 & 40;
    t11 = t10 + rbx;
    t4 = stack_pop();
    t3 = stack_pop();
    t6 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = rcx;
    t3 = 0;
    dtoa_lock(0);
    t3 = rbx;
    t8 = 1;
    t9 = 1 << rbx;
    t5 = &*(uintptr_t*)(rsi-0x1);
    t10 = (signed)t5;
    t11 = &*(uintptr_t*)(invalid+0x27);
    t12 = (unsigned)t11 >> 0x3;
    t13 = t12;
    t14 = t12 << 0x3;
    malloc(rcx_4);
    t2 = stack_pop();
    t8 = stack_pop();
    *(uintptr_t*)(rax+0x8) = rbx;
    *(uintptr_t*)(rax+0xC) = rsi;
    if (gvar_14000CAE9 == 2) {
    }
    *(uintptr_t*)(rax+0x10) = 0;
    t2 = stack_pop();
    t8 = stack_pop();
    t4 = &*(DWORD*)0x14000CA99;
    t3 = (signed)rbx;
    t5 = *(uintptr_t*)(rdx+0x0);
    if (t5 == 0) {
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    if (rcx == 0) {
    }
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = *(uintptr_t*)(rcx+0x14);
    t3 = (signed)invalid;
    t4 = (signed)rdx;
    t5 = 0;
    t6 = *(uintptr_t*)(rbx+0x18);
    t7 = t6 * t4;
    t8 = t7 + t3;
    *(uintptr_t*)(rbx+0x18) = t8;
    t9 = t8;
    t10 = 0 + 1;
    t11 = (unsigned)t8 >> 0x20;
    if (t2 > t10) {
    }
    if (rsi == 0) {
    }
    t6 = r12;
    t12 = stack_pop();
    t3 = stack_pop();
    t2 = stack_pop();
    t15 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = 0;
    dtoa_lock(0);
    t3 = t4;
    t3 = t4;
    t2 = &*(DWORD*)0x14000C199;
    t4 = t3;
    t6 = t3 - t2;
    t7 = (signed)t6 >> 0x3;
    t8 = t7 + 5;
    if ((unsigned)t8 <= (unsigned)288) {
    }
    t4 = *(DWORD*)0x1400096C1;
    *(uintptr_t*)(rax+0x8) = t4;
    if (gvar_14000CAE9 != 2) {
    }
    t4 = *(DWORD*)0x1400096C9;
    *(uintptr_t*)(rax+0x18) = rbx;
    *(uintptr_t*)(rax+0x10) = t4;
    t5 = stack_pop();
    t4 = *(uintptr_t*)(rax+0x0);
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = (signed)*(uintptr_t*)(rcx+0x14);
    t3 = (signed)*(uintptr_t*)(rdx+0x14);
    t4 = rcx;
    if (invalid < invalid) {
    }
    t6 = rcx + 1;
    arg_50 = r9;
    t8 = __Balloc_D2A(rcx);
    t5 = rdi;
    t7 = stack_pop();
    t11 = stack_pop();
    t8 = stack_pop();
    t10 = stack_pop();
    t3 = stack_pop();
    t2 = stack_pop();
    t27 = stack_pop();
    t10 = &*(uintptr_t*)(rax+0x18);
    t5 = (signed)rbx;
    t4 = r9;
    t11 = &*(uintptr_t*)(r12+0x0);
    if ((unsigned)t10 >= (unsigned)t11) {
    }
    t5 = r13;
    t20 = &*(uintptr_t*)(r15+0x19);
    t13 = r13 - r15;
    t14 = t13 - 25;
    t15 = (unsigned)t14 >> 0x2;
    t12 = &*(uintptr_t*)(invalid+0x4);
    t21 = 4;
    t22 = t12;
    t23 = *(uintptr_t*)(r9+0x0);
    t4 = r9 + 4;
    if (t23 == 0) {
    }
    if (rbx != 0) {
    }
    *(uintptr_t*)(rdi+0x14) = rbx;
    t5 = rdi;
    t7 = stack_pop();
    t11 = stack_pop();
    t8 = stack_pop();
    t10 = stack_pop();
    t3 = stack_pop();
    t2 = stack_pop();
    t27 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = rdx;
    t3 = rcx;
    t4 = rdx & 3;
    if ( != ) {
    }
    t5 = (signed)rbx >> 0x2;
    if ( == ) {
    }
    t2 = r12;
    t5 = stack_pop();
    t3 = stack_pop();
    t6 = stack_pop();
    t9 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = rdx;
    t3 = *(uintptr_t*)(rcx+0x8);
    t4 = *(uintptr_t*)(r13+0x14);
    t5 = (signed)rdx >> 0x5;
    t6 = *(uintptr_t*)(r13+0xC);
    t7 = t4 + t5;
    t8 = &*(uintptr_t*)(rbx+0x1);
    if (t8 <= t6) {
    }
    __Balloc_D2A(*(uintptr_t*)(rcx+0x8));
    t6 = r15;
    t4 = stack_pop();
    t2 = stack_pop();
    t10 = stack_pop();
    t26 = stack_pop();
    t27 = stack_pop();
    t28 = stack_pop();
    t29 = stack_pop();
    t10 = &*(uintptr_t*)(rax+0x18);
    if (rsi != 0) {
    }
    t15 = rdi;
    t11 = 0;
    t8 = 32 - 32;
    t6 = *(uintptr_t*)(rsi+0x0);
    t3 = t8;
    t16 = rdi + 4;
    t2 = rsi + 4;
    t17 = t6 << t8;
    t18 = t8;
    t19 = t17 | 0;
    *(uintptr_t*)(r9-0x4) = t19;
    t20 = *(uintptr_t*)(rsi-0x4);
    t21 = (unsigned)t20 >> t8;
    if ((unsigned)t2 < (unsigned)r8) {
    }
    t6 = r8;
    t3 = &*(uintptr_t*)(r13+0x19);
    t17 = r8 - r13;
    t19 = t17 - 25;
    t22 = (unsigned)t19 >> 0x2;
    t18 = 4;
    t23 = &*(uintptr_t*)(invalid+0x4);
    t24 = 4;
    *(uintptr_t*)(rdi+0x0) = rdx;
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

    t1 = (signed)*(uintptr_t*)(rdx+0x14);
    t2 = *(uintptr_t*)(rcx+0x14);
    t3 = t2 - t1;
    if ( != ) {
    }
    t1 = invalid;
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = (signed)*(uintptr_t*)(rdx+0x14);
    t3 = rdx;
    if ([rcx+0x14] != t2) {
    }
    t5 = *(uintptr_t*)(rsi+0x8);
    t8 = __Balloc_D2A(*(uintptr_t*)(rsi+0x8), rdx);
    t2 = r9;
    t27 = stack_pop();
    t3 = stack_pop();
    t7 = stack_pop();
    t11 = stack_pop();
    t10 = stack_pop();
    t24 = stack_pop();
    *(uintptr_t*)(rax+0x10) = rdi;
    t2 = (signed)*(uintptr_t*)(rsi+0x14);
    t10 = &*(uintptr_t*)(rsi+0x18);
    t11 = &*(uintptr_t*)(r9+0x18);
    t5 = 24;
    t4 = 0;
    t12 = &*(uintptr_t*)(r13+0x0);
    t13 = (signed)*(uintptr_t*)(rbx+0x14);
    t14 = &*(uintptr_t*)(rbx+0x18);
    t7 = *(uintptr_t*)(rbx+0x0);
    t15 = *(uintptr_t*)(rsi+0x0);
    t16 = t15 - t7;
    t17 = t16 - 0;
    *(uintptr_t*)(r9+0x0) = t17;
    t6 = t17;
    t18 = 24 + 4;
    t19 = t17;
    t20 = (unsigned)t17 >> 0x20;
    t21 = &*(uintptr_t*)(rcx+0x0);
    t22 = t20 & 1;
    if ((unsigned)t21 < (unsigned)t14) {
    }
    t2 = &*(uintptr_t*)(rbx+0x19);
    t5 = 4;
    t23 = (flags_CF == 0);
    t14 = r8 - rbx;
    t24 = &*(uintptr_t*)(r8-0x19);
    t25 = (unsigned)t24 >> 0x2;
    t13 = &*(uintptr_t*)(invalid+0x4);
    t15 = 4;
    t10 = r13 + t5;
    t26 = &*(uintptr_t*)(r12+0x0);
    t18 = t10;
    if ((unsigned)t10 >= (unsigned)r11) {
    }
    t4 = *(uintptr_t*)(rax-0x4);
    t2 = rax - 4;
    t23 = invalid - 1;
    if (t4 == 0) {
    }
    *(uintptr_t*)(r9+0x14) = invalid;
    t2 = r9;
    t27 = stack_pop();
    t3 = stack_pop();
    t7 = stack_pop();
    t11 = stack_pop();
    t10 = stack_pop();
    t24 = stack_pop();
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

    t1 = &*(uintptr_t*)(rsp+0x0);
    t2 = (signed)*(uintptr_t*)(rcx+0x14);
    t3 = &*(uintptr_t*)(rcx+0x18);
    t4 = &*(uintptr_t*)(r11+0x0);
    t5 = &*(uintptr_t*)(r10-0x4);
    t6 = bsr(invalid);
    t7 = t6;
    t8 = 32;
    t9 = t6 ^ 31;
    t10 = t8 - t9;
    *(uintptr_t*)(rdx+0x0) = t10;
    if (t9 <= 10) {
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

    t1 = rcx;
    if (rdx != 0) {
    }
    t1 = r8;
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

    t1 = rdx;
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

    t1 = *(DWORD*)0x140009769;
    t2 = *(uintptr_t*)(rax+0x0);
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

    t1 = *(DWORD*)0x140009759;
    t2 = *(uintptr_t*)(rax+0x0);
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = rcx;
    t3 = 0;
    __acrt_iob_func(0);
    t3 = &*(uintptr_t*)(rbx+0x30);
    t2 = stack_pop();
    t3 = 19;
    __acrt_iob_func(19);
    t3 = 0;
    t4 = __acrt_iob_func(0);
    t5 = rbx;
    t6 = rbx - rax;
    t7 = (signed)t6 >> 0x4;
    t8 = t7 * -1431655765;
    t9 = &*(uintptr_t*)(rax+0x10);
    _lock(*(uintptr_t*)(rax+0x10), rdx_0);
    *(uintptr_t*)(rbx+0x18) = *(uintptr_t*)(rbx+0x18) | 32768;
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    t2 = rcx;
    t3 = 0;
    __acrt_iob_func(0);
    t3 = &*(uintptr_t*)(rbx+0x30);
    t2 = stack_pop();
    t3 = 19;
    __acrt_iob_func(19);
    *(uintptr_t*)(rbx+0x18) = *(uintptr_t*)(rbx+0x18) & -32769;
    t3 = 0;
    __acrt_iob_func(0);
    t2 = rbx - rax;
    t4 = (signed)t2 >> 0x4;
    t5 = t4 * -1431655765;
    t6 = &*(uintptr_t*)(rbx+0x10);
    t7 = stack_pop();
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

    t1 = rcx;
    *(DWORD*)0x14000CB59 = t2;
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

    t1 = &*(uintptr_t*)(rsp+0x20);
    __iob_func();
    t2 = rcx;
    t3 = &*(uintptr_t*)(rcx+0x0);
    t4 = t3 << 0x4;
    t5 = rax + t4;
    t6 = stack_pop();
    t7 = stack_pop();
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

    t1 = rcx;
    arg_18 = rdx;
    t2 = invalid;
    if (invalid != 0) {
    }
    _errno(invalid, var_4);
    *(uintptr_t*)(rax+0x0) = 42;
    t1 = -1;
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

    t1 = &*(uintptr_t*)(rsp+0x30);
    t2 = &var_5;
    t3 = rdx;
    t4 = ___mb_cur_max_func();
    ___lc_codepage_func();
    t5 = (unsigned)rdx;
    t6 = t2;
    __wcrtomb_cp(rax_0, rdx);
    t7 = (signed)t2;
    t8 = stack_pop();
    t9 = stack_pop();
    t10 = stack_pop();
    t11 = stack_pop();
}

/* ═══════════════════════════════════════════════════
 * __mbrtowc_cp @ 0x1400076A0 (USER)
 * Blocks: 26 | SSA vars: 23
 * ═══════════════════════════════════════════════════ */
void __mbrtowc_cp(int param_1, int param_2) {
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

    t1 = &*(uintptr_t*)(rsp+0x40);
    t2 = rcx;
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

    t1 = &*(uintptr_t*)(rsp+0x40);
    t2 = 0;
    var_2 = 0;
    t3 = &t2;
    t4 = r9;
    t5 = rdx;
    ___mb_cur_max_func();
    ___lc_codepage_func();
    *(uintptr_t*)(rsp+0x28) = t3;
    t6 = r8;
    *(uintptr_t*)(rsp+0x20) = t3;
    t7 = &*(DWORD*)0x14000CB71;
    t8 = rdx;
    t9 = t3;
    t10 = t4;
    __mbrtowc_cp(rax_1, rdx, r8, rsi_0);
    t11 = (signed)t3;
    t12 = stack_pop();
    t13 = stack_pop();
    t14 = stack_pop();
    t15 = stack_pop();
    t16 = stack_pop();
    t17 = stack_pop();
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

