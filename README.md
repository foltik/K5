# K5 Engine
K5 is a simple 2D/3D game engine created with extensibility and ease of use in mind. It aims to provide simple abstractions to many common tasks, while still retaining the ability to write custom OpenGL code.

## Installation
First, clone the latest release code locally:
```bash
$ git clone https://github.com/Foltik/K5
```

Next, create and change into a build directory and invoke `cmake`:
```bash
$ mkdir K5/build
$ cd K5/build
$ cmake ..
```

Finally, build and install the library to your system.
You may be prompted to enter your password in order to install the binary:
```bash
$ make && sudo make install
```


## Creating a Project with K5
The K5 Engine comes with a script `init.sh` that sets up a bare bones project with the minimum code needed to run K5. Simply run it with the following command:
```bash
$ ./init.sh $ProjectName $ProjectPath
```
The script will create your project with the CMake build system in the specified directory with the specified name. Note that it should not contain spaces. 

## Building Your Project
Building your project is just as simple as building K5 itself. Simply run the following commands inside the project directory to build it:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```
And if everything went correctly, you can now run your compiled project!
```bash
$ ./$ProjectName
```
You are now free to continue this project however you want!
