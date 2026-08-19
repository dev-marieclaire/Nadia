# Nadia Game Engine
The goal of this project is to make a minimal game engine, where the final user can create its own modules and implementations to extends or improve the engine's functionality without waiting for an update, making it more versatile for a lot of types of games.

## Dependencies.
It uses C/C++ and SDL2 currently, with the future ambition of writing a custom graphic core for the future.

Currently, the dependency list (for development over GNU/Linux) is the following:
gcc, g++, make, sdl2, sdl2_image, djgpp-gcc

### GNU/Linux setup.
In most distros, the setting things up is straightforward:
`$ sudo [package manager] [install params] [dependencies]`

About DJGPP, the setup is a bit more complicated.
The installation guide can be found here:
https://github.com/andrewwutw/build-djgpp.git

For the moment, I haven't required to set the project to any C/C++ standards or compiler version, so, you'll be fine with the latest supported standards and version of GCC in DJGPP.

## External assets.
Since time is pretty much tight and I am not skillful at everything, some examples make use of assets that aren't of my property.

I appreciate the work of the people behind these cool assets and I wont include them inside the repositoire, but I will leave a list with the used resources below.

Please support the artists and creators.

examples/animated_sprites:
- https://merakintsugi.itch.io/platformer-character-pack
