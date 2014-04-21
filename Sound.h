#ifndef SOUND_H
#define SOUND_H

//#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

class Sound {
public:
	Sound();
	void init();
	void music(); // Play music
	void shutter(); // Play shutter
private:
	void errCheck(FMOD_RESULT result);
	FMOD::System *fmodSystem;
	FMOD::Sound *_music, *camShutter;
	FMOD::Channel *channel[1]; // Music channel and shutter channel
	FMOD_RESULT fmodResult;
	int musicToggle;
	unsigned int version;
};

#endif