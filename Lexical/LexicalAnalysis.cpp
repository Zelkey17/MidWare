//
// Created by ash on 15.02.24.
//

#include "LexicalAnalysis.h"

#include <utility>
#include <fstream>

LexicalAnalysis::LexicalAnalysis(const Reader &rd) : rd(rd) {}

LexicalAnalysis::LexicalAnalysis(std::string file) : rd(std::move(file)) {}


Lexem LexicalAnalysis::_start(std::string *str) {

    if (char s = rd.peek(); s == '0') {
        rd.ignore();
        str->push_back(s);
        if (char t = rd.peek();t == 'x') {

            rd.ignore();
            str->push_back(t);
            str->push_back('0');
            t = rd.peek();
            for (; '0' <= t && t <= '9' || 'a' <= t && t <= 'f' || 'A' <= t && t <= 'F'; t = rd.peek()) {
                rd.ignore();
                str->push_back(t);
            }
            if (rd.peek() == '.') {
                str->push_back('.');
                rd.ignore();
                t = rd.peek();
                for (; '0' <= t && t <= '9' || 'a' <= t && t <= 'f' || 'A' <= t && t <= 'F'; t = rd.peek()) {
                    rd.ignore();
                    str->push_back(t);
                }
                return {TokenType::HexFloat, *str};
            }
            return {TokenType::HexDigit, *str};
        } else if ('0' <= t && t <= '9') {
            rd.ignore();
            str->push_back(t);
            t = rd.peek();
            for (; '0' <= t && t <= '9'; t = rd.peek()) {
                rd.ignore();
                str->push_back(t);
            }
            if (rd.peek() == '.') {
                str->push_back('.');
                rd.ignore();
                t = rd.peek();
                for (; '0' <= t && t <= '9'; t = rd.peek()) {
                    rd.ignore();
                    str->push_back(t);
                }
                return {TokenType::Float, *str};
            }
            return {TokenType::Digit, *str};
        } else {
            (void) s;
            return {TokenType::Digit, "0"};
        }

    } else if (s == ':') {
        str->push_back(':');
        rd.ignore();
        if (s = rd.peek();s == ':') {
            rd.ignore();
            str->push_back(':');
            return {TokenType::DColon, "::"};
        }
        return {TokenType::Colon, ":"};

    } else if ('1' <= s && s <= '9') {
        for (; '0' <= s && s <= '9'; s = rd.peek()) {
            rd.ignore();
            str->push_back(s);
        }
        if (rd.peek() == '.') {
            str->push_back('.');
            rd.ignore();
            s = rd.peek();
            for (; '0' <= s && s <= '9'; s = rd.peek()) {
                rd.ignore();
                str->push_back(s);
            }
            return {TokenType::Float, *str};
        }
        return {TokenType::Digit, *str};
    } else if (s == '+') {
        rd.ignore();
        str->push_back('+');
        if (char t = rd.peek();t == '+') {
            rd.ignore();
            str->push_back('+');
            return {TokenType::UOperator, *str};
        } else if (t == '=') {
            rd.ignore();
            str->push_back('=');

            return {TokenType::BOperator, *str};
        }
        return {TokenType::UBOperator, *str};
    } else if (s == '-') {
        rd.ignore();
        str->push_back('-');
        if (char t = rd.peek();t == '-') {
            rd.ignore();
            str->push_back('-');
            return {TokenType::UOperator, *str};
        } else if (t == '=') {
            rd.ignore();
            str->push_back('=');

            return {TokenType::BOperator, *str};
        } else if (t == '>') {
            rd.ignore();
            str->push_back('>');

            return {TokenType::BOperator, *str};
        }
        return {TokenType::UBOperator, *str};
    }else if(s=='*'){
        str->push_back(s);
        rd.ignore();
        if (s = rd.peek();s == '=') {
            str->push_back('=');
            rd.ignore();
            return {TokenType::BOperator, *str};
        }
        return {TokenType::UBOperator, *str};

    } else if(s=='<'){
        str->push_back(s);
        rd.ignore();
        if(rd.peek()=='-'||rd.peek()=='='){
            str->push_back(rd.peek());
            rd.ignore();
        }
        return {TokenType::BOperator,*str};

    }else if (s == '/' || s == '%' || s == '^' || s == '|' || s == '&' || s == '=') {
        str->push_back(s);
        rd.ignore();
        if (s = rd.peek();s == '=') {
            str->push_back('=');
            rd.ignore();
        }
        return {TokenType::BOperator, *str};

    } else if (s == '~' || s == '$') {
        rd.ignore();
        str->push_back(s);
        return {TokenType::UOperator, *str};
    } else if (s == '!') {
        rd.ignore();
        str->push_back(s);
        if (s = rd.peek();s == '=') {
            rd.ignore();
            str->push_back('=');
            return {TokenType::BOperator, "!="};
        }
        return {TokenType::UOperator, "!"};
    } else if (s == '>') {
        str->push_back('>');
        rd.ignore();
        if (s = rd.peek();s == '<') {
            rd.ignore();
            str->push_back('<');
        } else if (s == '=') {
            rd.ignore();
            str->push_back('=');
        }
        return {TokenType::BOperator, *str};
    } else if (s == '"') {
        rd.ignore();
        for (;;) {
            char t;
            if (int esc = get_esc_char(rd, t);esc == 0) {
                str->push_back(t);
            } else if (esc == 1) {

                rd.error();
                std::cerr << ("Compile error: unrecognized escape sequence here:" | bold() | fclr(255, 0, 0))
                          << std::endl;
                _error(rd.str, rd.cr - 1, 2);
            } else if (esc == 2) {
                rd.error();
                std::cerr << ("Compile error: unexpected end of line:" | bold() | fclr(255, 0, 0)) << std::endl;
                _error(rd.str, rd.cr, 0, true);
                return {TokenType::String, *str};
            } else if (esc == 4) {
                rd.error();
                std::cerr << ("Compile error: unrecognized escape sequence here:" | bold() | fclr(255, 0, 0))
                          << std::endl;
                _error(rd.str, rd.cr - 2, 2);
            } else if (esc == -1) {
                return {TokenType::String, *str};
            }

        }
    } else if (s == '\'') {
        rd.ignore();
        if (s = rd.peek();s == '\'') {
            rd.ignore();
            if (s = rd.peek();s == '\'') {
                rd.ignore();
                while (str->size() <= 3 || !(str->at(str->size() - 1) == '\'' &&
                                             str->at(str->size() - 2) == '\'' &&
                                             str->at(str->size() - 3) == '\'')) {
                    rd.get_char(s);
                    if (s == '\0') {
                        rd.error();
                        std::cerr << ("Compile error: unexpected end of file:" | bold() | fclr(255, 0, 0)) << std::endl;
                        _error(rd.str, rd.cr, 0, true);
                        return {TokenType::String, *str};
                    }
                    str->push_back(s);
                }
                str->pop_back();
                str->pop_back();
                str->pop_back();
                return {TokenType::String, *str};
            } else {
                return {TokenType::String, ""};
            }
        } else {
            while (rd.peek() != '\'') {
                if (rd.peek() == '\0' || rd.peek() == '\n') {
                    rd.error();
                    std::cerr << ("Compile error: unexpected end of line:" | bold() | fclr(255, 0, 0)) << std::endl;
                    _error(rd.str, rd.cr, 0, true);
                    return {TokenType::String, *str};
                }
                str->push_back(rd.peek());
                rd.ignore();
            }
            rd.ignore();
            return {TokenType::String, *str};
        }
    } else if (s == '#') {
        std::cerr << ("Warning" | bold()) << std::endl;
    } else if (s == '@') {
        rd.ignore();
        s = rd.peek();
        while ('a' <= s && s <= 'z') {
            str->push_back(s);
            rd.ignore();
            s = rd.peek();
        }
        return {TokenType::SpecialWord, *str};
    } else if (('a' <= s && s <= 'z') || ('A' <= s && s <= 'Z') ) {
        str->push_back(s);
        rd.ignore();
        s = rd.peek();
        while (('a' <= s && s <= 'z') || ('A' <= s && s <= 'Z') || s == '_' || ('0' <= s && s <= '9')) {
            str->push_back(s);
            rd.ignore();
            s = rd.peek();
        }
        return {TokenType::Identifier, *str};
    } else if (s == ' ' || s == '\n') {
        rd.ignore();
        return _start(str);
    } else if (!rd || s == '\0') {
        return {TokenType::End, ""};
    } else if (s == '(' || s == '{' || s == '[') {
        rd.ignore();
        str->push_back(s);
        return {TokenType::Open, *str};
    } else if (s == ')' || s == '}' || s == ']') {
        rd.ignore();
        str->push_back(s);
        return {TokenType::Close, *str};
    } else if (s == ';') {
        rd.ignore();
        str->push_back(s);
        return {TokenType::Semicolon, *str};
    } else if (s == ',') {
        rd.ignore();
        str->push_back(s);
        return {TokenType::Coma, *str};
    } else {
        str->push_back(s);
        rd.ignore();

        rd.error();
        std::cerr << ("Compile error: unexpected symbol " | bold() | fclr(255, 0, 0));
        std::cerr << (*str | bold() | underline1() | underline2() | fclr(0, 100, 255));
        std::cerr << (" here:" | fclr(255, 0, 0)) << std::endl;
        _error(rd.str, rd.cr - 1, 1);
        str->pop_back();
        return _start(str);
    }
    __builtin_unreachable();
}

