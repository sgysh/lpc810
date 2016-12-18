/****************************************************************************
 * lpc810.h
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef LPC810_H_
#define LPC810_H_

#define SWM_BASE                    (0x4000c000)        /* SWM: SWitch Matrix */
#define SWM_PINASSIGN0              (SWM_BASE + 0x000)  /* Pin assign register 0 */
#define SWM_PINASSIGN0_U0_TXD_SHIFT (0)                 /* U0_TXD function assignment */

#define SYSCON_BASE                  0x40048000             /* System configuration */
#define SYSCON_SYSPLLCTRL            (SYSCON_BASE + 0x008)  /* System PLL control */
#define SYSCON_SYSPLLCTRL_MSEL_SHIFT (0)
#define SYSCON_SYSPLLCTRL_PSEL_SHIFT (5)
#define SYSCON_SYSPLLSTAT            (SYSCON_BASE + 0x00c)  /* System PLL status */
#define SYSCON_SYSPLLSTAT_LOCKED     (1 << 0)               /* PLL lock status: PLL locked */
#define SYSCON_SYSPLLCLKSEL          (SYSCON_BASE + 0x040)  /* System PLL clock source select */
#define SYSCON_SYSPLLCLKSEL_IRC      (0)                    /* System PLL clock source: IRC (12 MHz internal oscillator) */
#define SYSCON_SYSPLLCLKUEN          (SYSCON_BASE + 0x044)  /* System PLL clock source update enable */
#define SYSCON_SYSPLLCLKUEN_ENA      (1)                    /* Enable system PLL clock source update: Update clock source */
#define SYSCON_MAINCLKSEL            (SYSCON_BASE + 0x070)  /* Main clock source select */
#define SYSCON_MAINCLKSEL_PLLOUT     (3)                    /* Clock source for main clock: PLL output */
#define SYSCON_MAINCLKUEN            (SYSCON_BASE + 0x074)  /* Main clock source update enable */
#define SYSCON_MAINCLKUEN_ENA        (1)                    /* Enable main clock source update: Update clock source */
#define SYSCON_SYSAHBCLKDIV          (SYSCON_BASE + 0x078)  /* System clock divider */
#define SYSCON_SYSAHBCLKCTRL         (SYSCON_BASE + 0x080)  /* System clock control */
#define SYSCON_SYSAHBCLKCTRL_UART0   (1 << 14)              /* Enables clock for USART0 */
#define SYSCON_UARTCLKDIV            (SYSCON_BASE + 0x094)  /* USART clock divider */
#define SYSCON_PDRUNCFG              (SYSCON_BASE + 0x238)  /* Power configuration register */
#define SYSCON_PDRUNCFG_SYSPLL_PD    (1 << 7)               /* System PLL power down */

#define USART_BASE   (0x40064000)
#define USART_0_BASE (USART_BASE + 0x0000)

#endif  /* LPC810_H_ */

