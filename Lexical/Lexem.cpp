//
// Created by ash on 27.02.24.
//

#include "Lexem.h"
#include<string>


std::ostream &operator<<(std::ostream &out, TokenType t) {
    switch (t) {
        case TokenType::BOperator:
            out << std::string("BOperator");
            break;
        case TokenType::UBOperator:
            out << std::string("UBOperator");
            break;
        case TokenType::UOperator:
            out << std::string("UOperator");
            break;
        case TokenType::Identifier:
            out << std::string("Identifier");
            break;
        case TokenType::Coma:
            out << std::string("Coma");
            break;
        case TokenType::Colon:
            out << std::string("Colon");
            break;
        case TokenType::DColon:
            out << std::string("DColon");
            break;
        case TokenType::Digit:
            out << std::string("Digit");
            break;
        case TokenType::HexDigit:
            out << std::string("HexDigit");
            break;
        case TokenType::Float:
            out << std::string("Float");
            break;
        case TokenType::HexFloat:
            out << std::string("HexFloat");
            break;
        case TokenType::Open:
            out << std::string("Open");
            break;
        case TokenType::Close:
            out << std::string("Close");
            break;
        case TokenType::String:
            out << std::string("String");
            break;
        case TokenType::Semicolon:
            out << std::string("Semicolon");
            break;
        case TokenType::KeyWord:
            out << std::string("KeyWord");
            break;
        case TokenType::Macros:
            out << std::string("Macros");
            break;
        case TokenType::SpecialWord:
            out << std::string("SpecialWord");
            break;
        case TokenType::End:
            out << std::string("End");
            break;
    }
    return out;
}
