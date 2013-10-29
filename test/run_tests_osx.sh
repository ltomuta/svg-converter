#!/bin/sh

BIN=../binaries/svg2svgt.app
OUTDATA_DIR=testdata/output
TESTDATA_DIR=testdata/input
EXPECTDATA_DIR=testdata/expected

# Loop files in one directory:
test_dir() {
    # Figure out input directory, output directory, and
    # where to find the expect file.

    local in_dir=$1
    local out_dir=`echo $in_dir | sed s/input/output/`
    local exp_dir=`echo $in_dir | sed s/input/expected/`

    #rm -rf $out_dir
    #rm  $out_dir/*

    # Make sure output dir is available.
    mkdir -p $out_dir

    for file in $in_dir/*.svg; do tester "$file" $out_dir $exp_dir; done
}

# Test one file in a directory:
tester() { 
    # Figure out input file, output file and the expect file.
    local in=$1
    local out=$2/`basename $in`
    local exp=$3/`basename $in`

    echo "\nTesting:" $in

    if [ ! -e $exp ]; then
	echo "-- Skipping, expect file not found:" $exp
	return
    fi

    # Convert step
    open $BIN $in $out > /dev/null

    # xmllint converted output file
    xmllint --format --output $out.lint $out 2>$out.lintlog
    if [ `cat $out.lintlog | wc -c` -ne "0" ]; then
	echo "-- Error! xmllint found errors in the converted file, see" $out.lintlog
	return
    else
	rm $out.lintlog   # Remove empty log
    fi
    
    # xmllint expect file too
    xmllint --format --output $out.expect $exp  2>$out.expect.lintlog
    if [ `cat $out.expect.lintlog | wc -c` -ne "0" ]; then
	echo "-- Error! xmllint found errors in the expectation file, see" $out.expect.lintlog
	return
    else
	rm $out.expect.lintlog   # Remove empty log
    fi 

    # Simple diff between linted files
    diff -q $out.lint $out.expect
}

# Loop testdata directories:
for file in $TESTDATA_DIR/*; do test_dir $file; done



