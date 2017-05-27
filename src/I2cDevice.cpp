#include "I2cDevice.h"

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>

#include "I2cBus.h"


I2cDevice::I2cDevice(I2cBus &bus, int address) {
    this->address = address;
    this->bus = &bus;
    this->file = this->bus->get_file();
    enable();
}

void I2cDevice::write_register(int reg, int value) {
    this->bus->select_device((uint16_t) address);
    int result = i2c_smbus_write_byte_data(file, reg, value);
    if (result == -1) {
        printf("Failed to write byte to I2C.");
    }
}

uint8_t I2cDevice::read_register(int reg) {

    this->bus->select_device((uint16_t) address);
    return i2c_smbus_read_byte_data(file, reg);
}

void I2cDevice::write_registers(std::vector<int> registers, std::vector<int> values) {
    for (int i = 0; i < registers.size(); i++) {
        write_register(registers.at(i), values.at(i));
    }
}

std::vector<uint8_t> I2cDevice::read_data(int begin_register, int num_registers) {
    std::vector<uint8_t> a;
    uint8_t block[num_registers];
    this->bus->select_device((uint16_t) address);
    read_block(0x80 | begin_register, sizeof(block), block);

    for (int i = 0; i < num_registers; i++) {
        a.push_back(block[i]);
    }

    return a;
}

void I2cDevice::read_block(int command, int size, uint8_t *data) {
    int result = i2c_smbus_read_i2c_block_data(file, command, size, data);

    if (result != size) {
        printf("Failed to read block from I2C.");
    }
}

void I2cDevice::enable() {

}