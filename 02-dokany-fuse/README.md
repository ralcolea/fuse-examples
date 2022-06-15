# Repository 02-dokany-fuse
This repo was created for testing a hello-world fuse project with 
dokany, the open-source user mode file system library for Windows.

## Compiling Dokany in Windows:

In order to compile Dokany, the following software needs to be installed.

* Git (to download the code)
* [Cygwin](https://cygwin.org/) 64-bit (for compiling Cygwin-versions of dokanfuse)
  * Additional packages: cmake make gcc-core gcc-g++ pkg-config
  
**Note:** You need to use the same toolchain to compile your own dokanfuse and your FUSE program to make it compatible. Neglect of doing so will result in mysterious problems like stack overflows and BSOD.

## Install dokany library from binaries:

* Install dokany library using the binaries files from the repository
* Clone git repository with git clone https://github.com/dokan-dev/dokany/releases 

**Note:** This installation is necessary to copy the header files of fuse, that comes with dokany installation.
  
## Build the driver, library and tools

Dokany is a fork of Dokan Fuse, a wrapper library that makes Dokan compatible with FUSE API. To use it, you only have to link with the dynamic library _dokanfuse.dll_. This library can be compiled from the project _dokan_fuse_ inside the [Dokany repository](https://github.com/dokan-dev/dokany.git).

You can compile the dynamic library _dokanfuse.dll_ in two steps:
* Clone git repository with git clone https://github.com/dokan-dev/dokany.git
* Compile _dokanfuse.dll_ library with the needed compiler
  
#### Cygwin

The `cygdokanfuse.dll` distributed is compiled by cygwin gcc. You can also build it yourself using the _Cywing64 Terminal_ and typing the following commands:

```
cd dokan_fuse
cmake .
make
```

Be aware that `cygdokanfuse.dll` has dependencies to `cygwin1.dll`, `cyggcc_s-seh-1.dll` and `cygstdc++-6.dll`.

As a sample, to build `dokanyfuse.cpp` use the following command line:

```
g++ dokanyfuse.cpp -I../include -D_FILE_OFFSET_BITS=64 -L. -lcygdokanfuse2 -o dokanyfuse.exe
```

where `../include` is the path to the include folder of Dokan installation, i.e `C:\Program Files\Dokan\Dokan Library-2.0.4\include`

For running, use the following command line:

```
./dokanyfuse.exe h       # Mount a crash filesystem as drive H:\
```

#### mingw-w64

The `libdokanfuse.dll` can also be compiled using mingw-w64. You can build it yourself using the cmd terminal and typing the following commands:

```
cd dokan_fuse
cmake . -G "MinGW Makefiles"
make
```

As a sample, to build `dokanyfuse.cpp` use the following command line:

```
g++ dokanyfuse.cpp -I../include -D_FILE_OFFSET_BITS=64 -L. -llibdokanfuse2 -o dokanyfuse.exe
```

where `../include` is the path to the include folder of Dokan installation, i.e `C:\Program Files\Dokan\Dokan Library-2.0.4\include`

For running, use the following command line:

```
dokanyfuse.exe h       # Mount a crash filesystem as drive H:\
```

## Umount a mountpoint

To umount a mountpoint previously mounted with dokany, use the following command line:
```
dokanctl /u M
```

where `M` is the drive letter asigned to the mountpoint.
