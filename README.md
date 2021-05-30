# FM Synthesizer controlled by hand movement
## Introduction
Implementation of a FM synthesizer, designed in **SUPERCOLLIDER**, controlled by tracking hand movements and visualization through geometric and colorfull animations, using **P5**. 

### What is a FM Synthesizer?
It is a synthesizer that exploits **Frequency Modulation**, where the carrier oscillator is modulated in frequency with modulators. **FM Synthesis** can create both harmonic and inharmonic sounds, depending on the ratio between the carrier frequency and the modulator frequency. If the modulators frequencies are multiple integers of the carrier frequency the sound will be harmonic, instead if the ratio is a non-integer fraction the sound will be inharmonic. In a FM synthetiser can be used a lot of algorithms to produce a large variety of sounds mixing more than one carriers and modulators (in some cases with feedback loops).
## Implementation
The implementation is divided in two main frames: **SuperCollider** that manages the *synth*,*MIDI* and *OSC client* parts and the **Control Interface** that manages the *Hand Tracking*, *Animations* and *OSC server* parts.
### SuperCollider
#### FM Synth
(davide)
#### MIDI
The synth *fm* is instantiated as a global variable (~monoNote) with amplitude equal to zero. The *noteOnFunc* exploits the *set* function and set the frequency, the amplitude (according to the normalized velocity) and the gate in order to trigger the attack of the envelop. The *noteOffFunc* uses the same *set* function and set the gate equal to zero in order to trigger the release of the synth. Therefore, using a MIDI keyboard 
#### OSC


### Control Interface
#### Hand Interaction
#### Animations

## How to use it
In order to use the application, run the server using Node.js with the command node .\server.js from terminal. Then
connect to the url localhost:55123 in a browser (it may take some seconds to load the ML model). Open the synth in SuperCollider and run all the code. Now you can enjoy the experience from your localhost page!

## Result and Demo


