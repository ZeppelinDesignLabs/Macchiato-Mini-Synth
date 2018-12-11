 /*
The Macchiato Mini Synth v1.2.0 by Zeppelin Design Labs, Chicago, Illinois. Copyright 2016,2017.
You are free to edit, add to, improve, destroy, ruin and otherwise modify this
software in any way. It is covered by the Creative Commons - Share Alike / Attribution / Non-Commercial license. 
If you modify this software and then share or distribute it in any way, you must
keep the following attributions present:
1) distrribute it under the same license terms
2} refrain from selling your work until you talk to the upstream creators (Zeppelin Design Labs and Tim Barrass)
3) include the following attributions:
"Macchiato Mini Synth software by Stephen Collier Cass, Purdue University, Lafayette,Indiana,
and Glen van Alkemade, Rose-Hulman Institute of Technology, Terre Haute, Indiana,
and Thomas K. Wray, School of Hard Knox
for Zeppelin Design Labs, Chicago, Illinois.
Featuring the Mozzi Synth Library by Tim Barrass."

Features of the synth software:
    2-note polyphony
    MIDI input:
Responds to pitch bend, note velocity, modulation, channel volume,and portamento time
    13 Capacitive Touch Keys (1 octave)
    Output Waveshape Adjust (Sine, Triangle, Sawtooth, Square)
    Octave adjust (C2 --> C3,C3 --> C4, C4 --> C5, C5 --> C6)
    Attack
    Release
    LFO waveshape Adjust  (Sine, Ramp,Sawtooth, Square)
   LFO Rate Adjust
   LPF Cutoff Frequency Adjust
   LFO Depth

The Macchiato Mini Synth runs on an Atmel ATMega 644PA microcontroller. The 13 capacitive touch keys and 8 control pots occupy most of the 644PAÃ¢â‚¬â„¢s inputs, but there are a few still available for incorporating additional features.
Share your mods on our forum at www.zeppelindesignlabs.com and/or the Google group mozzi-users.
*/ 


class RCpollAbstract{
  public:
  inline virtual unsigned int next()=0;
};

//Included Header Files
#include <MozziGuts.h>
#include <mozzi_analog.h>
#include <IntMap.h>
#include <Oscil.h>
#include <MIDI.h>
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>      //Used for MIDI calcs.  See MIDI.h & mozzi_midi.h to see where it's used
#include <ADSR.h>
#include <Portamento.h>
#include <LowPassFilter.h>
#include <RCpoll.h>
#include <EEPROM.h>



struct MidiSettings : public midi::DefaultSettings
{
 static const bool HandleNullVelocityNoteOnAsNoteOff = false;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MidiSettings);

//Oscillator Tables used for output Waveshape
#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/saw2048_int8.h>
#include <tables/square_no_alias_2048_int8.h>

//Oscillator Tables used for Low Frequency Oscillator (LFO)
#include <tables/sin512_int8.h>
#include <tables/saw512_int8.h>
#include <tables/ramp512_int8.h>
#include <tables/square_no_alias512_int8.h>

//Oscillator Functions declared for output waveforms, envelope 1 & 2.
Oscil <2048, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <2048, AUDIO_RATE> aTriangle1(TRIANGLE2048_DATA);
Oscil <2048, AUDIO_RATE> aSaw1(SAW2048_DATA);
Oscil <2048, AUDIO_RATE> aSquare1(SQUARE_NO_ALIAS_2048_DATA);

Oscil <2048, AUDIO_RATE>* waveforms[5] = {0 ,&aSin1,&aTriangle1,&aSaw1,&aSquare1};

Oscil <2048, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <2048, AUDIO_RATE> aTriangle2(TRIANGLE2048_DATA);
Oscil <2048, AUDIO_RATE> aSaw2(SAW2048_DATA);
Oscil <2048, AUDIO_RATE> aSquare2(SQUARE_NO_ALIAS_2048_DATA);

Oscil <2048, AUDIO_RATE>* waveforms2[5] = {0 ,&aSin2,&aTriangle2,&aSaw2,&aSquare2};

//Oscillator Function declared/define for LFO1&2 waveform
Oscil <512, AUDIO_RATE> klfo_sin1(SIN512_DATA);
Oscil <512, AUDIO_RATE> klfo_saw1(SAW512_DATA);
Oscil <512, AUDIO_RATE> klfo_ramp1(RAMP512_DATA);
Oscil <512, AUDIO_RATE> klfo_square1(SQUARE_NO_ALIAS512_DATA);

