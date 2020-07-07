# Waggle

This is a tool to convert BVM object to the BittyBuzz virtual machine (BBVM). 
The name waggle is a reference to the dance bees does when they communicate a new source of nectar with other member of the hive.

Most of the code comes from MIST repo `https://github.com/MISTLab/BittyBuzz`


## Requirements 

For building you do not need external libraries, to use it you need bzzc from MIST `https://github.com/MISTLab/Buzz` to be able to generate .bo files.

## Usage


```waggle <compiledbuzzscript.bo> <outfile.h>```

## Installation

First clone the repo

```git clone https://github.com/SwarmUS/Template-Cpp.git```

Then you build the project

```
mkdir build
cd build 
cmake ..
make
```

Then you can install. You will probably need to run as a super user.

``` make install ```

## Uninstalling
Just use the provided install_manifest.txt after installation in your build directory. Note that you may need to run as a super user for that.

```
xargs rm < install_manifest.txt
```

## Tests

There is no tests at the moment.

git example modifications


