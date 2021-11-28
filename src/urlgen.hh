#include <string>

uint64_t generate_url_id();
std::string encode_url_id(uint64_t url_id);
uint64_t decode_url_id(std::string url_id_str);
