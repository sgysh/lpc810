/****************************************************************************
 *  armv6m.h
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef ARMV6M_H_
#define ARMV6M_H_

#define ARMV6M_SCS_BASE               0xe000e000                 /* System Control Space, address range 0xE000E000 to 0xE000EFFF */
#define ARMV6M_SCS_SYST_CSR           (ARMV6M_SCS_BASE + 0x010)  /* SysTick Control and Status Register */
#define ARMV6M_SCS_SYST_CSR_ENABLE    (1 << 0)                   /* counter is operating */
#define ARMV6M_SCS_SYST_CSR_TICKINT   (1 << 1)                   /* count to 0 changes the SysTick exception status to pending */
#define ARMV6M_SCS_SYST_CSR_CLKSOURCE (1 << 2)                   /* SysTick uses the processor clock */
#define ARMV6M_SCS_SYST_RVR           (ARMV6M_SCS_BASE + 0x014)  /* SysTick Reload Value Register */
#define ARMV6M_SCS_SYST_CALIB         (ARMV6M_SCS_BASE + 0x01c)  /* SysTick Calibration Value Register */

#endif  /* ARMV6M_H_ */

