#/usr/bin
cd ubuntu/editor
rm -r -f ./debian/opt/rockbot
mkdir -p ./debian/opt/rockbot
cp ../../../bin/editor ./debian/opt/rockbot/editor
mkdir -p ./debian/DEBIAN
cp ../../control_editor ./debian/DEBIAN/control

dpkg-deb --build debian/ ../../Rockbot_Editor_0.1b6.deb
