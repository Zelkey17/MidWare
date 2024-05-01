//
// Created by ash on 29.02.24.
//

#include "LexicalAnalysisReader.h"

LexicalAnalysisReader::LexicalAnalysisReader(std::string str) : lx(std::move(str)), buf() {

}

Lexem LexicalAnalysisReader::get() {
    if(buf.has_value()){
        Lexem ans=buf.value();
        buf.reset();
        return ans;
    }else{
        return lx.get();
    }
}

Lexem LexicalAnalysisReader::peek() {
    if(buf.has_value()){
        return buf.value();
    }else{
        buf=lx.get();
        return buf.value();
    }
}

LexicalAnalysisReader::LexicalAnalysisReader(LexicalAnalysis lx) :lx(std::move(lx)),buf(){}

void LexicalAnalysisReader::error(size_t s, int k, const std::string &t,bool g) {

    lx.error(s,k,t,g);
}
