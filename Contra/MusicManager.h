#pragma once
#include "debug.h"
#include <string>
#include <comdef.h> 
#include "fmod/fmod.hpp"


using namespace std;
#define DEBUG_FMOD_LOG false
enum
{
    BGM_TITLE,
    BGM_JUNGLE,
    BGM_WATERFALL,
    BGM_VICTORY,
    BGM_ENDING,
    BGM_GAME_OVER
};
constexpr auto SFX_CONTRA_DEATH = 1;
constexpr auto SFX_BOSS_DEFEAT = 2;
constexpr auto SFX_BASE_EXPLODE = 3;


constexpr auto SFX_CONTRA_DEFAULTGUN = 10;
constexpr auto SFX_CONTRA_RIFLE = 11;
constexpr auto SFX_CONTRA_SPREAD = 12;
constexpr auto SFX_CONTRA_FLAME = 13;
constexpr auto SFX_CONTRA_LASER = 14; //UNSUDED

constexpr auto SFX_CONTRA_LAND = 20;
constexpr auto SFX_CONTRA_ELECTRIC = 21;
constexpr auto SFX_CONTRA_UPGRADE = 22;

constexpr auto SFX_ENEMY_SHOOT_1 = 30;
constexpr auto SFX_ENEMY_SHOOT_2 = 301;

constexpr auto SFX_ENEMY_HIT = 40;
constexpr auto SFX_ENEMY_EXPLODE_1 = 41;
constexpr auto SFX_ENEMY_EXPLODE_2 = 411;

constexpr auto SFX_MAJOR_EXPLODE = 50;

constexpr auto SFX_NEXTROUND = 98;
constexpr auto SFX_GAMEOVER = 99;

constexpr auto CHANNEL_SFX_CONTRA = 0;
constexpr auto CHANNEL_SFX_CONTRA_MISC = 1;
constexpr auto CHANNEL_SFX_ENEMY = 2;
constexpr auto CHANNEL_SFX_ENV = 3;


class SoundSystem {
private:
    static SoundSystem* instance;
    FMOD::System* system;
    unordered_map<int, FMOD::Sound*> bgm;
    unordered_map<int, FMOD::Sound*> sfx;
    FMOD::Channel* bgmChannel;
    FMOD::Channel* sfxChannel_Contra;
    FMOD::Channel* sfxChannel_ContraMisc;
    FMOD::Channel* sfxChannel_Enemy;
    FMOD::Channel* sfxChannel_Env;

public:
    SoundSystem();

public:
    static SoundSystem* getInstance() {
        if (instance == nullptr) {
            instance = new SoundSystem();
        }
        return instance;
    }

    void playBGM(const int& fileName) {
        if (bgmChannel != nullptr) {
            bgmChannel->stop();
            bgmChannel = nullptr;
        }
        system->playSound((bgm[fileName]), nullptr, false, &bgmChannel);
    }
    void stopBGM()
    {
        if (bgmChannel != nullptr) {
            bgmChannel->stop();
            bgmChannel = nullptr;
        }
    }
    void playSFX(const int& fileName, int mode, int type) {
        switch (mode)
        {
        case CHANNEL_SFX_CONTRA:
            system->playSound(sfx[fileName], nullptr, false, &sfxChannel_Contra);
            break;
        case CHANNEL_SFX_CONTRA_MISC:
            system->playSound(sfx[fileName], nullptr, false, &sfxChannel_ContraMisc);
            break;
        case CHANNEL_SFX_ENEMY:
            system->playSound(sfx[fileName], nullptr, false, &sfxChannel_Enemy);
            break;
        case CHANNEL_SFX_ENV:
            system->playSound(sfx[fileName], nullptr, false, &sfxChannel_Env);
            break;
        }
      /*  if (type == 0)
        {
            
        }
        if (type == 1)
        {
            system->playSound(sfx1, nullptr, false, &sfxChannel_Enemy);
        }
        */
    }
};

