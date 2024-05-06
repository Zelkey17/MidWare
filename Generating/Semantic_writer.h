//
// Created by ash on 05.05.24.
//

#ifndef MIDWARE_SEMANTIC_WRITER_H
#define MIDWARE_SEMANTIC_WRITER_H

#include<vector>
#include <string>
#include<concepts>
#include<sstream>
#include<ranges>
#include <algorithm>
#include<ext/pb_ds/assoc_container.hpp>

#define pbds __gnu_pbds


enum SPR{
    in_func,
    in_global,
    in_expr
};


class Semantic_writer {

public:

    void add_struct();

    void add_func();

    void add_func_over();



    pbds::gp_hash_table<std::string,size_t> types;


};


#endif //MIDWARE_SEMANTIC_WRITER_H
