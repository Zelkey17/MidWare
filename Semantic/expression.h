//
// Created by ash on 14.03.24.
//

#ifndef MIDWARE_EXPRESSION_H
#define MIDWARE_EXPRESSION_H

#include <optional>
#include <stack>
#include<vector>
#include <stdexcept>
#include"../Lexical/Lexem.h"
#include "var_data.h"



// Операторы
// Приоритет Оператор Ассоциативность
// 4 ! правая
// 3 * / % левая
// 2 + - левая
// 1 = левая

/*
 :: ;0 ;9
 ++ ;1 ;8
 += ;2 ;1
 +  ;3 ;6
 -  ;4 ;6
 -= ;5 ;1
 -- ;6 ;8
 -> ;7 ;4
 *  ;8 ;7
 /  ;9 ;7
 %  ;10; 7
 ^  ;11; 2
 |  ;12; 2
 &  ;13; 2
 <  ;14; 3
 *= ;15; 1
 /= ;16; 1
 %= ;17; 1
 ^= ;18; 1
 |= ;19; 1
 &= ;20; 1
 <= ;21; 3
 >  ;22; 3
 >= ;23; 3
 >< ;24; 3
 !  ;25; 8
 ~  ;26; 8
 $  ;27; 8
 u+ ;28; 8
 u- ;29; 8
 u* ;30; 8
 ,  ;31; 5
 =  ;32; 1
 <- ;33; 1
 */

/*


 */

struct exprToken {
    char id;
    char type;
    std::optional<var_data> ind;

    exprToken(const Lexem &lx) {
        if (lx.getType() == TokenType::UOperator) {
            type = 0;
            if (lx.getToken() == "++")id = 1;
            if (lx.getToken() == "+")id = 28;
            if (lx.getToken() == "--")id = 6;
            if (lx.getToken() == "-")id = 29;
            if (lx.getToken() == "*")id = 30;
            if (lx.getToken() == "~")id = 26;
            if (lx.getToken() == "!")id = 25;
            if (lx.getToken() == "$")id = 27;
        } else if (lx.getType() == TokenType::BOperator) {
            if (lx.getToken() == "::")id = 0;
            if (lx.getToken() == "+=")id = 2;
            if (lx.getToken() == "+")id = 3;
            if (lx.getToken() == "-")id = 4;
            if (lx.getToken() == "-=")id = 5;
            if (lx.getToken() == "->")id = 7;
            if (lx.getToken() == "*")id = 8;
            if (lx.getToken() == "/")id = 9;
            if (lx.getToken() == "%")id = 10;
            if (lx.getToken() == "^")id = 11;
            if (lx.getToken() == "|")id = 12;
            if (lx.getToken() == "&")id = 13;
            if (lx.getToken() == "<")id = 14;
            if (lx.getToken() == "*=")id = 15;
            if (lx.getToken() == "/=")id = 16;
            if (lx.getToken() == "%=")id = 17;
            if (lx.getToken() == "^=")id = 18;
            if (lx.getToken() == "|=")id = 19;
            if (lx.getToken() == "&=")id = 20;
            if (lx.getToken() == "<=")id = 21;
            if (lx.getToken() == ">")id = 22;
            if (lx.getToken() == ">=")id = 23;
            if (lx.getToken() == "><")id = 24;
            if (lx.getToken() == ",")id = 31;
            if (lx.getToken() == "=")id = 32;
            if(lx.getToken()=="<-")id=33;
        } else if (lx == Lexem{TokenType::Open, "("}) {
            type=2;
            id=0;
        } else if (lx == Lexem{TokenType::Close, ")"}) {
            type=3;
            id=0;
        } else {
            auto var = var_data(lx);
            type=1;
            id=0;
            ind=var;
        }
    }

    [[nodiscard]] int get_priority() const {
        if (type == 0) {
            switch (id) {
                case 2:
                case 5:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 32:
                case 33:
                    return 1;
                case 11:
                case 12:
                case 13:
                    return 2;
                case 14:
                case 21:
                case 22:
                case 23:
                case 24:
                    return 3;
                case 7:
                    return 4;
                case 31:
                    return 5;
                case 3:
                case 4:
                    return 6;
                case 8:
                case 9:
                case 10:
                    return 7;
                case 1:
                case 6:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                    return 8;
                case 0:
                    return 9;
                default:
                    throw std::logic_error("");
            }
        } else if (type == 1) {
            throw std::logic_error("");
        }
        return 0;
    }

    [[nodiscard]] bool left() const {
        if (type == 0) {
            switch (id) {
                case 11:
                case 12:
                case 13:
                case 14:
                case 21:
                case 22:
                case 23:
                case 24:
                case 31:
                case 3:
                case 4:
                case 0:
                case 8:
                case 9:
                case 10:
                    return true;

                case 2:
                case 5:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 32:
                case 33:
                case 7:
                case 1:
                case 6:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                    return false;
                default:
                    throw std::logic_error("");
            }
        } else if (type == 1) {
            throw std::logic_error("");
        }
        return false;
    }

    [[nodiscard]] bool is_op() const {
        return type == 0;
    }

    [[nodiscard]] bool is_id() const {
        return type == 1;
    }

    [[nodiscard]] bool is_open() const {
        return type == 2;
    }

    [[nodiscard]] bool is_close() const {
        return type == 3;
    }

};

#endif //MIDWARE_EXPRESSION_H
