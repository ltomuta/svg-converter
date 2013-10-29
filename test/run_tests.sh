#!/bin/sh

BIN=../binaries/svg2svgt
OUTDATA_DIR=testdata/output
TESTDATA_DIR=testdata/input
#EXPECTDATA_DIR=testdata/expected


# Loop files in one directory:
test_dir() {
    # Figure out input directory, output directory, and
    # where to find the expect file.

    local in_dir=$1
    local out_dir=`echo $in_dir | sed s/input/output/`
    local exp_dir=`echo $in_dir | sed s/input/expected/`

    # Make sure output dir is availble:
    mkdir -p $out_dir

    for file in $in_dir/*.svg; do tester "$file" $out_dir $exp_dir; done
}

# Test one file in a directory:
tester() { 
    # Figure out input file, output file and the expect file.
    local in=$1
    local out_unmodified=$2/`basename $in`
    local out_linted=$2/`basename $in`.lint
    local out_lintlog=$2/`basename $in`.lintlog
    local exp=$3/`basename $in`
    local exp_linted=$2/`basename $in`.exp
    local exp_lintlog=$exp_linted.lintlog

    echo "\nTesting:" $out_unmodified

    # Convert step
    $BIN $in $out_unmodified > /dev/null

    # xmllint converted output file
    xmllint --format --output $out_linted $out_unmodified 2>$out_lintlog
    if [ `cat $out_lintlog | wc -c` -ne "0" ]; then
	echo "-- Error! xmllint found errors in the converted file, see" $out_lintlog
	return
    else
	rm $out_lintlog   # Remove empty log
    fi
    
    # xmllint expect file too, if available.
    if [ -e $exp ]; then
	xmllint --format --output $exp_linted $exp 2>$exp_lintlog
	if [ `cat $exp_lintlog | wc -c` -ne "0" ]; then
	    echo "-- Error! xmllint found errors in the expectation file, see" $exp_lintlog
	    return
	else
	    rm $exp_lintlog   # Remove empty log
	fi 
	
       # Simple diff between linted files
	diff -q $out_linted $exp_linted
    else
	echo "-- Expect file not found, diff skipped!"
    fi
}


echo "Test run" `date`

# Clean old output dir and make new.
if [ -d $OUTDATA_DIR ]; then
    echo "Cleaning old output..."
    rm -rf $OUTDATA_DIR
fi

# Loop testdata directories:
for file in $TESTDATA_DIR/*; do test_dir $file; done

