#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <tuple>

uint64_t generate_url_id() {
    uint64_t url_id = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    return url_id;
}

std::string a = "0123456789befhjmnrstvwyz";
size_t a_size = 24;

std::string encode_url_id(uint64_t url_id) {
    std::stringstream s;
    while (url_id) {
        s << a[url_id % a_size];
        url_id /= a_size;
    }
    auto str = s.str();
    std::reverse(str.begin(), str.end());
    return str;
}

static uint64_t pow24_cache[14] = {
    1,
    24,
    576,
    13824,
    331776,
    7962624,
    191102976,
    4586471424,
    110075314176,
    2641807540224,
    63403380965376,
    1521681143169024,
    36520347436056576,
    876488338465357824,
};

uint64_t pow24(int n) {
    if (n > 13) return -1;
    return pow24_cache[n];
}

uint64_t decode_url_id(std::string url_id_str) {
    uint64_t id = 0;

    size_t i = 0;
    for (auto &l : url_id_str) {
        id += a.find(l) * pow24(url_id_str.size() - (i + 1));
        i++;
    }
    return id;
}
