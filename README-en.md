## Icey Local Judge

------

![](https://img.shields.io/badge/build-passing-brightgreen.svg?longCache=true&style=flat-square) ![](https://img.shields.io/badge/size-<1MB-00BFFF.svg?longCache=true&style=flat-square) ![](https://img.shields.io/badge/icey-%20v2.0.0-blue.svg?longCache=true&style=flat-square) ![](https://img.shields.io/badge/price-$0-C0C0C0.svg?longCache=true&style=flat-square)

Welcome to use icey, this document will help you get started quickly. If you are experiencing problems during use, please check the answers in the FAQ or ask questions under this project.

```
icey [OPTION]... DATA... CODE...
```

------

[中文文档](README.md)

### icey?

icey is a lightweight open source OI local judge system. Developed by [Edgration](http://edgration.com/) and [Anoxiacxy](https://anoxiacxy.github.io).

You can quickly and accurately judge your program with a few short commands and get a report on the review.

### Install

It is very easy to install iecy.

First download the source file of this project, After opening the folder, copy the executable file `icey` to the  `usr/bin/` directory for global use.

Simple commands are as follows

```bash
git clone https://github.com/Edgration/icey.git
sudo cp icey/icey /usr/bin/
```

For those who don't have ```git``` installed, you can use the following command to install

```bash
sudo apt-get install git
```

### Uninstall

You can uninstall using the following command

```
sudo rm /usr/bin/icey
```

### Usage

![](images/Screenshot-from-2018-09-23-23-41-56.png)

#### Local Judge

```bash
icey [OPTION]... DATA... CODE...
```

Where `DATA` is a directory and `CODE` is a file, means use the data in the `DATA` directory to judge the `CODE` code.

#### About DATA

`DATA` must be a no-empty directory.

This directory can be an absolute path to the system or a relative path to the current working directory.

In this directory, several test data can be stored, and the format of each set of test data is

```
name1.in
name1.out
```

which is `name` + `number` + `.in/.out` .

icey will identify and pair files in this format from the directory. The name of the test data can be empty, but must have a number that matches each other.

In addition，you can use`-i=IN`，`-o=OUT` to specify the suffix of the test data.

#### About CODE

`CODE` must be a no-empty file.

This file can be an absolute path to the system or a relative path to the current working directory.

It is a source code written in C++.

Please make sure that no functions such as `freopen` are used in the program to avoid affecting the judge results.

#### About [OPTION]

These parameters are optional and can be added as needed when you need them.

|      Format       | description                                                  |
| :---------------: | ------------------------------------------------------------ |
|    -h, --help     | Display help information fo icey                             |
|   -v, --version   | Display version information of icey                          |
| -t, --time=SECOND | You can set the time limit for each test data in seconds, which can be a floating point number. The default is 1 |
|    -c, -C[opt]    | You can add compile options. For example, you want to add `-O2`, you can add the parameter `-CO2`.If you want to use `c++11`, the compile option `-std=c++11`, you can add the parameter `-Cstd=c++11` |
| -i, -I[name] | You can modify the input file suffix name, for example, you want to change to `input`, you can add the parameter `-Iinput`, the default is .in |
| -o, -O[name] | You can modify the output file suffix name. For example, if you want to change to `ans`, you can add the parameter `-Oans`, the default is .out |

#### About judge result

For each single test data

- AC：Accept. Your solution is correct.
- CE：Compile Error. Failed to compile your source code. 
- WA：Wrong Answer.Your program's output doesn't match judger's answer.
- RE：Runtime Error.Your program terminated abnormally. 
- TLE：Time Limit Exceeded.The CPU time your program used has exceeded limit.
- ~~MLE：Memory Limit Exceeded,The memory your program actually used has exceeded limit.~~
- UKE：Unknown Error.An unknown error has occurred, please check if the packet is named correctly.

Final result

- AK：All Killed, passed all tests.
- PC：Partially Correct.
- GG：Exploded. Unfortunately, you got zero point.

### FAQ



### Update log

#### v2.0.0

- Fixed a bug that the background .exe process could not automatically close caused system and caused the system crashed

- Added custom file suffix option, now you can customize the suffix name of the input and output files

- Beautify the -h and -v and error messages, partially add highlight and underline

#### v1.1.2

- Fixed the BUG that the judge result cannot go well after get TLE

#### v1.1.1

- Added Edglish readme

#### v1.1.0

- Added custom compilation options, now free to choose to open `-CO2` optimized

#### v1.0.3

- New judge results CE, UKE

#### v1.0.2

- It is now possible to judge both relative and absolute paths at the same time
- Slightly modify the display effect of the score and the result of the zero point

#### v1.0.1

- Fixed bug where `WA` could not be judged
- Added statistical display of final evaluation results

#### v1.0.0

- Add judge function
- Judge result color display
- Custom test point time limit







