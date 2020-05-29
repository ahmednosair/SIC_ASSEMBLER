cmake_minimum_required(VERSION 3.16)
project(SIC_ASSEMBLER)

set(CMAKE_CXX_STANDARD 20)

add_executable(SIC_ASSEMBLER main.cpp Parser.cpp Parser.h Inst.cpp Inst.h Directive.cpp Directive.h Exp.cpp Exp.h Assembler.cpp Assembler.h SymTable.cpp SymTable.h SymEntry.cpp SymEntry.h FwdRef.cpp FwdRef.h TextRec.cpp TextRec.h Util.cpp Util.h ExpFwdRef.cpp ExpFwdRef.h)