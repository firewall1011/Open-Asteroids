#include <vector>

#include "BulletFireSystem.h"

namespace BulletFireSystem
{
	std::vector<Bullet*> bullets;
	void SpawnBullet(Player* player) 
	{
		Bullet* b = FindInactiveBullet();
		if (b == nullptr)
			return;
		vec2 player_look_dir = vec2(cosf(player->rotation + T_PI / 2.f), sinf(player->rotation + T_PI / 2.f)).normalized();
		b->SetMoveDir(player_look_dir);
		b->position = player_look_dir * player->scale.x; // In front of player
		b->isActive = true;
	}

	void CreateBullets(BufferData& bufferData) 
	{
		for (int i = 0; i < MAX_BULLETS; i++) 
		{
			bullets.push_back(new Bullet());
			bufferData.data.push_back(bullets.back());
		}
	}

	Bullet* FindInactiveBullet() 
	{
		for (Bullet* b : bullets) {
			if (!b->isActive)
				return b;
		}
		return nullptr;
	}
}