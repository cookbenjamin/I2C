#ifndef IMU_I2C_BUS_H
#define IMU_I2C_BUS_H

#include "stdint.h"

class I2cBus {
public:
    I2cBus();
    I2cBus(int i2c_num);
    int open_bus(int i2c_num);
    void select_device(uint16_t address);
    int get_file();
private:
    int file;
};

#endif //IMU_I2C_BUS_H
