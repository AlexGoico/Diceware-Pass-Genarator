Diceware Password Generator
===========================
An implementation of Arnold Reinhold's
[work](http://world.std.com/~reinhold/diceware.html)

Building
--------
To build simply
```
mkdir build
cd build
cmake .
make
./src/dwgen
# or with a specific number of words
./src/dwgen 6

# On Windows you'll need to build the visual studio project
# in release mode.
# Double click on the .sln, change debug mode to release mode,
# build project by right clicking on the project name
```

You must copy or link the diceware_dict.txt file to the directory
the executable will be run from. By default this is the src directory
under the directory you built the project. You can link a file on
Windows by creating a shortcut while on linux its `ln -s` on the
terminal.

Thus on linux you would type the following before ./src/diceware
```
ln -s ../diceware_dict.txt .
```
