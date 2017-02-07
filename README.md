# Macchiato-Mini-Synth
Mini Synth setup files, software sketches, executables, code development, new releases

## INTRODUCTION

The Macchiato Mini Synth by Zeppelin Design Labs is a nifty digital synthesizer that fits in the palm of your hand. The control software was developed in the Arduino environment, incorporating the Mozzi Sound Synthesis library by Tim Barrass. The software runs on an AtMega 644PA microcontroller.

On this GitHub page, you can modify the original source code and propose changes to the Macchiato software. We may from time to time release updated and improved versions of the original software, or alternate versions with completely different functions and sounds. To successfully edit and compile the code in Arduino (the sketch files, ending in .ino), you will need to perform some considerable setup first, which we will cover in detail later, in the section PROGRAMMING THE MACCHIATO. On the other hand, you can just download new releases (the binary, or hex files, ending with .cpp.hex) and flash them to your Macchiato. This is pretty easy.

The following notes are based on the Macchiato Quick Start Guide and Reference Manual by Zeppelin Design Labs, available for free download from www.zeppelindesignlabs.com/products/macchiato-mini-synth. The downloadable PDF is full of clickable hyperlinks which are not avaiable in this README document.

## FLASHING A BINARY TO YOUR MACCHIATO

Look under the hood of your Macchiato cabinet. See that little cluster of six pins sticking up to the right of the Zeppelin logo? These are the In-System Programming (ISP) header pins that allow you to communicate with the microcontroller that runs your synth. You use an inexpensive device called a programmer that connects the ISP header to a USB port on your PC. This allows you to upload, or "flash", new control software to your synth.

The microcontroller is the little square chip to the right of the ISP header. It is an Atmega 644pa microcontroller by Atmel. It belongs to a class of microcontrollers broadly called AVRs. (Atmel says AVR does not stand for anything in particular.) The actual program on the microcontroller is in the form of a “hex” file – a jumble of machine code that you and I cannot understand or unpack. Think of Cipher looking at the Matrix datastream. You can flash a new hex file to your Macchiato at any time, and then put back the original if you prefer.

To flash your synth, you will need the following:

* A USB Programmer such as USBTiny by Adafruit, or the AVR Pocket Programmer by Sparkfun. This is a piece of hardware that runs from your computer to your Mini-Synth. The programmer comes with a cable that connects to the ISP header. 
* A USB cable to connect your computer to your Programmer. This will probably be a Standard USB to Mini USB cable and might be included with your programmer.
* A driver (software) to install on your computer, which enables it to recognize and communicate with the programmer. The programmer you buy should include detailed instructions for how to obtain and install this driver.
* AVRDUDE (software) version 5.10. This is a free, simple command-line utility that sets up communication between your computer and your synth, and transfers (flashes) files to the microcontroller. Sparkfun has a fantastic tutorial explaining all this stuff. Find it here:
https://learn.sparkfun.com/tutorials/pocket-avr-programmer-hookup-guide/using-avrdude
The initial release of Macchiato was flashed using AVRDUDE version 5.10. Newer (higher) versions should work as well, but if you run into errors, try installing version 5.10. 

To flash a hex file:

1) Install the programmer’s driver.

2) Install AVRDUDE. It is a wee little thing and we like to install it to the user’s desktop, but you can put it anywhere you like. (You will have to place the hex file in the same folder as the AVRDUDE executable.)

3) Plug your programmer into a USB port on your computer.

4) Open a command prompt window. (On Windows machines, that's Start > run > cmd) Change to the directory containing the AVRDUDE executable. If you placed AVRDUDE on your desktop, then on a Windows PC the directory will look something like this:
C:\Users\Yourname\Desktop\ 

5) Verify that AVRDUDE is functioning and that it can identify your programmer. Follow the general procedure described in the Sparkfun article, adapted to your particular programmer.

6) Download the binary (hex) file you are interested in from this GitHub page, in the Macchiato-Control-Software folder, or from the Releases page. Place the hex file in the same folder as avrdude.exe.

