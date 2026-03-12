#include <thread>
#include "AudioManager.h"
#include <chrono>

namespace Tmpl8 {

    AudioManager::AudioManager() :
        soundLoaded(false),
        musicEnabled(true),
        soundEffectsEnabled(true)
    {
    }

    void AudioManager::init() {
        //		std::thread([this]() {

        auto t0 = std::chrono::high_resolution_clock::now();
        this->backgroundMusic.loadMusic("assets/Audio/bgMusic.mp3");
        auto t1 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        printf("Background music loading took %lld ms\n", duration);
        //this->backgroundMusic.loadMusic("assets/Audio/bgMusic.ogg");
        this->coinSound.loadSound("assets/Audio/coin.wav");
        auto t2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        printf("Coin sound loading took %lld ms\n", duration);
        this->hurtSound.loadSound("assets/Audio/hurt.wav");
        auto t3 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
        printf("hurt.wave took %lld ms to load\n", duration);
        this->tapSound.loadSound("assets/Audio/tap.wav");
        auto t4 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
        printf("tap.wav took %lld ms to load\n", duration);
        
        this->backgroundMusic.setLooping(true);

        this->soundLoaded = true;

        this->setMusicPlaying(this->musicEnabled);
        auto t5 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t0).count();
        printf("Total audio loading took %lld ms\n", duration);
        //	}).detach();
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