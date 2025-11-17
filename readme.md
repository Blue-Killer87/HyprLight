<h1>HyprLight</h1>

*Simple universal display brightness and temperature controller for Hyprland.*

<h2>What is HyprLight?</h2>
Hyprlight is a simple tool written in C++ and built on GTK3 that allows you easily control your
 screen brightness and temperature. It is essentially just an extension of other tools commonly
 used in Hyprland environment control. These tools include brightnessctl for well... brightness control. 
 And hyprsunset for screen temperature related operations. So in order to run the application in the 
 first place, you will these two to be installed beforehand.

<h2>Dependencies</h2>

 |   Dependency   | Version |
 | -------------- | ------- |
 |   Hyprland     |   any   |
 | brightnessctl  |   any   |
 |  hyprsunset    |   any   |
 |      g++       |   any   |

 <h2>Installation</h2>

 I do not ship official builds yet, so in order to install HyprLight, you'll need to build it.
 In order to make the process a bit easier to humans, I made a simple build.sh script that will ease 
 the build. Simply set build.sh as executable and run it, it will call g++ with all its arguments on
 itself. After this, you should see hyprlight binary file with the application itself, just run it normally.


 
