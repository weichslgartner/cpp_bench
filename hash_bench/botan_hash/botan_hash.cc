#include <botan/hash.h>
#include <botan/hex.h>
#include <fstream>
#include <fmt/core.h>
#include <iterator>
#include <vector>
int main() {
	std::unique_ptr < Botan::HashFunction > hash1(Botan::HashFunction::create("SHA-256"));
	std::unique_ptr < Botan::HashFunction > hash2(Botan::HashFunction::create("SHA-384"));
	std::unique_ptr < Botan::HashFunction > hash3(Botan::HashFunction::create("SHA-3"));

	std::ifstream infile {"../lorem_ipsum.txt", std::ios::binary | std::ios::ate};
	if (!infile.is_open()) {
			fmt::print(stderr, "Cant open {}\n", "../lorem_ipsum.txt");
		}
	auto size = infile.tellg();
	infile.seekg(0, std::ios::beg);
	std::vector<uint8_t> buf((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());


	hash1->update(buf.data(),size);
	fmt::print("{}\n",Botan::hex_encode(hash1->final()));

	return 0;
}
