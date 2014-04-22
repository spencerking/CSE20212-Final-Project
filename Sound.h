#ifndef SOUND_H
#define SOUND_H

#ifdef __APPLE__
   #include <fmod.hpp>
   #include <fmod_errors.h>
#else
   #include <FMOD/fmod.hpp>
   #include <FMOD/fmod_errors.h>
#endif

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
	unsigned int version;
};

#endif
