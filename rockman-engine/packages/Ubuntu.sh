#/usr/bin
cd ubuntu/game
rm -r -f ./debian/opt/rockbot
mkdir -p ./debian/opt/rockbot
rm -r -f ./debian/opt/rockbot/data
cp -R ../../data ./debian/opt/rockbot
cp ../../../bin/rockbot ./debian/opt/rockbot/
mkdir -p ./debian/DEBIAN
cp ../../control ./debian/DEBIAN

dpkg-deb --build debian/ ../../Rockbot_0.1b6.deb
