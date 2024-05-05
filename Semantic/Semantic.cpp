//
// Created by ash on 12.03.24.
//

#include "Semantic.h"
#include "../Syntax/Syntax.h"

void Semantic::main(std::string str) {
    SyntaxAnalysis(str, this).analyze();
}

void Semantic::start_indexing() {
    std::cout << "start_indexing() " << std::endl;
}

void Semantic::end_indexing() {
    std::cout << "end_indexing() " << std::endl;
}

void Semantic::forin(const std::string &name) {
    if (func.contains(func_data{name}) ||
        local_f.top().contains(func_data{name}) ||
        vars.check(var_data{name})) {
        error("Semantic error: this name is busy" );
    } else
        vars.add(var_data{name});
}

void Semantic::forstart() {
    std::cout << "forstart() " << std::endl;
}

void Semantic::forend() {
    std::cout << "forend() " << std::endl;
}

void Semantic::if_() {
    std::cout << "if_() " << std::endl;
}

void Semantic::start_space(const std::string &space) {
    std::cout << "start_space() " << space << std::endl;
}

void Semantic::end_space() {
    std::cout << "end_space() " << std::endl;
}

void Semantic::create_gl_var(const std::string &name) {
    if (func.contains(func_data{name}) ||
        local_f.top().contains(func_data{name}) ||
        vars.check(var_data{name})) {
        error("Semantic error: this name is busy");
    } else
        vars.add(var_data{name});
}

void Semantic::start_func(const std::string &name, spec sp) {
    if (sp.local.value_or(false)) {
        if (func.contains(func_data{name}) ||
            local_f.top().contains(func_data{name}) ||
            vars.check(var_data{name})) {
            error("Semantic error");
        } else
            local_f.top().insert(func_data{name, sp});
    } else {
        if (func.contains(func_data{name}) ||
            local_f.top().contains(func_data{name}) ||
            vars.check(var_data{name})) {
            error("Semantic error");
        } else
            func.insert(func_data{name, sp});
    }
}

void Semantic::start_func_body() {
    std::cout << "start_func_body() " << std::endl;
}


void Semantic::import_(const std::string &lib) {
    local_f.emplace();
    auto prev = lx;
    SyntaxAnalysis(lib, this).analyze();
    lx = prev;
    local_f.pop();
}

void Semantic::while_() {
    std::cout << "while_() " << std::endl;
}

void Semantic::whilestart() {
    std::cout << "whilestart() " << std::endl;
}

void Semantic::whileend() {
    std::cout << "whileend() " << std::endl;
}

void Semantic::ifstart() {
    std::cout << "ifstart() " << std::endl;
}

void Semantic::ifend() {
    std::cout << "ifend() " << std::endl;
}

void Semantic::asm_(std::string basicString) {
    std::cout << "asm_() " << basicString << std::endl;
}

void Semantic::start_scope() {
    vars.add_scope();
}

void Semantic::end_scope() {
    vars.end_scope();
}

void Semantic::start_expr() {
    std::cout << "start_expr() " << std::endl;
}

void Semantic::end_expr() {
    std::cout << "end_expr() " << std::endl;
}

void Semantic::expr(Lexem lexem) {
    std::cout<<lexem.getToken()<<" ";
    if (lexem.getType() == TokenType::Identifier) {
        if (func.contains(func_data{lexem.getToken()}) ||
            local_f.top().contains(func_data{lexem.getToken()}) ||
            vars.check(var_data{lexem.getToken()})) {

        } else {
            error("Semantic error");
        }
    }
}

void Semantic::start_var() {
    std::cout << "start_var" << std::endl;
}

void Semantic::add_var(std::string name) {
    if (func.contains(func_data{name}) ||
        local_f.top().contains(func_data{name}) ||
        vars.check(var_data{name})) {
        error("Semantic error");
    } else {
        vars.add(var_data{std::move(name)});
    }
}

void Semantic::end_var(std::string typ) {

    if (!types.contains(type{typ})) {
        error("Semantic error");
    }
}

void Semantic::end_var(int typ) {

    //if(!types.contains(type{typ}));
}

void Semantic::return_() {

    std::cout << "return" << std::endl;
}

void Semantic::suspend() {

    std::cout << "suspend" << std::endl;
}

void Semantic::start_struct(std::string typ) {

    types.insert(type{std::move(typ)});
    vars.add_scope();
}

void Semantic::end_struct() {

    std::cout << "end struct" << std::endl;
    vars.end_scope();
}

void Semantic::overload(const std::string &name, const std::vector<Type> &type) {
    for (Type t: type) {
        if (t.type == -1) {
            if (!types.contains({t.ind.value()})) {
                error("Semantic error");
            }
        }
    }
    if (auto it = func.find(func_data{name});it != func.end()) {
        if (it->sp.overld.has_value() && it->sp.overld.value()) {

        } else {
            error("Semantic error");
        }
        return;
    }
    if (auto it = local_f.top().find(func_data{name});it != local_f.top().end()) {
        if (it->sp.overld.has_value() && it->sp.overld.value()) {

        } else {
            error("Semantic error");
        }
        return;
    }
    error("Semantic error");
}

void Semantic::error(const std::string& str) {
    fail();
    lx->error(0, true,
             (str + " " | bold() | fclr(255, 0, 0))
            + ("here:" | bold() | fclr(255, 0, 0)));
}

Semantic::Semantic() {
    local_f.emplace();
}

void Semantic::end_func_body() {

}
