/****************************************************************************
 * start.c
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include <stdint.h>

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _data_lma_start;

extern void mcu_init(void);
extern int main(void);

static void init_data(void) {
  const uint32_t *src;
  uint32_t *dst;

  for (src = &_data_lma_start, dst = &_sdata; dst < &_edata; ) {
    *dst++ = *src++;
  }
}

static void init_bss(void) {
  uint32_t *dst;

  for (dst = &_sbss; dst < &_ebss; ) {
    *dst++ = 0;
  }
}

void __start(void) {
  init_data();

  init_bss();

  mcu_init();

  (void)main();

  for (;;);
}

