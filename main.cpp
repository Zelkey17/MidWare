#include<optional>
#include<variant>
#include"IO/Writer.h"
#include"IO/Reader.h"
#include"Lexical/LexicalAnalysis.h"
#include"Syntax/Syntax.h"
#include<bits/stdc++.h>
#include <sys/mman.h>
#include "Semantic/expression.h"
#include "asm/_memory/_malloc.cpp"
#include "asm/gen_switch.cpp"
#include "asm/start.cpp"


using namespace std;

int main(int argc, char *argv[]) {
    vector<pair<int,std::string>> arr{{1,"mov $1, %rax"},
                                      {12,"mov $12, %rax"},
                                      {13,"mov $13, %rax"},
                                      {14,"mov $14, %rax"},
                                      {15,"mov $15, %rax"},
                                      {16,"mov $16, %rax"},
                                      {17,"mov $17, %rax"},
                                      {187,"mov $187, %rax"},
                                      {-12,"mov $-12, %rax"},
                                      {-13,"mov $-13, %rax"},
                                      {-14,"mov $-14, %rax"},
                                      {-17,"mov $-17, %rax"},
                                      {-18,"mov $-18, %rax"},
                                      {-132,"mov $-132, %rax"},
                                      {-1456,"mov $-1456, %rax"},
                                      {-17,"mov $-17, %rax"}};
    std::cout<<gen_switch(arr,"nop","switch","%rsi").str();

}