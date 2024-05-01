//
// Created by ash on 15.02.24.
//

#ifndef MIDWARE_LEXICALANALYSIS_H
#define MIDWARE_LEXICALANALYSIS_H


#include <iostream>
#include "Lexem.h"
#include "../IO/Reader.h"
#include "../IO/Colored.h"
#include <utility>
#include <fstream>
#include "escape_chars.h"

class LexicalAnalysis {
public:
    explicit LexicalAnalysis(const Reader &rd);

    explicit LexicalAnalysis(std::string file);

    Lexem get();

    void error(int s, bool k, const std::string &,bool g=true);

private:
    Reader rd;

    void _error(int str, int st, int cnt, bool k = false);

    Lexem _start(std::string *str);


    const static std::string kw[];
    const static std::string sw[];
};



#endif //MIDWARE_LEXICALANALYSIS_H
