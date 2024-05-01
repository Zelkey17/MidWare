//
// Created by ash on 15.02.24.
//

#ifndef MIDWARE_LEXEM_H
#define MIDWARE_LEXEM_H

#include <string>
#include <utility>

class LexicalAnalysis;

enum class TokenType {
    UBOperator,
    BOperator,
    UOperator,
    Identifier,
    Coma,
    Colon,
    DColon,
    Digit,
    HexDigit,
    Float,
    HexFloat,
    Open,
    Close,
    String,
    Semicolon,
    KeyWord,
    Macros,
    SpecialWord,
    End
};

std::ostream &operator<<(std::ostream &out, TokenType t);


class Lexem {
    TokenType type;
    std::string token;
public:
    Lexem(TokenType type, std::string token) : type(type), token(std::move(token)) {}

    [[nodiscard]] TokenType getType()const { return type; }

    [[nodiscard]] std::string getToken()const { return token; }

    friend LexicalAnalysis;

    bool operator==(const Lexem &lx)const {
        return lx.type == type && lx.token == token;
    }

    bool operator!=(const Lexem &lx) const{
        return !(lx.type == type && lx.token == token);
    }

};


#endif //MIDWARE_LEXEM_H
