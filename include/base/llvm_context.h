//
// Created by brian on 4/20/18.
//

#pragma once

namespace llvm {
class LLVMContext;
}

namespace x {

llvm::LLVMContext &get_global_llvm_context();

}
