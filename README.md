# Macchiato-Mini-Synth
Mini Synth software sketches, executables, code development, new releases. ALWAYS USE LATEST VERSION! Current Release is 1.1.0; file names include v1_171009.

## INTRODUCTION

The Macchiato Mini Synth by Zeppelin Design Labs is a nifty digital synthesizer that fits in the palm of your hand. The control software was developed in the Arduino environment, incorporating the Mozzi Sound Synthesis library by Tim Barrass. The software runs on an AtMega 644PA microcontroller.

On this GitHub page, you can modify the original source code and propose changes to the Macchiato software. We may from time to time release updated and improved versions of the original software, or alternate versions with completely different functions and sounds. It is easy to edit the sketch (the program code, file ending in .ino) in Arduino verison 1.8.3. Detailed installation instructions are in the section PROGRAMMING THE MACCHIATO. Or you can just download new releases (the binary, or hex files, ending with .hex) and flash them to your Macchiato. This is covered in the following section.

## FLASHING A BINARY TO YOUR MACCHIATO

Look under the hood of your Macchiato cabinet. See that little cluster of six pins sticking up to the right of the Zeppelin logo? These are the In-System Programming (ISP) header pins that allow you to communicate with the microcontroller that runs your synth. You use an inexpensive device called a programmer that connects the ISP header to a USB port on your PC. This allows you to upload, or "flash", new control software to your synth.

The microcontroller is the little square chip to the right of the ISP header. It is an ATmega644PA microcontroller by Atmel. It belongs to a class of microcontrollers broadly called AVRs. (Atmel says AVR does not stand for anything in particular.) The actual program on the microcontroller is in the form of a "binary" or “hex” file – a jumble of machine code that you and I cannot understand or easily unpack. Think of Cipher looking at the Matrix datastream. You can flash a new hex file to your Macchiato at any time.

To flash your synth, you will need the following:

* A USB Programmer such as AVR Pocket Programmer by Sparkfun (https://www.sparkfun.com/products/9825), or USBTiny by Adafruit (https://www.adafruit.com/products/46). This is a piece of hardware that runs from your computer to your Mini-Synth. The programmer comes with a cable that connects to the ISP header. 
* A USB cable to connect your computer to your Programmer. This will probably be a Standard USB to Mini USB cable and might be included with your programmer.
* A driver (software) to install on your computer, which enables it to recognize and communicate with the programmer. The programmer you buy should include detailed instructions for how to obtain and install this driver.
* AVRDUDE version 5.10 or later. This is a free, simple command-line software utility that sets up communication between your computer and your synth, and transfers (flashes) files to the microcontroller. It is included as part of any Arduino installation, or you can find it here:
http://download.savannah.gnu.org/releases/avrdude/?C=M;O=A
Sparkfun has a fantastic tutorial explaining all this stuff. Find it here:
https://learn.sparkfun.com/tutorials/pocket-avr-programmer-hookup-guide/using-avrdude
* A Macchiato hex file. See #6 below. 

To flash a hex file:

1) Install the programmer’s driver.

2) Install AVRDUDE. It is a wee little thing and we like to install it to the user’s desktop, but you can put it anywhere you like. (You will have to place the hex file in the same folder as the AVRDUDE executable.)

3) Plug your programmer into a USB port on your computer.

4) Open a command prompt window. (On Windows machines, that's Start > run > cmd) Change to the directory containing the AVRDUDE executable. If you placed AVRDUDE on your desktop, then on a Windows PC the directory will look something like this:
C:\Users\Yourname\Desktop\ 

5) Verify that AVRDUDE is functioning and that it can identify your programmer. Follow the general procedure described in the Sparkfun article, adapted to your particular programmer.

6) Download the binary (hex) file you are interested in from this GitHub page. Go to the Releases page, pick a release that sounds promising, and download the .hex file. As of this writing (October 2017) we only recommend Release 1.1.1, filename Macchiato_Mini_Synthv1_171009.hex. Place the hex file in the same folder as avrdude.exe.

7a) Plug the programmer into the synth. To do this, turn your synth off, turn the volume control all the way down, and connect your programmer cable to the ISP header. The MISO pin #1 is the top-left pin as you look at your synth. This pin will probably be identified with a dot on your programmer cable. Be careful not to attach the cable backwards. 