Oscil <512, AUDIO_RATE>* waveformsLFO[5] = {0 ,&klfo_sin1,&klfo_saw1,&klfo_ramp1,&klfo_square1};


#define CONTROL_RATE 128      // comment out to use default control rate of 64

//ADSR declaration/definition
ADSR <CONTROL_RATE, CONTROL_RATE> envelope1; 
ADSR <CONTROL_RATE, CONTROL_RATE> envelope2;
Portamento <CONTROL_RATE>aPortamento;

//Declaration/definitions for Capacitive Touch Sensor Keys

RCpoll <4>  key1;           //C 
RCpoll <10> key2;           //C_sharp
RCpoll <11> key3;           //D
RCpoll <14> key4;           //D_sharp
RCpoll <15> key5;           //E
RCpoll <16> key6;           //F
RCpoll <17> key7;           //F_sharp
RCpoll <18> key8;           //G
RCpoll <19> key9;           //G_sharp
RCpoll <20> key10;          //A
RCpoll <21> key11;          //A_sharp
RCpoll <22> key12;          //B
RCpoll <23> key13;          //High_C

RCpollAbstract * keys[13] = {&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8, &key9, &key10, &key11, &key12, &key13};

 int triggerA[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 int triggerB[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 int triggerC[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 int triggerZ[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 int debugCounter = 0;
 //byte midiSysex[128];

LowPassFilter lpf1;       //Short hand declaration for LowPassFilter
LowPassFilter lpf2;       // Necessary to get note2 to sound on its own


//-- Global variable declarations ----------------------------------------------------------------------------

byte mostRecentEnvelope = 2;                      // Holds record of most-recently-played note register.
int note1 = 129;                 // polyphony register 1. Default 129=no note assigned.
int note2 = 129;                 // polyphone register 2. Default 129=no note assigned.
int wav1;
int wav2;
int out;
byte velocity;  
byte gain_adsr1;        // Stores gain multiplier contributed by ADSR envelope1
byte gain_adsr2;        // Stores gain multiplier contributed by ADSR envelope2
byte gain_lfo1;         // Stores gain multiplier contributed by lfo.
float carrierFreq1 = 10.f;
float carrierFreq2 = 10.f;
float shifted1;
float shifted2;
float PBmax=0.12246;
float PBmin=0.10911;
byte channelVolume = 127;
bool PortaOn = false;
bool midiChannelSelect = false;
int pitch;
int pitch1;
int pitch2;
byte j = 1;           //a counter.
byte note_available[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};   //Array used to determine if a note is available to play

//The following stores four octaves of pitches, rounded to nearest integer value.

unsigned int pitch_array[4][13]= {
  {65,   69,  73,  78,  82,  87,  92,  98, 104, 110, 117, 123, 131},
  {131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262},
  {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523},
  {523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,1046}
  };  

float Bends[2][13] = {
  {0.000, 0.0595, 0.1225, 0.1892, 0.2599, 0.3348, 0.4142, 0.4983, 0.5874, 0.6818, 0.7818, 0.8877, 1.000}, // bend-up ratio, PBmax
  {0.000, 0.0561, 0.1091, 0.1591, 0.2063, 0.2508, 0.2929, 0.3326, 0.3700, 0.4054, 0.4388, 0.4703, 0.500}  // bend-down ratio, PBmin
  }; 
  
//The following are associated with the eight control pots on the synth, numbered 1-8 left to right.
byte wave_form;         // Store the output waveform selection 1-2-3-4. Pot 1.
byte octave;              // store the octave register (0-1-2-3). Pot 2. 
unsigned int attack_ms;     // Attack time, milliseconds. Pot 3.
unsigned int release_ms;    // Decay time, milliseconds. Pot 4.
byte LFO_wave_form;         // LFO waveshape select. Pot 5.
unsigned int lfo_speed;     // LFO speed, or LFO freq if you will. Pot 6.
unsigned int cutoff;      // LPF cutoff frequency f. Pot 7.
unsigned int lfo_depth;     
unsigned int lfo_depth_pot;   // LFO depth, pot 8
unsigned int lfo_depth_old;

// The following are the first half of mozzi Integer Map, faster than arduino map.
// They correspond to the eight pots on the synth. 

const IntMap waveIntMap(0,1024,1,7);        // returns 1-2-3-4. Pot 1
const IntMap octIntMap(0,1024,0,5);        // returns 0-1-2-3. Use as Array Row. Pot 2
const IntMap attackIntMap(0,1024,28,2500);    // Min value must be large enough to prevent click at note start.
const IntMap releaseIntMap(0,1024,25,3000);   // Min value must be large enough to prevent click at note end.
const IntMap lfo_waveIntMap(0,1024,1,5);    // 1,5 returns 1-2-3-4.  
const IntMap lfo_speedIntMap(0,1024,0,1400);  // 
const IntMap cutoffIntMap(0, 1024, 30, 180);  // Valid range 0-255 corresponds to freq 0-8192 (audio rate/2).
const IntMap lfo_depthIntMap(0, 1024, 1, 256);  // LFO depth, as a percent multiplier of cutoff. 1=0% of cutoff, 256=100% of cutoff.

// ----------------------------------------------------------------------------------------- 

void setup()
{
  int midiChannel;
  bool x = true;
  for (int i = 24; i <= 31; i++) {     
  if (analogRead(i) < 1000){
  x = false;
    }    
  }
  if (x){
    midiChannelSelect = true;
    EEPROM.write(3, true);
  }
  if (EEPROM.read(3) == true){
    midiChannel = MIDI_CHANNEL_OMNI;
  }
  else{
    midiChannel = EEPROM.read(2) > 16 ? 0 : EEPROM.read(2);
  }
  startMozzi(CONTROL_RATE);                     // Start the use of Mozzi with defined CONTROL_RATE
  MIDI.begin(midiChannel);               
  MIDI.setHandleNoteOn(handle_note_on);         // For detecting and setting what MIDI note is being pressed
  MIDI.setHandleNoteOff(handle_note_off);
  MIDI.setHandlePitchBend(HandlePitchBend);
  MIDI.setHandleControlChange(handle_control_change);
  aPortamento.setTime(0); //prt
  envelope1.setADLevels(250,250);               // Sets Attack and Decay Levels; assumes Sustain, Decay, and Idle times
  envelope1.setDecayTime(100);                  // Sets Decay time in milliseconds
  envelope1.setSustainTime(32500);              // Sustain Time setting for envelope1 
  envelope2.setADLevels(250,250);               // Sets Attack and Decay Levels; assumes Sustain, Decay, and Idle times
  envelope2.setDecayTime(100);                  // Sets Decay time in milliseconds
  envelope2.setSustainTime(32500);              // Sustain Time setting for envelope2
//------FUNCTIONS-------------------------------------------------------------------------------

}


void handle_note_on(byte channel, byte note, byte velocity)
{
    if (midiChannelSelect){
    EEPROM.write(2, channel);
    EEPROM.write(3, false);
    MIDI.setInputChannel(channel);
  } 
  if (velocity == 0)            // if key has just been released
  {
    if(note == note1)     // If the note was playing in register 1,
    {
      envelope1.noteOff();      // turn off envelope1
      note1 = 129;               // reset register 1 to default not-in-use value of 129.
    }
    if(note == note2)   // If note was playing on register 2,
    {
      envelope2.noteOff();      // turn off envelope2
      note2 = 129;               // reset register 2 to default not-in-use value of 129.
    }
  }
  else                          // If key has just been pressed,
  if(PortaOn==true)
    {
    aPortamento.start(note);    
      note2 = note;  
    //Store the second MIDI note in register 2
    envelope2.setADLevels(velocity*2,velocity*2); 
    envelope2.noteOn();
     mostRecentEnvelope=2;
    }
   else
  if((note1 == 129) || (mostRecentEnvelope == 2 && note2 < 129))      // condidtions for sounding on register 1
   {
      note1 = note;                 //Store the value of MIDI note in register 1.
      if(PortaOn==false)
    {
    pitch1 = Q16n16_to_float(Q16n16_mtof(Q8n0_to_Q16n16(note)));
    waveforms[wave_form]->setFreq(pitch1);
    }
      envelope1.setADLevels(velocity*2,velocity*2);               // Sets Attack and Decay Levels; assumes Sustain, Decay, and Idle times
    envelope1.noteOn();
     mostRecentEnvelope=1;
    }
    else                      // if not register 1, then use register 2.
   {
      note2 = note;                 //Store the second MIDI note in register 2.
      if(PortaOn==false)
    {
    pitch2 = Q16n16_to_float(Q16n16_mtof(Q8n0_to_Q16n16(note)));
    waveforms2[wave_form]->setFreq(pitch2);
    }
      envelope2.setADLevels(velocity*2,velocity*2); 
    envelope2.noteOn();
     mostRecentEnvelope=2;
    }
  }
void handle_note_off(byte channel, byte note, byte velocity){   
    handle_note_on(channel, note, 0);
}


void handle_control_change(byte channel, byte number, byte value){
  if (midiChannelSelect){
    EEPROM.write(2, channel);
    EEPROM.write(3, false);
    MIDI.setInputChannel(channel);
  }
switch (number)
  {
  case 1:   // Modulation
    lfo_depth = value*2+1;  // MIDI produces 0-127. lfo_depth wants 1-256.
    break;

  case 5:   // PortamentoTime   
    PortaOn = (bool)value;
    if (PortaOn){
    aPortamento.setTime(value*8);// value=0-127, so time=0-1000 milliseconds
    }
    break;  
    
  case 7:   // Channel volume
    channelVolume = value;
    break;
      
  case 20:    // Pitch Bned Max/Min, value = 2->7 semitones. Look up multiplier in Bends array.
    PBmax = Bends[0][value];
    PBmin = Bends[1][value];
    break;
  case 124:
   EEPROM.write(3, false);
   MIDI.setInputChannel(EEPROM.read(2) > 16 ? 0 : EEPROM.read(2));   
  break;
  case 125:
  EEPROM.write(3, true);
  MIDI.setInputChannel(MIDI_CHANNEL_OMNI);
  break;
  default:
  break;
  }
}

float iPitchBend(int bend){
  if(bend>0){
    return (1 + float(bend/8192.0f) * PBmax);//bend value from +/-8192. Bend range from 0 to 12 semitones, rec'd on CC#20
  }
  else if(bend < 0){
    return (1 + float(bend/8192.0f) * PBmin);
  }
    else return 1;
  }
  
void HandlePitchBend (byte channel, int bend){
  float pitchBend = iPitchBend(bend);
waveforms[wave_form]->setFreq(pitch1*pitchBend);
waveforms2[wave_form]->setFreq(pitch2*pitchBend);
}



//-----end Setup-----------------------------------------------------------------------------------

void updateControl()
{
  //TCCR2B = 0;
 // Local Variables ------------------------------------------------
//noInterrupts();

 // ---------------------------------------------------------------------
 
 // Read the Pots, just one per Update cycle. This saves tremendous CPU time with no audible difference (in most cases)

 switch (j){
    case 1:
      wave_form = waveIntMap(mozziAnalogRead(30));          // returns 1-2-3-4. Pot 1
      break;
    case 2:
      octave = octIntMap(mozziAnalogRead(31));            // returns 0-1-2-3. Pot 2
      break;
    case 3:
      attack_ms = attackIntMap(mozziAnalogRead(24));    // pot 3
    envelope1.setAttackTime(attack_ms);
      envelope2.setAttackTime(attack_ms);
    break;
    case 4:
      release_ms = releaseIntMap(mozziAnalogRead(25));    // Pot 4
      envelope1.setReleaseTime(release_ms); 
      envelope2.setReleaseTime(release_ms); 
    break;
    case 5: 
      LFO_wave_form = lfo_waveIntMap(mozziAnalogRead(26));  // returns 1-2-3-4. Pot 5
      break;
    case 6:
    lfo_speed = lfo_speedIntMap(mozziAnalogRead(27));
    waveformsLFO[LFO_wave_form]->setFreq((int)lfo_speed);
    break;
   case 7:
    lfo_depth_pot = lfo_depthIntMap(mozziAnalogRead(29));   // LFO Depth, Pot 8
      if(lfo_depth_pot != lfo_depth_old)
    {
    lfo_depth_old = lfo_depth_pot;
    lfo_depth = lfo_depth_pot;
    }
  break;
    }
j++;
if(j>7){j=0;}         // This index steps us through the above seven pot reads, one per control update.

// The following control requires CONTROL_RATE update for smooth sound. 
cutoff = cutoffIntMap(mozziAnalogRead(28));             // Pot 7

// Set up LFO ----------------------------------------------------------------------------------
  /*
    The following section sets up the LFO to contribute to cutoff frequency.
    Setting paramters and updates occur in a logical order, not related to 
    the order of the pots on the synth:
      --> LFO speed (already set, above)
      --> LFO waveshape 
      --> LPF Cutoff Frequency
      --> Resonance
  */
/*
  Following calculates the value of the LFO wave and stores the result
  in a variable (gain_lfo1) used to influence cutoff frequency.
  The conditionals retrieve gain value from the appropriate waveform
  based on the value of LFO_wave_form.
  The math returns values from 1-256 which is combined with
  cutoff and LFO_depth. 
*/

gain_lfo1 = (int)((long)(waveformsLFO[LFO_wave_form]->next() + 128) * lfo_depth) >> 8; 
    
// Set up LPF ------------------------------------------------------------------------------------

  out = cutoff - ((long)(cutoff * gain_lfo1)>>8);   // This adds the LFO component dangling below the cutoff value. Increasing lfo_depth extends this componenet down to cutoff=0 at max depth.
  lpf1.setCutoffFreq(out);
  lpf2.setCutoffFreq(out);            // It really does appear necessary to use two lpf calls to create proper polyphony.
  
  switch(wave_form)
    {case 1:
    lpf1.setResonance(190);                 // Sine wave max resonance    
    lpf2.setResonance(190);
  case 2:
    lpf1.setResonance(190);                 // Triangle max resonance
    lpf2.setResonance(190);
    case 3:
    lpf1.setResonance(180);                 // Saw max resonance
    lpf2.setResonance(180);
  case 4:
    lpf1.setResonance(35);                  // Square wave max resonance
    lpf2.setResonance(35);
  }
   
// Poll for Notes: MIDI then CTKeys -------------------------------------------------------------------------

  MIDI.read();                      //Reads if there is a MIDI event and handles it.
// "For" loop for polling capacitive touch keys and turning notes on and off. ----------------

  for (byte i = 0; i < 13; i++)
  {
   triggerA[i] = keys[i]->next();
   triggerZ[i] = triggerZ[i] & (triggerA[i] | triggerB[i] | triggerC[i]) | (triggerA[i] & triggerB[i] & triggerC[i]);
   triggerC[i] = triggerB[i];
   triggerB[i] = triggerA[i];   

  if((triggerZ[i] > 0) && (note_available[i] == 1))  //if key #i is pressed and is available to sound (ie, not already sounding)
    { 
    pitch = pitch_array[octave][i]; 
    note_available[i] = 0;              // mark note as unavailable, ie, playing
    if((note1 == 129) || (mostRecentEnvelope == 2 && note2 < 129))    // condidtions for sounding on register 1
    {
      note1 = i;                  //Indicate that Register 1 is currently playing note i.
        pitch1 = pitch;
        waveforms[wave_form]->setFreq(pitch1);                                            
      envelope1.setADLevels(240,240);
      envelope1.noteOn();
      mostRecentEnvelope = 1;                   // Mark register 1 as most recently played.
    }
    else                      // If conditions for using Reg 1 are not met, then use Register 2.
    {
      if(PortaOn==false)
        {
      note2 = i;                  // Indicate that Register 2 is currently playing note i.
        pitch2 = pitch;
        waveforms2[wave_form]->setFreq(pitch2);  
        
      envelope2.setADLevels(240,240);
      envelope2.noteOn();
      mostRecentEnvelope = 2;
        }// Mark register 2 as most recently played.
    }
  }
  if(triggerZ[i] == 0 && note_available[i] == 0)     // Key is not pressed but was playing, ie, key has just been released
    {
    note_available[i] = 1;              // key has just been released; mark it as available
    if(i == note1)                  // if current note i was playing in register 1,
    {
      envelope1.noteOff();                    // Turn off envelope1
      note1 = 129;                              // Clear register 1.
      mostRecentEnvelope = 2;
    }
    else if(i == note2)               // else, if current note i was playing in register 2,
    {
      envelope2.noteOff();                    // Turn off envelope2
      note2 = 129;                              // Clear register 2.
      mostRecentEnvelope = 1;
    }
  } 
  }                           // Next i.

  envelope1.update();
  envelope2.update();
  gain_adsr1 = (long)channelVolume * envelope1.next() >> 8;
 if(PortaOn==true){
  waveforms2[wave_form]->setFreq_Q16n16(aPortamento.next());
  }
  gain_adsr2 = (long)channelVolume * envelope2.next() >> 8;
/*
  midiSysex[debugCounter] = trigger[2];
  debugCounter++;
  if (debugCounter >= 128){
  MIDI.sendSysEx(128, midiSysex, false);
  debugCounter = 0;
  }
  */
 //interrupts();
} 
//----------end UpdateControl ---------------------------------------------------------------

int updateAudio()

{ 
wav1 = waveforms[wave_form]->next();
wav2 = waveforms2[wave_form]->next();
return (int) (((long) gain_adsr1 * (-1 - lpf1.next(wav1)) + (long) gain_adsr2 * (-1 -lpf2.next(wav2))) >> 3);  
}

//----end updateAudio -------------------------------------------------------------------------

void loop()
{
  audioHook();              //Required here
}





