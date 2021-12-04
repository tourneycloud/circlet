/*
 * Copyright 2021 Michael P. Nitowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <chrono>
#include <sstream>
#include <tuple>

uint64_t generate_url_id() {
    uint64_t url_id = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    return url_id;
}

std::string a = "23456789CFGHJMPQRVWXcfghjmpqrvwx";
size_t a_size = 32;

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

static uint64_t pow32_cache[14] = {
    1,
    32,
    1024,
    32768,
    1048576,
    33554432,
    1073741824,
    34359738368,
    1099511627776,
    35184372088832,
    1125899906842624,
    36028797018963968,
    1152921504606846976
};

uint64_t pow32(int n) {
    if (n > 13) return -1;
    return pow32_cache[n];
}

uint64_t decode_url_id(std::string url_id_str) {
    uint64_t id = 0;

    size_t i = 0;
    for (auto &l : url_id_str) {
        id += a.find(l) * pow32(url_id_str.size() - (i + 1));
        i++;
    }
    return id;
}
