# Macchiato-Mini-Synth
Mini Synth software sketches, executables, code development, new releases. ALWAYS USE LATEST RELEASE!

## INTRODUCTION

The Macchiato Mini Synth by Zeppelin Design Labs is a nifty digital synthesizer that fits in the palm of your hand. The control software was developed in the Arduino environment, incorporating the Mozzi Sound Synthesis library by Tim Barrass. The software runs on an AtMega 644PA microcontroller.

On this GitHub page, you can modify the original source code (files ending in .ino) and propose changes to the Macchiato software. We may from time to time release updates, or even alternate versions with  different functions and sounds. Currently, the sketch must be edited and compiled in Arduino 1.0.5r2. It will not run properly if compiled in later versions. It takes some setup of the IDE to get the sketch to compile properly. Instructions are in the section PROGRAMMING THE MACCHIATO. On the other hand, it's easy to just download new releases (the binary, or hex files, ending with .hex) and flash them to your Macchiato. This is covered in the following section.

## FLASHING A BINARY TO YOUR MACCHIATO

Look under the hood of your Macchiato cabinet. See that little cluster of six pins sticking up to the right of the Zeppelin logo? These are the In-System Programming (ISP) header pins that allow you to communicate with the microcontroller that runs your synth. You use an inexpensive device called a programmer that connects the ISP header to a USB port on your PC. This allows you to upload, or "flash", new control software to your synth.

The microcontroller is the little square chip to the right of the ISP header. It is an ATmega644PA microcontroller by Atmel. It belongs to a class of microcontrollers broadly called AVRs. (Atmel says AVR does not stand for anything in particular.) The actual program on the microcontroller is in the form of a "binary" or “hex” file – a jumble of machine code that you and I cannot understand or easily unpack. Think of Cipher looking at the Matrix datastream. You can flash a new hex file to your Macchiato at any time.

To flash your synth, you will need the following:

* A USB Programmer such as USBTiny by Adafruit (https://www.adafruit.com/products/46); or you can get the self-same programmer we used to flash your synth from our web store (https://zeppelindesignlabs.com/product/usbtiny-programmer/). This is a piece of hardware that runs from your computer to your Mini-Synth. The programmer comes with a cable that connects to the ISP header. 

* A USB cable to connect your computer to your Programmer. This will probably be a Standard USB to Mini USB cable and might be included with your programmer. (The programmer we sell comes with everything you need.)

* A driver (software) to install on your computer, which enables it to recognize and communicate with the programmer. The programmer you buy should include detailed instructions for how to obtain and install this driver. The drivers for our USBTiny programmer are available here for Windows: https://rayshobby.net/dead-simple-driver-installation-for-usbasp-and-usbtiny-on-windows/
and here for Mac: http://macappstore.org/libusb/

* AVRDUDE version 5.10 or later. This is a free, simple command-line software utility that sets up communication between your computer and your synth, and transfers (flashes) files to the microcontroller. It is included as part of any Arduino installation, but some users have found it tricky to flash our .hex files from within Arduino. You may want to add an independent avrdude installation on your desktop. Look here:
http://download.savannah.gnu.org/releases/avrdude/?C=M;O=A
Look for the file with the highest version number that looks like this: avrdude-[version-number]-mingw32.zip
This file will contain avrdude.exe and avrdude.conf. Place them together in a convenient place on your machine, like the desktop.
Sparkfun has a fantastic tutorial explaining all this stuff. Find it here:
https://learn.sparkfun.com/tutorials/pocket-avr-programmer-hookup-guide/using-avrdude

* A Macchiato hex file. See #6 below. 

To flash a hex file:

1) Install the programmer’s driver.

2) Install AVRDUDE. Place avrdude.exe and avrdude.conf together someplace convenient. We like to install it to the user’s desktop, but you can put it anywhere you like. (You will have to place the hex file in the same folder as the AVRDUDE executable.)

3) Plug your programmer into a USB port on your computer.

