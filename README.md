# Macchiato-Mini-Synth
Mini Synth software sketches, executables, code development, new releases. ALWAYS USE LATEST RELEASE!

## INTRODUCTION

The Macchiato Mini Synth by Zeppelin Design Labs is a nifty digital synthesizer that fits in the palm of your hand. The control software was developed in the Arduino environment, incorporating the Mozzi Sound Synthesis library by Tim Barrass. The software runs on an AtMega 644PA microcontroller.

On this GitHub page, you can modify the original source code (files ending in .ino) and propose changes to the Macchiato software. We may from time to time release updates, or even alternate versions with  different functions and sounds. Releases v1.1.2 and higher were compiled using Arduio IDE v1.8.4. There's just a little setup needed to get your IDE to properly compile your customized sketch. Instructions follow in the section PROGRAMMING THE MACCHIATO. On the other hand, it is incredibly simple to just download new releases (the binary, or hex files, ending with .hex) and flash them to your Macchiato. This is covered in the next section.

## FLASHING A BINARY TO YOUR MACCHIATO

Look under the hood of your Macchiato cabinet. See that little cluster of six pins sticking up to the right of the Zeppelin logo? These are the In-System Programming (ISP) header pins that allow you to communicate with the microcontroller that runs your synth. The microcontroller is the little square chip to the right of the ISP header. It is an ATmega644PA  by Atmel. An inexpensive device called a programmer connects the ISP header to a USB port on your PC. This allows you to upload, or "flash", new control software to your synth.  With our new Updater App, this is incredibly simple.

To flash your synth, you will need the following:

* A USB Programmer such as USBTiny by Adafruit (https://www.adafruit.com/products/46); or you can get the self-same programmer we used to flash your synth from our web store (https://zeppelindesignlabs.com/product/usbtiny-programmer/). This piece of hardware runs from your computer to your Mini-Synth.

* Zeppelin Updater App (https://www.zeppelindesignlabs.com/wp-content/uploads/docs/Zeppelin_Setup.msi), hosted on our own server. To install, follow the simple instructions on our web page, on the "Installation" tab (https://zeppelindesignlabs.com/product/zdl-updater/). Once it is installed, there is a detailed Help file inside the Updater. The Updater itself contains all of our currently published hex files.

## PROGRAMMING THE MACCHIATO

The Macchiato Mini-Synth incorporates the Mozzi Sound Synthesis Library for Arduino by Tim Barrass. Mozzi and Macchiato are both covered by the Creative Commons / Attribution / Non-Commercial license. You are free to modify and redistribute the Macchiato software as long as you 1) distribute it under the same license terms, 2) give proper credit to the contributing creators, and 3) don't sell your derivative work without contacting the authors first. 

The Macchiato source code (file suffix .ino) is posted here on Github on the Releases page. Only use the Latest Release. To write and compile Macchiato sketches in the Arduino environment requires a little bit of setup. 

NOTE: We assume you are already familiar with Arduino, AVRDUDE, and coding in C++.
NOTE: Macchiato Software versions 1.1.2 and higher compile with Arduino 1.8.4. Earlier versions will only compile with Arduino 1.0.5r2 with considerable setup. The earlier sketches and binaries exist only as legacy releases. We do not support them at all.

WHAT YOU WILL NEED

* Arduino IDE 1.8.4 
https://www.arduino.cc/en/main/OldSoftwareReleases 
* AVRDUDE v 5.10 or later (usually bundled with Arduino.) 
http://download.savannah.gnu.org/releases/avrdude/?C=M;O=A

* Mozzi library v1.0.2 or higher
https://github.com/sensorium/Mozzi/releases

* Notepad++ or another text editor for working with program files
https://notepad-plus-plus.org/download/v7.3.1.html

* Two files from the Macchiato Setup Files folder, in this repository: RCPoll.h and ramp512_int8.h 

* Macchiato-Mini-Synth sketch ( *.ino) Latest Release from this repository.

### Let’s begin! 

1) If your installation of Arduino includes AVRDUDE version 5.10 or higher, skip to 3. Otherwise, install / upgrade to the latest version of AVRDUDE. 

2) If you do not already have a good C++ editor, treat yourself to Notepad++. This is the software we used to edit the Macchiato sketches. https://notepad-plus-plus.org/download/

3) Obtain and install the Mozzi library. Read the author’s release notes. Mozzi is a set of tools that tricks a microcontroller into behaving something like an oscillator. Place the Mozzi folder in your sketchbook\libraries\ folder. The path will look something like this:
C:\Users\Yourname\Documents\Arduino\libraries\

4) If your installation of Arduino does not include the MIDI library, fetch it here:
https://github.com/FortySevenEffects/
Note there are several different MIDI libraries in circulation. This is the one that comes bundled with new versions of Arduino, and is the one we used to deveolop Macchiato. Put this in the same folder as the Mozzi library.

5) Start Arduino 1.8.4 and install or activate the Mozzi and MIDI libraries. 

6) Find (search for) the file mozzi_config.h and open it for edit in Notepad++.
Uncomment the line “#define AUDIO_MODE HIFI” (delete the “//”). 
Comment out the line “#define AUDIO_MODE STANDARD_PLUS” (insert “//” at the start of the line). 
Save mozzi_config.h.

7) In the Mozzi library, look for a folder called \tables\. it may look like this: 
C:\Users\Yourname\Documents\Arduino\libraries\sensorium_Mozzi-1.x.x\tables\.
Place the file ramp512_int8.h in this folder.

8) In the Mozzi library, look for the file RCpoll.h. Overwrite it with the file with the same name which you obtained from Github.

9) Place your Latest Release Macchiato sketch (suffix .ino) in your Sketchbook folder.

The remaining steps add support for the 644PA microcontroller to your Arduino installation. 

1. Arduino 1.6.4 and higher includes a fancy BOARDS manager that can automatically find and install support for a gazillion microcontrollers. The MightyCore package, available on Github, will add support for the 644 and many other boards. Go to this Github page:
https://github.com/MCUdude/MightyCore#boards-manager-installation
and follow the simple instructions to install MightyCore using your Board Manager.
  
2. Close and restart Arduino. Under "Tools" make the following selections:

Board:  "Atmega644"
Variant: "644P / 644PA"
BOD: "2.7v"
Pinout: "Standard"
Clock: "16 MHz external"
Compiler LTO: "Enabled"
Port: "COM1"
Programmer: "USBTinyISP(MightyCore)"

## TESTING

Load a short sample sketch from the EXAMPLES folders in the Mozzi library and see if it will compile. Now load the Macchiato sketch and see if it will compile. (The first time you open this file, Arduino will ask if you want to move it into its own folder. Say Yes.) If it does not compile, read the error messages carefully. They will likely reveal a missing or misplaced component somewhere. (There are usually some compile warnings generated by the Mozzi library itself. You can ignore these.) Compare the errors to these setup instructions. Correct the error and try again until the Macchiato sketch compiles. Write to us on our forum if you get stuck.

Congratulations! You are now ready to familiarize yourself with the possibilities of the Mozzi library and to develop your own custom Macchiato. For terrific Mozzi support, join the mozzi-users Google group. Either tweak the code as-is for enhanced performance, or use the Macchiato as a hardware platform to develop a completely different instrument. You have thirteen keys, eight knobs to mess with!
