TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=  Main.cpp \
	    Cortical_Column.cpp \
	    Sleep_Regulation.cpp\
	    Cortex.cpp

HEADERS +=  \
	    ODE.h \
	    saves.h \
	    Cortical_Column.h \
	    Sleep_Regulation.h \
	    Stimulation.h

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES -= Cortex.cpp
