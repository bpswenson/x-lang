//
// Created by brian on 4/20/18.
//

#pragma once

#include <utility>
#include <llvm/ADT/DenseMap.h>
#include <llvm/Support/Allocator.h>
#include "base/allocator.h"


namespace x {


template<typename K, typename V, typename AllocatorTy = llvm::MallocAllocator>
class TreeScopedHashTable;

template<typename K, typename V, typename AllocatorTy = llvm::MallocAllocator>
class TreeScopedHashTableScope;

template<typename K, typename V>
class TreeScopedHashTableVal {
private:
    TreeScopedHashTableVal *_next_in_scope;
    TreeScopedHashTableVal *_next_for_key;
    K _key;
    V _value;

    TreeScopedHashTableVal(const K &key, const V &val) : _key(key), _value(val) {}

public:
    const K &get_key() const { return _key; }

    const V &get_value() const { return _value; }

    V &get_value() { return _value; }

    TreeScopedHashTableVal *get_next_for_key() { return _next_for_key; }

    const TreeScopedHashTableVal *get_next_for_key() const { return _next_for_key; }

    template<typename AllocatorTy>
    static TreeScopedHashTableVal *create(TreeScopedHashTableVal *next_in_scope, TreeScopedHashTableVal *next_for_key,
                                          const K &key, const V &val, AllocatorTy &allocator) {
        TreeScopedHashTableVal *new_val = allocator.template Allocate<TreeScopedHashTableVal>();

        new(new_val) TreeScopedHashTableVal(key, val);
        new_val->_next_in_scope = next_in_scope;
        new_val->_next_for_key = next_for_key;
        return new_val;
    }

    template<typename AllocatorTy>
    void destroy(AllocatorTy &allocator) {
        this->~TreeScopedHashTableVal();
        allocator.Deallocate(this);
    }
};

template<typename K, typename V, typename AllocatorTy = llvm::MallocAllocator>
class TreeScopedHashTableScopeImpl {
public:
    using HTTy = TreeScopedHashTable<K, V, AllocatorTy>;
    HTTy *ht;
};

}
