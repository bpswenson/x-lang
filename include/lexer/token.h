//
// Created by brian on 4/20/18.
//

// based on swift front end

#pragma once

#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/StringSwitch.h>

#include "token_types.h"

namespace x {

class Token {
private:
    Tok _kind;
    bool _at_start_of_line = false;
    bool _escaped_identifier = false;
    bool _multi_line_string = false;
    u32 _comment_length;
    StringRef _text;

public:
    Token(Tok kind, StringRef text, u32 comment_length = 0) :
            _kind(kind), _at_start_of_line(false), _escaped_identifier(false),
            _multi_line_string(false), _comment_length(comment_length),
            _text(text) {}

    Token() :
            Token(Tok::NUM_TOKENS, {}) {}

    Tok get_kind() const { return _kind; }

    void set_kind(Tok k) { _kind = k; }

    bool is_kind(Tok k) const { return _kind == k; }

    bool is_not_kind(Tok k) const { return _kind != k; }

    bool is_any(Tok k) const {
        return is_kind(k);
    }

    template<typename ...TYPES>
    bool is_any(Tok k1, Tok k2, TYPES... K) const {
        if (is_any(k1))
            return true;
        return is_any(k2, K...);
    }

    template<typename ...TYPES>
    bool is_not_kind(Tok k, TYPES... K) const {
        return !is_any(k, K...);
    }

    bool is_binary_operator() const {
        return _kind == Tok::OPER_BINARY_SPACED || _kind == Tok::OPER_BINARY_UNSPACED;
    }

    bool is_any_operator() const {
        return is_binary_operator() || _kind == Tok::OPER_POSTFIX || _kind == Tok::OPER_PREFIX;
    }

    bool is_not_any_operator() const {
        return !is_any_operator();
    }

    bool is_ellipsis() const {
        return is_any_operator() && _text == "...";
    }

    bool is_not_ellipsis() const {
        return !is_ellipsis();
    }

    bool is_at_start_of_line() const { return _at_start_of_line; }

    void set_at_start_of_line(bool v) { _at_start_of_line = v; }

    bool is_escaped_identifier() const { return _escaped_identifier; }

    void set_escaped_identifier(bool v) {
        assert(_kind == Tok::IDENTIFIER);
        _escaped_identifier = v;
    }

    bool is_identifier_or_underscore() const {
        return is_any(Tok::IDENTIFIER);
    }
};

}