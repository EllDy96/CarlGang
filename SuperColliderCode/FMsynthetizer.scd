

//Booting the server and adding some plotting for visualizazion porpuses.
(
  s.boot;
  s.scope;// plotting the wave in time domain
  FreqScope.new // ploting the spectogram
)



/*********************************FM SYNTHESIS GUIDELINES********************/


// 1. As modulator amplitude increases, the   number of sidebands increases.
// 2. The frequency interval at which sidebands appear equals modulator frequency.
// 3. The output signal will tend to produce a clear sense of pitch when the carrier/modulator frequencies form a simple ratio (e.g. 2:1).



//***************** SYNTH PARAMETERS****************************************/

//ModulationRatio= it define the modulation frequency based on the freq param
//CarrierRatio= it define the carrier frequency based on the freq param

// index of modulation= modAmp/modHz
// the more you increase the index, the  more sideband populate the spectrum due to the increasing of the molulation- oscillator amplitude.



(
 SynthDef(\FMsynth,{
	arg freq=440, amp=0.5, modulationRatio=2, carrierRatio=1, index=1,
	atk=1,rel=5,cut_off=20000, feedback= 0.2, curveAtk=3.5, curveRel=(-2),
	revVolume=0.5;

	var carrier, modulator1, env, indexEnv, hpf_carrier, revEnv, lpf_hpf_carrier,snd, hpf_reverb, signalOut;

	env= EnvGen.kr(Env.adsr(atk,1,2,rel,-2), doneAction:2);

	modulator1=SinOscFB.ar(freq*modulationRatio,feedback, mul:freq*modulationRatio*index);

	carrier= SinOsc.ar(freq*carrierRatio+modulator1)*env*amp;

	hpf_carrier = HPF.ar(carrier, 150);
	lpf_hpf_carrier= LPF.ar(hpf_carrier,8000,1);

	revEnv = EnvGen.kr(Env.adsr(1,2,3,rel*0.5));
    //Adding a high-pass filter to clean the reverb sound
	hpf_reverb= HPF.ar(FreeVerb.ar(in:lpf_hpf_carrier*revEnv,mix:0.7,room:0.5, damp:0.5, mul:revVolume),250);

    snd = Mix.ar([lpf_hpf_carrier,hpf_reverb]);
    signalOut=LPF.ar(snd, cut_off, mul:2);
	Out.ar([0,1],signalOut/4);
 }).add;
)


//****************************************MIDI SETUP*******************************************/

//Istantiation of the Midi keyboard for a monophonic synthetizer

(

MIDIClient.init;
MIDIIn.connectAll;

~monoNote= Synth(\FMsynth,[\amp,0]);

~noteOnFunc = {arg val, num, chan, src;


	~monoNote.set(\freq, num.midicps,\amp, val/127);


	[chan,num,val].postln;
};

// assign the function to the note on message

a = MIDIFunc.noteOn(func:~noteOnFunc);

//note off function
~noteOffFunc = {arg val, num, chan, src;
	~monoNote.set(\amp,0);

};

b = MIDIFunc.noteOff(func:~noteOffFunc);

q = {a.free; b.free};

)

/**************************************************SERVER CONNECTION****************************/

// Create a network with the listener
// SuperCollider will listen to msgs at defined port and address
(
NetAddr("127.0.0.1",57120);

(
OSCdef('OSCreceiver',
	{
		arg msg;
		var x_map, y_map, z_map,k_map;

		x = msg[1]; // x centroid  -> feedback     ->the sphere radius
		y = msg[2];//  y  centroid -> index        ->the spere rays
        z = msg[3];// palm length  -> LPF cut-off  ->the double squares
		k = msg[4];// palm slope   -> Reverb amount->the square magnitude


		x_map= LinLin.ar(x,0,1,0.01,0.3);// mapping the feedback
        y_map= LinLin.ar(y,0,1,0.1,1.5); // mapping of the index (increase the modulation amplitude)
        z_map= LinLin.ar(z, 0, 1, 20,2000);// mapping of the cut off lpf
		k_map= LinLin.ar(k,0,1,0,0.6); //  mapping of the Reverb amount

		~monoNote.set(\feedback,x_map,\index,y_map,\cut_off, z_map,\revVolume, k_map);


        //Printing the OSC values:
		postln("Tracking parameter: x: "+x+" - y: "+ y + "z: "+z+" - k: "+k);
		postln("Mapped parameter: x_map: "+x_map +" - y_map: "+ y_map + "z_map: "+ z_map +" - k_map: "+k_map);
	},"/params");
)

)




/************************************ SYNTH PRESETS**************************************************/

//Compile one of this to try the synth with different presets

// modulation ratio 2:1
~monoNote.set(\feedback,0.3,\curveRel,-3,\rel,2\modulationRatio,2,\index,0.5,\cut_off, 3000,\revVolume, 0.3);

// high index and low modulationRatio, high feedback
~monoNote.set(\feedback,0.8, \curveRel,-2,\rel,3,\index,2,\modulationRatio,0.5,\revVolume, 0.5,);

// Odd modulation Ratio: enhance of the odd harmonics
~monoNote.set(\feedback,0.5,\curveRel,1,\rel,5,\index,0.8,\modulationRatio,5,\revVolume,0.8);
