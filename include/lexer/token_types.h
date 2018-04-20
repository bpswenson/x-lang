//
// Created by brian on 4/20/18.
//

#pragma once

#include "base/types.h"

namespace x {

enum class Tok {
#define TOKEN(X) X,

#include "token_types.def"

    NUM_TOKENS
};

bool is_token_text_determined(Tok type);

StringRef get_token_type(Tok kind);

}
