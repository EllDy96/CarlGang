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
The user interface is hosted as a web page/application in an Express server, the connection is set up through the framework Socket.io. All the control parameter mentioned above are computed in the client and then sent to the server. From the server, the parameters are written in OSC messages and forwarded to SuperCollider. This last past is handled through the library osc.js, which can generate OSC messages from javascript objects and establish a connection with a receiver (i.e., SuperCollider through an
UDP connection). The OSC message has only one path \/params" in which are contained all the parameters as oats.

#### Hand Interaction
Modules and libraries used: Node.js, Socket.io, Express, p5.js, ml5.js, osc.js. The synthesizer can be controlled through hand gestures captured from a webcam. For the hand pose recognition, we used a pre-trained ML modelfrom ml5.js (a javascript framework for creative coding built on top of TensorFlow.js), which takes frame by frame the video stream and return the coordinates of 21 points of the hand (this process is GPU intensive, even though the model is lightweight, a system with a dedicated graphic card is advised for best results). The hand is tracked by 21 points and from these points we compute 3 parameters: the centroid, the distance between the tip of the middle finger and the base of the palm and the orientation of the hand. 

#### Animations
The user interface, as we just said, is a web application in which we imported the libraries ml5.js and p5.js. We set p5.js in Instance Mode in order to manage 4 different sketches which compose the main window. The bigger p5 sketch at the top left is the one visualizing the webcam, the 21 points of the hand and the control parameters. The other three are a representation of the control parameters using **psychedelic animations**. At the bottom left we have a visualization for the hand orientation, at the top right for the x and y position of the centroid, and finally at the bottom right, for the distance between the middle finger and the palm base. Going into more depth on the animations implementation, we used as a reference the examples on the https://p5js.org website and a number of Youtube tutorials, in order to properly manage all the instructions in the code. 

The **Squared Rose** animation is a easily interpretable as visually impactful effect that describes the variation of the LPF cut off frequency. 

About the **Sun Sphere** animation instead, the astonishing effect given by the cohesion between the central sphere (created with a for cycle of multiple ellipses) and the colorful rays (created with a for cycle of multiple triangles) is essentially possible thanks to the double rotation implemented, through the functions rotateX and rotateY. The behaviour of the colors is similar to the previous animation, except for the increased velocity in the transitions. This "2 in 1 animation canvas" is used to describe the variations of feedback and modulation amplitude.

Talking about the **Double Square** animation, we decided to implement an immediately readable effect, describing the variation of the reverb volume. The 2 squares gradually decrease & increase their dimension following the hand orientation, as we'll show in the demo.


## How to use it
In order to use the application, run the server using Node.js with the command node .\server.js from terminal. Then
connect to the url localhost:55123 in a browser (it may take some seconds to load the ML model). Open the synth in SuperCollider and run all the code. Now you can enjoy the experience from your localhost page!

## Result and Demo


