(
s.scope;// plotting the wave in time domain
FreqScope.new // ploting the spectogram
)


// first test for FM Synthesis

// Creting a first sinusoidal oscillator and then adding to it another oscillator controlling its amplitude with the y position and its freq with the x position
(
ControlSpec.new(minval: 0.0, maxval: 1.0, warp: 'lin', step: 0.0, default, units, grid)
)


/*{SinOsc.ar(800+ SinOsc.ar(freq:MouseX.kr( mul: MouseY.kr(0,400).poll))*0.2!2}.play;*/

//Poll - Print the current output value of a UGen


// Rules/Guidelines of FM:
// 1. As modulator amplitude increases, the   number of sidebands increases.
// 2. The frequency interval at which sidebands appear equals modulator frequency.
// 3. The output signal will tend to produce a clear sense of pitch when the carrier/modulator frequencies form a simple ratio (e.g. 2:1).

//fm synth
// (
// SynthDef(\fm,{
// 	arg freq=500, modulationRatio=1, carrierRatio=1,
// 	index=1, iScale=5, carrieriAtk=4, carrierRel=(-4),
// 	amp=0.2, atk=0.5, rel=3, pan=0,
// 	out=0, fx=0, fxsend=(-25), modHz=400, modAmp=100, carHz;
// 	var carrier, modulator, env, indexEnv;
//
// 	env= EnvGen.kr(Env.perc(atk,rel),doneAction:2);
// 	modulator=SinOsc.ar(modHz, mul:modAmp);
// 	carrier= SinOsc.ar(carHz+modulator)*env*amp;
// 	carrier=Pan2.ar(carrier,pan);
// 	a = EnvGen.kr(Env.asr(0.01,1,dur), gate:t_gate);
// 	Out.ar(0, Pan2.ar(FreeVerb.ar(out*a,room:0.3), 0, 0.5));
// 	Out.ar(0,carrier);
// }).add
// )


//*****************PARAMETERS****************************************/

//ModulationRatio= it define the modulation frequency based on the freq param
//CarrierRatio= it define the carrier frequency based on the freq param
//
// index of modulation= modAmp/modHz
// increasing it more and more overmore sideband populate the spectrum

// we set the same envelope for the amplitude and the modulation index

(
 SynthDef(\fm,{
	arg freq=440, amp=0.5, modulationRatio=1, carrierRatio=1, index=1,
	atk=0.01,rel=3,pan=0, feedback= 0.2, indexScale=0.2, curveAtk=3.5, curveRel=(-4),
	revVolume=0.5, gate= 1;

	var carrier, modulator1, env, indexEnv, hpf_carrier, revEnv, lpf_hpf_carrier;

	//index= MouseY.kr(0,10);
	indexEnv=EnvGen.kr(
		Env.new(
			[index,index*indexScale,index],
			[atk,rel],
			[curveAtk,curveRel]
		)
	);

	env= EnvGen.kr(Env.perc(atk, rel,curve:[curveAtk,curveRel]),gate, doneAction:2);

	modulator1=SinOscFB.ar(freq*modulationRatio,feedback, mul:freq*modulationRatio*indexEnv);

	carrier= SinOsc.ar(freq*carrierRatio+modulator1)*env*amp;
	//carrier=Pan2.ar(carrier,pan);
	hpf_carrier = HPF.ar(carrier, 150);
	lpf_hpf_carrier= LPF.ar(hpf_carrier,10000, 0.8);
	revEnv = EnvGen.kr(Env.asr(1,3,rel*0.5));
	//Out.ar([0,1], Pan2.ar(FreeVerb.ar(lpf_carrier*revEnv,room:1), 0, 0.5));
	Out.ar([0,1],lpf_hpf_carrier);
	Out.ar([0,1], FreeVerb.ar(lpf_hpf_carrier*revEnv,mix:0.7,room:0.75, damp:0.5, mul:revVolume));

 }).add;
)


