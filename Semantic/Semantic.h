//
// Created by ash on 12.03.24.
//

#ifndef MIDWARE_SEMANTIC_H
#define MIDWARE_SEMANTIC_H

#include<string>
#include <optional>
#include <vector>
#include <set>
#include "../Lexical/Lexem.h"
#include"Scoped_set.h"
#include "expression.h"
#include "../Syntax/LexicalAnalysisReader.h"


struct Type {
    int type = 0;
    std::optional<std::string> ind;
};


class Semantic {
public:
    Semantic();

    void import_(const std::string &lib);

    void fail() {
        _fail = true;
    }

    void start_space(const std::string &space);

    void end_space();

    void create_gl_var(const std::string &basicString);

    void start_func(const std::string &, spec sp = {});

    void start_func_body();

    void main(std::string str);

    void start_indexing();

    void end_indexing();

    void forin(const std::string &basicString); //do this

    void forstart();

    void forend();

    void if_();

    void while_();

    void whilestart();

    void whileend();

    void ifstart();

    void ifend();

    void asm_(std::string basicString);

    void expr(Lexem lexem);

    void start_scope();

    void end_scope();

    void start_expr();

    void end_expr();

    void start_var();

    void add_var(std::string basicString);

    void end_var(std::string type);

    void end_var(int type);

    void return_();

    void suspend();

    void start_struct(std::string basicString);

    void end_struct();

    void overload(const std::string &basicString, const std::vector<Type> &vector1);

    void error(const std::string &);

    LexicalAnalysisReader *lx;

    void end_func_body();

private:

    bool _fail = false;

    std::set<type> types{};
    std::stack<std::set<func_data>> local_f{{}};
    std::set<func_data> func{};
    scoped_set<var_data> vars{};

};


#endif //MIDWARE_SEMANTIC_H
