#pragma once
#include <psppower.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <cstring>
#include <malloc.h>
#include "kcall.h"

#define u8  unsigned char
#define u16 unsigned short int
#define u32 unsigned int

#define nrp          u32*
#define nrg(addr)    (*((nrp)(addr)))
#define vrp          volatile u32*
#define vrg(addr)    (*((vrp)(addr)))

#define me_section_size (&__stop__me_section - &__start__me_section)
#define _meLoop      vrg((0xbfc00040 + me_section_size))

static inline void meDCacheWritebackInvalidAll() {
 asm("sync");
 for (int i = 0; i < 8192; i += 64) {
  asm("cache 0x14, 0(%0)" :: "r"(i));
  asm("cache 0x14, 0(%0)" :: "r"(i));
 }
 asm("sync");
}

static volatile bool _meExit = false;
static inline void meExit() {
  _meExit = true;
  meDCacheWritebackInvalidAll();
}