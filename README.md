# pacam
Point-and-Click Adventure Maker

### Building
From the root directory, just run:
```
make
```
This will build an executable `pacam` in the build dir. By running this file, e.g. with `./build/pacam`, a demo will start. The code for the demo is in `src/pacam.c`, and it uses assets in the resources dir. This demo can be modified to be an entry point for your game!

To clean, simply use:
```
make clean
```