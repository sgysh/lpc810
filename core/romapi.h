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

/* I2C */
// I2C ROM driver variables
typedef void* I2C_HANDLE_T;
typedef void (*I2C_CALLBK_T) (uint32_t err_code, uint32_t n);
// PARAM and RESULT structure
typedef struct i2c_A { // parameters passed to ROM function
  uint32_t num_bytes_send;
  uint32_t num_bytes_rec;
  uint8_t *buffer_ptr_send;
  uint8_t *buffer_ptr_rec;
  I2C_CALLBK_T func_pt; // callback function pointer
  uint8_t stop_flag;
  uint8_t dummy[3]; // required for word alignment
} I2C_PARAM;
typedef struct i2c_R { // RESULTs struct--results are here when returned
  uint32_t n_bytes_sent;
  uint32_t n_bytes_recd;
} I2C_RESULT;
// Error structure
typedef enum {
  LPC_OK = 0, /**< enum value returned on Success */
  ERROR,
  ERR_I2C_BASE = 0x00060000,
  /*0x00060001*/ ERR_I2C_NAK = ERR_I2C_BASE + 1,
  /*0x00060002*/ ERR_I2C_BUFFER_OVERFLOW,
  /*0x00060003*/ ERR_I2C_BYTE_COUNT_ERR,
  /*0x00060004*/ ERR_I2C_LOSS_OF_ARBRITRATION,
  /*0x00060005*/ ERR_I2C_SLAVE_NOT_ADDRESSED,
  /*0x00060006*/ ERR_I2C_LOSS_OF_ARBRITRATION_NAK_BIT,
  /*0x00060007*/ ERR_I2C_GENERAL_FAILURE,
  /*0x00060008*/ ERR_I2C_REGS_SET_TO_DEFAULT
} ErrorCode_t;
// I2C Mode
typedef enum I2C_mode {
  IDLE,
  MASTER_SEND,
  MASTER_RECEIVE,
  SLAVE_SEND,
  SLAVE_RECEIVE
} I2C_MODE_T;

typedef struct I2CD_API { // index of all the i2c driver functions
  void (*i2c_isr_handler)(I2C_HANDLE_T* h_i2c); // ISR interrupt service request
  // MASTER functions ***
  ErrorCode_t (*i2c_master_transmit_poll)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_master_receive_poll)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_master_tx_rx_poll)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_master_transmit_intr)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_master_receive_intr)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_master_tx_rx_intr)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  // SLAVE functions ***
  ErrorCode_t (*i2c_slave_receive_poll)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_slave_transmit_poll)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_slave_receive_intr)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_slave_transmit_intr)(I2C_HANDLE_T* h_i2c, I2C_PARAM* ptp, I2C_RESULT* ptr);
  ErrorCode_t (*i2c_set_slave_addr)(I2C_HANDLE_T* h_i2c, uint32_t slave_addr_0_3, uint32_t slave_mask_0_3);
  // OTHER functions
  uint32_t (*i2c_get_mem_size)(void); // ramsize_in_bytes memory needed by I2C drivers
  I2C_HANDLE_T* (*i2c_setup)(uint32_t i2c_base_addr, uint32_t *start_of_ram);
  ErrorCode_t (*i2c_set_bitrate)(I2C_HANDLE_T* h_i2c, uint32_t P_clk_in_hz, uint32_t bitrate_in_bps);
  uint32_t (*i2c_get_firmware_version)();
  I2C_MODE_T (*i2c_get_status)(I2C_HANDLE_T* h_i2c);
  ErrorCode_t (*i2c_set_timeout)(I2C_HANDLE_T *handle, uint32_t timeout);
} I2CD_API_T;

/* UART */
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
#define LPC_I2CD_API ((I2CD_API_T *) ((*(ROM_API_T * *) (ROM_DRIVER_BASE))->pI2CD))
#define LPC_UART_API ((UARTD_API_T *) ((*(ROM_API_T * *) (ROM_DRIVER_BASE))->pUARTD))

#define i2c_isr_handler          LPC_I2CD_API->i2c_isr_handler
#define i2c_master_transmit_poll LPC_I2CD_API->i2c_master_transmit_poll
#define i2c_master_receive_poll  LPC_I2CD_API->i2c_master_receive_poll
#define i2c_master_tx_rx_poll    LPC_I2CD_API->i2c_master_tx_rx_poll
#define i2c_master_transmit_intr LPC_I2CD_API->i2c_master_transmit_intr
#define i2c_master_receive_intr  LPC_I2CD_API->i2c_master_receive_intr
#define i2c_master_tx_rx_intr    LPC_I2CD_API->i2c_master_tx_rx_intr
#define i2c_slave_receive_poll   LPC_I2CD_API->i2c_slave_receive_poll
#define i2c_slave_transmit_poll  LPC_I2CD_API->i2c_slave_transmit_poll
#define i2c_slave_receive_intr   LPC_I2CD_API->i2c_slave_receive_intr
#define i2c_slave_transmit_intr  LPC_I2CD_API->i2c_slave_transmit_intr
#define i2c_set_slave_addr       LPC_I2CD_API->i2c_set_slave_addr
#define i2c_get_mem_size         LPC_I2CD_API->i2c_get_mem_size
#define i2c_setup                LPC_I2CD_API->i2c_setup
#define i2c_set_bitrate          LPC_I2CD_API->i2c_set_bitrate
#define i2c_get_firmware_version LPC_I2CD_API->i2c_get_firmware_version
#define i2c_get_status           LPC_I2CD_API->i2c_get_status
#define i2c_set_timeout          LPC_I2CD_API->i2c_set_timeout

#define uart_get_mem_size LPC_UART_API->uart_get_mem_size
#define uart_setup        LPC_UART_API->uart_setup
#define uart_init         LPC_UART_API->uart_init
#define uart_get_char     LPC_UART_API->uart_get_char
#define uart_put_char     LPC_UART_API->uart_put_char
#define uart_get_line     LPC_UART_API->uart_get_line
#define uart_put_line     LPC_UART_API->uart_put_line
#define uart_isr          LPC_UART_API->uart_isr

#define I2C_WORK_SIZE (96)      /* TODO: use i2c_get_mem_size() */
#define SYS_CLK (24*1000*1000)  /* TODO */

#define UART_INSTANCE_SIZE (40)  /* TODO: use uart_get_mem_size() */
#define UART_CLK (24*1000*1000)  /* TODO */

#endif  /* ROMAPI_H_ */

