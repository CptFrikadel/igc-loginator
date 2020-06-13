# IGC Logbook

Small utility to create a logbook from one or more igc files. Intended for use on the OpenVario flight computer.

## Usage

Simply run with a bunch of `.igc` files as argument. On OpenVario output is best viewed when piped into `less`.

## Cross Compiling

Cross compiling for OpenVario: use bitbake recipe my fork of meta-openvario.

## ToDo:

* Detect takeoff time from altitude change
* ncurses user interface
* Add departure / arrival aerodrome
* Save and export
* Add notes
