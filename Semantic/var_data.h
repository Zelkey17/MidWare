//
// Created by ash on 14.03.24.
//

#ifndef MIDWARE_VAR_DATA_H
#define MIDWARE_VAR_DATA_H

#include<string>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <optional>
#include "../Lexical/Lexem.h"

struct var_data{

    explicit var_data(const Lexem& lx):name(std::move(lx.getToken())){
        switch (lx.getType()) {
            case TokenType::Identifier:
            case TokenType::Digit:
            case TokenType::HexDigit:
            case TokenType::Float:
            case TokenType::HexFloat:
            case TokenType::String:
                break;
            default:
                throw std::logic_error(lx.getToken());
                break;
        }
        offset=0;
    }
    explicit var_data(std::string nn):name(std::move(nn)){

    }
    size_t offset=0;
    std::string name;
    bool operator<(const var_data& a) const{
        return name<a.name;
    }
    bool operator==(const var_data& a) const{
        return name==a.name;
    }
};
struct spec{
    std::optional<int> ssize;
    std::optional<bool> isvoid;
    std::optional<bool> editable;
    std::optional<bool> local;
    std::optional<bool> no_except;
    std::optional<bool> overld;
    std::optional<bool> ranged;
    std::optional<bool> entry;
};


struct type{
    std::string name;
    int sz;
    bool operator<(const type& a) const{
        return name<a.name;
    }
    bool operator==(const type& a) const{
        return name==a.name;
    }
};

struct func_data{
    std::string name;
    spec sp;
    std::map<std::vector<type>,bool> overld;
    bool operator<(const func_data& a) const{
        return name<a.name;
    }
    bool operator==(const func_data& a) const{
        return name==a.name;
    }
};

#endif //MIDWARE_VAR_DATA_H
