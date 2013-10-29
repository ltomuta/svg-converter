TEMPLATE      = subdirs
SUBDIRS       = common \
                gui

unix {
   QMAKE_EXTRA_TARGETS += deb
   deb.commands = dpkg -b install svgconverter.deb
}
