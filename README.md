# Sunrise alarm
> My annual sunrise alarm make.
> 
i.e. a device that emits light at a certain time in the morning to aid waking up.

## This is a WIP

## Requirements
* System maintains its own time
* The sunrise trigger time is configurable
* The duration if the 'sunrise' is configurable
* The 'sunrise' should simulate a real sunrise in colors and duration.
* The device's interface is browser based


## Hardware
* NodeMCU 1.0 (ESP8266)
* Neopixels or similar individually controllable LED strip.

## Software

This repository is mostly for myself, so I will leave installation and other details for you to figure them out.

I'm using Visual Studio Code with the Arduino plugin. This allows me to retain bits of my sanity (I'm looking at you Arduino IDE). It allows me to run scripts automagically during build, and many other nice things.

I use a modified version of [mkspiffs](https://github.com/igrr/mkspiffs) to generate the binary version of the SPIFFS file system.
```
$ mkspiffs --version
mkspiffs ver. 0.2.3-2-g4eae236
Build configuration name: generic
SPIFFS ver. 0.3.7-5-gf5e26c4
Extra build flags: -DSPIFFS_OBJ_NAME_LEN=60
SPIFFS configuration:
  SPIFFS_OBJ_NAME_LEN: 60
  SPIFFS_OBJ_META_LEN: 0
  SPIFFS_USE_MAGIC: 1
  SPIFFS_USE_MAGIC_LENGTH: 1
  SPIFFS_ALIGNED_OBJECT_INDEX_TABLES: 0
```

You will also need
* npm for frontend development.
* esptool for uploading firmware and SPIFFS to the NodeMCU.

