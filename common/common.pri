QT          += core xml

VERSION = 0.2.1

# Store temp-files out of the way
OBJECTS_DIR = $$TEMP_DIR
MOC_DIR = $$TEMP_DIR
RCC_DIR = $$TEMP_DIR
UI_DIR = $$TEMP_DIR

INCLUDEPATH += $$PWD

# Headers
HEADERS += $$PWD/logger.h
HEADERS += $$PWD/tracer.h
HEADERS += $$PWD/statisticsprocessorstep.h
HEADERS += $$PWD/ruleengine.h
HEADERS += $$PWD/processorengine.h
HEADERS += $$PWD/processorstep.h
HEADERS += $$PWD/errorcodes.h
HEADERS += $$PWD/nodefilterstep.h
HEADERS += $$PWD/cmdlineparser.h
HEADERS += $$PWD/gradientprocessorstep.h
HEADERS += $$PWD/opacityconverterstep.h
HEADERS += $$PWD/emptynoderemoverstep.h
HEADERS += $$PWD/nodewalker.h
HEADERS += $$PWD/nodefinder.h
HEADERS += $$PWD/validationstep.h
HEADERS += $$PWD/pathconverterstep.h
HEADERS += $$PWD/fillconverterstep.h
HEADERS += $$PWD/stylesheetconverterstep.h

# Sources
SOURCES += $$PWD/cmdlineparser.cpp
SOURCES += $$PWD/ruleengine.cpp
SOURCES += $$PWD/validationstep.cpp
SOURCES += $$PWD/nodefilterstep.cpp
SOURCES += $$PWD/gradientprocessorstep.cpp
SOURCES += $$PWD/processorengine.cpp
SOURCES += $$PWD/opacityconverterstep.cpp
SOURCES += $$PWD/emptynoderemoverstep.cpp
SOURCES += $$PWD/statisticsprocessorstep.cpp
SOURCES += $$PWD/nodefinder.cpp
SOURCES += $$PWD/logger.cpp
SOURCES += $$PWD/tracer.cpp
SOURCES += $$PWD/pathconverterstep.cpp
SOURCES += $$PWD/fillconverterstep.cpp
SOURCES += $$PWD/stylesheetconverterstep.cpp

# Resources
RESOURCES += $$PWD/rules.qrc
OTHER_FILES += $$PWD/rules.xml
