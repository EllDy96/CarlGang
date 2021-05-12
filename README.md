# Sound effect classifier

Implementation of a SVM classifier system able to predict the presence or not of a Tremolo or a the Distorsion effect applied to a guitar and bass mono audio recording.

For training and testing the model we use the [IDMT-SMT-AUDIO-EFFECTS dataset](https://www.idmt.fraunhofer.de/en/business_units/m2d/smt/audio_effects.html).
[Audio Demo](https://polimi365-my.sharepoint.com/:u:/g/personal/10751438_polimi_it/ESSG1VdlCZVMsWpJDyI5JisBTeKSS_7I16fRfVOw2sIelg?e=JC0Wi9).


We focused on the classification of 3 classes:
- distortion
- tremolo
- no effect

We use only a portion of the dataset composed of all the monophonic guitar and bass tracks. For a further explanation please see the report [CMLS HW1](https://github.com/EllDy96/CarlGang/blob/master/Hw_1/report/CMLS%20HW1.pdf).
