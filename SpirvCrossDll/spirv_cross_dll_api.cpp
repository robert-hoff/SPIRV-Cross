#include "pch.h"
#include "spirv_cross_dll_api.h"
#include "../spirv_glsl.hpp"
#include "../spirv_parser.hpp"
#include <vector>

using namespace std;
using namespace spirv_cross;

SpirvDecompiler::SpirvDecompiler()
{
}

void SpirvDecompiler::PushUInt32(uint32_t val)
{
	this->spirv_binary.push_back(val);
}

void SpirvDecompiler::Parse()
{
	CompilerGLSL glsl(move(this->spirv_binary));
	ShaderResources resources = glsl.get_shader_resources();
	glsl.build_dummy_sampler_for_combined_images();
	glsl.build_combined_image_samplers();
	string source = glsl.compile();
	this->result = source;
	this->result_len = source.length();
}

int SpirvDecompiler::GetDataLength()
{
	return this->result_len;
}

char SpirvDecompiler::GetChar(int i)
{
	return this->result[i];
}
