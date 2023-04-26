#pragma once
#include "debug.h"
#include <string>
#include "fmod/fmod.hpp"
class SoundSystem {
private:
    static SoundSystem* instance;
    FMOD::System* system;
    FMOD::Sound* bgm;
    FMOD::Sound* sfx;
    FMOD::Sound* sfx1;

    FMOD::Channel* bgmChannel;
    FMOD::Channel* sfxChannel;

    FMOD::Channel* sfxChannel1;

    SoundSystem() {
        FMOD::System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, nullptr);
        bgm = nullptr;
        sfx = nullptr; sfx1 = nullptr;


        bgmChannel = nullptr;
        sfxChannel = nullptr;

        sfxChannel1 = nullptr;
    }

public:
    static SoundSystem* getInstance() {
        if (instance == nullptr) {
            instance = new SoundSystem();
        }
        return instance;
    }

    void playBGM(std::string fileName) {
        if (bgmChannel != nullptr) {
            bgmChannel->stop();
            bgmChannel = nullptr;
        }
        system->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, nullptr, &bgm);
        system->playSound(bgm, nullptr, false, &bgmChannel);
    }

    void playSFX(std::string fileName, int mode, int type) {
        if (type == 0)
        {
            system->createSound(fileName.c_str(), mode, nullptr, &sfx);

            system->playSound(sfx, nullptr, false, &sfxChannel);
        }
        if (type == 1)
        {
            system->createSound(fileName.c_str(), mode, nullptr, &sfx1);
            system->playSound(sfx1, nullptr, false, &sfxChannel1);
        }
    }
};