7) Plug the programmer into the synth. Turn your synth off, turn the volume control all the way down, and connect your synth to your computer via your programmer cable. The MISO pin #1 is the top-left pin as you look at your synth. This pin will probably be identified with a dot on your programmer cable. Be careful not to attach the cable backwards. Your programmer probably has an option to send power through to the synthesizer. Turn it on. It will be a tiny switch on the programmer labelled something like "POWER TARGET". 

8) Verify that communication is established between the computer and the synth by entering this command:

C:\Users\Yourname\Desktop\ avrdude -c usbtiny -p m644p

Your file location may look different, and you may have a different argument after –c if you are using a different programmer. AVRDUDE should display a “Fuses OK” message. If not, study the Sparkfun article to troubleshoot.	

9) You are ready to upload your new hex file. Enter this command:

C:\Users\Yourname\Desktop\ avrdude -c usbtiny -p m644p -U flash:w:[filename].cpp.hex

Be sure the [filename] argument exactly matches the name of the hex file we sent you. AVRDUDE should erase the chip, read the new hex file, flash it to the chip, read it back off the chip, compare it to the original, and then announce that everything is OK and Thank you. 
Unplug the synth from the programmer. Turn it on, turn up the volume, and check out your new instrument!

## PROGRAMMING THE MACCHIATO

The Macchiato Mini-Synth incorporates the Mozzi Sound Synthesis Library for Arduino by Tim Barrass. Mozzi and Macchiato are both covered by the Creative Commons / Attribution license. You are free to modify and redistribute the Macchiato software as long as you give proper credit to the contributing creators. We hope you will use this GitHub page as the place to collaborate on new Macchiato software.

The Macchiato source code is posted in the folder Macciato Control Software. We encourage you to develop your own Macchiato software and submit it here for inclusion in future releases. To write and compile Macchiato sketches in the Arduino environment requires considerable setup. Following is a guide to the process. 

NOTE: We assume you are already running Arduino; you are familiar with AVRDUDE; and you are familiar with coding in C++.

WHAT YOU WILL NEED

Here are the software versions we used to compile the original Macchiato software, release v1_161122. Other versions may not be compatible: your sketch may not compile, or if it does, it may not run properly (or at all) on your Macchiato. PLEASE LET US KNOW if you discover specific version compatibilities or incompatibilities so we can develop a compatibility chart!

* Arduino IDE 1.0.5r2. 
https://www.arduino.cc/en/main/OldSoftwareReleases 
Newer versions may need a configuration change to be compatible with Mozzi 1.0.2. See Mozzi notes below.
* AVRDUDE v 5.10 or later (usually bundled with Arduino.) If you are using a newer version but run into persistent errors, try installing this version. It worked for us.
http://download.savannah.gnu.org/releases/avrdude/?C=M;O=A

* Mozzi library v1.0.2.
https://github.com/sensorium/Mozzi/releases
The versions of Mozzi and Arduuino listed here work great together. Some newer versions have known compatibility issues. Read the Mozzi release notes carefully when choosing a Mozzi version to use with your Arduino version. We will publish a compatibility chart as we receive data, so let us hear from you!

* Notepad++ or another text editor for working with program files
https://notepad-plus-plus.org/download/v7.3.1.html

* All the files and folders in the GitHub repository Macchiato-Mini-Synth/Macchiato Setup Files/. 

### Let’s begin! 

Be patient. This process is a little tricky; it may take some experimenting, research and troubleshooting to get it running.

1) If you are running Arduino version higher than 1.5, you will need to edit a configuration file to force the compiler to optimize for speed instead of size. See instructions on the Mozzi Github page. http://sensorium.github.io/Mozzi/blog/2016/11/26/tweak-for-faster-code/

2) If your installation of Arduino includes AVRDUDE version 5.10 or higher, skip to 3. Otherwise, install / upgrade to the latest version of AVRDUDE. Follow the author’s instructions and guidance.

