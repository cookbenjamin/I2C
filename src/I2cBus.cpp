#include "I2cBus.h"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>


I2cBus::I2cBus() {
    this->file = open_bus(1);
}

I2cBus::I2cBus(int i2c_num) {
    this->file = open_bus(i2c_num);
}

int I2cBus::open_bus(int i2c_num) {
    char filename[20];
    sprintf(filename, "/dev/i2c-%d", i2c_num);
    file = open(filename, O_RDWR);
    if (file < 0) {
        printf("Unable to open I2C bus!");
    } else {
        return file;
    }
}

void I2cBus::select_device(uint16_t address) {
    if (ioctl(this->file, I2C_SLAVE, address) < 0) {
        printf("Failed to select I2C device at address: %x\n", address);
    }
}

int I2cBus::get_file() {
    return file;
}