4) Open a command prompt window. (On Windows machines, that's Start > run > cmd) Change to the directory containing the AVRDUDE executable. If you placed AVRDUDE on your desktop, then on a Windows PC the directory will look something like this:
C:\Users\Yourname\Desktop\ 

5) Verify that AVRDUDE is functioning and that it can identify your programmer. Follow the general procedure described in the Sparkfun article, adapted to your particular programmer.

6) Download the latest binary (hex) file from this GitHub page. Go to the Releases page and look for Latest Release, and download the .hex file. Place the hex file in the same folder as avrdude.exe.

7) Plug the programmer into the synth. To do this, turn your synth off, turn the volume control down, and connect your programmer cable to the ISP header. The MISO pin #1 is the top-left pin as you look at your synth. This pin will probably be identified with a dot on your programmer, or a line on one wire in the cable. Be careful not to attach the cable backwards. 

8) Your programmer probably has an option to send power through to the synthesizer. Turn it on. It will be a tiny switch on the programmer labelled something like "POWER TARGET". 

9) Verify that communication is established between the computer and the synth by entering this command:

C:\Users\Yourname\Desktop\ avrdude -c usbtiny -p m644p

Your file location may look different, and you may have a different argument after –c if you are using a different programmer. AVRDUDE should display a “Fuses OK” message. If not, study the Sparkfun article to troubleshoot.	

10) You are ready to upload your new hex file. Enter this command:

C:\Users\Yourname\Desktop\ avrdude -c usbtiny -p m644p -V -B 1 -U flash:w:[filename].cpp.hex

Be sure the [filename] argument exactly matches the name of the hex file you downloaded. AVRDUDE should erase the chip, read the new hex file, flash it to the chip, and then announce that everything is OK and Thank you. 

11) Unplug the synth from the programmer. Turn it on, turn up the volume, and check out your new instrument!

## PROGRAMMING THE MACCHIATO

The Macchiato Mini-Synth incorporates the Mozzi Sound Synthesis Library for Arduino by Tim Barrass. Mozzi and Macchiato are both covered by the Creative Commons / Attribution / Non-Commercial license. You are free to modify and redistribute the Macchiato software as long as you 1) distribute it under the same license terms, 2) give proper credit to the contributing creators, and 3) don't sell your derivative work without contacting the authors first. We hope you will use this GitHub page as the place to collaborate on new Macchiato software.

The Macchiato source code (file suffix .ino) is posted here on Github on the Releases page. Only use the Latest Release. We encourage you to develop your own Macchiato software and submit it here for inclusion in future releases. To write and compile Macchiato sketches in the Arduino environment requires a little bit of setup. 

NOTE: We assume you are already familiar with Arduino, AVRDUDE, and coding in C++.
NOTE: Macchiato Software only compiles properly in Arduino 1.0.5r2, using Mozzi library version 1.0.2. Efforts to update to newer compatibility have not yet been successful.

WHAT YOU WILL NEED

* Arduino IDE 1.0.5r2 
https://www.arduino.cc/en/main/OldSoftwareReleases 
* AVRDUDE v 5.10 or later (usually bundled with Arduino.) 
http://download.savannah.gnu.org/releases/avrdude/?C=M;O=A

* Mozzi library v1.0.2.
https://github.com/sensorium/Mozzi/releases/tag/v1.0.2

* Notepad++ or another text editor for working with program files
https://notepad-plus-plus.org/download/v7.3.1.html

* Macchiato Setup Files folder, from this repository 

* Macchiato-Mini-Synth sketch ( .ino) Latest Release from this repository.

### Let’s begin! 

1) If your installation of Arduino includes AVRDUDE version 5.10 or higher, skip to 3. Otherwise, install / upgrade to the latest version of AVRDUDE. 

2) If you do not already have a good C++ editor, treat yourself to Notepad++. This is the software we used to edit the Macchiato sketches. https://notepad-plus-plus.org/download/v7.4.2.html

3) Obtain and install the Mozzi library. Read the author’s release notes. Mozzi is a set of tools that tricks a microcontroller into behaving something like an oscillator. Place the Mozzi folder in your sketchbook\libraries\ folder. The path will look something like this:
C:\Users\Yourname\Documents\Arduino\libraries\

