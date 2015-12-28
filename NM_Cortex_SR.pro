TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET =    Cortex_SR.cpp

SOURCES +=  Cortex_SR.cpp       \
            Cortex_SR_mex.cpp   \
            Cortical_Column.cpp \
            Sleep_Regulation.cpp

HEADERS +=  Cortical_Column.h   \
            Data_Storage.h      \
            ODE.h               \
            Random_Stream.h     \
            Sleep_Regulation.h

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES -= Cortex_SR_mex.cpp
