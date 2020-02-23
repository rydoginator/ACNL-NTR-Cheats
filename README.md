# ACNL-NTR-Cheats

ACNL-~~NTR~~-LumaCFW-Cheats is a plugin/3gx extension to be used with Luma's cheat plugin loader found [here](https://github.com/mariohackandglitch/Luma3DS/releases)

Please join our [discord!](https://discord.gg/EZSxqRr)

## Introduction 
This plugin was originally based off of this [plugin](https://github.com/Lustyn/NLT2I) , which was a very basic plugin that converted text to hex in  order to spawn items in the inventory. 

I then forked that plugin, created moon jump and teleport, but then with the help of others, it blew up into a full fledged cheat menu that included many different custom cheats that I could use. The possibilities were endless with C!

Version 2.0 -> Version 3.3 was written in C and was based off of libgateshark(link needed)

Version 4.0+ was a complete rewrite of the plugin, rewritten in C++ and was based off of [CTRPluginFramework](https://github.com/Nanquitas/CTRPluginFramework-BlankTemplate) 

Plugin development slowed as the developer of CTRPF wanted it to be perfect before it was released, and between 2017-2020 many of the devs have either moved on to different projects or are busy with life.

I was on the fence of whether or not to release the source code... many forks of the plugin have been made, either removing me from the credits, abusing licenses, selling forks of the plugin, putting the plugin behind adf.ly links... you name it. But I don't care anymore. The community can be toxic, but there's nothing I can do about that. 

I am finally releasing the source code of 4.0+ that has been private for so many years now. I will no longer be actively updating the plugin, but please feel free to contribute :)

 
## Installation
1. Download the .zip file posted found in [releases](https://github.com/rydoginator/ACNL-NTR-Cheats/releases)
2. Move the .zip file to your 3DS SD Card (or simply the root) then use the "Extract here" option. Do **NOT** extract it in another folder. Make sure to replace all the files when prompted. (Picture as reference)
Note: Even if you already have a boot.firm you'll need the one in this .zip since it contains the necessary plugin loader.
3. Boot up your 3DS and change any settings you want in the Luma config menu
4. While on the home menu of the 3DS activate the Plugin Loader by pressing L+Dpad Down+Select and choose [Enable Plugin Loader]
5. Launch Animal Crossing New Leaf, you should get a blue flash. Then simply load up your town and press Select to open the plugin menu.
6. Congrats, you did it!

### Video

[![Installation](https://img.youtube.com/vi/qs5qQ5O3wYw/hqdefault.jpg)](https://youtu.be/qs5qQ5O3wYw)

## Usage
[![Videos](https://img.youtube.com/vi/cSYLnRyX-fI/hqdefault.jpg)](https://youtu.be/cSYLnRyX-fI)


## Contributing
Pull requests are welcome. If you have any new codes you'd like to add, please specify which version of the game that you created the cheats in, and port them if possible. If you'd like to try finishing the universal region free pointers, please be my guest and use the region-free branch :^)

## Compiling
Make sure you have [DevkitPro](https://devkitpro.org/wiki/devkitPro_pacman)
And [3gxtools](https://github.com/Nanquitas/3gxtool/releases)

Open command line or terminal in the directory and run `make`

**Please don't create a new issue for compilation issues...**

If you can't figure out how to compile, then you shouldn't be creating a plugin in the first place...

## License
[MIT](https://choosealicense.com/licenses/mit/)