3) If you do not already have a good C++ editor, treat yourself to Notepad++. This is the software we used to edit the Macchiato sketches.

4) Obtain and install the Mozzi library. Read the author’s release notes and installation instructions. Mozzi is a set of tools that fools an Arduino environment into handling audio signals, and tricks a microcontroller into behaving something like an oscillator. You will import the Mozzi tools into Arduino as a library.

5) Download everything in the Zeppelin Design Labs Github repository Macchiato-Mini-Synth\Macchiato Setup Files\. Place it all in a convenient temporary folder somewhere on your computer. You will copy the files and folders to various places on your computer. You will make edits to some existing Arduino files.

6) Copy the MIDI folder from Macchiato Setup Files\ to Arduino\libraries\. This is a set of tools that enables Arduino to interpret data entering a pin from a MIDI device.

7) Navigate to the file Arduino\libraries\sensorium_Mozzi-1.x.x\mozzi_config.h and open it for edit in Notepad++.
Uncomment the line “#define AUDIO_MODE HIFI” (delete the “//”). 
Comment out the line “#define AUDIO_MODE STANDARD_PLUS” (insert “//” at the start of the line). 
Save mozzi_config.h.
This changes the Mozzi system from Standard 8-bit audio mode to an enhanced HiFi mode. In Standard mode the microcontroller outputs an 8-bit signal on one output pin. In HiFi mode, it uses two output pins whose signals are merged downstream, to provide a much higher resolution signal. Clever, eh? You would suppose that's just like a 16-bit output signal, but actually it is customary to bit-shift the output to 14 bits, to provide a little headroom. 

8) Navigate to the file Arduino\libraries\sensorium_Mozzi-1.x.x\config\known_16bit_timers.h. Open the file for edit in Notepad++. 

9) In Macchiato_Setup_Files\, open the file Add_644pa_to_timers.txt. Copy and paste its contents into known_16bit_timers.h, near the end, just above the pair of #endif. 
Save known_16bit_timers.h.
Mozzi does not natively support the AtMega 644PA microcontroller. This edit tells Mozzi where to find the timer pins on the 644PA.

10) Copy the file ramp512_int8.h from Macchiato_Setup_Files\ to 
Arduino\libraries\sensorium_Mozzi-1.x.x\tables\.

(Mozzi creates sound waves by keeping track of what time it is, then looking up the amplitude of a waveform in a simple table of numbers. Silence = 0, maximum amplitude = 127. Mozzi comes standard with several different waveform tables in a variety of resolutions. A sawtooth waveform comes standard, in which the amplitude rises steadily from silence to maximum over one cycle: think "whooP! whooP! whooP!". This custom Ramp waveform is just a backwards Saw: the amplitude falls steadily from maximum to silence over one cycle: think "Pow! Pow! Pow!". Used as an audio waveform, the two shapes sound about the same, but used as a low frequency oscillator, they create dramatically different effects. This file drives the Ramp effect on the LFO Shape control, knob #5.)

The remaining steps add configuration information to your Arduino install so it will support a few more AtMega boards, including the 644PA at 16MHz. Taken together, they configure the 644PA specifically to run the Macchiato software. 

11) Navigate to the file Arduino\hardware\arduino\boards.txt and open the file for edit in Notepad++.

12) In Macchiato_Setup_Files\, open the file Atmel_Microcontroller_addition.txt in Notepad++. Copy and paste the file contents to the end of the boards.txt file. Save the boards.txt file. 

13) Copy the folder 1284p from Macchiato_Setup_Files\ to 
Arduino\hardware\arduino\bootloaders\.

14) Copy the file pins_arduino.h from Macchiato_Setup_Files\ to 
Arduino\hardware\arduino\variants\.

You are almost there! If Arduino is running, close it and then re-start it. Look in the pulldown menu Tools > Board >. Look for and select the entry "Atmega644PA @ 16MHz w/Arduino as ISP".

## TESTING
