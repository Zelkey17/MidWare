//
// Created by ash on 12.03.24.
//
#include <vector>
#include "Syntax.h"
#include "../Semantic/utils.h"


void SyntaxAnalysis::err() {
    err("Invalid syntax: unexpected token");
}

void SyntaxAnalysis::err(const std::string &str) {
    semantic->fail();
    lx.error(lx.peek().getToken().size(), false,
             (str + " " | bold() | fclr(255, 0, 0)) +
             (lx.peek().getToken() | bold() | underline1() | underline2() |

              fclr(50, 130, 235)) + (" here:" | bold() | fclr(255, 0, 0)));
}

void SyntaxAnalysis::_import() {
    auto name = lx.peek();
    if (name.getType() == TokenType::String) {
        lx.get();
        auto with = lx.peek();
        if (with.getType() == TokenType::KeyWord && with.getToken() == "with") {
            lx.get();
            auto space = lx.peek();
            if (space.getType() == TokenType::Identifier) {
                semantic->start_space(lx.get().getToken());
                semantic->import_(name.getToken());
                semantic->end_space();
            } else {
                err("Invalid syntax: unexpected token (expected space name)");
            }
        } else {

            semantic->import_(name.getToken());
        }
    } else {
        err();
    }

}


void SyntaxAnalysis::_gl_var() {
    if (auto tk = lx.peek();tk.getType() == TokenType::Identifier) {
        semantic->create_gl_var(tk.getToken());
        lx.get();
        if (lx.peek().getType() == TokenType::Semicolon) {
            lx.get();
            return;
        } else if (lx.peek().getType() == TokenType::Coma) {
            lx.get();
            _gl_var();
            return;
        }
    }
    err();
}

void SyntaxAnalysis::_func_body() {
    semantic->start_func_body();
    _scope();
    semantic->end_func_body()
}

void SyntaxAnalysis::_indexing() {
    lx.get();
    semantic->start_indexing();
    _expression(":", true);
    _expression(":", true);
    _expression("]", true);
    //semantic add expr indexing
    semantic->end_indexing();
}

void SyntaxAnalysis::_func(const std::string &f_name) {
    auto start = lx.peek();
    if (start.getType() == TokenType::Colon) {
        lx.get();
        auto spec=_get_spec();
        semantic->start_func(f_name, spec);
        if(!spec.isvoid) {
            _func_body();
        }else{
            if(lx.peek().getType()==TokenType::Semicolon){
                lx.get();
            }else{
                err("Expected ; got");
            }
        }
    } else if (start.getType() == TokenType::Open && start.getToken() == "{") {
        semantic->start_func(f_name);
        _func_body();
    } else {
        err();
        return;
    }
}

spec SyntaxAnalysis::_get_spec() {
    spec an;
    while (lx.peek().getToken() != "{") {
        if (lx.peek().getType() == TokenType::KeyWord) {
            if (auto tk = lx.peek();tk.getToken() == "ssize") {
                lx.get();
                if (lx.peek().getType() != TokenType::Open || lx.peek().getToken() != "(") {
                    err();
                }
                lx.get();

                if (lx.peek().getType() != TokenType::Digit && lx.peek().getType() != TokenType::HexDigit) {
                    err();
                }

                int ss = to_int(lx.peek());
                if (an.ssize) {
                    err("ssize value is set");
                } else {
                    an.ssize = ss;
                }
                lx.get();
                if (lx.peek().getType() != TokenType::Close || lx.peek().getToken() != ")") {
                    err();
                }
                lx.get();

            } else if (tk.getToken() == "noexcept") {
                lx.get();
                if (!an.no_except)an.no_except = true;
            } else if (tk.getToken() == "overld") {
                lx.get();
                if (!an.overld)an.overld = true;
            } else if (tk.getToken() == "ranged") {
                lx.get();
                if (!an.ranged)an.ranged = true;

            } else if (tk.getToken() == "editable") {
                lx.get();
                if (!an.editable)an.editable = true;

            } else if (tk.getToken() == "local") {
                lx.get();
                if (!an.local)an.local = true;
            } else if (tk.getToken() == "entry") {
                lx.get();
                if (!an.entry)an.entry = true;
            } else if (tk.getToken() == "empty") {
                lx.get();
                an.isvoid = true;
                return an;

            } else {
                err();
                return an;
            }
        } else if (lx.peek().getType() == TokenType::Coma) {
            lx.get();

        } else {
            err();
            return an;
        }
    }
    return an;
}

