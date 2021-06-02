#pragma once
#include "Bullet.h"
#include "Player.h"
#include "BufferData.h"

namespace BulletFireSystem
{
	#define MAX_BULLETS 50
	
	extern std::vector<Bullet*> bullets;

	void SpawnBullet(Player* player);

	void CreateBullets(BufferData& bufferData);

	Bullet* FindInactiveBullet();
}