#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
	

std::vector<std::string> split(const std::string &str, const char d);
std::vector<unsigned char> convert_to_uchars(const std::vector<std::string>& ip);
auto filter(const std::vector<std::vector<unsigned char> >& ip_list, 
            const unsigned char octet_1) -> std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type;
auto filter(const std::vector<std::vector<unsigned char> >& ip_list, 
            const unsigned char octet_1, 
            const unsigned char octet_2) -> std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type;
auto filter_any(const std::vector<std::vector<unsigned char> >& ip_list, 
            const unsigned char octet) -> std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type;