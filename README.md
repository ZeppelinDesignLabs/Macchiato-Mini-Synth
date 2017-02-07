# Macchiato-Mini-Synth
Mini Synth setup files, software sketches, executables, code development, new releases

# INTRODUCTION

The Macchiato Mini Synth by Zeppelin Design Labs is a nifty digital synthesizer that fits in the palm of your hand. The control software was developed in the Arduino environment, incorporating the Mozzi Sound Synthesis library by Tim Barrass. The software runs on an AtMega 644PA microcontroller.

On this GitHub page, you can modify the original source code and propose changes to the Macchiato software. We may from time to time release updated and improved versions of the original software, or alternate versions with completely different functions and sounds. To successfully edit and compile the code in Arduino (the sketch files, ending in .ino), you will need to perform some considerable setup first, which we will cover in detail later, in the section PROGRAMMING THE MACCHIATO. On the other hand, you can just download new releases (the binary, or hex files, ending with .cpp.hex) and flash them to your Macchiato. This is pretty easy.

The following notes are based on the Macchiato Quick Start Guide and Reference Manual by Zeppelin Design Labs, available for free download from www.zeppelindesignlabs.com/products/macchiato-mini-synth. The downloadable PDF is full of clickable hyperlinks which are not avaiable in this README document.

# FLASHING A BINARY TO YOUR MACCHIATO

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

# PROGRAMMING THE MACCHIATO

The Macchiato Mini-Synth incorporates the Mozzi Sound Synthesis Library for Arduino by Tim Barrass. Mozzi and Macchiato are both covered by the Creative Commons / Attribution license. You are free to modify and redistribute the Macchiato software as long as you give proper credit to the contributing creators. We hope you will use this GitHub page as the place to collaborate on new Macchiato software.

The Macchiato source code is posted in the folder Macciato Control Software. on the Zeppelin Design Labs Github page, both as an Arduino sketch (.ino file) and as a compiled hex file (.cpp.hex). We may from time to time publish updates, or even completely new code for a totally different synth to run on the same Macchiato hardware. You may develop your own Macchiato software and contribute it to our Github page. To upload a hex file is a fairly easy matter, and is discussed in the section “ISP Header; Flashing New Programs” above. To write, compile and flash your own code requires considerably more setup. Following is a guide to the process. 
NOTE: We assume you are already running Arduino; you are familiar with AVRDUDE; and you are familiar with coding in C++.
WHAT YOU WILL NEED
Here are the software versions we used to compile the original Macchiato software. Other versions may not be compatible: your sketch may not compile, or if it does, it may not run properly (or at all) on your Macchiato. The Zeppelin Design Labs Github page will have the latest versions and variants.
Arduino IDE 1.0.5r2. Newer versions may need a configuration change to be compatible with Mozzi 1.0.2.
AVRDUDE v 5.10 or later (usually bundled with Arduino.)
Mozzi library v1.0.2 added to Arduino. The listed versions of Mozzi and Arduuino work great together. Newer versions have compatibility issues. See the Zeppelin Design Labs Github page for latest compatibility news.
Notepad++ or another text editor for working with program files
All the files in the Macchiato-Setupfiles repository on Github -- except files beginning with .git! Download all the files and folders into one new, temporary folder in a convenient location on your workstation.
Let’s begin! 
Be patient. This process is a little tricky; it may take a little experimenting, research and troubleshooting to get it running.
If you are running Arduino version higher than 1.0.5, you will need to edit a configuration file to force the compiler to optimize for speed instead of size. See instructions here.
If your installation of Arduino includes AVRDUDE version 5.10 or higher, skip to 3. Otherwise, install / upgrade to the latest version of AVRDUDE here. Follow the author’s instructions and guidance.
If you do not already have a good C++ editor, treat yourself to Notepad++. This is the software we used to edit the Macchiato sketches.
Obtain and install the Mozzi library. Read the author’s release notes and installation instructions.
Obtain Macchiato_Setup_Files.zip from Zeppelin Design Labs. Unpack it somewhere temporary on your computer. There’s a bunch of stuff in there that you will copy to various places on your computer. You will make edits to some existing Arduino files.
Copy the MIDI folder from Macchiato_Setup_Files to Arduino\libraries\.
Navigate to Arduino\libraries\Mozzi-1.0.x\mozzi_config.h and open for edit in Notepad++.
Uncomment the line “#define AUDIO_MODE HIFI” (delete the “//”). 
Comment out the line “#define AUDIO_MODE STANDARD_PLUS” (insert “//” at the start of the line). 
Save mozzi_config.h.
Navigate to Arduino\libraries\Mozzi-1.0.x\config\known_16bit_timers.h. Open for edit in Notepad++. 
In Macchiato_Setup_Files, open the file Add_644p_to_timers.txt. Copy and paste its contents into known_16bit_timers.h, near the end, just above the pair of #endif. 
Save known_16bit_timers.h.
Copy the file ramp2048_int8.h from Macchiato_Setup_Files to 
Arduino\libraries\Mozzi-1.0.x\tables\.
Navigate to Arduino\hardware\arduino\boards.txt and open the file for edit in Notepad++.
In Macchiato_Setup_Files, open the file Atmel_Microcontroller_addition.txt in Notepad++. Copy and paste the file contents to the end of the boards.txt file. Save the boards.txt file. 
Copy the folder 1284p from Macchiato_Setup_Files to 
Arduino\hardware\arduino\bootloaders\.
Copy the file pins_arduino.h from Macchiato_Setup_Files to 
Arduino\hardware\arduino\variants\.
You are almost there. It may be helpful to reboot your computer at this point.
Run Arduino. In the BOARDS pulldown menu, set the board to “Atmega644p @ 16MHz w/Arduino as ISP”.