void SyntaxAnalysis::_global() {
    while (true) {
        auto tk = lx.get();

        if (tk.getType() == TokenType::End) {
            return;
        }

        if (tk.getType() == TokenType::KeyWord) {
            if (tk.getToken() == "import") {
                _import();
            } else if (tk.getToken() == "overld") {
                _overld_f();
            } else if (tk.getToken() == "var") {
                _gl_var();
            } else if (tk.getToken() == "struct") {
                _struct();
            } else {
                lx.error(tk.getToken().size(), false,
                         ("Invalid syntax: unexpected keyword " | bold() | fclr(255, 0, 0)) +
                         (tk.getToken() | bold() | underline1() | underline2() |
                          fclr(50, 130, 235)) + (" here:" | bold() | fclr(255, 0, 0)));
            }
        } else if (tk.getType() == TokenType::Identifier) {
            _func(tk.getToken());

        } else if (tk.getType() == TokenType::String) {
            // comment
        } else if (tk.getType() == TokenType::Semicolon) {

        } else {
            lx.error(tk.getToken().size(), false, ("Invalid syntax: unexpected token " | bold() | fclr(255, 0, 0)) +
                                                  (tk.getToken() | bold() | underline1() | underline2() |
                                                   fclr(50, 130, 235)) + (" here:" | bold() | fclr(255, 0, 0)));
        }
    }
}

void SyntaxAnalysis::_for() {
    auto name = lx.get();
    if (lx.peek().getType() != TokenType::Identifier) {
        err();
        return;
    }
    lx.get();
    if (lx.peek().getType() != TokenType::KeyWord || lx.peek().getToken() != "in") {
        err("expected in, got");

    }
    lx.get();
    semantic->forin(name.getToken());
    _expression("{", false);
    semantic->forstart();
    _scope();
    semantic->forend();

}

void SyntaxAnalysis::_while() {
    semantic->while_();
    lx.get();
    _expression("{", false);
    semantic->whilestart();
    _scope();
    semantic->whileend();
}

void SyntaxAnalysis::_if() {
    semantic->if_();
    lx.get();
    _expression("{", false);
    semantic->ifstart();
    _scope();
    semantic->ifend();
    while (lx.peek() == Lexem{TokenType::KeyWord, "elif"}) {
        lx.get();
        _expression("{", false);
        _scope();
    }
    if (lx.peek() == Lexem{TokenType::KeyWord, "else"}) {
        lx.get();
        _scope();
    }
}

void SyntaxAnalysis::_asm() {
    lx.get();
    if (lx.peek().getType() != TokenType::String) {
        err("expected asm code, got");
    }
    semantic->asm_(lx.get().getToken());

    if (lx.peek().getType() != TokenType::Semicolon) {
        err();
    } else {
        lx.get();
    }

}

Type SyntaxAnalysis::_get_type() {

    if (lx.peek().getType() != TokenType::Identifier && lx.peek().getType() != TokenType::Digit &&
        lx.peek().getType() != TokenType::HexDigit) {
        err("expected type or a number, got");
    }
    if (lx.peek().getType() == TokenType::Digit ||
        lx.peek().getType() == TokenType::HexDigit) {
        return {to_int(lx.get())};
    } else {
        return {-1, lx.get().getToken()};
    }
}

void SyntaxAnalysis::_local_var(bool start = true) {
    if (start) {
        semantic->start_var();
    }

    if (auto tk = lx.peek();tk.getType() == TokenType::Identifier) {
        semantic->add_var(lx.get().getToken());
        if (lx.peek().getType() == TokenType::Semicolon) {
            lx.get();
            semantic->end_var(0);
            return;
        } else if (lx.peek().getType() == TokenType::Coma) {
            lx.get();
            _local_var(false);
            return;
        } else if (lx.peek().getType() == TokenType::Colon) {
            lx.get();
            if(auto a=_get_type();a.type==-1){

                semantic->end_var(a.ind.value());
            }else{
                semantic->end_var(a.type);
            }
            if (lx.peek().getType() == TokenType::Semicolon) {
                lx.get();
                //semantic gl_var;
                return;
            }
            err();
            return;
        }
    }
    err();
}

