/****************************************************************************
 * utility.h
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

#define getreg8(a)  (*(volatile uint8_t  *)(a))
#define getreg16(a) (*(volatile uint16_t *)(a))
#define getreg32(a) (*(volatile uint32_t *)(a))

#define putreg8(v,a)  (*(volatile uint8_t  *)(a) = (v))
#define putreg16(v,a) (*(volatile uint16_t *)(a) = (v))
#define putreg32(v,a) (*(volatile uint32_t *)(a) = (v))

#endif  /* UTILITY_H_ */

