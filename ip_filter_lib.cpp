#include "ip_filter_lib.h"

auto filter(std::vector<std::vector<std::string> > ip_list, 
            const unsigned char& octet_1) -> decltype(ip_list)
{
    decltype(ip_list) r;
    r.reserve(ip_list.size());
    auto filter_octet_1 = std::to_string(octet_1);
    for(const auto& ip : ip_list)
    {
        if(ip.at(0) == filter_octet_1)
        {
            r.push_back(ip);
        }
    }
    r.shrink_to_fit();
    return r;
}

auto filter(std::vector<std::vector<std::string> > ip_list, 
            const unsigned char& octet_1, 
            const unsigned char& octet_2) -> decltype(ip_list)
{
    decltype(ip_list) r;
    r.reserve(ip_list.size());
    auto filter_octet_1 = std::to_string(octet_1);
    auto filter_octet_2 = std::to_string(octet_2);
    for(const auto& ip : ip_list)
    {
        if(ip.at(0) == filter_octet_1 && ip.at(1) == filter_octet_2)
        {
            r.push_back(ip);
        }
    }
    r.shrink_to_fit();
    return r;
}

auto filter_any(std::vector<std::vector<std::string> > ip_list, 
            const unsigned char& octet) -> decltype(ip_list)
{
    decltype(ip_list) r;
    r.reserve(ip_list.size());
    auto filter_octet = std::to_string(octet);
    for(const auto& ip : ip_list)
    {
        auto it = std::find(ip.begin(), ip.end(), filter_octet);
        if(it != ip.end())
        {
            r.push_back(ip);
        }
    }
    r.shrink_to_fit();
    return r;
}