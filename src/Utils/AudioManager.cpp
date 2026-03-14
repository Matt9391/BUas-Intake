#include "AudioManager.h"


namespace Tmpl8 {

    AudioManager::AudioManager() :
        soundLoaded(false),
        musicEnabled(true),
        soundEffectsEnabled(true)
    {}

    void AudioManager::init() {
        this->backgroundMusic.loadMusic("assets/Audio/bgMusic.mp3");
        
        this->coinSound.loadSound("assets/Audio/coin.wav");
        this->hurtSound.loadSound("assets/Audio/hurt.wav");
        this->tapSound.loadSound("assets/Audio/tap.wav");
        
        this->backgroundMusic.setLooping(true);

        this->soundLoaded = true;

        this->setMusicPlaying(this->musicEnabled);
        
    }

    void AudioManager::setMusicPlaying(bool state) {
        this->musicEnabled = state;

        if (!this->soundLoaded)
            return;

        if (state)
            this->backgroundMusic.play();
        else
            this->backgroundMusic.stop();
    };

    void AudioManager::setSoundPlaying(bool state) {
        this->soundEffectsEnabled = state;
    };

    void AudioManager::playCoinSound() {
        if (!this->soundLoaded || !this->soundEffectsEnabled)
            return;

        this->coinSound.play();
    };

    void AudioManager::playHurtSound() {
        if (!this->soundLoaded || !this->soundEffectsEnabled)
            return;

        this->hurtSound.play();
    };

    void AudioManager::playTapSound() {
        if (!this->soundLoaded || !this->soundEffectsEnabled)
            return;

        this->tapSound.play();
    };

    bool AudioManager::isLoaded() const {
        return this->soundLoaded;
    }
}