7b) Your programmer probably has an option to send power through to the synthesizer. Turn it on. It will be a tiny switch on the programmer labelled something like "POWER TARGET". 

8) Verify that communication is established between the computer and the synth by entering this command:

C:\Users\Yourname\Desktop\ avrdude -c usbtiny -p m644p

Your file location may look different, and you may have a different argument after –c if you are using a different programmer. AVRDUDE should display a “Fuses OK” message. If not, study the Sparkfun article to troubleshoot.	

9) You are ready to upload your new hex file. Enter this command:

C:\Users\Yourname\Desktop\ avrdude -c usbtiny -p m644p -U flash:w:[filename].ino.hex

Be sure the [filename] argument exactly matches the name of the hex file you downloaded. AVRDUDE should erase the chip, read the new hex file, flash it to the chip, read it back off the chip, compare it to the original, and then announce that everything is OK and Thank you. 
Unplug the synth from the programmer. Turn it on, turn up the volume, and check out your new instrument!

## PROGRAMMING THE MACCHIATO

The Macchiato Mini-Synth incorporates the Mozzi Sound Synthesis Library for Arduino by Tim Barrass. Mozzi and Macchiato are both covered by the Creative Commons / Attribution / Non-Commercial license. You are free to modify and redistribute the Macchiato software as long as you give proper credit to the contributing creators. (You cannot sell anything incorporating Mozzi without the permission of its creator Tim Barrass.) We hope you will use this GitHub page as the place to collaborate on new Macchiato software.

The Macchiato source code (file suffix .ino) is posted here on Github on the Releases page. We suggest you only use the Latest Release, 1.1.1 as of this writing, October 2017.  We encourage you to develop your own Macchiato software and submit it here for inclusion in future releases. To write and compile Macchiato sketches in the Arduino environment requires a little bit of setup. 

NOTE: We assume you are already running Arduino version 1.8.3; you are familiar with AVRDUDE; and you are familiar with coding in C++.

WHAT YOU WILL NEED

Here are the software versions we used to compile the latest Macchiato software, version 1.1.0. The original release required considerable setup to compile in Arduino; the latest version is easy. PLEASE LET US KNOW if you discover specific version compatibilities or incompatibilities so we can develop a compatibility chart!

* Arduino IDE 1.8.3 
https://www.arduino.cc/en/main/OldSoftwareReleases 
* AVRDUDE v 5.10 or later (usually bundled with Arduino.) 
http://download.savannah.gnu.org/releases/avrdude/?C=M;O=A

* Mozzi library v1.0.3rc6.
https://github.com/sensorium/Mozzi/releases
Older versions of Arduino and Mozzi have serious compatibility issues.

* Notepad++ or another text editor for working with program files
https://notepad-plus-plus.org/download/v7.3.1.html

* Macchiato-Mini-Synth v1.1.0 from this GitHub Releases page. Download the sketch file, Macchiato_Mini_Synthv1_171009.ino. 

### Let’s begin! 

1) If your installation of Arduino includes AVRDUDE version 5.10 or higher, skip to 3. Otherwise, install / upgrade to the latest version of AVRDUDE. 

2) If you do not already have a good C++ editor, treat yourself to Notepad++. This is the software we used to edit the Macchiato sketches. https://notepad-plus-plus.org/download/v7.4.2.html

3) Obtain and install the Mozzi library. Read the author’s release notes and installation instructions. Mozzi is a set of tools that fools an Arduino environment into handling audio signals, and tricks a microcontroller into behaving something like an oscillator. You will import the Mozzi tools into Arduino as a library. Place the Mozzi folder in your sketchbook folder, in the \libraries\ folder. The path will look something like this:
C:\Users\Yourname\Documents\Arduino\libraries\

4) If your installation of Arduino does not include the MIDI library, fetch it here:
https://github.com/FortySevenEffects/
Note there are several different MIDI libraries in circulation. This is the one that comes bundled with new versions of Arduino, and is the one we used to deveolop Macchiato 1.1.1. Put this in the same folder as the Mozzi library.

5) Start Arduino and install or activate the Mozzi and MIDI libraries using Library Manager. 

6) Find (search for) the file mozzi_config.h and open it for edit in Notepad++.
Uncomment the line “#define AUDIO_MODE HIFI” (delete the “//”). 
Comment out the line “#define AUDIO_MODE STANDARD_PLUS” (insert “//” at the start of the line). 
Save mozzi_config.h.

