#pragma once
#include "debug.h"
#include <string>
#include <comdef.h> 
#include "fmod/fmod.hpp"


using namespace std;
#define DEBUG_FMOD_LOG false
constexpr auto BGM_TITLE= 1;
constexpr auto BGM_JUNGLE = 2;

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

#define MUSIC_PATH "music/"
#define BGM_PATH MUSIC_PATH "bgm/"
#define BGM_JUNGLE_PATH BGM_PATH "2 - Jungle  Hangar (Stages 1  7).mp3"
#define SFX_PATH MUSIC_PATH "sfx/"
#define SFX_CONTRA_DEATH_PATH SFX_PATH  "death.mp3"
#define SFX_BOSS_DEFEAT_PATH SFX_PATH  "boss-defeat.mp3"
#define SFX_BASE_EXPLODE_PATH SFX_PATH  "base-explosion.mp3"

#define SFX_CONTRA_DEFAULTGUN_PATH SFX_PATH "enemy-gun.mp3"
#define SFX_CONTRA_RIFLE_PATH SFX_PATH "enemy-gun.mp3"
#define SFX_CONTRA_SPREAD_PATH SFX_PATH "spread.mp3"
#define SFX_CONTRA_FLAME_PATH SFX_PATH "flame.mp3"
#define SFX_CONTRA_LASER_PATH SFX_PATH "laser.mp3"

#define SFX_CONTRA_LAND_PATH SFX_PATH "land.mp3"
#define SFX_CONTRA_ELECTRIC_PATH SFX_PATH "electro.mp3"
#define SFX_CONTRA_UPGRADE_PATH SFX_PATH "1-up.mp3"

#define SFX_ENEMY_SHOOT_1_PATH SFX_PATH "enemy-gun.mp3"
#define SFX_ENEMY_SHOOT_2_PATH SFX_PATH "enemy-gun-2.mp3"

#define SFX_ENEMY_HIT_PATH SFX_PATH "enemy-hit.mp3"
#define SFX_ENEMY_EXPLODE_1_PATH SFX_PATH "explode.mp3"
#define SFX_ENEMY_EXPLODE_2_PATH SFX_PATH "explode-2.mp3"

#define SFX_MAJOR_EXPLODE_PATH SFX_PATH "major-explosion.mp3"

#define SFX_NEXTROUND_PATH SFX_PATH "area-clear.mp3"
#define SFX_GAMEOVER_PATH SFX_PATH "game-over.mp3"
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

