#-------------------------------------------------
#
# Project created by QtCreator 2011-04-04T12:54:00
#
#-------------------------------------------------


QT       += core xml
QT       -= gui

macx {
    ICON = ../gui/gfx/svg2svgt.icns
}
win32 {
    RC_FILE = ../gui/svg2svgt.rc
}

TARGET = svg-converter
CONFIG   += console

# DEBUG BUILD:
#CONFIG   += debug 

TEMPLATE = app
DESTDIR = ../binaries

include(common.pri)
SOURCES += main.cpp

INCLUDEPATH += .

# Store temp-files out of the way
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp

win32 {
    OTHER_FILES += test/run_tests.bat
    QMAKE_EXTRA_TARGETS += testrun
    testrun.commands = cd test && run_tests.bat
} else:unix {
    OTHER_FILES += test/run_tests.sh
    QMAKE_EXTRA_TARGETS += testrun
    testrun.commands = cd test && sh run_tests.sh
}

unix {
   INSTALLS += target
   target.path = ../install/usr/local/bin
}

message(Using Qt $$[QT_VERSION] from $$[QT_INSTALL_PREFIX])
