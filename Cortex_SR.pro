TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = Cortex.cpp

SOURCES +=  Cortex.cpp \
	    Cortex_mex.cpp \
	    Cortical_Column.cpp \
	    Sleep_Regulation.cpp


HEADERS +=  Cortical_Column.h \
	    ODE.h \
	    saves.h \
	    Sleep_Regulation.h

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES -= Cortex_mex.cpp
