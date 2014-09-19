#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T15:29:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = ANNmt

TEMPLATE = lib

OBJECTS_DIR = $$OUT_PWD/out
MOC_DIR = $$OUT_PWD/out
RCC_DIR = $$OUT_PWD/out
UI_DIR = $$OUT_PWD/out
win32 { # it is strange that in windows the output folder for the obj file cannot be created. There may be some bugs in the pro file.
    message($${OBJECTS_DIR})
    MKOUTDIR = $$OUT_PWD/out
    MKOUTDIR ~= s,/,\\,g
    !exists(OBJECTS_DIR) : system(mkdir $$MKOUTDIR)
}

INCLUDEPATH += ./include

SOURCES += $$files(./src/*.cpp)

HEADERS += $$files(./include/ANNmt/*)

QMAKE_CXXFLAGS += -O2 -Wall -Wno-deprecated -pthread -mfpmath=sse -fpermissive -shared

macx | linux-g++* {
QMAKE_LFLAGS += -fPIC -march=native
}

win32 {
    DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
    CONFIG -= lex yacc rtti_off \
              exceptions_off stl_off incremental_off thread_off \
              link_prl copy_dir_files \
              debug_and_release_target \ # this flag is important to remove redundant build folder in the output directory.
              precompile_header ltcg exceptions debug_and_release
}
win32-g++ {
    QMAKE_CXXFLAGS += -Werror=return-type -Werror=ignored-qualifiers
}
