Svg2SvgT
========

Library and tools to convert SVG images to SVG Tiny, the subset of SVG implemented by QtSvg.

This is a fork of the stale https://github.com/microsoft-mobile/svg-converter, with the following improvements:
* CMake used as build system
* Builds with Qt5
* Provides a shared library
* Conformance to FHS for easy packaging

Usage:
------

Minimal library usage example:

    #include <svg2svgt/processorengine.h>
    #include <svg2svgt/ruleengine.h>
    #include <svg2svgt/logger.h>
    
    svg2svgt::Logger logger;
    svg2svgt::RuleEngine ruleEngine(logger);
    ruleEngine.setDefaultRules();
    svg2svgt::ProcessorEngine processor(ruleEngine, logger);
    
    QByteArray inputSvg = /* ... */;
    QByteArray outputSvgT = processor.process(inputSvg);

See also [cli/main.cpp](https://github.com/manisandro/svg2svgt/blob/master/cli/main.cpp).
