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
	Ground3, 
	GroundBridge,

	// Effect
	EffectDestroy, 

	//Enemy
	RunMan,
	RunMan_Fire,
	Sniper_Stand,
	Sniper_Hide,
	
	
	// Item
	ItemM,
	ItemL,
	ItemR,
};

// loai object
enum BasicType
{
	Player,
	Bullet,
	Ground,
	Effect,
	Enemy
};

#endif
