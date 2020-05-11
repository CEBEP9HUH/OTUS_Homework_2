#include "ip_filter_lib.h"

std::vector<std::string> split(const std::string &str, const char d)
{
    std::vector<std::string> r;

    decltype(auto) stop = str.find_first_of(d);
    decltype(stop) start = 0;
    while(stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}

std::vector<unsigned char> convert_to_uchars(const std::vector<std::string>& ip)
{
    std::vector<unsigned char> r;
    for(const auto& octet: ip)
    {
        if(octet.find_first_not_of("0123456789", 0) != std::string::npos)
        {
            break;
        }
        int int_octet = std::stoi(octet);
        if(0 <= int_octet && int_octet <= __UINT8_MAX__)
        {
            r.push_back(int_octet);
        }
    }
    if(r.size() != ip.size() || r.size() != 4)
    {
        throw(std::invalid_argument("Ip error"));
    }
    return r;
}

auto filter(const std::vector<std::vector<unsigned char> >& ip_list, 
            const unsigned char octet_1) -> std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type
{
    std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type r;
    r.reserve(ip_list.size());
    for(const auto& ip : ip_list)
    {
        if(ip.at(0) == octet_1)
        {
            r.emplace_back(ip);
        }
    }
    r.shrink_to_fit();
    return r;
}

auto filter(const std::vector<std::vector<unsigned char> >& ip_list, 
            const unsigned char octet_1, 
            const unsigned char octet_2) -> std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type
{
    std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type r;
    r.reserve(ip_list.size());
    for(const auto& ip : ip_list)
    {
        if(ip.at(0) == octet_1 && ip.at(1) == octet_2)
        {
            r.emplace_back(ip);
        }
    }
    r.shrink_to_fit();
    return r;
}

auto filter_any(const std::vector<std::vector<unsigned char> >& ip_list, 
            const unsigned char octet) -> std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type
{
    std::remove_const<std::remove_reference<decltype(ip_list)>::type >::type r;
    r.reserve(ip_list.size());
    for(const auto& ip : ip_list)
    {
        auto it = std::find(ip.begin(), ip.end(), octet);
        if(it != ip.end())
        {
            r.emplace_back(ip);
        }
    }
    r.shrink_to_fit();
    return r;
}