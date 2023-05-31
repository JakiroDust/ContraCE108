#pragma once

#pragma region CONTRA


#define CONTRA_ANI_IDLE_RIGHT 10000
#define CONTRA_ANI_IDLE_LEFT CONTRA_ANI_IDLE_RIGHT+1

#define CONTRA_ANI_IDLE_SHOOTING_RIGHT	10010
#define CONTRA_ANI_IDLE_SHOOTING_LEFT CONTRA_ANI_IDLE_SHOOTING_RIGHT+1


////////////////////////////////////LOOK_UP(_SHOOTING)////////////////////////////////////////////
//#define CONTRA_ANI_LOOK_UP_STANING_RIGHT	10500
//#define CONTRA_ANI_LOOK_UP_STANING_LEFT CONTRA_ANI_LOOK_UP_STANING_RIGHT+1
////////////////////////////////////WALK_RIGHT(_SHOOTING)////////////////////////////////////////////
#define CONTRA_ANI_WALK_RIGHT 10100
#define CONTRA_ANI_WALK_LEFT CONTRA_ANI_WALK_RIGHT+1

#define CONTRA_ANI_WALK_SHOOTING_RIGHT 10200
#define CONTRA_ANI_WALK_SHOOTING_LEFT CONTRA_ANI_WALK_SHOOTING_RIGHT+1

///////////////////////////////////WALK_DOWN(_SHOOTING)/////////////////////////////////////////////
#define CONTRA_ANI_WALK_DOWN_RIGHT 10110
#define CONTRA_ANI_WALK_DOWN_LEFT CONTRA_ANI_WALK_DOWN_RIGHT+1

#define CONTRA_ANI_WALK_DOWN_SHOOTING_RIGHT 10210
#define CONTRA_ANI_WALK_DOWN_SHOOTING_LEFT CONTRA_ANI_WALK_DOWN_SHOOTING_RIGHT+1

//////////////////////////////////WALK_UP(_SHOOTING)//////////////////////////////////////////////
#define CONTRA_ANI_WALK_UP_RIGHT 10120
#define CONTRA_ANI_WALK_UP_LEFT CONTRA_ANI_WALK_UP_RIGHT+1

#define CONTRA_ANI_WALK_UP_SHOOTING_RIGHT 10220
#define CONTRA_ANI_WALK_UP_SHOOTING_LEFT CONTRA_ANI_WALK_UP_SHOOTING_RIGHT+1
//////////////////////////////////LOOK_UP(_SHOOTING)///////////////////////////////////////////

#define CONTRA_ANI_LOOK_UP_RIGHT 10500
#define CONTRA_ANI_LOOK_UP_LEFT CONTRA_ANI_LOOK_UP_RIGHT+1

#define CONTRA_ANI_LOOK_UP_SHOOTING_RIGHT 10510
#define CONTRA_ANI_LOOK_UP_SHOOTING_LEFT CONTRA_ANI_LOOK_UP_SHOOTING_RIGHT+1
//////////////////////////////////LIE(_SHOOTING)//////////////////////////////////////////////
#define CONTRA_ANI_LIE_RIGHT 10300
#define CONTRA_ANI_LIE_LEFT CONTRA_ANI_LIE_RIGHT+1

#define CONTRA_ANI_LIE_SHOOTING_RIGHT 10310
#define CONTRA_ANI_LIE_SHOOTING_LEFT CONTRA_ANI_LIE_SHOOTING_RIGHT+1
//////////////////////////////////////////////////////////////////////////////////////////////
#define CONTRA_ANI_JUMP_RIGHT 10400
#define CONTRA_ANI_JUMP_LEFT CONTRA_ANI_JUMP_RIGHT+1

#define CONTRA_ANI_FALL_RIGHT 10000
#define CONTRA_ANI_FALL_LEFT CONTRA_ANI_FALL_RIGHT+1

#define CONTRA_ANI_DIE_RIGHT 10990
#define CONTRA_ANI_DIE_LEFT CONTRA_ANI_DIE_RIGHT+1

#define CONTRA_ANI_DIE_JUMPING_RIGHT 10990
#define CONTRA_ANI_DIE_JUMPING_LEFT CONTRA_ANI_DIE_JUMPING_RIGHT+1

#define CONTRA_ANI_SWIM_RIGHT 11100
#define CONTRA_ANI_SWIM_LEFT CONTRA_ANI_SWIM_RIGHT+1

