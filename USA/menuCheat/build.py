#!/usr/bin/python
import sys
import os
import ftplib
import glob

# the path plugin was copied to
COPYTOPATH = 'cheat.plg'

CC = "arm-none-eabi-gcc"
CP = "arm-none-eabi-g++"
OC = "arm-none-eabi-objcopy" 
LD = "arm-none-eabi-ld"
CTRULIB = '../libctru'
DEVKITARM = 'c:/devkitPro/devkitARM'
LIBPATH = '-L ./lib'


def allFile(pattern):
    s = "";
    for file in glob.glob(pattern):
        s += file + " ";
    return s;

def run(cmd):
	#print(cmd);
	os.system(cmd)

cwd = os.getcwd() 
run("rm obj/*.o")
run("rm bin/*.elf")
run(CC+  " -Os -s  -g -I include -I include/libntrplg " + allFile('source/libntrplg/*.c') + allFile('source/ns/*.c') + allFile('source/*.c') + allFile('source/libctru/*.c') + " -c  -march=armv6 -mlittle-endian  ");
run(CC+"  -Os " + allFile('source/libntrplg/*.s') +  allFile('source/ns/*.s')  + allFile('source/*.s') + allFile('source/libctru/*.s') + " -c -s -march=armv6 -mlittle-endian ");

run(LD + ' ' + LIBPATH + " -pie --print-gc-sections  -T 3ds.ld -Map=homebrew.map " + allFile("*.o") + " " + allFile("lib/*.o") + " -lc -lgcc --nostdlib"  )
run("cp -r *.o obj/ ")
run("cp a.out bin/homebrew.elf ")
run(OC+" -O binary a.out payload.bin -S")
run("rm *.o")
run("rm *.out")
run('copy payload.bin ' + COPYTOPATH);
