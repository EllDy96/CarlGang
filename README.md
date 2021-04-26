# Sound effect classifier

Implementation of a SVM classifier system able to predict the presence or not of a Tremolo or a the Distorsion effect applied to a guitar and bass mono audio recording.

For training and testing the model we use the IDMT-SMT-AUDIO-EFFECTS dataset which is available at the following link:
https://www.idmt.fraunhofer.de/en/business_units/m2d/smt/audio_effects.html

We focused on the classification of 3 classes:
- distortion
- tremolo
- no effect

We use only a portion of the dataset composed of all the monophonic guitar and bass tracks. For a further explanation please see the  PDF report inside the report folder.
