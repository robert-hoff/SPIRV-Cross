#include "../spirv_cross_parsed_ir.cpp"
#include "../spirv_glsl.hpp"
#include "../spirv_parser.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace spirv_cross;
extern vector<uint32_t> readFileAsUints(const char *filename);
extern vector<char> readFileAsBytes(const char *filename);

int main()
{
	try
	{
		// vector<uint32_t> spirv_binary = readFileAsUints("../../vcs_vulkan_samples/source0.spv");
		vector<uint32_t> spirv_binary = readFileAsUints("../../vcs_vulkan_samples/source2.spv");
		spirv_cross::CompilerGLSL glsl(move(spirv_binary));
		spirv_cross::ShaderResources resources = glsl.get_shader_resources();
		glsl.build_dummy_sampler_for_combined_images();
		glsl.build_combined_image_samplers();
		string source = glsl.compile();
		cout << source;
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "SPIRV-Cross threw an exception: %s\n", e.what());
		return EXIT_FAILURE;
	}
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
