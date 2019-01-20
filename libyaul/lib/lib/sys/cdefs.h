/*-
 * Copyright (c) 1991, 1993
 * The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_

#include <stddef.h>

#ifdef __GNUC__
#define __ASMNAME(cname)  __XSTRING (__USER_LABEL_PREFIX__) cname
#endif /* __GNUC__ */

/*
 * Testing against Clang-specific extensions.
 */
#ifndef __has_attribute
#define __has_attribute(x)      0
#endif /* !__has_attribute */
#ifndef __has_extension
#define __has_extension         __has_feature
#endif /* !__has_extension */
#ifndef __has_feature
#define __has_feature(x)        0
#endif /* !__has_feature */
#ifndef __has_include
#define __has_include(x)        0
#endif /* !__has_include */
#ifndef __has_builtin
#define __has_builtin(x)        0
#endif /* !__has_builtin */

#ifdef __cplusplus
#define __BEGIN_DECLS   extern "C" {
#define __END_DECLS     }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/*
 * Compiler memory barriers, specific to gcc and clang.
 */
#ifdef __GNUC__
#define __compiler_membar() __asm __ volatile(" " : : : "memory")
#endif /* __GNUC__ */

/*
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky to use if it must work in non-ANSI
 * mode -- there must be no spaces between its arguments, and for nested
 * __CONCAT's, all the __CONCAT's must be at the left.  __CONCAT can also
 * concatenate double-quoted strings produced by the __STRING macro, but
 * this only works with ANSI C.
 *
 * __XSTRING is like __STRING, but it expands any macros in its argument
 * first.  It is only available with ANSI C.
 */
#if defined(__STDC__) || defined(__cplusplus)
#define __P(protos)     protos /* full-blown ANSI C */
#define __CONCAT1(x,y)  x ## y
#define __CONCAT(x,y)   __CONCAT1(x,y)
#define __STRING(x)     #x /* stringify without expanding x */
#define __XSTRING(x)    __STRING(x) /* expand x, then stringify */

#define __const         const /* define reserved names to standard */
#define __signed        signed
#define __volatile      volatile

#if defined(__cplusplus)
#define __inline        inline /* convert to C++ keyword */
#endif /* !__cplusplus */

#else /* !(__STDC__ || __cplusplus) */
#define __P(protos)     () /* traditional C preprocessor */
#define __CONCAT(x,y)   x/**/y
#define __STRING(x)     "x"
#endif /* !(__STDC__ || __cplusplus) */

#ifndef static_assert
#define static_assert(__e)                                                     \
        typedef char __CONCAT(STATIC_ASSERT_FAILED_AT_LINE,                    \
                __CONCAT(_, __LINE__))[(__e) ? 1 : -1]
#endif /* !static_assert */

#define __interrupt_handler	__attribute__ ((interrupt_handler))

/*
 * Compiler-dependent macros to help declare dead (non-returning) and
 * pure (no side effects) functions, and unused variables.  They are
 * null except for versions of gcc that are known to support the features
 * properly (old versions of gcc-2 supported the dead and pure features
 * in a different (wrong) way).  If we do not provide an implementation
 * for a given compiler, let the compile fail if it is told to use
 * a feature that we cannot live without.
 */

#define __noreturn              __attribute__ ((noreturn))
#define __dead2                 __attribute__ ((__noreturn__))
#define __pure2                 __attribute__ ((__const__))
#define __unused                __attribute__ ((__unused__))
#define __used                  __attribute__ ((__used__))
#define __packed                __attribute__ ((__packed__))
#define __weak                  __attribute__ ((__weak__))
#define __aligned(x)            __attribute__ ((__aligned__(x)))
#define __section(x)            __attribute__ ((__section__(x)))
#define __alloc_size(x)         __attribute__ ((__alloc_size__(x)))

#if __has_attribute(__alloc_align__)
#define __alloc_align(x)        __attribute__ ((__alloc_align__(x)))
#else
#define __alloc_align(x)
#endif /* __has_attribute(__alloc_align__) */

#define __alignof(x)    __offsetof(struct { char __a; x __b; }, __b)

/*
 * C99 Static array indices in function parameter declarations.  Syntax such as:
 * void bar(int myArray[static 10]);
 * is allowed in C99 but not in C++.  Define __min_size appropriately so
 * headers using it can be compiled in either language.  Use like this:
 * void bar(int myArray[__min_size(10)]);
 */
#if !defined(__cplusplus) &&                                                   \
    (defined(__clang__)) &&                                                    \
    (!defined(__STDC_VERSION__) || (__STDC_VERSION__ >= 199901))
#define __min_size(x) static (x)
#else
#define __min_size(x) (x)
#endif

#define __may_alias             __attribute__ ((__may_alias__))

#define __malloc_like           __attribute__ ((__malloc__))
#define __pure                  __attribute__ ((__pure__))

#define __always_inline         __attribute__ ((__always_inline__))

#define __noinline              __attribute__ ((__noinline__))

#define __nonnull(x)            __attribute__ ((__nonnull__(x)))
#define __nonnull_all           __attribute__ ((__nonnull__))

#define __fastcall              __attribute__ ((__fastcall__))
#define __result_use_check      __attribute__ ((__warn_unused_result__))

#define __returns_twice         __attribute__ ((__returns_twice__))

#define __unreachable()         __builtin_unreachable()

#define __func__                NULL

/* GCC 2.95 provides `__restrict' as an extension to C90 to support the
 * C99-specific `restrict' type qualifier.  We happen to use
 * `__restrict' as a way to define the `restrict' type qualifier without
 * disturbing older software that is unaware of C99 keywords.
 */
#if !(__GNUC__ == 2 && __GNUC_MINOR__ == 95)
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901 || defined(lint)
#define __restrict
#else
#define __restrict      restrict
#endif
#endif /* !(__GNUC__ == 2 && __GNUC_MINOR__ == 95) */

