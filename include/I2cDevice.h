#ifndef IMU_I2C_SENSOR_H
#define IMU_I2C_SENSOR_H

#include <stdint.h>
#include <vector>

#include "I2cBus.h"

class I2cDevice {
    I2cBus *bus;
    int address;
    int file;
public:
    I2cDevice(I2cBus &bus, int address);
    void enable();
    void select_this_device();
    std::vector<uint8_t> read_data(int begin_register, int num_registers);
    void write_register(int reg, int value);
    uint8_t read_register(int reg);
    void write_registers(std::vector<int> registers, std::vector<int> values);
    void read_block(int command, int size, uint8_t *data);
    bool is_enabled;
};

#endif //IMU_I2C_SENSOR_H