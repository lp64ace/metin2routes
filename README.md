# Hook
Metin2 internal cheat for Raventor V2

## Build

Here are some instructions for building the cheat, the project uses CMake for build configuration.

```sh
cmake -G "Visual Studio 17 2022" -A Win32 /path/to/source
```

Compiling the project is also straight forward.

```sh
cmake --build . --config Release
```

## Launch

Here are some example launch options in order to run the cheat, the launcher needs to have elevated permissions.

!launch.json
```json
{
    "metin2": {
	"directory": "path\\to\\Raventor_V2",
	"metin2client.exe": "metin2client.exe"
    }
}
```
