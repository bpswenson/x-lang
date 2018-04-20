//
// Created by brian on 4/20/18.
//
// This source file was originally part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//



#pragma once

#include <llvm/Support/raw_ostream.h>

#include "types.h"

namespace x {

using llvm::raw_ostream;

class OSColor {
private:
    raw_ostream &os;
    bool _has_colors;

public:
    OSColor(raw_ostream &os, raw_ostream::Colors color) :
            os(os) {

        _has_colors = os.has_colors();
    }

    ~OSColor() {
        if (_has_colors) {
            os.resetColor();
        }
    }

    OSColor &operator<<(char c) {
        os << c;
        return *this;
    }

    OSColor &operator<<(StringRef str) {
        os << str;
        return *this;
    }
};
}

