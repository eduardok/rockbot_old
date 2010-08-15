#!/bin/sh

cd ../game
make clean
make
cd ../packages
rm -r -f ./linux
mkdir ./linux
cp ./docs/README.LINUX.TXT ./linux/README.TXT
cp ../bin/rockbot ./linux
cp ../bin/editor ./linux
sh ../bin/pack_data.sh
cp -r ./data ./linux
cd ./linux
tar -cvf ../rockbot_linux.tar *
gzip ../rockbot_linux.tar
