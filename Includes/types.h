/**
 * @file types.h
 * @brief Various system types.
 */
#pragma once
#ifndef TYPES_H
#define TYPES_H

#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#define __asm__  __asm
#define __volatile__
#define _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE 1
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
/// The maximum value of a u64.
#define U64_MAX	UINT64_MAX

/// would be nice if newlib had this already
#ifndef SSIZE_MAX
#ifdef SIZE_MAX
#define SSIZE_MAX ((SIZE_MAX) >> 1)
#endif
#endif

typedef uint8_t u8;   ///<  8-bit unsigned integer
typedef uint16_t u16; ///< 16-bit unsigned integer
typedef uint32_t u32; ///< 32-bit unsigned integer
typedef uint64_t u64; ///< 64-bit unsigned integer

typedef int8_t s8;   ///<  8-bit signed integer
typedef int16_t s16; ///< 16-bit signed integer
typedef int32_t s32; ///< 32-bit signed integer
typedef int64_t s64; ///< 64-bit signed integer

typedef volatile u8 vu8;   ///<  8-bit volatile unsigned integer.
typedef volatile u16 vu16; ///< 16-bit volatile unsigned integer.
typedef volatile u32 vu32; ///< 32-bit volatile unsigned integer.
typedef volatile u64 vu64; ///< 64-bit volatile unsigned integer.

typedef volatile s8 vs8;   ///<  8-bit volatile signed integer.
typedef volatile s16 vs16; ///< 16-bit volatile signed integer.
typedef volatile s32 vs32; ///< 32-bit volatile signed integer.
typedef volatile s64 vs64; ///< 64-bit volatile signed integer.

typedef u32 Handle;                 ///< Resource handle.
typedef s32 Result;                 ///< Function result.
typedef void (*ThreadFunc)(void *); ///< Thread entrypoint function.
typedef void (*voidfn)(void);

/// Creates a bitmask from a bit number.
#define BIT(n) (1U<<(n))

#if defined(_MSC_VER)
#define ALIGN(m)
#define PACKED
#else
/// Aligns a struct (and other types?) to m, making sure that the size of the struct is a multiple of m.
#define ALIGN(m)   __attribute__((aligned(m)))
/// Packs a struct (and other types?) so it won't include padding bytes.
#define PACKED     __attribute__((packed))
#endif
#ifndef LIBCTRU_NO_DEPRECATION
/// Flags a function as deprecated.
#define DEPRECATED __attribute__ ((deprecated))
#else
/// Flags a function as deprecated.
#define DEPRECATED
#endif

/// Structure representing CPU registers
typedef struct {
	u32 r[13]; ///< r0-r12.
	u32 sp;    ///< sp.
	u32 lr;    ///< lr.
	u32 pc;    ///< pc. May need to be adjusted.
	u32 cpsr;  ///< cpsr.
} CpuRegisters;

/// Structure representing FPU registers
typedef struct {
	union{
		double d[16]; ///< d0-d15.
		float  f[32]; ///< f0-f31.
	};
	u32 fpscr;        ///< fpscr.
	u32 fpexc;        ///< fpexc.
} FpuRegisters;

#endif