# Xsaitekpanels X-Plane plugin for Saitek Switch, Radio, Multi & BIP panels.

### How to build
Building requires cmake and a c++ compiler. Here's how I do it:

    mkdir build
    cd build && cmake ..
    make

#### Building on Windows
On Windows, you can use the Visual Studio project generator to do something like this:

    mkdir build
    cd build && cmake -G "Visual Studio 12 Win64" -DMSVC_RUNTIME=dynamic ..

at which point you can just use Visual Studio to build the project, or you can build on the command line:

    msbuild src/plugin.vcxproj /p:Configuration=Release /flp:logfile=plugin_build.log;verbosity=normal

### Author
Xsaitekpanels is written by William R. Good.
