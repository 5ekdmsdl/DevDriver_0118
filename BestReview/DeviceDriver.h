#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    int readFromDevice(long address);
    void writeOnDevice(long address, int data);

    const int READ_TRYCNT = 5;
};