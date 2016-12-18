/****************************************************************************
 * romapi.h
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef ROMAPI_H_
#define ROMAPI_H_

#include <stdint.h>

typedef void *PWRD_API_T;  /* TODO */
typedef void *I2CD_API_T;  /* TODO */

typedef struct _ROM_API {
  const uint32_t unused[3];
  const PWRD_API_T *pPWRD;
  const uint32_t p_dev1;
  const I2CD_API_T *pI2CD;
  const uint32_t p_dev3;
  const uint32_t p_dev4;
  const uint32_t p_dev5;
  const UARTD_API_T *pUARTD;
} ROM_API_T;
#define ROM_DRIVER_BASE (0x1FFF1FF8UL)

#endif  /* ROMAPI_H_ */

