cmake_minimum_required(VERSION 3.15)
project(PA_Final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PA_Final
    avltree.h
    catch.hpp
    document.cpp
    document.h
    documentparser.cpp
    documentparser.h
    fix.cpp
    fix.h
    hashtable.h
    index.h
    interactive.cpp
    interactive.h
    main.cpp
    maintenance.cpp
    maintenance.h
    query.cpp
    query.h
    stemmer.cpp
    stemmer.h
    term.cpp
    term.h
    test.cpp
    type2.cpp
    type2.h
    ui.cpp
    ui.h
    )
