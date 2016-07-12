Tiny Asteroids for Arduboy - Zero gravity

## Description
Tiny Asteroids is Asteroids(1979) clone.

I know, Arduboy Arcade is making.
Please excuse duplicate games. :D


## Installation
Request : Arduino IDE 1.6.x

1. download from github
2. pls edit test.bat(windows) or test.sh(osx) for your computer(must change COM port number)
3. execute test.bat
4. play it


## Controls
L/R : move
A   : shot
B   : accel
U   : warp(random)


## Arange rule
max stage is 5. UFO and UFO shot dont hit player ship.


## Development
compiler        : windows Arduino IDE 1.6.8(avr-gcc) + 1.0.6(make.exe)
image converter : python 2.6 + PIL
etc             : Visual Studio 2015 C#, OpenOffice 4.1.2


## History
v1.02 2016/07/12    fix button A, B
v1.01 2016/05/15    support arduboy 1.0
v1.00 2016/04/08    first version


Arduboy 1.0 infomation.

AVR Memory Usage
----------------
Device: atmega32u4

Program:   16254 bytes (49.6% Full)
(.text + .data + .bootloader)

Data:       1830 bytes (71.5% Full)
(.data + .bss + .noinit)
