#include "SoundManager.h"
#include "Arduino.h"


/*
	Constructor. Generic. Boring
*/
SoundManager::SoundManager() {

	_wTrig.start();
	_wTrig.stopAllTracks();
	_wTrig.masterGain(0);

	//Set the volume of the individual sounds here

	_wTrig.trackGain(206, -23);  //Door warning blips
	_wTrig.trackGain(209, -20);  //Timer ticks
	_wTrig.trackGain(208, -20);  //Red timer ticks 
	_wTrig.trackGain(202, -12);  //Door open 
	_wTrig.trackGain(203, -15);  //Keypad button
	_wTrig.trackGain(204, -13);  //backspace button
	_wTrig.trackGain(218, -18);  //Ambient radar
	_wTrig.trackGain(219, -15);  //radio chatter
	_wTrig.trackGain(215, -5);  //Cage rising
	_wTrig.trackGain(223, -7);  //Time travel
	_wTrig.trackGain(217, -13);  //Single radar blip
	_wTrig.trackGain(205, -13);  //incorrect digit
	_wTrig.trackGain(220, -6);  //teleport whoosh



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
