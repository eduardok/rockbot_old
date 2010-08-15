#!/bin/sh

cd ../game
make clean
make -f Makefile.ps2 clean
make -f Makefile.nds clean
make -f Makefile.ps2
cd ../packages
rm -r -f ./PS2
mkdir ./PS2
mkdir ./PS2/Rockbot
cp ../game/game.elf ./PS2/Rockbot/rockbot.elf
sh ../bin/pack_data.sh
cp -r ./data ./PS2/Rockbot
cd ./PS2
zip -r ../Rockbot_PS2.zip *
