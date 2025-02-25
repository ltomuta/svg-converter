SET(svg2svgt-gui_SRCS
  aboutdialog.cpp
  conversiontask.cpp
  existingfiledialog.cpp
  exportdialog.cpp
  exporttask.cpp
  main.cpp
  mainwindow.cpp
  svglistitemdelegate.cpp
)

SET(svg2svgt-gui_HDRS
  aboutdialog.h
  conversiontask.h
  existingfiledialog.h
  exportdialog.h
  exporttask.h
  mainwindow.h
  svglistitemdelegate.h
  task.h
)

FILE(GLOB svg2svgt-gui_FORMS *.ui)
FILE(GLOB svg2svgt-gui_RESOURCES *.qrc)

IF(MINGW)
  ENABLE_LANGUAGE(RC)
  SET(CMAKE_RC_COMPILER_INIT ${CMAKE_GENERATOR_RC})
  SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> -O coff -i <SOURCE> -o <OBJECT>")
  LIST(APPEND svg2svgt-gui_SRCS svg2svgt.rc)
ENDIF(MINGW)

QT5_WRAP_UI(svg2svgt-gui_FORMS_HEADERS ${svg2svgt-gui_FORMS})
QT5_ADD_RESOURCES(svg2svgt-gui_RESOURCES_RCC ${svg2svgt-gui_RESOURCES})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(svg2svgt-gui ${svg2svgt-gui_SRCS} ${svg2svgt-gui_HDRS} ${svg2svgt-gui_FORMS_HEADERS} ${svg2svgt-gui_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(svg2svgt-gui Qt5::Widgets Qt5::Svg svg2svgt)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
IF(MINGW)
  TARGET_LINK_LIBRARIES(svg2svgt-gui -mwindows)
ENDIF(MINGW)


INSTALL(TARGETS svg2svgt-gui DESTINATION bin)
INSTALL(FILES gfx/svg2svgt.png DESTINATION share/icons/hicolor/64x64/apps/)
INSTALL(FILES gfx/svg2svgt.svg DESTINATION share/icons/hicolor/scalable/apps/)
INSTALL(FILES svg2svgt.appdata.xml DESTINATION share/metainfo)
INSTALL(FILES svg2svgt.desktop DESTINATION share/applications)