#define CONTRA_ANI_SWIM_UP_STAND_RIGHT 11220
#define CONTRA_ANI_SWIM_UP_STAND_LEFT CONTRA_ANI_SWIM_UP_STAND_RIGHT+1

#define CONTRA_ANI_SWIM_RIGHT_UP 11210
#define CONTRA_ANI_SWIM_LEFT_UP CONTRA_ANI_SWIM_RIGHT_UP+1

#define CONTRA_ANI_DIV 11301
#pragma endregion

#pragma region CONTRA_BULLET
#define	CONTRA_BULLET_ANI_BASE_RIGHT 1099010
#define	CONTRA_BULLET_ANI_BASE_LEFT	CONTRA_BULLET_ANI_BASE_RIGHT+1
#pragma endregion

#pragma region INFARY
#define	INFARY_ANI_WALK_RIGHT 20100
#define	INFARY_ANI_WALK_LEFT INFARY_ANI_WALK_RIGHT+1

#define	INFARY_ANI_AIM_RIGHT 20010
#define	INFARY_ANI_AIM_LEFT	INFARY_ANI_AIM_RIGHT+1

#define INFARY_ANI_SHOOT_RIGHT	20110
#define	INFARY_ANI_SHOOT_LEFT	INFARY_ANI_SHOOT_RIGHT+1

#define INFARY_ANI_JUMP_RIGHT 20990
#define INFARY_ANI_JUMP_LEFT INFARY_ANI_JUMP_RIGHT+1

#define INFARY_ANI_DIE_RIGHT 20990
#define INFARY_ANI_DIE_LEFT INFARY_ANI_DIE_RIGHT+1
#pragma endregion

#pragma region SNIPER
#define	SNIPER_ANI_AIM_RIGHT 40010
#define	SNIPER_ANI_AIM_LEFT	SNIPER_ANI_AIM_RIGHT+1

#define SNIPER_ANI_AIM_UP_RIGHT 40030
#define SNIPER_ANI_AIM_UP_LEFT SNIPER_ANI_AIM_UP_RIGHT+1

#define SNIPER_ANI_AIM_DOWN_RIGHT 40020
#define SNIPER_ANI_AIM_DOWN_LEFT SNIPER_ANI_AIM_DOWN_RIGHT+1

#define	SNIPER_ANI_SHOOT_RIGHT 40110
#define	SNIPER_ANI_SHOOT_LEFT	SNIPER_ANI_SHOOT_RIGHT+1

#define SNIPER_ANI_SHOOT_UP_RIGHT 40130
#define SNIPER_ANI_SHOOT_UP_LEFT SNIPER_ANI_SHOOT_UP_RIGHT+1

#define SNIPER_ANI_SHOOT_DOWN_RIGHT 40120
#define SNIPER_ANI_SHOOT_DOWN_LEFT SNIPER_ANI_SHOOT_DOWN_RIGHT+1

#define SNIPER_ANI_DIE_RIGHT 40990
#define SNIPER_ANI_DIE_LEFT SNIPER_ANI_DIE_RIGHT +1
#pragma endregion


#define ANI_MOVING_ROCK 96990
#define ANI_FALLING_ROCK	96980

#pragma region TURRET360
#define ANI_TURRET_360_12 80500
#define ANI_TURRET_360_1 80280
#define ANI_TURRET_360_2 80270
#define ANI_TURRET_360_3 80010
#define ANI_TURRET_360_4 80250	
#define ANI_TURRET_360_5 80260	
#define ANI_TURRET_360_6 80290
#define ANI_TURRET_360_11 80300
#define ANI_TURRET_360_10 80310
#define ANI_TURRET_360_9 80320
#define ANI_TURRET_360_8 80330	
#define ANI_TURRET_360_7 80340
#define ANI_TURRET_360_DIE	80000
#define ANI_TURRET_360_WIND_UP	80020
#define ANI_TURRET_360_IDLE	80980
#pragma endregion

#pragma region CANNON
#define ANI_CANNON_WIND_UP_LEFT	77230
#define ANI_CANNON_9 77010
#define ANI_CANNON_10 77330
#define ANI_CANNON_11 77320
#pragma endregion

//since sniper 
#pragma region BUSH_SNIPER
#define ANI_BUSH_SNIPER_WIND_UP 50000
#define ANI_BUSH_SNIPER_SHOOT	50010
#pragma endregion

#pragma region EXPLO
#define ANI_EXPLOSION_CONSTRUCT	80550
#define ANI_EXPLOSION_ARMY	20550
#pragma endregion


#pragma region TERRAIN
#define BLACK_BOX_ANI 99990
#pragma endregion