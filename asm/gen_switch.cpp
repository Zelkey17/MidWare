//
// Created by ash on 29.04.24.
//

#include<vector>
#include <string>
#include<concepts>
#include<sstream>
#include<ranges>
#include <algorithm>

#pragma once

template<std::forward_iterator RAI_T>
void __gen_switch_body(RAI_T _begin, RAI_T _end, const std::string &id, const std::string &val, std::stringstream &ans,
                       int lvl = 1) {
    if (_begin == _end) {
        ans << "jmp __switch_" << id << "_default__" << std::endl;
        return;
    }
    auto mid = _begin + (_end - _begin) / 2;
    ans << "cmp $" << static_cast<unsigned long long>(mid->first) << ", " << val << std::endl;
    ans << "jae " << "__switch_" << id << "__lvl_" << lvl << std::endl;
    __gen_switch_body(_begin, mid, id, val, ans, 2 * lvl);
    ans << "__switch_" << id << "__lvl_" << lvl << ":" << std::endl;
    ans << "je " << "__switch_" << id << "__lvl_" << lvl << "_eq" << std::endl;
    __gen_switch_body(mid + 1, _end, id, val, ans, 2 * lvl + 1);
    ans << "__switch_" << id << "__lvl_" << lvl << "_eq:" << std::endl;
    ans << std::endl << "# switch " << id << " value:" << mid->first << std::endl;
    ans << mid->second << std::endl;
    ans << "jmp __switch_" << id << "_end__" << std::endl;

}


template<std::integral T>
std::stringstream
gen_switch(std::vector<std::pair<T, std::string>> all, const std::string &defaul, const std::string &unique_switch_name,
           const std::string &value) {
    std::stringstream ans;
    ans << "# switch " << unique_switch_name << " started: " << std::endl;
    std::ranges::sort(all, [](std::pair<T, std::string> &a, std::pair<T, std::string> &b) {
        return static_cast<unsigned long long>(a.first) < static_cast<unsigned long long>(b.first);
    });

    __gen_switch_body(all.begin(), all.end(), unique_switch_name, value, ans);
    ans << "__switch_" << unique_switch_name << "_default__:" << std::endl;
    ans << defaul << std::endl;
    ans << "__switch_" << unique_switch_name << "_end__:" << std::endl;

    return ans;
}

