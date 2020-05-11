#include <cassert>
#include <cstdlib>
#include <iostream>

#include "libs/ip_filter_lib.h"

void print_ip(const std::vector<std::vector<unsigned char> >& ip_pool)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << +*ip_part;
        }
        std::cout << std::endl;
    }
}

int main()
{
    try
    {
        std::vector<std::vector<unsigned char> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            try{
                ip_pool.emplace_back(convert_to_uchars(split(v.at(0), '.')));
            }
            catch(const std::exception &e)
            {
                std::cout << e.what() << "\n";
            }
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](auto& ip_1, auto& ip_2){
            for(decltype(ip_1.size()) i = 0; i<ip_1.size(); ++i)
                if(ip_1 != ip_2)
                    return ip_1 > ip_2;
            return false;
        });

        print_ip(ip_pool);
        
        auto ip_filter_1 = filter(ip_pool, 1);
        print_ip(ip_filter_1);
        
        auto ip_filter_2 = filter(ip_pool, 46, 70);
        print_ip(ip_filter_2);
        
        auto ip_filter_3 = filter_any(ip_pool, 46);
        print_ip(ip_filter_3);
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
