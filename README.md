# Nadia Game Engine
The goal of this project is to be a minimal game engine, where the final user can make its own modules and implementations to extend or improve the engine's functionality without waiting for an update, making it more versatile for a lot of types of games.

## Dependencies.
This project uses C, C++, SDL2 and Allegro 4.2.2 xc currently (I'm planning on writing a custom graphic renderer for the future).

The dependency list (for development on GNU/Linux) is the following:
gcc, g++, djgpp-gcc, make, sdl2, sdl2_image, imagemagick

The previously mentioned version of Allegro already comes in the files.

### GNU/Linux setup.
In most distros, the setting things up is straightforward:
`$ sudo [package manager] [install param] [dependencies]`

About DJGPP, the setup is a bit more special, but not-so-complicated.
The installation files and guide can be found here:
https://github.com/andrewwutw/build-djgpp.git

For the moment, I haven't required to set the project to any C/C++ standard or compiler version, so, you'll be fine with the latest supported standards and version of GCC in DJGPP.

## External assets.
Since time is pretty tight, and I am not skillful at everything, some examples make use of assets that aren't of my property.

I appreciate the work of the people behind these cool assets and I won't include them inside the repository, but I will leave a list with the used resources below.

Please support the artists and creators if it is inside your possibilities.

examples/animated_sprites:
- https://merakintsugi.itch.io/platformer-character-pack
- Used files: `from idle.png`, `idle.png`, and `walk.png`

## DOS support.
DOS specifications will be detailed with the time.

### Image formatting
Image formatting is quite strict in DOS. So far, the project has support for BITMAP only.

The way to convert a BMP image into a supported DOS format is the following:
`convert [your_file.bmp] -type TrueColor -compress None -define bmp:format=bmp3 [converted_file].bmp`

And to check if the BMP image is a valid Windows 3.x bitmap is the following:
`file fixed_dither.bmp`

If converted correctly, the information displayed by the `file` command must look similar to this:
`dither.bmp: PC bitmap, Windows 3.x format, 800 x 699 x 24, image size 1677600, resolution 11811 x 11811 px/m, cbSize 1677654, bits offset 54`