const std::string LexicalAnalysis::kw[] = {"for", "while", "if", "const", "import", "empty", "overld",
                                           "return", "with", "suspend", "var", "local", "ssize", "noexcept",
                                           "import",  "else","elif", "asm", "struct","entry",
                                           "editable", "ranged", "in", "break", "continue", "goto","nullptr", "void", "true", "false", "undef"
                                           };

const std::string LexicalAnalysis::sw[] = {"range", "size", "init", "del", "cmp", "less_equal", "greater_equal", "less",
                                           "greater", "equal", "not_equal", "abs", "invert", "add", "sub", "mul", "div",
                                           "and", "or", "xor", "mod", "flag", "hash", "in", "call", "copy", "next",
                                           "ret", "id"};

Lexem LexicalAnalysis::get() {
    auto *str = new std::string();

    Lexem ans = _start(str);
    delete str;
    if (ans.getType() == TokenType::SpecialWord) {
        bool flag = false;
        for (std::string str1: sw) {
            if (str1 == ans.getToken()) {
                flag = true;
            }
        }
        if (!flag) {
            rd.error();
            std::cerr << ("Compile error: unknown special word " | bold() | fclr(255, 0, 0));
            std::cerr << ("@" + ans.getToken() | bold() | underline1() | underline2() | fclr(50, 130, 235));
            std::cerr << (" here:" | fclr(255, 0, 0)) << std::endl;
            _error(rd.str, rd.cr - 1 - ans.getToken().size(), ans.getToken().size() + 1);
        }

    }
    if (ans.getType() == TokenType::Identifier) {
        for (std::string st: kw) {
            if (ans.getToken() == st)ans.type = TokenType::KeyWord;
        }
    }
    return ans;
}

void LexicalAnalysis::_error(int str, int st, int cnt, bool k) {
    std::ifstream file(rd.get_file_name());
    std::string line;
    for (int i = 0; i < str; i++) {
        getline(file, line);
    }
    std::string h = std::to_string(str);
    try {
        std::cerr << h << " | " << (line.substr(0, st) | fclr(255, 255, 255));
    } catch (std::out_of_range) {}catch(std::length_error){}
    try { std::cerr << (line.substr(st, cnt) | fclr(255, 0, 50)); } catch (std::out_of_range) {}catch(std::length_error){}
    try { std::cerr << (line.substr(st + cnt) | fclr(255, 255, 255)) << std::endl; } catch (std::out_of_range) {}catch(std::length_error){}
    try {
        std::cerr << std::string(h.size() + 1, ' ') << '|' << std::string(st + 1, ' ')
                  << std::string((k ? 10 : cnt), (k ? '~' : '^')) << std::endl << std::endl;
    } catch (std::out_of_range) {}catch(std::length_error){}
}

void LexicalAnalysis::error(int s, bool k, const std::string &str, bool g) {
    rd.error();
    std::cerr << str << std::endl;
    if (g)
        _error(rd.str, rd.cr - s, s, k);
}