void SyntaxAnalysis::_return() {
    lx.get();
    if (lx.peek().getType() == TokenType::Semicolon) {
        lx.get();
        semantic->return_();
        return;
    }
    if (lx.peek() == Lexem{TokenType::KeyWord, "with"}) {
        lx.get();
        _expression(";");
        semantic->return_();
        return;
    }
    err();

}

void SyntaxAnalysis::_suspend() {
    lx.get();
    if (lx.peek().getType() == TokenType::Semicolon) {
        lx.get();
        semantic->suspend();
        return;
    }
    if (lx.peek() == Lexem{TokenType::KeyWord, "with"}) {
        lx.get();
        _expression(";");
        semantic->suspend();
        return;
    }
    err();
}

void SyntaxAnalysis::_scope() {
    if (lx.peek() != Lexem{TokenType::Open, "{"}) {
        err();
    }
    lx.get();
    while (lx.peek() != Lexem{TokenType::Close, "}"}) {
        auto tk = lx.peek();
        switch (tk.getType()) {
            case TokenType::Open:
                if (tk.getToken() == "{") {
                    semantic->start_scope();
                    _scope();
                    semantic->end_scope();
                    break;
                }
            case TokenType::UBOperator:
            case TokenType::UOperator:
            case TokenType::Identifier:
            case TokenType::Digit:
            case TokenType::HexDigit:
            case TokenType::Float:
            case TokenType::HexFloat:
            case TokenType::SpecialWord:
            case TokenType::String:
                semantic->start_expr();
                _expression(";");
                semantic->end_expr();
                break;
            case TokenType::BOperator:
            case TokenType::Coma:
                err("invalid binary operator");
                lx.get();
                break;
            case TokenType::DColon:
                err("unrecognized namespace or class access operator");
                lx.get();
                break;
            case TokenType::End:
                err("Unexpected end of the file");
                lx.get();
                return;
            case TokenType::Colon:
            case TokenType::Close:
                err();
                lx.get();
                break;
            case TokenType::Semicolon:
                lx.get();
                break;
            case TokenType::KeyWord:
                if (tk.getToken() == "for") {
                    _for();
                } else if (tk.getToken() == "while") {
                    _while();
                } else if (tk.getToken() == "if") {
                    _if();
                } else if (tk.getToken() == "var") {
                    lx.get();
                    _local_var();
                } else if (tk.getToken() == "asm") {
                    _asm();
                } else if (tk.getToken() == "nullptr" || tk.getToken() == "true" || tk.getToken() == "false" ||
                           tk.getToken() == "undef" || tk.getToken() == "void") {
                    _expression(";");
                } else if (tk.getToken() == "return") {
                    _return();
                } else if (tk.getToken() == "suspend") {
                    _suspend();
                } else {
                    err("unexpected keyword");
                    lx.get();
                }
                break;
            case TokenType::Macros:
                lx.get();
                //WARNING
                break;
        }
    }
    lx.get();
}