(This changes the Mozzi system from Standard 8-bit audio mode to an enhanced HiFi mode. In Standard mode the microcontroller outputs an 8-bit signal on one output pin. In HiFi mode, it uses two output pins whose signals are merged downstream, to provide a much higher resolution signal. Clever, eh? You would suppose that's just like a 16-bit output signal, but actually it is customary to bit-shift the output to 14 bits, to provide a little headroom.)

7) Download the file ramp512_int8.h from our Github page. In the Mozzi library, look for a folder called \tables\. it may look like this: 
C:\Users\Yourname\Documents\Arduino\libraries\sensorium_Mozzi-1.x.x\tables\.
Place the file in this folder.

(Mozzi creates sound waves by keeping track of what time it is, then looking up the amplitude of a waveform in a simple table of numbers. Silence = 0, maximum amplitude = 127. Mozzi comes standard with several different waveform tables in a variety of resolutions. A sawtooth waveform comes standard, in which the amplitude rises steadily from silence to maximum over one cycle: think "whooP! whooP! whooP!". This custom Ramp waveform is just a backwards Saw: the amplitude falls steadily from maximum to silence over one cycle: think "Pow! Pow! Pow!". Used as an audio waveform, the two shapes sound about the same, but used as a low frequency oscillator, they create dramatically different effects. This file drives the Ramp effect on the LFO Shape control, knob #5.)

8) And of course download the sketch, Release 1.1.1, Macchiato_Mini_Synthv1_171009.ino. Place the file in your Sketchbook folder.

The remaining steps add support for the 644PA microcontroller to your Arduino installation. 

9) Open the Arduino IDE.
Open the File > Preferences menu item.
Enter the following URL in Additional Boards Manager URLs:
https://mcudude.github.io/MightyCore/package_MCUdude_MightyCore_index.json
Separate the URLs using a comma ( , ) if you have more than one URL
Open the Tools > Board > Boards Manager... menu item.
Wait for the platform indexes to finish downloading.
Scroll down until you see the MightyCore entry and click on it.
Click Install.
After installation is complete close the Boards Manager window.

10) The last step is to make an edit to the pinout file associated with the 644 board. The filename is pins_arduino.h, but there are a lot of files with that name in an Arduino installation. The one you need is in a path that looks something like this: 
C:\Users\Yourname\appdata\Local\Arduino15\packages\mightycore\hardware\avr\{version number}\variants\standard\pins_arduino.h
Try searching your appdata folder for \standard\pins_arduino.h. When you find it, create a backup and then open the .h file in Notepad++.

11) Find the TIMER section under the AT644P__ board. The file version I am editing contains these lines:

defined(__AVR_ATmega644P__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{

Change everything inside the braces to "NOT_ON_TIMER". There should be several lines already like this so you can just copy those lines onto the ones that aren't. You may want to leave a comment to yourself of when and why you made this edit, and where to find the backup. Save the pins_arduino.h file.

You are almost there! If Arduino is running, close it and then re-start it. Look in the pulldown menu Tools > Board > and make these selections: ATmega644, version A, clock 16MHz crystal, BOD 4.7, TOD Disabled, Arduino as ISP.

## TESTING

Load a short sample sketch from the EXAMPLES folders in the Mozzi library and see if it will compile. Now load the Macchiato sketch and see if it will compile. (The first time you open this file, Arduino will ask if you want to move it into its own folder. Say Yes.) If it does not compile, read the error messages carefully. They will likely reveal a missing or misplaced component somewhere. (There are usually some compile warnings generated by the Mozzi library itself. You can ignore these.) Compare the errors to these setup instructions. Correct the error and try again until the Macchiato sketch compiles. Write to us on our forum if you get stuck.

Congratulations! You are now ready to familiarize yourself with the possibilities of the Mozzi library and to develope your own custom Macchiato. For terrific Mozzi support, join the mozzi-users Google group. If you wish, feel free to create a branch off the Master branch here on Github. Either tweak the code as-is for enhanced performance, or use the Macchiato as a hardware platform to develop a completely different instrument. You have thirteen keys, eight knobs and even a few extra pins for input. Find out what you can do with them, and share it with the world!
