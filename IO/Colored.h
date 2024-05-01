//
// Created by ash on 23.09.23.
//

#ifndef LZV_LIMITED_COLORED_H
#define LZV_LIMITED_COLORED_H

#include <string>

std::string fclr(unsigned char r, unsigned char g, unsigned char b);
std::string fclr(unsigned char r);

std::string bclr(unsigned char r, unsigned char g, unsigned char b);

std::string underline1();

std::string underline2();

std::string bold();

std::string strike();

std::string encircled();


std::string operator|(std::string a, std::string b);


#endif //LZV_LIMITED_COLORED_H
