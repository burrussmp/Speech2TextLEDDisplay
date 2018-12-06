# Speech2TextLEDDisplay
Converts speech recording from a USB microphone to an LED text display using the BeagleBone Black

Audio to Text Conversion:
- We used the PocketSphinx library from CMU to complete the conversion
- We created custom language models and dictionaries to increase efficiency, but the defaults provide the best accuracy

Materials
- 16x32 LED display
- Ribbon cables
- BeagleBone Black with Debian v9 installed
- USB Microphone (preferrably one with 16kHz capabilities... we used an old Rock Band microphone)

Libraries
- ALSA
- PocketSphinx and its dependencies

If you have any questions or comments reach out to either of the authors

![Hello LED Display](https://github.com/burrussmp/Speech2TextLEDDisplay/blob/master/LED%20Matrix/helloPhoto.jpg)
