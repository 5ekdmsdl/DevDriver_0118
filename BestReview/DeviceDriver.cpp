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
	writeOnDevice(address, data);
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

	return initialRes;
}

void DeviceDriver::writeOnDevice(long address, int data)
{
	int readRes = m_hardware->read(address);
	if (readRes != 0xFF) throw std::exception("WriteFailException");

	m_hardware->write(address, (unsigned char)data);
}