/*
 * GNU C version 2.96 adds explicit branch prediction so that
 * the CPU back-end can hint the processor and also so that
 * code blocks can be reordered such that the predicted path
 * sees a more linear flow, thus improving cache behavior, etc.
 *
 * The following two macros provide us with a way to utilize this
 * compiler feature.  Use __predict_true() if you expect the expression
 * to evaluate to true, and __predict_false() if you expect the
 * expression to evaluate to false.
 *
 * A few notes about usage:
 *
 *      * Generally, __predict_false() error condition checks (unless
 *        you have some _strong_ reason to do otherwise, in which case
 *        document it), and/or __predict_true() `no-error' condition
 *        checks, assuming you want to optimize for the no-error case.
 *
 *      * Other than that, if you don't know the likelihood of a test
 *        succeeding from empirical or other `hard' evidence, don't
 *        make predictions.
 *
 *      * These are meant to be used in places that are run `a lot'.
 *        It is wasteful to make predictions in code that is run
 *        seldomly (e.g. at subsystem initialization time) as the
 *        basic block reordering that this affects can often generate
 *        larger code.
 */
#define __predict_true(exp)     __builtin_expect((exp), 1)
#define __predict_false(exp)    __builtin_expect((exp), 0)

#define __visibility(x)         __attribute__ ((visibility((x))))

#define __null_sentinel         __attribute__ ((__sentinel__))
#define __exported              __attribute__ ((__visibility__("default")))
/* Only default visibility is supported on PE/COFF targets. */
#define __hidden                __attribute__ ((__visibility__("hidden")))

#define __offsetof(type, field) offsetof(type, field)
#define __rangeof(type, start, end)                                            \
        (__offsetof(type, end) - __offsetof(type, start))

/*
 * Given the pointer x to the member m of the struct s, return
 * a pointer to the containing structure.  When using GCC, we first
 * assign pointer x to a local variable, to check that its type is
 * compatible with member m.
 */
#define __containerof(x, s, m) ({                                              \
        const volatile __typeof(((s *)0)->m) *__x = (x);                       \
        __DEQUALIFY(s *, (const volatile char *)__x - __offsetof(s, m));       \
})

/*
 * Compiler-dependent macros to declare that functions take printf-like
 * or scanf-like arguments.  They are null except for versions of gcc
 * that are known to support the features properly (old versions of gcc-2
 * didn't permit keeping the keywords out of the application namespace).
 */
#define __printflike(fmtarg, firstvararg)                                      \
            __attribute__ ((__format__ (__printf__, fmtarg, firstvararg)))
#define __format_arg(fmtarg)    __attribute__ ((__format_arg__ (fmtarg)))

#if defined(__GNUC__)
#define __strong_reference(sym, aliassym)                                       \
        extern __typeof (sym) aliassym __attribute__ ((__alias__ (#sym)))

#ifdef __ELF__
#ifdef __STDC__
#define __weak_reference(sym,alias)                                            \
        __asm__ (".weak " #alias);                                             \
        __asm__ (".equ "  #alias ", " #sym)
#define __warn_references(sym,msg)                                             \
        __asm__ (".section .gnu.warning." #sym);                               \
        __asm__ (".asciz \"" msg "\"");                                        \
        __asm__ (".previous")
#define __sym_compat(sym,impl,verid)                                           \
        __asm__ (".symver " #impl ", " #sym "@" #verid)
#define __sym_default(sym,impl,verid)                                          \
        __asm__ (".symver " #impl ", " #sym "@@" #verid)
#else
#define __weak_reference(sym,alias)                                            \
        __asm__ (".weak alias");                                               \
        __asm__ (".equ alias, sym")
#define __warn_references(sym,msg)                                             \
        __asm__ (".section .gnu.warning.sym");                                 \
        __asm__ (".asciz \"msg\"");                                            \
        __asm__ (".previous")
#define __sym_compat(sym,impl,verid)                                           \
        __asm__ (".symver impl, sym@verid")
#define __sym_default(impl,sym,verid)                                          \
        __asm__ (".symver impl, sym@@verid")
#endif /* __STDC__ */
#else /* !__ELF__ */
#ifdef __STDC__
#define __weak_reference(sym,alias)                                            \
        __asm__ (".stabs \"_" #alias "\",11,0,0,0");                           \
        __asm__ (".stabs \"_" #sym "\",1,0,0,0")
#define __warn_references(sym,msg)                                             \
        __asm__ (".stabs \"" msg "\",30,0,0,0");                               \
        __asm__ (".stabs \"_" #sym "\",1,0,0,0")
#else
#define __weak_reference(sym,alias)                                            \
        __asm__ (".stabs \"_/**/alias\",11,0,0,0");                            \
        __asm__ (".stabs \"_/**/sym\",1,0,0,0")
#define __warn_references(sym,msg)                                             \
        __asm__ (".stabs msg,30,0,0,0");                                       \
        __asm__ (".stabs \"_/**/sym\",1,0,0,0")
#endif /* __STDC__ */
#endif /* __ELF__ */
#endif /* __GNUC__ */

#ifndef __DECONST
#define __DECONST(type, var)    ((type)(__uintptr_t)(const void *)(var))
#endif /* !__DECONST */

#ifndef __DEVOLATILE
#define __DEVOLATILE(type, var) ((type)(__uintptr_t)(volatile void *)(var))
#endif /* !__DEVOLATILE */

#ifndef __DEQUALIFY
#define __DEQUALIFY(type, var)                                                 \
        ((type)(__uintptr_t)(const volatile void *)(var))
#endif /* !__DEQUALIFY */

#endif /* !_SYS_CDEFS_H_ */
