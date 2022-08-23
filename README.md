# RevoSaveConverter
Revo K101 Plus savefile converter for Gameboy Advance

How to build🏗️:

```
git clone https://github.com/RegWin32/RevoSaveConverter.git && \
cd RevoSaveConverter && \
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

How does it work?🤔
```
The Revo K-Card expects 139264 bytes for a savegame file.
We simply add 0xDEAD bytes until the size requirement is met. 
The K-Card savefile is named "*.bak.sav", probably to distinguish it from unmodified savefiles.
My EZFLASH OMEGA reads savefiles with the maximum size of 131072 bytes.
To convert back, we simply copy the "*.bak.sav" file and remove the excess 8192 bytes. 
We save the copy with the extension "*.sav" and delete the original "*.bak.sav" file once we are done with the conversion.
```
