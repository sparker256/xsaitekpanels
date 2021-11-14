# Xsaitekpanels X-Plane plugin for
# Saitek Switch, Radio, Multi & BIP panels.
=========================

### Author
Xsaitekpanels is written by William R. Good.

This project **is and will be continue to be completely free**, but if you want to support it by means of donation, I really would appreciate that.

Thank you,

Bill

[![](https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=JZG2ALMZQZYNG&lc=US&item_name=Xsaitekpanels&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted)



[![CMake](https://github.com/sparker256/xsaitekpanels/actions/workflows/cmake.yml/badge.svg)](https://github.com/sparker256/xsaitekpanels/actions/workflows/cmake.yml)



## Building Xsaitekpanels from source

### On windows

1.  Install required software using [Chocolatey](https://chocolatey.org/) using admin command prompt:

    ```
    choco install git cmake
    choco install mingw --version 8.1.0
    ```

    You can also install the same programs manually if you prefer.

2.  Checkout and configure the project:

    ```
    git clone https://github.com/sparker256/xsaitekpanels.git
    cd xsaitekpanels
    cmake -G "MinGW Makefiles" -S .\src -B .\build -DCMAKE_BUILD_TYPE=RelWithDebInfo
    ```

3.  Build the project and copy the plugin DLL into the appropriate directory:

    ```
    cmake --build .\build
    cp .\build\win.xpl .\Xsaitekpanels\64\
    ```

### On Ubuntu:

1. Install required software:

   ```
   sudo apt-get install -y --no-install-recommends build-essential cmake git freeglut3-dev libudev-dev libopenal-dev

   ```

2. Checkout and configure the project:

   ```
   git clone https://github.com/sparker256/xsaitekpanels.git
   cd xsaitekpanels
   cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=RelWithDebInfo
   ```

3. Build the project and copy the plugin DLL into the appropriate directory:

   ```
   cmake --build ./build
   cp ./build/lin.xpl ./Xsaitekpanels/64
   ```

### On OS X:

1. Install XCode, Git, CMake (Homebrew can be convenient for this).

2. Checkout and configure the project:

   ```
   git clone https://github.com/sparker256/xsaitekpanels.git
   cd xsaitekpanels
   cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=RelWithDebInfo
   ```

3. Build the project and copy the plugin DLL into the appropriate directory:

   ```
   cmake --build ./build
   cp ./build/mac.xpl ./Xsaitekpanels/64
