#-------------------------------------------------
#
# Project created by QtCreator 2011-05-11T11:00:39
#
#-------------------------------------------------

message(Using Qt $$[QT_VERSION] from $$[QT_INSTALL_PREFIX])

QT       += core gui xml svg 

macx {
    TARGET = "SVG-Converter-UI"
    ICON = gfx/svg2svgt.icns
}
!macx {
    TARGET = svg2svgt-gui
}
win32 {
    RC_FILE = svg2svgt.rc
}

TEMPLATE = app

TEMP_DIR = $$PWD/build-temp

DESTDIR = ../binaries

INCLUDEPATH += .

include(../common/common.pri)

SOURCES += main.cpp
SOURCES += existingfiledialog.cpp
SOURCES += mainwindow.cpp
SOURCES += aboutdialog.cpp
SOURCES += svglistitemdelegate.cpp
SOURCES += exportdialog.cpp
SOURCES += conversiontask.cpp
SOURCES += exporttask.cpp

HEADERS += mainwindow.h
HEADERS += existingfiledialog.h
HEADERS += aboutdialog.h
HEADERS += svglistitemdelegate.h
HEADERS += exportdialog.h
HEADERS += task.h
HEADERS += conversiontask.h
HEADERS += exporttask.h

FORMS   += mainwindow.ui
FORMS   += existingfiledialog.ui
FORMS   += aboutdialog.ui
FORMS   += exportdialog.ui

RESOURCES += icons.qrc
RESOURCES += translations.qrc

# Store temp-files out of the way
OBJECTS_DIR = $$TEMP_DIR
MOC_DIR = $$TEMP_DIR
RCC_DIR = $$TEMP_DIR
UI_DIR = $$TEMP_DIR

OTHER_FILES += svg2svgt.rc

TRANSLATIONS = svg2svgt_en.ts \
               svg2svgt_fi.ts


unix {
   INSTALLS += target
   target.path = ../install/usr/local/bin
}
