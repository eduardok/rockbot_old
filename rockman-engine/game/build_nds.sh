cp ../bin/data/sfx/*.wav ./maxmod_data/
make clean
make -f Makefile.ps2 clean
make -f Makefile.nds clean
make -f Makefile.nds
cp ./rockbot.nds ../bin/