void SyntaxAnalysis::_expression(const std::string &end, bool endian) {
    enum State {
        Start,
        Leaf,
        Binary

    } state{Start};
    while (lx.peek().getToken() != end) {
        switch (lx.peek().getType()) {
            case TokenType::Open:
                if (lx.peek().getToken() == "(") {
                    switch (state) {
                        case Start:
                            state = Leaf;
                            break;
                        case Leaf:
                            err();
                            break;
                        case Binary:
                            state = Leaf;
                            break;
                    }
                    semantic->expr(lx.get());
                    _expression(")");
                    break;
                } else if (lx.peek().getToken() == "[") {
                    switch (state) {
                        case Start:
                            _indexing();
                            state = Leaf;
                            break;
                        case Leaf:
                            err("unexpected start of indexing");
                            lx.get();
                            break;
                        case Binary:
                            _indexing();
                            state = Leaf;
                            break;
                    }
                } else {
                    err("starting scope in the expression");
                    lx.get();
                }
                break;
            case TokenType::Close:
                err("unexpected close bracket");
                lx.get();
                break;
            case TokenType::UBOperator:
                switch (state) {
                    case Start:
                        semantic->expr({TokenType::UOperator, lx.get().getToken()});
                        //semantic add expr unary
                        break;
                    case Leaf:
                        semantic->expr({TokenType::BOperator, lx.get().getToken()});
                        //semantic add expr binary
                        state = Binary;
                        break;
                    case Binary:
                        semantic->expr({TokenType::UOperator, lx.get().getToken()});
                        //semantic add expr unary
                        break;
                }
                break;
            case TokenType::UOperator:
                if (state == Leaf) {
                    err("unexpected unary operator");

                } else {
                    semantic->expr(lx.peek());
                }
                lx.get();
                break;
            case TokenType::Digit:
            case TokenType::HexDigit:
            case TokenType::Float:
            case TokenType::HexFloat:
            case TokenType::SpecialWord:
            case TokenType::String:
            case TokenType::Identifier:
                switch (state) {
                    case Start:
                        semantic->expr(lx.get());
                        //semantic add operand
                        state = Leaf;
                        break;
                    case Leaf:
                        err("expected binary operator or end of the expression");
                        lx.get();
                        break;
                    case Binary:
                        semantic->expr(lx.get());
                        //semantic add operand
                        state = Leaf;
                        break;
                }
                break;
            case TokenType::Coma:
            case TokenType::DColon:
            case TokenType::BOperator:
                switch (state) {
                    case Start:
                        err("unexpected binary operator");
                        lx.get();
                        break;
                    case Leaf:
                        semantic->expr({TokenType::BOperator, lx.get().getToken()});
                        //semantic add expr binary
                        state = Binary;
                        break;
                    case Binary:
                        err("unexpected binary operator");
                        lx.get();
                        break;
                }


                break;
            case TokenType::End:
                err("Unexpected end of the file");
                lx.get();
                return;
            case TokenType::Colon:
                err();
                lx.get();
                break;

            case TokenType::Semicolon:
                err();
                lx.get();
                break;
            case TokenType::KeyWord:
                if (lx.peek().getToken() == "nullptr" || lx.peek().getToken() == "true" ||
                    lx.peek().getToken() == "false" ||
                    lx.peek().getToken() == "undef" || lx.peek().getToken() == "void") {

                } else {
                    err();
                    lx.get();
                    break;
                }
                switch (state) {
                    case Start:
                        semantic->expr({TokenType::Identifier, lx.get().getToken()});
                        //semantic add operand
                        state = Leaf;
                        break;
                    case Leaf:
                        err("expected binary operator or end of the expression");
                        lx.get();
                        break;
                    case Binary:
                        semantic->expr({TokenType::Identifier, lx.get().getToken()});
                        //semantic add operand
                        state = Leaf;
                        break;
                }
                break;
            case TokenType::Macros:
                lx.get();
                //WARNING
                break;
        }
    }
    if(state==Binary){
        err("Unexpected end of expression");
    }
    if (endian) lx.get();
}

void SyntaxAnalysis::_struct() {

    if (lx.peek().getType() != TokenType::Identifier) {
        err("expected namespace name, got");
        return;
    }
    semantic->start_struct(lx.get().getToken());
    if (lx.peek() != Lexem{TokenType::Open, "{"}) {
        err("expected open bracket, got");
    } else {
        lx.get();
    }
    while (lx.peek() != Lexem{TokenType::Close, "}"}) {
        if (lx.get() != Lexem{TokenType::KeyWord, "var"}) {
            err();
        } else {
            _local_var();
        }
    }
    lx.get();
    semantic->end_struct();
}

void SyntaxAnalysis::_overld_f() {
    if (lx.peek() == Lexem{TokenType::Open, "("}) {
        lx.get();
    } else {
        err();
    }
    std::vector<Type> types;
    while (lx.peek() != Lexem{TokenType::Close, ")"}) {
        types.push_back(_get_type());
        if (lx.peek().getType() == TokenType::Coma) {
            lx.get();
        }
    }
    lx.get();
    if (lx.peek() == Lexem{TokenType::BOperator, "->"}) {
        lx.get();
    } else {
        err();
    }
    if (lx.peek().getType() == TokenType::Identifier) {

        semantic->overload(lx.get().getToken(), types);
    } else {
        err();
        return;
    }
    _scope();

}
