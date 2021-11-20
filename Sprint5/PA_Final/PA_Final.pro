TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        document.cpp \
        documentparser.cpp \
        fix.cpp \
        interactive.cpp \
        main.cpp \
        maintenance.cpp \
        query.cpp \
        stemmer.cpp \
        term.cpp \
        test.cpp \
        type2.cpp \
        ui.cpp

HEADERS += \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/indexing/common_lang_constants.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/indexing/string_util.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/danish_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/dutch_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/english_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/finnish_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/french_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/german_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/italian_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/norwegian_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/portuguese_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/russian_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/spanish_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/stemming.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/swedish_stem.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/utilities/debug_logic.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/utilities/safe_math.h \
    ../../lib/OleanderStemmingLibrary-master/include/olestem/utilities/utilities.h \
    ../../lib/english_stem.h \
    avltree.h \
    catch.hpp \
    document.h \
    documentparser.h \
    fix.h \
    hashtable.h \
    index.h \
    interactive.h \
    maintenance.h \
    query.h \
    stemmer.h \
    term.h \
    type2.h \
    ui.h
