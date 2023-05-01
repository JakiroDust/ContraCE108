#include "MusicManager.h"
SoundSystem* SoundSystem::instance = nullptr;
SoundSystem::SoundSystem() {
    if(!DEBUG_FMOD_LOG)
    FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_NONE, FMOD_DEBUG_MODE_TTY, nullptr, nullptr);
    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, nullptr);
#pragma region INIT SFX
    system->createStream(SFX_CONTRA_DEATH_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_DEATH]);
    system->createStream(SFX_BOSS_DEFEAT_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_BOSS_DEFEAT]);
    system->createStream(SFX_BASE_EXPLODE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_BASE_EXPLODE]);
    system->createStream(SFX_CONTRA_DEFAULTGUN_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_DEFAULTGUN]);
    system->createStream(SFX_CONTRA_RIFLE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_RIFLE]);
    system->createStream(SFX_CONTRA_SPREAD_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_SPREAD]);
    system->createStream(SFX_CONTRA_LASER_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_LASER]);
    system->createStream(SFX_CONTRA_LAND_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_LAND]);
    system->createStream(SFX_CONTRA_FLAME_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_FLAME]);
    system->createStream(SFX_CONTRA_ELECTRIC_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_ELECTRIC]);
    system->createStream(SFX_CONTRA_UPGRADE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_UPGRADE]);
    system->createStream(SFX_ENEMY_SHOOT_1_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_SHOOT_1]);
    system->createStream(SFX_ENEMY_SHOOT_2_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_SHOOT_2]);
    system->createStream(SFX_ENEMY_HIT_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_HIT]);
    system->createStream(SFX_ENEMY_EXPLODE_1_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_EXPLODE_1]);
    system->createStream(SFX_ENEMY_EXPLODE_2_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_EXPLODE_2]);
    system->createStream(SFX_MAJOR_EXPLODE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_MAJOR_EXPLODE]);
    system->createStream(SFX_NEXTROUND_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_NEXTROUND]);
    system->createStream(SFX_GAMEOVER_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_GAMEOVER]);
#pragma endregion

    system->createStream(BGM_JUNGLE_PATH, FMOD_LOOP_NORMAL, nullptr, &bgm[BGM_JUNGLE]);
    bgmChannel = nullptr;
    sfxChannel_Contra = nullptr;
    sfxChannel_ContraMisc = nullptr;
    sfxChannel_Enemy = nullptr;
    sfxChannel_Env = nullptr;
}
