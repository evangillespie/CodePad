#include "SoundManager.h"
#include "Arduino.h"


/*
	Constructor. Generic. Boring
*/
SoundManager::SoundManager() {}


/*
	Trigger a chosen sound to play.
	
	:param sound_index: the sound to play, as named on the Wav Trigger sd card.
*/
void SoundManager::play_sound(int sound_index){
	Serial.print("!$! ");
	Serial.print("Playing sound: ");
	Serial.print(sound_index);
	Serial.print(" !$!\n");
}