x= Synth(\fm, [\freq, 45.midicps, \indexScale,0.7,\feedback,0, \curveRel,-5,\modulationRatio,3]);
x.free;
x = Synth(\fm, [\freq, 45.midicps, \indexScale,0.2,\feedback,0.5, \curveRel,-2,\modulationRatio,0.5, \revVolume, 0.7, \index,20 ]);
x.set(\indexScale,0.2,\feedback,0.5, \curveRel,-2,\modulationRatio,0.5, \revVolume, 0.7, \index,20);
x = Synth(\fm, [\freq, 65.midicps, \rel,5,\index,15,\indexScale,0.5, feedback:0.1]);
x=Synth(\fm, [\freq, 40.midicps, \rel,3,\index,10,\indexScale,0.05,\modulationRatio,3]);
~monoNote.set(\indexScale,0.2,\feedback,0.5, \curveRel,-2,\modulationRatio,0.5,\revVolume, 0.7, \index,20);
~monoNote.set(


x.set(\freq, 45.midicps);




// (
// SynthDef(\fm, {
// 	arg freq=500, mRatio=1, cRatio=1,
// 	index=1, iScale=5, cAtk=4, cRel=(-4),
// 	amp=0.2, atk=0.01, rel=3, pan=0,
// 	out=0, fx=0, fxsend=(-25);
// 	var car, mod, env, iEnv;
//
// 	//index of modulation
// 	iEnv = EnvGen.kr(
// 		Env(
// 			[index, index*iScale, index],
// 			[atk, rel],
// 			[cAtk, cRel]
// 		)
// 	);
//
// 	//amplitude envelope
// 	env = EnvGen.kr(Env.perc(atk,rel,curve:[cAtk,cRel]),doneAction:2);
//
// 	//modulator/carrier
// 	mod = SinOsc.ar(freq * mRatio, mul:freq * mRatio * iEnv);
// 	car = SinOsc.ar(freq * cRatio + mod) * env * amp;
//
// 	car = Pan2.ar(car, pan);
//
// 	//direct out/reverb send
// 	Out.ar(out, car);
// 	Out.ar(fx, car * fxsend.dbamp);
// }).add;
// )
// Synth(\fm);

//************************************************MIDI SETUP**********************************************************************/
//Istantiation the Midi keyboard
MIDIClient.init;
MIDIIn.connectAll;


(
//*var keys;
// create a new array with all slots filled with nils
//keys = Array.newClear(128);*/
~monoNote= Synth(\fm,[\amp,0]);


// we are going to write a function that will be assigned to the message NoteOn; by default it has some arguments, check the documentation for knowing the arguments of each message
// For NoteOn:
// val: message value (velocity)
// num: messange number (note)
// chan : MIDIchannel, goes from 0 to 15
// src : unique identifier of the MIDI port

~noteOnFunc = {arg val, num, chan, src;
	//var node;
	// first assign to node the element of the array having as index the key number
	/*node = keys.at(num);
	// if the node is not Nil then release the node and put nil in the correspondent element
	if (node.notNil, {
		node.release;
		keys.put(num, nil);
	});*/

	// if the node is not Nil means that the correpondent synth is already playing
	// if the node is Nil then create an instance of Rhodes synth with the correct arguments and using the tail method

	// the tail method create and return a Synth; the first argument is generally a Group, when is setted to nil the synth is added to the tail of the default_group of the default server
	//Synths on the server are a type of what are called nodes. There's another type of node: groups. Groups are simply collections of nodes, and can contain synths, other groups, or combinations of both.

	//node = Synth.tail(nil, \fm, [\freq, num.midicps, \amp, val/(127)]);
	~monoNote.set(\freq, num.midicps,\amp, val/127,\gate,1);

	// assign the instance to the correspondent element of the array
	//keys.put(num, node);

	[chan,num,val].postln;
};

// assign the function to the note on message

a = MIDIFunc.noteOn(func:~noteOnFunc);


// now we need to write the note off function
~noteOffFunc = {arg val, num, chan, src;
	//var node;
	/*node = keys.at(num);

	if (node.notNil, {
		node.set(\gate,0);
	    node.release;
		keys.put(num, nil);
	});
*/
	~monoNote.set(\gate,0);
};

~monoNote = MIDIFunc.noteOff(func:~noteOffFunc);

q = {a.free; ~midiNote.free};
)

q.value();
