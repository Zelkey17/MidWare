cmake_minimum_required(VERSION 3.27)
project(Midware)


set(CMAKE_CXX_STANDARD 26)
add_executable(Midware main.cpp
        Lexical/LexicalAnalysis.cpp
        Lexical/LexicalAnalysis.h
        Lexical/Lexem.h
        IO/Reader.cpp
        IO/Reader.h
        IO/Writer.cpp
        IO/Writer.h
        IO/Colored.cpp
        Lexical/escape_chars.h
        Lexical/escape_chars.cpp
        Lexical/Lexem.cpp
        Syntax/Syntax.h
        Syntax/LexicalAnalysisReader.cpp
        Syntax/LexicalAnalysisReader.h
        Syntax/Syntax.cpp
        Semantic/Semantic.cpp
        Semantic/Semantic.h
        Semantic/utils.h
        Semantic/Scoped_set.cpp
        Semantic/Scoped_set.h
        Semantic/expression.cpp
        Semantic/expression.h
        Semantic/var_data.cpp
        Semantic/var_data.h
        asm/vars.c
        asm/gen_switch.cpp

        asm/gen_func.cpp
        Generating/Semantic_reader.cpp
        Generating/Semantic_reader.h
        asm/exprs.cpp)
