#include "Sound.h"
#include <stdio.h>

Sound::Sound() {

}

void Sound::init() {
	fmodResult = FMOD::System_Create(&fmodSystem);
	Sound::errCheck(fmodResult);

	fmodResult = fmodSystem->getVersion(&version);
	Sound::errCheck(fmodResult);
	if (version < FMOD_VERSION) {
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
	}

	fmodResult = fmodSystem->init(32, FMOD_INIT_NORMAL, NULL);
	Sound::errCheck(fmodResult);

	fmodResult = fmodSystem->createSound("Sound/music.mp3", FMOD_SOFTWARE, 0, &_music);
	Sound::errCheck(fmodResult);

	fmodResult = fmodSystem->createSound("Sound/camShutter.wav", FMOD_SOFTWARE, 0, &camShutter);
	Sound::errCheck(fmodResult);

	fmodResult = camShutter->setMode(FMOD_LOOP_OFF);
	Sound::errCheck(fmodResult);

	// Start music initially
	fmodResult = fmodSystem->playSound(FMOD_CHANNEL_FREE, _music, 0, &channel[0]);
	errCheck(fmodResult);
}

void Sound::music() {
	bool isPaused;
	channel[0]->getPaused(&isPaused);
	channel[0]->setPaused(!isPaused);
}

void Sound::shutter() {
	fmodResult = fmodSystem->playSound(FMOD_CHANNEL_FREE, camShutter, 0, &channel[1]);
	errCheck(fmodResult);
}

void Sound::errCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		printf("FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
	}
}