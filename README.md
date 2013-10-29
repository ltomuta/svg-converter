SVG Converter 0.9.5
===================

## New features in this release

* GUI: Drag-and-drop addition of file to the export queue.
* GUI: Added initial English and Finnish localization files.
* GUI: Improved PNG export dialogue.
* Debian installation package for Ubuntu (installs files to  /usr/local/bin).
* Output XML file now contains a comment field with information about the converter.

## Fixed issues in this release

* GUI: Message, Errors, and Warnings are displayed correctly.
* GUI: File overwrite dialogue fixes.
* Filtering rules fix: Added 'tspan' element and 'style'-attribute for 'use' element.
* Many other small fixes.

## Known issues

 * Elements that are removed currently include the following: animation, audio, discard, font-face-src, solidColor, textArea
 * Elliptical arc conversion doesn't support paths that contain both absolute and relative arcs. Such cases are rare.
 * Export functionality uses the !QtSvg-module that supports SVG Tiny 1.2 and not the full SVG.
 * Debian installation doesn't provide desktop icon.

## Use instructions

See the online wiki: https://github.com/nokia-developer/svg-converter/wiki

## Source repository organisation

 * common: Converter engine code and the command line interface application.
 * gui: GUI application
 * test/testdata: This directory contains SVG images for testing. Some have been found using Google Image Search and some are from [http://www.openclipart.org].
 * test/s60: Series 60 test application. This application displays test SVG T images created by the converter. Scroll to next or previous image by use of the arrow keys or by touching the upper or lower half of the screen. There is an installation package in test/s60/svgtester/sis, which is compatible with S60 5th Edition and S^3 phones.

## Compiling

Compile with the following commands in the directory containing svg2svgt.pro: qmake && make. This will compile the command line application svg2svgt and the UI application  and place them in the binaries directory.

## Prerequisites

* Linux: Qt 4.7 or newer environment for compilation and running. 
* Windows: Qt SDK for compilation. No specific libraries needed for running.
* Mac OS X: Qt 4.7 framework for compilation. No specific libraries needed for running. 
* Symbian: S60 5th Edition or S^3 phone for running the test application.
