set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

SET(svg2svgt_SRCS
  ruleengine.cpp
  validationstep.cpp
  nodefilterstep.cpp
  gradientprocessorstep.cpp
  processorengine.cpp
  opacityconverterstep.cpp
  emptynoderemoverstep.cpp
  statisticsprocessorstep.cpp
  nodefinder.cpp
  logger.cpp
  tracer.cpp
  pathconverterstep.cpp
  fillconverterstep.cpp
  stylesheetconverterstep.cpp
)

SET(svg2svgt_HDRS
  logger.h
  tracer.h
  statisticsprocessorstep.h
  ruleengine.h
  processorengine.h
  processorstep.h
  errorcodes.h
  nodefilterstep.h
  gradientprocessorstep.h
  opacityconverterstep.h
  emptynoderemoverstep.h
  nodewalker.h
  nodefinder.h
  validationstep.h
  pathconverterstep.h
  fillconverterstep.h
  stylesheetconverterstep.h
)

SET(svg2svgt_RESOURCES rules.qrc)
QT5_ADD_RESOURCES(svg2svgt_RESOURCES_RCC ${svg2svgt_RESOURCES})

ADD_DEFINITIONS(-DSVG2SVGT_VERSION=\"${SVG2SVGT_VERSION}\")

SET(SVG2SVGT_LIB_VERSION ${SVG2SVGT_MAJOR}.${SVG2SVGT_MINOR}.0)
SET(SVG2SVGT_SO_VERSION ${SVG2SVGT_MAJOR})

ADD_LIBRARY(svg2svgt SHARED ${svg2svgt_SRCS} ${svg2svgt_HDRS} ${svg2svgt_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(svg2svgt Qt5::Widgets Qt5::Xml Qt5::XmlPatterns)
SET_TARGET_PROPERTIES(svg2svgt PROPERTIES VERSION ${SVG2SVGT_LIB_VERSION} SOVERSION ${SVG2SVGT_SO_VERSION})
IF(MINGW)
    SET_TARGET_PROPERTIES(svg2svgt PROPERTIES SUFFIX "-${SVG2SVGT_SO_VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX}")
ENDIF(MINGW)

CONFIGURE_FILE(svg2svgt.pc.in svg2svgt.pc @ONLY)

INSTALL(TARGETS svg2svgt
    RUNTIME DESTINATION bin COMPONENT libraries
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT libraries
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT libraries
)

INSTALL(FILES ${svg2svgt_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR}/svg2svgt)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/svg2svgt.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)
INSTALL(FILES ${svg2svgt_QM} DESTINATION share/${QT_VER}/translations)
