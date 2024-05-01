//
// Created by ash on 29.02.24.
//

#ifndef MIDWARE_LEXICALANALYSISREADER_H
#define MIDWARE_LEXICALANALYSISREADER_H

#include <utility>
#include <optional>
#include"../Lexical/LexicalAnalysis.h"

class LexicalAnalysisReader {
public:
    explicit LexicalAnalysisReader(std::string str);

    explicit LexicalAnalysisReader(LexicalAnalysis lx);

    Lexem get();

    Lexem peek();

    void error(size_t s,int k,const std::string& t,bool g=true);

private:
    LexicalAnalysis lx;
    std::optional<Lexem> buf;
};


#endif //MIDWARE_LEXICALANALYSISREADER_H
