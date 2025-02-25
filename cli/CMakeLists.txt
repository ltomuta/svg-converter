SET(svg2svgt-cli_SRCS
  main.cpp
  cmdlineparser.cpp
)

SET(svg2svgt-cli_HDRS
  cmdlineparser.h
)

ADD_EXECUTABLE(svg2svgt-cli ${svg2svgt-cli_SRCS} ${svg2svgt-cli_HDRS})
TARGET_LINK_LIBRARIES(svg2svgt-cli Qt5::Widgets svg2svgt)
SET_TARGET_PROPERTIES(svg2svgt-cli PROPERTIES OUTPUT_NAME svg2svgt)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})


INSTALL(TARGETS svg2svgt-cli DESTINATION bin)
