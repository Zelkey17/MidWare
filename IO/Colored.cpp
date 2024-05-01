//
// Created by ash on 23.09.23.
//

#include "Colored.h"

std::string fclr(unsigned char r, unsigned char g, unsigned char b) {
    return "\x1B[38;2;"+std::to_string((int)r)+";"+std::to_string((int)g)+";"+std::to_string((int)b)+"m";
}

std::string fclr(unsigned char r) {
    return "\x1B[38;5;"+std::to_string((int)r)+"m";
}


std::string underline1() {
    return "\x1B[4m";
}

std::string bclr(unsigned char r, unsigned char g, unsigned char b) {
    return "\x1B[48;2;"+std::to_string((int)r)+";"+std::to_string((int)g)+";"+std::to_string((int)b)+"m";
}

std::string underline2() {
    return "\x1B[21m";
}

std::string bold() {
    return "\x1B[1m";
}

std::string strike() {
    return "\x1B[9m";
}

std::string encircled() {
    return "\x1B[52m";
}

std::string operator|(std::string a, std::string b) {
    return b+a+"\033[0m";
}
