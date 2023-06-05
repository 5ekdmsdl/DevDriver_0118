#include "DeviceDriver.h"
#include "Windows.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    return readFromDevice(address);
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}

int DeviceDriver::readFromDevice(long address)
{
	int initialRes = (int)(m_hardware->read(address));

	for (int i = 2; i <=  READ_TRYCNT; i++)
	{
		Sleep(200);
		int newRes = (int)(m_hardware->read(address));
		if (newRes == initialRes) continue;

		throw std::exception("");
	}
}
