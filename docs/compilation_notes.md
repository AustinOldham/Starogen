
# Compilation Notes

- Folders containing data that must be read by the C++ plugins need to be manually copied over due to the way Godot handles exporting.
- Make sure the plugins are compiled in release mode and the project is not exported in debug mode.
- Attempting to compile while Godot is open may cause errors.
- I will attempt to add a script that does all of this automatically in the future

  

  

## godot-cpp

NOTE: This must be done before compiling the plugins
  

1. Switch to the godot-cpp directory

```cd Starogen/source/godot-cpp```

2. May need to see README.md in this directory to see how to generate and use custom bindings if you are having issues with compiling
3. Compile
```scons platform=<platform> generate_bindings=yes bits=64 -j<number of cores (optional flag)>```
4. Add `target=release` or `target=debug` depending on which one you need

## Boost

- You should follow the instructions on the official website but this may be helpful if you have issues getting it to compile
- Run bootstrap.bat/bootstrap.sh (Starogen requires the compiled version, not the header-only version)
- Run b2.exe/b2 afterwards with `-j8 address-model=64 link=static threading=multi --build-type=complete` (might need `debug-symbols=on` for debug mode)
- `<your boost path>` refers to the directory that has bootstrap.bat/bootstrap.sh 
- Might have to change all `-MD` and `-MDd` arguments to `-MT` and `-MTd` in the SCons file in order to release it


## Galaxy Generator

1. Switch to the directory
``` cd Starogen/source/plugins/GalaxyGenerator```
2. Compile (ignore the target argument for debug mode)
```scons platform=<platform> bits=64 boost_path=<your boost path> target=release```

## Planet Generator (currently not in use)

1. Switch to the directory
``` cd Starogen/source/plugins/PlanetGenerator```
2. Compile (ignore the target argument for debug mode)
```scons platform=<platform> boost_path=<your boost path> bits=64 target=release``
