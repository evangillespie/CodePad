#include "SoundManager.h"
#include "Arduino.h"


/*
	Constructor. Generic. Boring
*/
SoundManager::SoundManager() {

	_wTrig.start();
	_wTrig.stopAllTracks();
	_wTrig.masterGain(0);
}


/*
	Trigger a chosen sound to play.
	
	:param sound_index: the sound to play, as named on the Wav Trigger sd card.
*/
void SoundManager::play_sound(int sound_index){
	_wTrig.trackPlayPoly(sound_index);
}


/*
	Stop a particular sound if it's playing

	:param sound_index: the sound to stop
*/
void SoundManager::stop_sound(int sound_index){
	_wTrig.trackStop(sound_index);
}