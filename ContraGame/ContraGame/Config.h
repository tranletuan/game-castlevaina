#ifndef _CONFIG_H_
#define _CONFIG_H_

#define MAP_FOLDER L"resources/map/"

//GRAVITY
#define GRAVITY 0.025f

//BILL 
#define BILL_VX 0.08f
#define BILL_VY 9.5f
#define BILL_VY_DIE 7.0f
#define BILL_BOUNDS_WIDTH 8
#define BILL_BOUNDS_HEIGHT 28

//BULLET
#define BULLET_REINFORCE 0.05f

#define BULLET_N_V 0.2f
#define BULLET_N_TOTAL 4

#define BULLET_S_TOTAL 10
#define BULLET_S_COUNT_ONE_SHOOT 5
#define BULLET_S_ELAPSED_DEGREES 10
#define BULLET_S_V 0.25f
#define BULLET_S_ELAPSED_TIME 100

#define BULLET_F_V 0.12f
#define BULLET_F_R 18
#define BULLET_F_ELAPSED_DEGREES 20
#define BULLET_F_TOTAL 4

#define BULLET_L_V 0.3f
#define BULLET_L_ELAPSED_DIS 10
#define BULLET_L_TOTAL 3

#define BULLET_M_V 0.25f
#define BULLET_M_TOTAL 4

#define BULLET_NE_V 0.06f
#define BULLET_NE_TOTAL 30

#define BULLET_B_VX 0.05f
#define BULLET_B_RANDOM_VX 150
#define BULLET_B_VY 5.0f
#define BULLET_B_TOTAL 4

//GROUND
#define GROUND_SIZE_NORMAL 32
#define GROUND_TIME_EFFECT 300

#define GROUND_BRIDGE_DESTROY_EFFECT_COUNT 4
#define GROUND_BRIDGE_ELAPSED_RANDOM_POSITION 14
#define GROUND_BRIDGE_DESTROY_TIME 800
#define GROUND_BRIDGE_DISTANCE_DESTROY 32

//EFFECT 
#define EFFECT_DESTROY_TIME 200

//ENEMY
#define ENEMY_ATTACK_DISTANCE 110
#define ENEMY_ATTACK_DEGREES 30
#define ENEMY_VY_DIE 7.0f

#define ENEMY_RIFLEMAN_MAX_BULLET 3
#define ENEMY_RIFLEMAN_ELAPSED_SHOOT 200


//BACKGROUND
#define BG_TILED_WIDTH 16
#define BG_TILED_HEIGTH 16

#endif