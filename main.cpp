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
    Semantic sem;
    sem.main("../example.wdr");

}