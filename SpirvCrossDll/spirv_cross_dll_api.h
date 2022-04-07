#pragma once
#include <iostream>
#include <vector>

using namespace std;

class SpirvDecompiler
{
	vector<uint32_t> spirv_binary;
	string result;
	int result_len;

public:
	SpirvDecompiler();
	void PushUInt32(uint32_t val);
	void Parse();
	int GetDataLength();
	char GetChar(int i);
};

extern "C" __declspec(dllexport) void *CreateSpirvDecompiler()
{
	return (void *)new SpirvDecompiler();
}
extern "C" __declspec(dllexport) void PushUInt32(SpirvDecompiler *a, uint32_t y)
{
	a->PushUInt32(y);
}
extern "C" __declspec(dllexport) void Parse(SpirvDecompiler *a)
{
	return a->Parse();
}
extern "C" __declspec(dllexport) int GetDataLength(SpirvDecompiler *a)
{
	return a->GetDataLength();
}
extern "C" __declspec(dllexport) char GetChar(SpirvDecompiler *a, int i)
{
	return a->GetChar(i);
}
