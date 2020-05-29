//
// Created by ahmed on 5/29/20.
//

#include "ExpFwdRef.h"

ExpFwdRef::ExpFwdRef() = default;

ExpFwdRef::ExpFwdRef(int locCnt, int base, bool e, bool x, int addr, bool isBase, const Exp &exp) : locCnt(locCnt),
                                                                                                    base(base), e(e),
                                                                                                    x(x), addr(addr),
                                                                                                    isBase(isBase),
                                                                                                    exp(exp) {}
