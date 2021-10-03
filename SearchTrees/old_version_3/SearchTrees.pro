TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static

@
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_LFLAGS_RELEASE += -O3

QMAKE_CXXFLAGS += -static -static-libgcc -static-libstdc++
@

SOURCES += main.cpp \
    binarysearchtree.cpp \
    redblacktree.cpp \
    avltree.cpp \
    aatree.cpp \
    timer.cpp \
    treetest.cpp \
    randomvalue.cpp \
    treetest_template.cpp \
    treetesthelper.cpp \
    bsttree_template.cpp

HEADERS += \
    binarysearchtree.hh \
    redblacktree.hh \
    avltree.hh \
    aatree.hh \
    timer.hh \
    treetest.hh \
    randomvalue.hh \
    treetesthelper.hh \
    bsttree.hh \
    bstnode.hh \
    simplebstbalancer.hh \
    bsttrees.hh \
    redblackbalancer.hh

DISTFILES +=
