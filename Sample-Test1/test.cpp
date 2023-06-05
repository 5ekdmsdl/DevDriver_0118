#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../BestReview/DeviceDriver.h"
#include "../BestReview/FlashMemoryDevice.h"

using namespace testing;

class Mock_FlashDev : public FlashMemoryDevice
{
public:
	unsigned char read(long address) override;
	void write(long address, unsigned char data) override;
};

TEST(CalTest,CalMock)
{
	Mock_FlashDev m_flash;
}