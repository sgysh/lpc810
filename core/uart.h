/****************************************************************************
 * uart.h
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef UART_H_
#define UART_H_

#include <stdint.h>

#include "config.h"

typedef struct UART_CONFIG {
  uint32_t sys_clk_in_hz;  // Sytem clock in hz.
  uint32_t baudrate_in_hz; // Baudrate in hz
  uint8_t config; //bit 1:0
                  // 00: 7 bits length, 01: 8 bits lenght, others: reserved
                  //bit3:2
                  // 00: No Parity, 01: reserved, 10: Even, 11: Odd
                  //bit4
                  // 0: 1 Stop bit, 1: 2 Stop bits
  uint8_t sync_mod; //bit0: 0(Async mode), 1(Sync mode)
                    //bit1: 0(Un_RXD is sampled on the falling edge of SCLK)
                    // 1(Un_RXD is sampled on the rising edge of SCLK)
                    //bit2: 0(Start and stop bits are transmitted as in asynchronous mode)
                    // 1(Start and stop bits are not transmitted)
                    //bit3: 0(the UART is a slave on Sync mode)
                    // 1(the UART is a master on Sync mode)
  uint16_t error_en; //Bit0: OverrunEn, bit1: UnderrunEn, bit2: FrameErrEn,
                     // bit3: ParityErrEn, bit4: RxNoiseEn
} UART_CONFIG_T;

typedef void (*UART_CALLBK_T)(uint32_t err_code, uint32_t n);

typedef struct uart_A { // parms passed to uart driver function
  uint8_t *buffer; // The pointer of buffer.
                       // For uart_get_line function, buffer for receiving data.
                       // For uart_put_line function, buffer for transmitting data.
  uint32_t size; // [IN] The size of buffer.
                 //[OUT] The number of bytes transmitted/received.
  uint16_t transfer_mode;
                 // 0x00: For uart_get_line function, transfer without
                 // termination.
                 // For uart_put_line function, transfer without termination.
                 // 0x01: For uart_get_line function, stop transfer when
                 // <CR><LF> are received.
                 // For uart_put_line function, transfer is stopped after
                 // reaching \0. <CR><LF> characters are sent out after that.
                 // 0x02: For uart_get_line function, stop transfer when <LF>
                 // is received.
                 // For uart_put_line function, transfer is stopped after
                 // reaching \0. A <LF> character is sent out after that.
                 // 0x03: For uart_get_line function, RESERVED.
                 // For uart_put_line function, transfer is stopped after
                 // reaching \0.
  uint16_t driver_mode;
                 // 0x00: Polling mode, function is blocked until transfer is
                 // finished.
                 // 0x01: Intr mode, function exit immediately, callback function
                 // is invoked when transfer is finished.
                 // 0x02: RESERVED
  UART_CALLBK_T callback_func_pt; // callback function
} UART_PARAM_T;

typedef void *UART_HANDLE_T; // define TYPE for uart handle pointer

typedef struct UARTD_API { // index of all the uart driver functions
  uint32_t (*uart_get_mem_size)(void);
  UART_HANDLE_T (*uart_setup)(uint32_t base_addr, uint8_t *ram);
  uint32_t (*uart_init)(UART_HANDLE_T handle, UART_CONFIG_T *set);
  //--polling functions--//
  uint8_t (*uart_get_char)(UART_HANDLE_T handle);
  void (*uart_put_char)(UART_HANDLE_T handle, uint8_t data);
  uint32_t (*uart_get_line)(UART_HANDLE_T handle, UART_PARAM_T *param);
  uint32_t (*uart_put_line)(UART_HANDLE_T handle, UART_PARAM_T *param);
  //--interrupt functions--//
  void (*uart_isr)(UART_HANDLE_T handle);
} UARTD_API_T; // end of structure

#include "romapi.h"

#define LPC_UART_API ((UARTD_API_T *) ((*(ROM_API_T * *) (ROM_DRIVER_BASE))->pUARTD))

#define uart_get_mem_size LPC_UART_API->uart_get_mem_size
#define uart_setup        LPC_UART_API->uart_setup
#define uart_init         LPC_UART_API->uart_init
#define uart_get_char     LPC_UART_API->uart_get_char
#define uart_put_char     LPC_UART_API->uart_put_char
#define uart_get_line     LPC_UART_API->uart_get_line
#define uart_put_line     LPC_UART_API->uart_put_line
#define uart_isr          LPC_UART_API->uart_isr

#define UART_CLK (24*1000*1000)  /* TODO */

#define UART_INSTANCE_SIZE (40)  /* TODO: use uart_get_mem_size() */

#endif  /* UART_H_ */

