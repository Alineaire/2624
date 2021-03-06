#!/bin/bash
ACTUALDIR=$(pwd)
DIR=$(dirname $0)

cd $DIR

amixer cset numid=3 1

sudo ./bin/Release/2624 --led-rows=16 --led-cols=32 --led-chain=4 --led-gpio-mapping=adafruit-hat -f "./fonts/5x8.bdf" -s "./Scenario - Scenario.tsv" -l "./Scenario - Loc.tsv"

cd $ACTUALDIR