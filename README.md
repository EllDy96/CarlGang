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
The synth *fm* is instantiated as a global variable (~monoNote) with amplitude equal to zero, in order to easily have access to the parameters and immediately change them "on the fly" when the user is playing. The *noteOnFunc* exploits the *set* function and set the frequency, the amplitude (according to the normalized velocity). The *noteOffFunc* uses the same *set* function and set the amplitude equal to zero in order to stop the synth. Therefore, using a MIDI keyboard you can control the carrier's frequency and amplitude as well as the duration of the sound produced.

#### OSC
Osc is used to manage the client-server part that is responsible to the exchange of messages from the user interface and the synthetiser. The OSC receiver is active at the address 127.0.0.1 (localhost) at port 57120. The received messages contain 4 parameters that correspond to the horizontal and vertical coordinates of the centroid of the hand, the palm-index distance and the palm slope. This parameters are received in the interval [0,1] and mapped, using the *LinLin* function, in proper intervals selected with the purpose of have a pleasent experience. The x-axis coordinate of the centroid is mapped into the [0.01,0.3] interval and assigned to the feedback; the y-axis coordinate of the centroid is mapped in [0.1,1.5] and manage the modulation amplitude; the palm length is mapped into [20,2000] and set the cut off frequency of the LPF and the palm slope is mapped intp [0,0.6] and set the reverb amount. The parameters after the mapping phase are assigned to the *~monoNote* through the *set* function.

### Control Interface
#### Hand Interaction
#### Animations

## How to use it
In order to use the application, run the server using Node.js with the command node .\server.js from terminal. Then
connect to the url localhost:55123 in a browser (it may take some seconds to load the ML model). Open the synth in SuperCollider and run all the code. Now you can enjoy the experience from your localhost page!

## Result and Demo


