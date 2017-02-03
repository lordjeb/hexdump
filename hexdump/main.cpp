#include "stdafx.h"
#include "..\hexdump_lib\hexdump.h"

using namespace std;

void usage()
{
	cout << "HexDump - Copyright LordJeb Software" << endl << endl
		<< "Usage:" << endl
		<< "   hexdump [filename] [offset] [length]" << endl;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		usage();
	}

	string filename{ argv[1] };
	auto offset = argc < 3 ? stol(argv[2]) : 0;
	auto length = argc < 4 ? stol(argv[3]) : 0;

	return hexdump(filename, offset, length);
}
