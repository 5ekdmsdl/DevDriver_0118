#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../BestReview/DeviceDriver.cpp"
#include "../BestReview/FlashMemoryDevice.h"

using namespace testing;

class MockFlashDev : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(Read_Drive_Test,Read_Drive_Read_5times)
{
	MockFlashDev fdev_mock;
	EXPECT_CALL(fdev_mock, read(_))
		.Times(5)
		.WillRepeatedly(Return(0x01));

	DeviceDriver devdriv( &fdev_mock );
	devdriv.read(0x00);
}

TEST(Read_Drive_Test,Read_Drive_FAIL_1Address)
{
	MockFlashDev fdev_mock;
	EXPECT_CALL(fdev_mock, read(_))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x02));

	DeviceDriver devdriv( &fdev_mock );
	EXPECT_THROW(devdriv.read(0x00), std::exception);
}

TEST(Read_Drive_Test,Read_Drive_SUCCESS_1Address)
{
	MockFlashDev fdev_mock;
	EXPECT_CALL(fdev_mock, read(_))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01))
		.WillOnce(Return(0x01));

	DeviceDriver devdriv( &fdev_mock );
	EXPECT_EQ(devdriv.read(0x00), 0x01);
}