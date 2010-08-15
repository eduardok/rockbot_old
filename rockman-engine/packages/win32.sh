#!/bin/sh

sh ../bin/pack_data.sh
rm -r -f ./win32/data
cp -r ./data ./win32
zip ../Rockbot_WIN32.zip *