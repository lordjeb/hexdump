#pragma once
#include <string>
#include <Windows.h>

std::string formatBytes(const BYTE* bytes, long length);
std::string formatLine(long offset, const BYTE* bytes, long length);
int hexdump(const std::string& filename, long offset, long length);
