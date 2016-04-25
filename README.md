Diceware Password Generator
===========================
An implementation of Arnold Reinhold's
[work](http://world.std.com/~reinhold/diceware.html)

Building
--------
To build simply
```
cmake .
make
./diceware
# or with a specific number of words
./diceware 6

# On Windows you'll need to build the visual studio project
# in release mode.
# Double click on the .sln, change debug mode to release mode,
# build project by right clicking on the project name
```

If you decide to build in another directory you must copy or link the
diceware_dict.txt file to that directory. Lining is done on windows by
creating a shortcut while on linux its `ln -s` on the terminal.