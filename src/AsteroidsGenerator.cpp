#pragma once
#include "AsteroidsGenerator.h"
#include "Random.h"
#include "AsteroidPoolingSystem.h"

AsteroidsGenerator::AsteroidsGenerator(float min_asteroid_radius, float max_asteroid_radius, int min_asteroid_vertices, int max_asteroid_vertices, float min_asteroid_speed, float max_asteroid_speed, float orbit_radius)
{
	this->max_asteroid_radius = max_asteroid_radius;
	this->min_asteroid_radius = min_asteroid_radius;
	this->max_asteroid_vertices = max_asteroid_vertices;
	this->min_asteroid_vertices = min_asteroid_vertices;
	this->min_asteroid_speed = min_asteroid_speed;
	this->max_asteroid_speed = max_asteroid_speed;
	this->orbit_radius = orbit_radius;
}

Asteroid * AsteroidsGenerator::CreateAsteroid()
{
	int num_vertices = Random::Range(min_asteroid_vertices, max_asteroid_vertices);
	float radius = Random::Range(min_asteroid_radius, max_asteroid_radius);
	
	float noise = Random::Value() * 0.1f;

	float angle = Random::Value() * 2 * T_PI;

	float speed = Random::Range(min_asteroid_speed, max_asteroid_speed);

	return new Asteroid(num_vertices, radius, noise, speed);
}

void AsteroidsGenerator::CreateAsteroids(int qtd)
{
	for (int i = 0; i < qtd; i++)
	{
		AsteroidPoolingSystem::asteroids.push_back(CreateAsteroid());
	}
}
