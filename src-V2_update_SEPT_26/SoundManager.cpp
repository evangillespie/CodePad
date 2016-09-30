#include "SoundManager.h"
#include "Arduino.h"
#include "Pins.h"

/*
	Constructor. Generic. Boring
*/
SoundManager::SoundManager() {

	_wTrig.start();
	_wTrig.stopAllTracks();	
	_wTrig.masterGain(0);//Command to set volume on wave trigger.

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
	_wTrig.trackGain(248, -22);  //ambient city
	_wTrig.trackGain(250, -15);  //ambient city
	_wTrig.trackGain(243, -6);  //errie alien antennae
	_wTrig.trackGain(241, 2);  //girl talking
	_wTrig.trackGain(228, -10);  //ambient city
	_wTrig.trackGain(1, 2);  //tubaman
	_wTrig.trackGain(2, 2);  //tubaman
	_wTrig.trackGain(3, 2);  //tubaman
	_wTrig.trackGain(4, 2);  //tubaman
	_wTrig.trackGain(5, 2);  //tubaman
	_wTrig.trackGain(6, 2);  //tubaman
	_wTrig.trackGain(7, 2);  //tubaman
	_wTrig.trackGain(8, 2);  //tubaman
	_wTrig.trackGain(9, 2);  //tubaman
	_wTrig.trackGain(10, 2);  //tubaman
	_wTrig.trackGain(11, 2);  //tubaman
	_wTrig.trackGain(12, 2);  //tubaman
	_wTrig.trackGain(13, 2);  //tubaman
	_wTrig.trackGain(14, 2);  //tubaman
	_wTrig.trackGain(15, 2);  //tubaman
	_wTrig.trackGain(16, 2);  //tubaman
	_wTrig.trackGain(17, 2);  //tubaman
	_wTrig.trackGain(18, 2);  //tubaman
	_wTrig.trackGain(19, 2);  //tubaman
	_wTrig.trackGain(20, 2);  //tubaman
	_wTrig.trackGain(21, 2);  //tubaman
	_wTrig.trackGain(22, 2);  //tubaman
	_wTrig.trackGain(23, 2);  //tubaman
	_wTrig.trackGain(24, 2);  //tubaman
	_wTrig.trackGain(25, 2);  //tubaman
	_wTrig.trackGain(26, 2);  //tubaman
	_wTrig.trackGain(27, 2);  //tubaman
	_wTrig.trackGain(28, 2);  //tubaman
	_wTrig.trackGain(29, 2);  //tubaman
	_wTrig.trackGain(30, 2);  //tubaman
	_wTrig.trackGain(31, 2);  //tubaman
	_wTrig.trackGain(32, 2);  //tubaman
	_wTrig.trackGain(33, 2);  //tubaman
	_wTrig.trackGain(34, 2);  //tubaman
	_wTrig.trackGain(35, 2);  //tubaman
	_wTrig.trackGain(36, 2);  //tubaman
	_wTrig.trackGain(37, 2);  //tubaman
	_wTrig.trackGain(38, 2);  //tubaman
	_wTrig.trackGain(39, 2);  //tubaman
	_wTrig.trackGain(40, 2);  //tubaman
	_wTrig.trackGain(41, 2);  //tubaman
	_wTrig.trackGain(42, 2);  //tubaman
	_wTrig.trackGain(43, 2);  //tubaman
	_wTrig.trackGain(44, 2);  //tubaman
	_wTrig.trackGain(45, 2);  //tubaman
	_wTrig.trackGain(46, 2);  //tubaman
	_wTrig.trackGain(47, 2);  //tubaman
	_wTrig.trackGain(48, 2);  //tubaman
	_wTrig.trackGain(49, 2);  //tubaman
	_wTrig.trackGain(50, 2);  //tubaman
	_wTrig.trackGain(51, 2);  //tubaman
	_wTrig.trackGain(52, 2);  //tubaman
	_wTrig.trackGain(53, 2);  //tubaman
	_wTrig.trackGain(54, 2);  //tubaman
	_wTrig.trackGain(55, 2);  //tubaman
	_wTrig.trackGain(56, 2);  //tubaman
	_wTrig.trackGain(57, 2);  //tubaman
	_wTrig.trackGain(58, 2);  //tubaman
	_wTrig.trackGain(59, 2);  //tubaman
	_wTrig.trackGain(60, 2);  //tubaman
	_wTrig.trackGain(61, 2);  //tubaman
	_wTrig.trackGain(62, 2);  //tubaman
	_wTrig.trackGain(63, 2);  //tubaman
	_wTrig.trackGain(64, 2);  //tubaman
	_wTrig.trackGain(65, 2);  //tubaman
	_wTrig.trackGain(66, 2);  //tubaman
	_wTrig.trackGain(67, 2);  //tubaman
	_wTrig.trackGain(68, 2);  //tubaman
	_wTrig.trackGain(69, 2);  //tubaman
	_wTrig.trackGain(70, 2);  //tubaman
	_wTrig.trackGain(71, 2);  //tubaman
	_wTrig.trackGain(72, 2);  //tubaman
	_wTrig.trackGain(73, 2);  //tubaman
	_wTrig.trackGain(74, 2);  //tubaman
	_wTrig.trackGain(75, 2);  //tubaman
	_wTrig.trackGain(76, 2);  //tubaman
	_wTrig.trackGain(77, 2);  //tubaman
	_wTrig.trackGain(78, 2);  //tubaman
	_wTrig.trackGain(79, 2);  //tubaman
	_wTrig.trackGain(80, 2);  //tubaman
	_wTrig.trackGain(81, 2);  //tubaman
	_wTrig.trackGain(82, 2);  //tubaman
	_wTrig.trackGain(83, 2);  //tubaman
	_wTrig.trackGain(84, 2);  //tubaman
	_wTrig.trackGain(85, 2);  //tubaman
	_wTrig.trackGain(86, 2);  //tubaman
	_wTrig.trackGain(87, 2);  //tubaman
	_wTrig.trackGain(88, 2);  //tubaman
	_wTrig.trackGain(89, 2);  //tubaman
	_wTrig.trackGain(90, 2);  //tubaman
	_wTrig.trackGain(91, 2);  //tubaman
	_wTrig.trackGain(92, 2);  //tubaman
	_wTrig.trackGain(93, 2);  //tubaman
	_wTrig.trackGain(94, 2);  //tubaman
	_wTrig.trackGain(95, 2);  //tubaman
	_wTrig.trackGain(96, 2);  //tubaman
	_wTrig.trackGain(97, 2);  //tubaman
	_wTrig.trackGain(98, 2);  //tubaman
	_wTrig.trackGain(99, 2);  //tubaman
	_wTrig.trackGain(100, 2);  //tubaman
	_wTrig.trackGain(101, 2);  //tubaman
	_wTrig.trackGain(102, 2);  //tubaman
	_wTrig.trackGain(103, 2);  //tubaman
	_wTrig.trackGain(104, 2);  //tubaman
	_wTrig.trackGain(105, 2);  //tubaman
	_wTrig.trackGain(106, 2);  //tubaman
	_wTrig.trackGain(107, 2);  //tubaman
	_wTrig.trackGain(108, 2);  //tubaman
	_wTrig.trackGain(109, 2);  //tubaman
	_wTrig.trackGain(110, 2);  //tubaman
	_wTrig.trackGain(111, 2);  //tubaman
	_wTrig.trackGain(112, 2);  //tubaman
	_wTrig.trackGain(113, 2);  //tubaman
	_wTrig.trackGain(114, 2);  //tubaman
	_wTrig.trackGain(115, 2);  //tubaman
	_wTrig.trackGain(116, 2);  //tubaman
	_wTrig.trackGain(117, 2);  //tubaman
	_wTrig.trackGain(118, 2);  //tubaman
	_wTrig.trackGain(119, 2);  //tubaman
	_wTrig.trackGain(120, 2);  //tubaman
	_wTrig.trackGain(121, 2);  //tubaman
	_wTrig.trackGain(122, 2);  //tubaman
	_wTrig.trackGain(123, 2);  //tubaman
	_wTrig.trackGain(124, 2);  //tubaman
	_wTrig.trackGain(125, 2);  //tubaman
	_wTrig.trackGain(126, 2);  //tubaman
	_wTrig.trackGain(127, 2);  //tubaman
	_wTrig.trackGain(128, 2);  //tubaman
	_wTrig.trackGain(129, 2);  //tubaman
	_wTrig.trackGain(130, 2);  //tubaman
	_wTrig.trackGain(131, 2);  //tubaman
	_wTrig.trackGain(132, 2);  //tubaman
	_wTrig.trackGain(133, 2);  //tubaman
	_wTrig.trackGain(134, 2);  //tubaman
	_wTrig.trackGain(135, 2);  //tubaman
	_wTrig.trackGain(136, 2);  //tubaman
	_wTrig.trackGain(137, 2);  //tubaman
	_wTrig.trackGain(138, 2);  //tubaman
	_wTrig.trackGain(139, 2);  //tubaman
	_wTrig.trackGain(140, 2);  //tubaman
	_wTrig.trackGain(141, 2);  //tubaman
	_wTrig.trackGain(142, 2);  //tubaman
	_wTrig.trackGain(143, 2);  //tubaman
	_wTrig.trackGain(144, 2);  //tubaman
	_wTrig.trackGain(145, 2);  //tubaman
	_wTrig.trackGain(146, 2);  //tubaman
	_wTrig.trackGain(300, 2);  //bad pin tubaman
	_wTrig.trackGain(301, 2);  //bad pin tubaman
	_wTrig.trackGain(302, 2);  //bad pin tubaman
	_wTrig.trackGain(303, 2);  //bad pin tubaman
	_wTrig.trackGain(304, 2);  //bad pin tubaman
	_wTrig.trackGain(305, 2);  //bad pin tubaman
	_wTrig.trackGain(306, 2);  //bad pin tubaman
	_wTrig.trackGain(307, 2);  //bad pin tubaman
	_wTrig.trackGain(308, 2);  //bad pin tubaman
	_wTrig.trackGain(309, 2);  //bad pin tubaman
	_wTrig.trackGain(310, 2);  //bad pin tubaman
	_wTrig.trackGain(311, 2);  //bad pin tubaman
	_wTrig.trackGain(312, 2);  //good pin tubaman
	_wTrig.trackGain(313, 2);  //good pin tubaman
	_wTrig.trackGain(314, 2);  //good pin tubaman
	_wTrig.trackGain(315, 2);  //good pin tubaman
	_wTrig.trackGain(316, 2);  //good pin tubaman
	_wTrig.trackGain(317, 2);  //good pin tubaman
	_wTrig.trackGain(318, 2);  //good pin tubaman
	_wTrig.trackGain(319, 2);  //good pin tubaman
}


/*
	Trigger a chosen sound to play.
	
	:param sound_index: the sound to play, as named on the Wav Trigger sd card.
*/
void SoundManager::play_sound(int sound_index){
	//Set volume of sounds by pot
	_wTrig.masterGain((-54*(float)analogRead(POT_VOLUME_INPUT))/1023+4);

	_wTrig.trackPlayPoly(sound_index);
}


/*
	Stop a particular sound if it's playing

	:param sound_index: the sound to stop
*/
void SoundManager::stop_sound(int sound_index){
	_wTrig.trackStop(sound_index);
}

