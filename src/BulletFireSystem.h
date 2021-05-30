#pragma once
#include "Bullet.h"
#include "Player.h"
#include "BufferData.h"

namespace BulletFireSystem
{
	#define MAX_BULLETS 50

	void SpawnBullet(Player* player);

	void CreateBullets(BufferData& bufferData);

	Bullet* FindInactiveBullet();
}