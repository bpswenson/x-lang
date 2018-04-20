cmake_minimum_required(VERSION 3.10)
project(xc)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(
        ${LLVM_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include

)
add_definitions(${LLVM_DEFINITIONS})

#break these up into multiple files later
set(HEADER_FILES
        include/base/color_utils.h
        include/base/types.h
        include/lexer/token.h
        include/lexer/token_types.h
        include/lexer/token_types.def
        )

set(SOURCE_FILES
        src/lexer/token.cc

        include/base/llvm_context.h include/base/allocator.h include/base/tree_scoped_hash_table.h)

add_library(xc ${HEADER_FILES} ${SOURCE_FILES})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(xc ${llvm_libs})

#########
# Test driver
#########

add_executable(tester main.cc ${HEADER_FILES})
target_link_libraries(tester xc)