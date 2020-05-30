//
// Created by ahmed on 5/27/20.
//



#include "../headers/FwdRef.h"

FwdRef::FwdRef() = default;


FwdRef::FwdRef(int locCount, int base, bool e, bool x, int address, bool isBase) : locCnt(locCount), base(base), e(e), x(x), addr(address),
                          isBase(isBase){}
