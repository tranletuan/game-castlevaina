#ifndef COBJECT_H
#define COBJECT_H

// object cu the
enum  SpecificType
{
	//Player
	Player1,
	Player2,

	// bullet
	BulletN,
	BulletM,
	BulletL,
	BulletF,
	BulletS,
	BulletNE,
	BulletB,
	BulletB2,
	BulletSP,

	// Ground
	Ground_Grass, // vo hinh
	Ground_Water,
	Ground_Bridge,
	Ground_RockFly, // hòn đá bay qua lại
	Ground_Electron, // cầu điện ở map 2 để fire di chuyển lên

	// Effect
	EffectDestroy,
	Effect_Star,
	Effect_Water,
	Effect_WaterFall,

	//Enemy
	RunMan,		// nguoi chay
	RunMan_Fire, // nguoi chay ban sung
	Sniper_Stand, // sinper dung yen 
	Sniper_Hide,
	Ground_Canon,
	Wall_Turret,
	Fire_Run, // Ngọn lửa di chuyển ở map 2
	Rock_Roll,  // Viên đá rơi ở map 2
	Sniper_Boss,
	Boom_Throw, // Quả boom ném map 3
	Sniper_Block, // Sniper map 3
	Tank,
	Sniper_Water,

	// Item
	ItemM,
	ItemB,
	ItemL,
	ItemR,
	ItemF,
	ItemS,
	ItemM_Stand, // item dung yen
	ItemF_Stand,
	ItemS_Stand,
	ItemL_Stand,
	ItemB_Stand,	

	// Boss
	Boss1,
	Boss1_Gun,
	Boss2,
	Boss2_Elbow,
	Boss2_Hand, 
	Boss2_Arm,
	Boss3,

};

// loai object
enum BasicType
{
	Player,
	Bullet,
	Ground,
	Effect,
	Enemy,
	Item
};

// đường đi của ob
enum TrackID
{
	Track_LR, // trai sang pai
	Track_RL,
	Track_UD, // tren xuong duoi
	Track_DU,
};

#endif
