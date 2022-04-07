#include "../spirv_cross_parsed_ir.cpp"
#include "../spirv_glsl.hpp"
#include "../spirv_parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace spirv_cross;
extern vector<uint32_t> readFileAsUints(const char *filename);
extern vector<char> readFileAsBytes(const char *filename);
extern int tryDecompile();

int main()
{
	try
	{
		return tryDecompile();
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "SPIRV-Cross threw an exception: %s\n", e.what());
		return EXIT_FAILURE;
	}
	return 0;
}

int tryDecompile()
{
	// Read SPIR-V from disk or similar.
	vector<uint32_t> spirv_binary = readFileAsUints("../../vcs_vulkan_samples/source0.spv");
	spirv_cross::CompilerGLSL glsl(move(spirv_binary));
	spirv_cross::ShaderResources resources = glsl.get_shader_resources(); //spirv is parsed, we can perform reflection
	for (auto &resource : resources.sampled_images) // Get all sampled images in the shader.
	{
		unsigned set = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
		unsigned binding = glsl.get_decoration(resource.id, spv::DecorationBinding);
		printf("Image %s at set = %u, binding = %u\n", resource.name.c_str(), set, binding);
		glsl.unset_decoration(resource.id,
		                      spv::DecorationDescriptorSet); // Modify the decoration to prepare it for GLSL.
		glsl.set_decoration(resource.id, spv::DecorationBinding,
		                    set * 16 + binding); // Some arbitrary remapping if we want.
	}
	spirv_cross::CompilerGLSL::Options options;
	options.version = 450;
	options.es = true;
	glsl.set_common_options(options);
	string source = glsl.compile(); // Compile to GLSL, ready to give to GL driver.
	return 0;
}

vector<uint32_t> readFileAsUints(const char *filename)
{
	vector<char> b = readFileAsBytes(filename);
	vector<uint32_t> data;
	for (int i = 0; i < b.size(); i += 4)
	{
		uint32_t myInt = b[i + 3] + (b[i + 2] << 8) + (b[i + 1] << 16) + (b[i + 0] << 24);
		data.push_back(myInt);
	}
	return data;
}

vector<char> readFileAsBytes(const char *filename)
{
	ifstream file(filename, ios::binary);
	file.unsetf(ios::skipws); // don't skip whitespace
	streampos fileSize; // get the filesize
	file.seekg(0, ios::end);
	fileSize = file.tellg();
	file.seekg(0, ios::beg);

	vector<char> vec;
	vec.reserve(fileSize);
	vec.insert(vec.begin(), istream_iterator<char>(file), istream_iterator<char>()); // read the file
	return vec;
}
