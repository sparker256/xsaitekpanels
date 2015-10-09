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

Support for multiple Saitek Pro Flight panels in X-Plane 10 using Linux, Windows and the Mac Including switch, radio, multi and the BIP.

This project **is and will be continue to be completely free**, but if you want to support it by means of donation, I really would appreciate that.

Thank you,

Bill

[![](https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=JZG2ALMZQZYNG&lc=US&item_name=Xsaitekpanels&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted)
