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

	// Ground
	Ground_Grass, // vo hinh
	Ground_Water,
	Ground_Effect1,
	Ground_Bridge,

	// Effect
	EffectDestroy,

	//Enemy
	RunMan,
	RunMan_Fire,
	Sniper_Stand,
	Sniper_Hide,
	Ground_Canon,
	Wall_Turret,


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

	// Boss
	Boss1,
	Boss_Gun,
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
