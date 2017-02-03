#include "stdafx.h"
#include <memory>
#include <gtest\gtest.h>
#include "..\hexdump_lib\hexdump.h"

TEST(formatBytes, when_zero_bytes_then_displays_nothing)
{
	EXPECT_EQ("", formatBytes(nullptr, 0));
}

TEST(formatBytes, when_single_byte_then_displays_single_byte_spaced_correctly)
{
	std::vector<BYTE> bytes{ 0 };

	EXPECT_EQ("00                                                   .", formatBytes(&bytes[0], long(bytes.size())));
}

TEST(formatBytes, displays_values_in_hex)
{
	std::vector<BYTE> bytes{ 10, 255 };

	EXPECT_EQ("0A FF                                                ..", formatBytes(&bytes[0], long(bytes.size())));
}

TEST(formatBytes, when_16_bytes_then_spaced_correctly)
{
	std::vector<BYTE> bytes{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	EXPECT_EQ("00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00    ................", formatBytes(&bytes[0], long(bytes.size())));
}

TEST(formatBytes, when_character_data_then_displays_printable)
{
	std::vector<BYTE> bytes{ 'T', 'e', 's', 't' };

	EXPECT_EQ("54 65 73 74                                          Test", formatBytes(&bytes[0], long(bytes.size())));
}

TEST(formatLine, displays_offset_in_hex)
{
	std::vector<BYTE> bytes{ 'T', 'e', 's', 't' };

	EXPECT_EQ("000A: 54 65 73 74                                          Test", formatLine(10, &bytes[0], long(bytes.size())));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
