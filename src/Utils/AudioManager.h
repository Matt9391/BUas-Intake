#pragma once

#include <Audio/Sound.hpp>

namespace Tmpl8 {

	class AudioManager
	{
	public:
		AudioManager();
		void init();

		void setMusicPlaying(bool state);
		void setSoundPlaying(bool state);

		void playCoinSound();
		void playHurtSound();
		void playTapSound();

		bool isLoaded() const;

	private:
		Audio::Sound backgroundMusic;
		Audio::Sound coinSound;
		Audio::Sound hurtSound;
		Audio::Sound tapSound;

		bool soundEffectsEnabled;
		bool musicEnabled;

		bool soundLoaded;

	};

}

