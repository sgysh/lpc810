/****************************************************************************
 * main.c
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include "lpc810.h"
#include "romapi.h"

int main() {
  uint8_t uart_work[UART_INSTANCE_SIZE];
  int i;

  UART_HANDLE_T huart;
  UART_CONFIG_T cfg;

  huart = uart_setup(USART_0_BASE, uart_work);

  cfg.sys_clk_in_hz  = UART_CLK;
  cfg.baudrate_in_hz = 115200;
  cfg.config         = 0x01;
  cfg.sync_mod       = 0x0;
  cfg.error_en       = 0x0;

  uart_init(huart, &cfg);

  while (1) {
    for (i = 'A'; i <= 'F'; i++)
      uart_put_char(huart, i);
    uart_put_char(huart, '\r');
    uart_put_char(huart, '\n');
  }

  return 0;
}

