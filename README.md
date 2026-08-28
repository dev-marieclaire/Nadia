# Nadia Game Engine
The goal of this project is to be a minimal game engine, where the final user can make its own modules and implementations to extend or improve the engine's functionality without waiting for an update, making it more versatile for a lot of types of games.

## Dependencies.
This project uses C, C++, SDL2 and Allegro 4.2.2 xc currently (I'm planning on writing a custom graphic renderer for the future).

The dependency list (for development on GNU/Linux) is the following:
gcc, g++, make, sdl2, sdl2_image, djgpp-gcc

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
