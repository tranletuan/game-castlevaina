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
#define BULLET_N_COUNT 4

#define BULLET_S_COUNT 10
#define BULLET_S_COUNT_ONE_SHOOT 5
#define BULLET_S_ELAPSED_DEGREES 10
#define BULLET_S_V 0.2f
#define BULLET_S_ELAPSED_TIME 100

#define BULLET_F_V 0.1f
#define BULLET_F_R 20
#define BULLET_F_ELAPSED_DEGREES 20

#define BULLET_L_V 0.3f
#define BULLET_L_ELAPSED_DIS 10

#define BULLET_M_V 0.25f

#define BULLET_NE_V 0.06f

//GROUND
#define GROUND_SIZE_NORMAL 32
#define GROUND_TIME_EFFECT 300

#define GROUND_BRIDGE_DESTROY_EFFECT_COUNT 4
#define GROUND_BRIDGE_ELAPSED_RANDOM_POSITION 14
#define GROUND_BRIDGE_DESTROY_TIME 800
#define GROUND_BRIDGE_DISTANCE_DESTROY 32

//EFFECT 
#define EFFECT_DESTROY_TIME 200

#endif