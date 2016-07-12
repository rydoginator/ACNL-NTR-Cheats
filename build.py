#!/usr/bin/python
import sys
import os
import ftplib
import glob


def allFile(pattern):
    s = "";
    for file in glob.glob(pattern):
        s += file + " ";
    return s;

def allFolderFile(pattern, ext):
	s = "";
	for dirpath, dirnames, filenames in os.walk(pattern):
		for filename in [f for f in filenames if f.endswith(ext)]:
			s+= os.path.join(dirpath, filename) + ' '
	return s;

	
NAME = 'ACNL_MULTI'
COPYTOPATH = NAME + '.plg'

CC 			= "arm-none-eabi-gcc"
CP 			= "arm-none-eabi-g++"
OC			= "arm-none-eabi-objcopy" 
LD 			= "arm-none-eabi-ld"
CTRULIB 	= '../libctru'
DEVKITARM 	= 'c:/devkitPro/devkitARM'
LIBPATH 	= '-L ./lib '

ARCH 		= ' -march=armv6k -mlittle-endian -mtune=mpcore -mfloat-abi=hard '
CFLAGS		= ' -Os -c ' + ARCH
ASFLAGS		= ' -Os -c -s ' + ARCH
LIBFLAGS 	= " -lg -lsysbase -lntr -lShark2NTR -lctr -lc -lgcc "# -lc -lgcc --nostdlib "
LDFLAGS		= ' -pie --gc-sections -T 3ds.ld -Map=' + NAME +'.map ' #--print-gc-sections

INCLUDES 	= " -I Includes -I Sources -I Includes/libntrplg "
CFILES		= allFolderFile(".\\Sources\\", ".c")
ASFILES		= allFolderFile(".\\Sources\\", ".s")





def run(cmd):
	#print(cmd);
	os.system(cmd)

cwd = os.getcwd()
print("\n\nHello !\n");
print("How are you ?\n");
print("I'm preparing to compile your " + COPYTOPATH + " plugin.\n");
print("Please just wait a second...\n");
if (os.path.isfile("obj/cheats_usa.o")):
	run("rm obj/*.o")
if (os.path.isfile(COPYTOPATH)):
	run("rm *.plg")
print("Compiling C files");
print(CC +  CFLAGS + INCLUDES + CFILES);
run(CC +  CFLAGS + INCLUDES + CFILES);
print("")

print("Compiling S files");
print(CC + ASFLAGS + ASFILES);
run(CC + ASFLAGS + ASFILES);
print("")

OFILES = allFile("*.o") + " " + allFile("lib/*.o")
print("Linking all files into " + COPYTOPATH);
print(LD + LDFLAGS + ' ' + LIBPATH  + OFILES + LIBFLAGS )
run(LD + LDFLAGS + ' ' + LIBPATH  + OFILES + LIBFLAGS )
print("")

if (os.path.isfile("cheats_usa.o")):
	run("cp -r *.o obj/ ")
if (os.path.isfile("a.out")):
	run(OC +" -O binary a.out payload.bin -S")
if (os.path.isfile("cheats_usa.o")):
	run("rm *.o")
if (os.path.isfile("a.out")):
	run("rm *.out")
if (os.path.isfile("payload.bin")):
	run('copy payload.bin ' + COPYTOPATH);
	run("rm payload.bin");
if (os.path.isfile(NAME + ".map")):
	run("rm *.map");
if (os.path.isfile(COPYTOPATH)):
	print("\nCopying the plugin into each folder...");
	run("cp " + COPYTOPATH + " plugin/0004000000086400/" + COPYTOPATH);
	run("cp " + COPYTOPATH + " plugin/0004000000086300/" + COPYTOPATH);
	run("cp " + COPYTOPATH + " plugin/0004000000086200/" + COPYTOPATH);
	print("\n\nDone, enjoy your plugin !\n\n");
else:
	print("\n\nSeems like something went wrong, check the compilation logs.\n\n");
