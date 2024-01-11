cmake_minimum_required(VERSION 3.20)
project(compiler)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(compiler "lex.yy.cpp"
        unistd.h
        classes_functions.cpp
        classesnodes.h
        semantics/tools/datatype.cpp
        semantics/tools/datatype.h
        semantics/tables/fieldtable.cpp
        semantics/tables/fieldtable.h
        semantics/tables/vartable.cpp
        semantics/tables/vartable.h
        semantics/tools/tools.h
        semantics/tools/tools.cpp
        semantics/tables/methodtable.cpp
        semantics/tables/methodtable.h
        semantics/tables/classtable.cpp
        semantics/tables/classtable.h
        semantics/tables/constable.cpp
        semantics/tables/constable.h
        semantics/rtl/RTLContainer.cpp
        semantics/rtl/RTLContainer.h
        code_generation/command.h
        code_generation/tools/byte_convert.h
        code_generation/tools/byte_convert.cpp
        code_generation/tools/utils.h
        code_generation/code_generator.cpp
        code_generation/code_generator.h
)