4) If your installation of Arduino does not include the MIDI library, fetch it here:
https://github.com/FortySevenEffects/
Note there are several different MIDI libraries in circulation. This is the one that comes bundled with new versions of Arduino, and is the one we used to deveolop Macchiato. Put this in the same folder as the Mozzi library.

5) Start Arduino 1.0.5 and install or activate the Mozzi and MIDI libraries. 

6) Find (search for) the file mozzi_config.h and open it for edit in Notepad++.
Uncomment the line “#define AUDIO_MODE HIFI” (delete the “//”). 
Comment out the line “#define AUDIO_MODE STANDARD_PLUS” (insert “//” at the start of the line). 
Save mozzi_config.h.

7) Download the file ramp512_int8.h from our Github page. In the Mozzi library, look for a folder called \tables\. it may look like this: 
C:\Users\Yourname\Documents\Arduino\libraries\sensorium_Mozzi-1.x.x\tables\.
Place the file in this folder.

(Mozzi creates sound waves by keeping track of what time it is, then looking up the amplitude of a waveform in a simple table of numbers. Silence = 0, maximum amplitude = 127. Mozzi comes standard with several different waveform tables in a variety of resolutions. A sawtooth waveform comes standard, in which the amplitude rises steadily from silence to maximum over one cycle: think "whooP! whooP! whooP!". This custom Ramp waveform is just a backwards Saw: the amplitude falls steadily from maximum to silence over one cycle: think "Pow! Pow! Pow!". Used as an audio waveform, the two shapes sound about the same, but used as a low frequency oscillator, they create dramatically different effects. This file drives the Ramp effect on the LFO Shape control, knob #5.)

8) Place your Latest Release Macchiato sketch (suffix .ino) in your Sketchbook folder.

The remaining steps add support for the 644PA microcontroller to your Arduino installation. 

9) Navigate to the file Arduino\hardware\arduino\boards.txt and open the file for edit in Notepad++.

10) In Macchiato_Setup_Files, open the file Atmel_Microcontroller_addition.txt in Notepad++. Copy and paste the file contents to the end of the boards.txt file. Save the boards.txt file.

11) Copy the folder 1284p from Macchiato_Setup_Files\ to Arduino\hardware\arduino\bootloaders.

12) Navigate to Arduino\hardware\arduino\variants\ and create the subfolder \1284p\.

Copy the file pins_arduino.h from Macchiato_Setup_Files\ to Arduino\hardware\arduino\variants\1284p\. WARNING! DO NOT USE ANY FILE OTHER THAN THE ONE INSIDE THE  Macchiato_Setup_Files FOLDER! There is a more recent file in the repository that WILL NOT WORK. It was associated with an obsolete release. We can't figure out how to remove it.

13) You are almost there! If Arduino is running, close it and then re-start it. Look in the pulldown menu Tools > Board >. Look for and select the entry "Atmega644PA @ 16MHz w/Arduino as ISP".

## TESTING

Load a short sample sketch from the EXAMPLES folders in the Mozzi library and see if it will compile. Now load the Macchiato sketch and see if it will compile. (The first time you open this file, Arduino will ask if you want to move it into its own folder. Say Yes.) If it does not compile, read the error messages carefully. They will likely reveal a missing or misplaced component somewhere. (There are usually some compile warnings generated by the Mozzi library itself. You can ignore these.) Compare the errors to these setup instructions. Correct the error and try again until the Macchiato sketch compiles. Write to us on our forum if you get stuck.

Congratulations! You are now ready to familiarize yourself with the possibilities of the Mozzi library and to develope your own custom Macchiato. For terrific Mozzi support, join the mozzi-users Google group. If you wish, feel free to create a branch off the Master branch here on Github. Either tweak the code as-is for enhanced performance, or use the Macchiato as a hardware platform to develop a completely different instrument. You have thirteen keys, eight knobs and even a few extra pins for input. Find out what you can do with them, and share it with the world!
