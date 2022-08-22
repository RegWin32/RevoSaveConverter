# RevoSaveConverter
Revo K101 Plus savefile converter for Gameboy Advance

How to build🏗️:

```
git clone https://github.com/RegWin32/RevoSaveConverter.git && \
cd RevoSaveConverter && \
cmake . && \
make 
```

Usage💡:
```
GBA_Convert [OPTION] [SAVE-FILE]
OPTION
    revo   to revo file format
    gba    to gba file format
SAVEFILE
    string  name of the savefile
```

Example📄:
```
./GBA_Convert revo SuperMario.sav
=> Generates SuperMario.gba.sav working on the Revo K101 Plus
```
