# IGC Logbook

Small utility to create a logbook from one or more igc files. Intended for use on the OpenVario flight computer.

## Usage

Simply run with a bunch of `.igc` files as argument.

## Cross Compiling

Cross compile for arm with (staticly link libstdc++):
```
make CXX=arm-linux-gnueabihf-g++ CFLAGS=-static-libstdc++

```

## ToDo:

* Detect takeoff time from altitude change
* Add pilot name
* Add departure / arrival aerodrome
* Save and export
* Add notes
