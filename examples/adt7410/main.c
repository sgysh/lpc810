/****************************************************************************
 * main.c
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include "lpc810.h"
#include "romapi.h"

int main() {
  uint8_t i2c_work[I2C_WORK_SIZE];
  uint8_t buf[3];
  volatile uint16_t temp;
  I2C_PARAM param;
  I2C_RESULT result;
  I2C_HANDLE_T *i2c_handle;

  buf[0] = 0x48;

  i2c_handle = i2c_setup(I2C_BASE, i2c_work);
  i2c_set_bitrate(i2c_handle, SYS_CLK, 50000);
  while (1) {
    i2c_set_timeout(i2c_handle, 1000000);

    param.num_bytes_rec  = 3;
    param.buffer_ptr_rec = buf;
    param.stop_flag      = 1;
    result.n_bytes_recd  = 0;

    i2c_master_receive_poll(i2c_handle, &param, &result);
    temp = (buf[1] << 8 | buf[2]) >> 3;
  }

  return 0;
}

