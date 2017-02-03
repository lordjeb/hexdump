#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const long DISPLAY_BUFFER_SIZE = 16;

void addBytes(stringstream& ss, const BYTE* bytes, long length)
{
	ss.fill('0');
	for (long i = 0; i < DISPLAY_BUFFER_SIZE; ++i)
	{
		if (i > 0)
		{
			ss << ' ';
		}

		if (i == 8)
		{
			ss << "  ";
		}

		if (i < length)
		{
			ss << setw(2) << uppercase << hex << int(bytes[i]);
		}
		else
		{
			ss << "  ";
		}
	}
	ss.fill(' ');
}

void addPrintableCharacters(stringstream& ss, const BYTE* bytes, long length)
{
	for (long i = 0; i < DISPLAY_BUFFER_SIZE; ++i)
	{
		if (i < length)
		{
			if (isprint(bytes[i]))
			{
				ss << bytes[i];
			}
			else
			{
				ss << '.';
			}
		}
	}
}

string formatBytes(const BYTE* bytes, long length)
{
	if (length == 0)
	{
		return "";
	}

	stringstream ss;

	addBytes(ss, bytes, length);

	ss << "    ";

	addPrintableCharacters(ss, bytes, length);

	return ss.str();
}

string formatLine(long offset, const BYTE* bytes, long length)
{
	stringstream ss;
	ss.fill('0');
	ss << setw(4) << uppercase << hex << offset << ": " << formatBytes(bytes, length);
	ss.fill(' ');
	return ss.str();
}

int hexdump(const string& filename, long offset, long length)
{
	vector<char> bytes(DISPLAY_BUFFER_SIZE);
	ifstream f(filename, ios::ate | ios::in | ios::binary);
	if (f.good())
	{
		auto fileSize = long(f.tellg());
		auto readableBytes = fileSize - offset;
		length = length == 0 ? readableBytes : min(length, readableBytes);

		f.seekg(offset);

		do
		{
			f.read(&bytes[0], DISPLAY_BUFFER_SIZE);

			auto bytesRead = long(f.gcount());

			cout << formatLine(offset, reinterpret_cast<BYTE*>(&bytes[0]), min(length, bytesRead)) << endl;

			length -= bytesRead;
			offset += bytesRead;
		} while (length > 0);
	}
	else
	{
		cout << "Failed to open file " << filename << endl;
	}

	return 0;
}

