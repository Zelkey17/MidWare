//
// Created by ash on 28.02.24.
//

#ifndef MIDWARE_SYNTAX_H
#define MIDWARE_SYNTAX_H

#include <utility>
#include<cassert>

#include "LexicalAnalysisReader.h"
#include "../Semantic/Semantic.h"

class SyntaxAnalysis {
public:

    explicit SyntaxAnalysis(LexicalAnalysis a, Semantic *sem) : lx(std::move(a)), semantic(sem) {
        assert(sem);
        sem->lx=&lx;
    }

    explicit SyntaxAnalysis(LexicalAnalysisReader a, Semantic *sem) : lx(std::move(a)), semantic(sem) {
        assert(sem);
        sem->lx=&lx;
    }

    SyntaxAnalysis(std::string str, Semantic *sem) : lx(std::move(str)), semantic(sem) {
        assert(sem);
        sem->lx=&lx;
    }

    void analyze() {
        _global();
    }

private:
    LexicalAnalysisReader lx;
    Semantic *semantic;

    void err();

    void err(const std::string &str);

    void _import();

    void _gl_var();

    void _func_body();

    void _indexing();

    void _func(const std::string &f_name);

    spec _get_spec();

    void _global();

    void _for();

    void _while();

    //TODO
    void _if();

    void _asm();

    Type _get_type();

    void _local_var(bool);

    void _return();

    void _suspend();

    void _scope();

    ////TODO
    void _expression(const std::string &end, bool endian = true);

    void _overld_f();

    void _struct();

};

#endif //MIDWARE_SYNTAX_H
