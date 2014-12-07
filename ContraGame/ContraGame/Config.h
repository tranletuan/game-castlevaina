#ifndef _CONFIG_H_
#define _CONFIG_H_

#define MAP_FOLDER L"resources/map/"

//GRAVITY
#define GRAVITY 0.011f

//BILL 
#define BILL_VX 0.06f
#define BILL_VY 5.95f	
#define BILL_VY_DIE  5.0f
#define BILL_BOUNDS_WIDTH 8
#define BILL_BOUNDS_HEIGHT 28

//BULLET
#define BULLET_REINFORCE 0.05f

#define BULLET_N_V 0.18f
#define BULLET_N_TOTAL 4

#define BULLET_S_TOTAL 10
#define BULLET_S_COUNT_ONE_SHOOT 5
#define BULLET_S_ELAPSED_DEGREES 10
#define BULLET_S_V 0.2f
#define BULLET_S_ELAPSED_TIME 100

#define BULLET_F_V 0.12f
#define BULLET_F_R 18
#define BULLET_F_ELAPSED_DEGREES 20
#define BULLET_F_TOTAL 4

#define BULLET_L_V 0.25f
#define BULLET_L_ELAPSED_DIS 10
#define BULLET_L_TOTAL 3

#define BULLET_M_V 0.25f
#define BULLET_M_TOTAL 4

#define BULLET_NE_V 0.08f
#define BULLET_NE_TOTAL 30

#define BULLET_B_VX 0.05f
#define BULLET_B_RANDOM_VX 150
#define BULLET_B_VY 5.0f
#define BULLET_B_TOTAL 4

//GROUND
#define GROUND_SIZE_NORMAL 32
#define GROUND_TIME_EFFECT 300

#define GROUND_BRIDGE_DESTROY_EFFECT_COUNT 3
#define GROUND_BRIDGE_ELAPSED_RANDOM_POSITION 14
#define GROUND_BRIDGE_DESTROY_TIME 900
#define GROUND_BRIDGE_DISTANCE_DESTROY 32

//EFFECT 
#define EFFECT_DESTROY_TIME 300

//ENEMY
#define ENEMY_ATTACK_DISTANCE 150
#define ENEMY_ATTACK_DEGREES 30
#define ENEMY_VY_DIE 4.8f

#define ENEMY_SNIPER_STAND_MAX_BULLET 3
#define ENEMY_SNIPER_STAND_ELAPSED_SHOOT 300

#define ENEMY_SNIPER_HIDE_MAX_BULLET 1
#define ENEMT_SNIPER_HIDE_TIME_WAIT 2000

#define ENEMY_GROUND_CANON_MAX_BULLET 3
#define ENEMY_GROUND_CANON_ELAPSED_SHOOT 300

#define ENEMY_WALL_TURRET_MAX_BULLET 1
#define ENEMY_GROUND_CANON_ELAPSED_SHOOT 300

#define ENEMY_RUN_MAN_VX 0.08f
#define ENEMY_RUN_MAN_VY 8.0f
#define ENEMY_RUN_MAN_BOUNDS_WIDTH 18
#define ENEMY_RUN_MAN_BOUNDS_HEIGHT 34
#define ENEMY_RUN_MAN_TOTAL 5

//BACKGROUND
#define BG_TILED_WIDTH 16
#define BG_TILED_HEIGTH 16

// ITEM
#define ITEM_STAND_VY_ENABLE 6.7f
#define ITEM_STAND_VX_ENABLE 0.044f

#define ITEM_FLY_VX_MOVE 0.08f
#define ITEM_FLY_VY_MOVE 0.08f
#define ITEM_FLY_ANGLE 5 
#define ITEM_FLY_BOUND_COS 2
#define ITEM_FLY_VX_DIE 0.05f
#define ITEM_FLY_VY_DIE 10.0f

// BOSS
#define BOSS1_SPACE_X 36
#define BOSS1_SPACE_Y 36
#define BOSS1_SPACE_DESTROY_X 15
#define BOSS1_SPACE_DESTROY_Y 30
#define BOSS1_NUMBER_DESTROY 8


#endif