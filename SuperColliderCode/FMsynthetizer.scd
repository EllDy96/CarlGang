

//*****************PARAMETERS****************************************/

//ModulationRatio= it define the modulation frequency based on the freq param
//CarrierRatio= it define the carrier frequency based on the freq param
//
// index of modulation= modAmp/modHz
// increasing it more and more overmore sideband populate the spectrum

// we set the same envelope for the amplitude and the modulation index

(
 SynthDef(\FMsynth,{
	arg freq=440, amp=0.5, modulationRatio=0.5, carrierRatio=1, index=1,
	atk=0.01,rel=0.5,cut_off=20000, feedback= 0.2, indexScale=0.2, curveAtk=3.5, curveRel=(-4),
	revVolume=0.01;

	var carrier, modulator1, env, indexEnv, hpf_carrier, revEnv, lpf_hpf_carrier,snd, hpf_reverb, signalOut;

	//index= MouseY.kr(0,10);
	indexEnv=EnvGen.kr(
		Env.new(
			[index,index*indexScale,index],
			[atk,rel],
			[curveAtk,curveRel]
		)
	);

	env= EnvGen.kr(Env.adsr(atk,1,2,rel,-2), doneAction:2);

	modulator1=SinOscFB.ar(freq*modulationRatio,feedback, mul:freq*modulationRatio*indexEnv);

	carrier= SinOsc.ar(freq*carrierRatio+modulator1)*env*amp;

	hpf_carrier = HPF.ar(carrier, 150);
	lpf_hpf_carrier= LPF.ar(hpf_carrier,8000,1);
	revEnv = EnvGen.kr(Env.adsr(1,2,3,rel*0.5));
	//Out.ar([0,1], Pan2.ar(FreeVerb.ar(lpf_carrier*revEnv,room:1), 0, 0.5));
	/*Out.ar([0,1],lpf_hpf_carrier);*/
	hpf_reverb= HPF.ar(FreeVerb.ar(in:lpf_hpf_carrier*revEnv,mix:0.5,room:0.2, damp:0.8, mul:revVolume),200);

	//Out.ar([0,1], FreeVerb.ar(lpf_hpf_carrier*revEnv,mix:0.7,room:0.75, damp:0.5, mul:revVolume));*/
	snd = Mix.ar([lpf_hpf_carrier,hpf_reverb]);
	signalOut=RLPF.ar(snd,SinOsc.ar(XLine(10,0.1,dur:0.5), add:cut_off, mul:10));
	Out.ar([0,1],signalOut, mul:2);
 }).add;
)


// high oindex and modulationRatio btw[0,1] high feedback
~monoNote.set(\indexScale,0.6,\feedback,0.8, \curveRel,-2,\modulationRatio,0.5,\revVolume, 0.5,\index,20);

//high modulation ratio
~monoNote.set(\freq, 45.midicps, \indexScale,0.5,\feedback,0.2, \curveRel,-3,\modulationRatio,2,\index,5,\cut_off,50);


//
//

~monoNote.set(\rel,4,\index,10,\indexScale,0.5, \feedback,0.5, \modulationRatio,4);


//****************************************MIDI SETUP**********************************************************************/


(
//Istantiation the Midi keyboard for a monophonic synthetizer
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
 //q.value();


/**************************************************SERVER CONNECTION*****************************************************/

// Create a network with the listener
// SuperCollider will listen to msgs at defined port and address
(
NetAddr("127.0.0.1",57120);

(
OSCdef('OSCreceiver',
	{
		arg msg;
		var x_map, y_map, z_map,k_map;

		x = msg[1]; // x del baricentro -> feedback
		y = msg[2];// y del baricentro -> index
		z= msg[3];// palm distance -> indexScalex
		k= msg[4];// palm slope -> panning

		postln("x: "+x+" - y: "+y);
		x_map= LinLin.ar(y,0,1,0, 0.5);// mapoping the feedback
		y_map= LinLin.ar(y,0,1,0.5,20);  // mapping of the indexScale from 0.5 to 10
		z_map= LinLin.ar(z,0,1,1,20);     //  mapping of the index from 1 to 20
		k_map= LinLin.ar(k, 0, 1, 150, 15000);// mapping of the lpf from 150 to 15000
		~monoNote.set(\feedback,x_map,\indexScale, y_map, \indexScale,z,\cut_off,k_map);

	},
	"/params");
)
)

