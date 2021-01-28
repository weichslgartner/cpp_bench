#define __cplusplus 201703L
#include "openssl/sha.h"
#include <fstream>
#include <fmt/core.h>
#include <iterator>
#include <vector>
#include <array>
#include <execution>
#include <numeric>
#include <fmt/ranges.h>
#include <string>

int main() {

	std::ifstream infile { "./lorem_ipsum.txt", std::ios::binary | std::ios::ate };
	if (!infile.is_open()) {
		fmt::print(stderr, "Cant open {}\n", "../lorem_ipsum.txt");
	}
	auto size = infile.tellg();
	infile.seekg(0, std::ios::beg);
	std::vector<uint8_t> buf((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
	std::array<unsigned char, SHA256_DIGEST_LENGTH> hash { };
	SHA256_CTX sha256 { };
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, buf.data(), buf.size());
	SHA256_Final(hash.data(), &sha256);
	auto hex_string =std::reduce(std::execution::par,hash.begin(),hash.end(),std::string{},[](auto const a, auto const b){return a+fmt::format("{:x}",b);});
	fmt::print("{}\n",hex_string);

	return 0;
}
