#pragma once
#include <string>
#include <vector>
#include <algorithm>

auto filter(std::vector<std::vector<std::string> > ip_list, 
            const unsigned char& octet_1) -> decltype(ip_list);
auto filter(std::vector<std::vector<std::string> > ip_list, 
            const unsigned char& octet_1, 
            const unsigned char& octet_2) -> decltype(ip_list);
auto filter_any(std::vector<std::vector<std::string> > ip_list, 
            const unsigned char& octet) -> decltype(ip_list);