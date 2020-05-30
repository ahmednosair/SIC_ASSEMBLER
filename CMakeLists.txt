cmake_minimum_required(VERSION 3.16)
project(SIC_ASSEMBLER)

set(CMAKE_CXX_STANDARD 20)

add_executable(SIC_ASSEMBLER src/main.cpp src/Parser.cpp headers/Parser.h src/Inst.cpp headers/Inst.h src/Directive.cpp headers/Directive.h src/Exp.cpp headers/Exp.h src/Assembler.cpp headers/Assembler.h src/SymTable.cpp headers/SymTable.h src/SymEntry.cpp headers/SymEntry.h src/FwdRef.cpp headers/FwdRef.h src/TextRec.cpp headers/TextRec.h src/Util.cpp headers/Util.h src/ExpFwdRef.cpp headers/ExpFwdRef.h)