/****************************************************************************
 * lpc810_init.c
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include <stdint.h>

#include "config.h"

#include "armv6m.h"
#include "lpc810.h"
#include "utility.h"

#ifndef CONFIG_SYST_RELOAD_VALUE
#define CONFIG_SYST_RELOAD_VALUE ((24*1000*1000)/100)
#endif

static void pll_init() {
  uint32_t val;

  /* Power up the system PLL */
  val = getreg32(SYSCON_PDRUNCFG);
  val &= ~(SYSCON_PDRUNCFG_SYSPLL_PD);
  putreg32(val, SYSCON_PDRUNCFG);

  /* Select the PLL input */
  val = SYSCON_SYSPLLCLKSEL_IRC;
  putreg32(val & 0x3, SYSCON_SYSPLLCLKSEL);

  /* Update the PLL clock source */
  val = SYSCON_SYSPLLCLKUEN_ENA;
  putreg32(val & 0x1, SYSCON_SYSPLLCLKUEN);

  /* Configure the PLL M and N dividers */
  val = 1 << SYSCON_SYSPLLCTRL_PSEL_SHIFT | 1 << SYSCON_SYSPLLCTRL_MSEL_SHIFT;
  putreg32(val & 0x7f, SYSCON_SYSPLLCTRL);

  /* Wait for the PLL to lock */
  while(!(getreg32(SYSCON_SYSPLLSTAT) & SYSCON_SYSPLLSTAT_LOCKED));
}

static void main_clk_init() {
  uint32_t val;

  /* Select the main clock */
  val = SYSCON_MAINCLKSEL_PLLOUT;
  putreg32(val & 0x3, SYSCON_MAINCLKSEL);

  /* Update the main clock source */
  val = SYSCON_MAINCLKUEN_ENA;
  putreg32(val & 0x1, SYSCON_MAINCLKUEN);
}

static void sys_clk_init() {
  uint32_t val;

  /* Select the divider value for the system clock */
  val = 0x1;
  putreg32(val & 0xff, SYSCON_SYSAHBCLKDIV);

  /* Configures the clock for the fractional baud rate generator and all USARTs */
#if defined(CONFIG_ENABLE_CLOCK_UART0) || defined(CONFIG_ENABLE_CLOCK_UART1)
  val = 0x1;
  putreg32(val & 0xff, SYSCON_UARTCLKDIV);
#endif

  /*
     Select the memories and peripherals that are operating in your application and
     therefore must have an active clock. The core is always clocked.
   */
#ifdef CONFIG_ENABLE_CLOCK_UART0
  val = getreg32(SYSCON_SYSAHBCLKCTRL);
  val |= SYSCON_SYSAHBCLKCTRL_UART0;
  putreg32(val, SYSCON_SYSAHBCLKCTRL);
#endif
#ifdef CONFIG_ENABLE_CLOCK_I2C
  val = getreg32(SYSCON_SYSAHBCLKCTRL);
  val |= SYSCON_SYSAHBCLKCTRL_I2C;
  putreg32(val, SYSCON_SYSAHBCLKCTRL);
#endif
}

static void clk_init() {
  pll_init();

  main_clk_init();

  sys_clk_init();
}

static void reset_ctrl() {
  uint32_t val;

#ifdef CONFIG_ENABLE_CLOCK_UART0
  val = getreg32(SYSCON_PRESETCTRL);
  val |= 1 << SYSCON_PRESETCTRL_UART0_SHIFT;
  putreg32(val, SYSCON_PRESETCTRL);
#endif
#ifdef CONFIG_ENABLE_CLOCK_I2C
  val = getreg32(SYSCON_PRESETCTRL);
  val |= 1 << SYSCON_PRESETCTRL_I2C_SHIFT;
  putreg32(val, SYSCON_PRESETCTRL);
#endif
}

static void irq_init() {
  /* SysTick */
  putreg32(CONFIG_SYST_RELOAD_VALUE, ARMV6M_SCS_SYST_RVR);
  putreg32(ARMV6M_SCS_SYST_CSR_ENABLE   |
           ARMV6M_SCS_SYST_CSR_TICKINT  |
           ARMV6M_SCS_SYST_CSR_CLKSOURCE,
           ARMV6M_SCS_SYST_CSR);
}

enum function_t {
  FUNCTION_U0_TXD,
  FUNCTION_I2C0_SDA,
  FUNCTION_I2C0_SCL
};

static void set_mux(const enum function_t ftype, const uint32_t pio_num) {
  uint32_t val, shift;
  uint32_t *pin;

  switch (ftype) {
    case FUNCTION_U0_TXD:
      pin   = (uint32_t *)SWM_PINASSIGN0;
      shift = SWM_PINASSIGN0_U0_TXD_SHIFT;
      break;
    case FUNCTION_I2C0_SDA:
      pin   = (uint32_t *)SWM_PINASSIGN7;
      shift = SWM_PINASSIGN0_I2C0_SDA_SHIFT;
      break;
    case FUNCTION_I2C0_SCL:
      pin   = (uint32_t *)SWM_PINASSIGN8;
      shift = SWM_PINASSIGN0_I2C0_SCL_SHIFT;
      break;
    default:
      return;
  }

  val = getreg32(pin);
  val &= ~(0xff << shift);
  val |= (pio_num & 0xff) << shift;
  putreg32(val, pin);
}

/*
         _____          _______
         RESET/PIO0_5 1|  `-'  |8 PIO0_0/ACMP_I1/TDO
                 ____  |       |
   PIO0_4/WAKEUP/TRST 2|       |7 VSS
                       |       |
     SWCLK/PIO0_3/TCK 3|       |6 VDD
                       |       |
     SWDIO/PIO0_2/TMS 4|_______|5 PIO0_1/ACMP_I2/CLKIN/TDI

   8:
   7: VSS
   6: VDD
   5:
   4: SWDIO
   3: SWCLK
   2: _____
   1: RESET
 */
static void mux_init() {
#ifdef CONFIG_SWM_U0_TXD_PIO
  set_mux(FUNCTION_U0_TXD, CONFIG_SWM_U0_TXD_PIO);
#endif
#ifdef CONFIG_SWM_I2C0_SDA_PIO
  set_mux(FUNCTION_I2C0_SDA, CONFIG_SWM_I2C0_SDA_PIO);
#endif
#ifdef CONFIG_SWM_I2C0_SCL_PIO
  set_mux(FUNCTION_I2C0_SCL, CONFIG_SWM_I2C0_SCL_PIO);
#endif
}

void mcu_init() {
  clk_init();

  reset_ctrl();

  irq_init();

  mux_init();
}

