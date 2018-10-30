#!/usr/bin/env bash

rm -rf data
mkdir data

# Assuming react product build has already been made.
cp -r esp_react/build/* data
gzip -r data/*

mkspiffs -p 256 -b 8192 -s 1048576 -c data/ spiffs_image.bin
$HOME/.arduino15/packages/esp8266/tools/esptool/0.4.13/esptool -vv -cd nodemcu -cb 115200 -cp /dev/ttyUSB0 -ca 0x300000 -cf spiffs_image.bin

echo "Prebuild complete"