### BlobToChar

![C/C++ CI](https://github.com/AandersonL/BlobToChar/workflows/C/C++%20CI/badge.svg)

## What is this ?

BlobToChar its an C++ program that allows you to load an binary file in C arrays format, this is good if you want to embed files inside your source code.


## Examples


Dumping in stdout
```shell
$ ./BlobToChar --blobname simple_dump
char arr[] = {0x7,0xbc,0xef,0xce,0x90,0x90,};
```
Dumping inside an source code

actual code
```cpp
#include <stdio.h>



int main()
{
    return 0;
}
```
Run BlobToChar
```shell
$ ./BlobToChar --blobname simple_dump --filename source.c --linenumber 4 --varname buff
New variable buff inserted with success in line 3 of the file source.c
```

Modified code
```cpp
#include <stdio.h>


char buff[] = {0x7,0xbc,0xef,0xce,0x90,0x90,};

int main()
{
    return 0;
}
```



## Usage


You can use this tool for: 
* Load files inside your code
* Load shellcode inside your source quickly
* Load anything that you want be in C arrays format!


## Example

![](res/example.gif)

### Options
```shell
$ ./BlobToChar
Usage: ./BlobToChar [options]

--blobname      Name of the binary file
--filename      Name of the target source
--linenumber    Number to insert
--varname       variable name inside code
```


## Install

You will need ```cmake``` in order to compile & install this tool.

```shell
mkdir build
cd build
cmake .. && make && sudo make install
```


Thanks 
