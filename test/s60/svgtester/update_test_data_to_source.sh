#!/bin/sh

# This script attempts to update some parts of the S60 UI application sources
# so that all testdata icons are used there.

#IN=../../testdata/input

find ../../testdata/input/ -type f | sed 's/^.*input\//$(IN)\\/' | sed 's/\//\\/' | sed 's/$/ \\/' 
