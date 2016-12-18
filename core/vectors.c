/****************************************************************************
 * vectors.c
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include <stdint.h>

#define RESERVED (0)

extern void __start(void);
void sp_main(void);
void nxp_checksum(void);

uint32_t jiffies = 0 - 100;

static __attribute__((noreturn)) void exception_default_handler(void) {
  for (;;);
}

static __attribute__((noreturn)) void extirq_default_handler(void) {
  for (;;);
}

void nmi_handler(void)       __attribute__((weak, alias("exception_default_handler")));
void hardfault_handler(void) __attribute__((weak, alias("exception_default_handler")));
void svcall_handler(void)    __attribute__((weak, alias("exception_default_handler")));
void pendsv_handler(void)    __attribute__((weak, alias("exception_default_handler")));

static void systick_handler(void) {
  jiffies++;
}

void spi0_handler(void)    __attribute__((weak, alias("extirq_default_handler")));
void spi1_handler(void)    __attribute__((weak, alias("extirq_default_handler")));
void uart0_handler(void)   __attribute__((weak, alias("extirq_default_handler")));
void uart1_handler(void)   __attribute__((weak, alias("extirq_default_handler")));
void uart2_handler(void)   __attribute__((weak, alias("extirq_default_handler")));
void i2c0_handler(void)    __attribute__((weak, alias("extirq_default_handler")));
void sct_handler(void)     __attribute__((weak, alias("extirq_default_handler")));
void mrt_handler(void)     __attribute__((weak, alias("extirq_default_handler")));
void cmp_handler(void)     __attribute__((weak, alias("extirq_default_handler")));
void wdt_handler(void)     __attribute__((weak, alias("extirq_default_handler")));
void bod_handler(void)     __attribute__((weak, alias("extirq_default_handler")));
void wkt_handler(void)     __attribute__((weak, alias("extirq_default_handler")));
void pinint0_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint1_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint2_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint3_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint4_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint5_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint6_handler(void) __attribute__((weak, alias("extirq_default_handler")));
void pinint7_handler(void) __attribute__((weak, alias("extirq_default_handler")));

unsigned int vectors[] __attribute__((section(".vectors"))) = {
  /* Core Exception for Cortex-M0, Cortex-M0+ (ARMv6-M) */
  (unsigned int)sp_main,            /*  0: the reset value of the Main stack pointer */
  (unsigned int)__start,            /*  1 */
  (unsigned int)nmi_handler,        /*  2 */
  (unsigned int)hardfault_handler,  /*  3 */
  (unsigned int)RESERVED,           /*  4 */
  (unsigned int)RESERVED,           /*  5 */
  (unsigned int)RESERVED,           /*  6 */
  (unsigned int)nxp_checksum,       /*  7: checksum */
  (unsigned int)RESERVED,           /*  8 */
  (unsigned int)RESERVED,           /*  9 */
  (unsigned int)RESERVED,           /* 10 */
  (unsigned int)svcall_handler,     /* 11 */
  (unsigned int)RESERVED,           /* 12 */
  (unsigned int)RESERVED,           /* 13 */
  (unsigned int)pendsv_handler,     /* 14 */
  (unsigned int)systick_handler,    /* 15 */

  /* External Interrupts */
  (unsigned int)spi0_handler,       /* 16 ( 0) */
  (unsigned int)spi1_handler,       /* 17 ( 1) */
  (unsigned int)RESERVED,           /* 18 ( 2) */
  (unsigned int)uart0_handler,      /* 19 ( 3) */
  (unsigned int)uart1_handler,      /* 20 ( 4) */
  (unsigned int)uart2_handler,      /* 21 ( 5) */
  (unsigned int)RESERVED,           /* 22 ( 6) */
  (unsigned int)RESERVED,           /* 23 ( 7) */
  (unsigned int)i2c0_handler,       /* 24 ( 8) */
  (unsigned int)sct_handler,        /* 25 ( 9): State configurable timer interrupt */
  (unsigned int)mrt_handler,        /* 26 (10): Multi-rate timer interrupt */
  (unsigned int)cmp_handler,        /* 27 (11): Analog comparator interrupt */
  (unsigned int)wdt_handler,        /* 28 (12): Windowed watchdog timer interrupt */
  (unsigned int)bod_handler,        /* 29 (13): BOD(BrownOut Detection) interrupts */
  (unsigned int)RESERVED,           /* 30 (14) */
  (unsigned int)wkt_handler,        /* 31 (15): Self wake-up timer interrupt */
  (unsigned int)RESERVED,           /* 32 (16) */
  (unsigned int)RESERVED,           /* 33 (17) */
  (unsigned int)RESERVED,           /* 34 (18) */
  (unsigned int)RESERVED,           /* 35 (19) */
  (unsigned int)RESERVED,           /* 36 (20) */
  (unsigned int)RESERVED,           /* 37 (21) */
  (unsigned int)RESERVED,           /* 38 (22) */
  (unsigned int)RESERVED,           /* 39 (23) */
  (unsigned int)pinint0_handler,    /* 40 (24) */
  (unsigned int)pinint1_handler,    /* 41 (25) */
  (unsigned int)pinint2_handler,    /* 42 (26) */
  (unsigned int)pinint3_handler,    /* 43 (27) */
  (unsigned int)pinint4_handler,    /* 44 (28) */
  (unsigned int)pinint5_handler,    /* 45 (29) */
  (unsigned int)pinint6_handler,    /* 46 (30) */
  (unsigned int)pinint7_handler,    /* 47 (31) */
};

