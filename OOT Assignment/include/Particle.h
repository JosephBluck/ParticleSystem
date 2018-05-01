#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SDL.h>
#include "Partition.h"

class Partition;

class Particle
{
public:
	Particle(SDL_Renderer* _renderer, float _x, float _y, float _w, float _h);
	~Particle();

	void Update(float _deltaTime);
	void Draw();

	int GetX() { return m_x; }
	int GetY() { return m_y; }

private:
	SDL_Renderer* m_renderer;
	float m_x, m_y, m_xSpeed, m_ySpeed;
	float m_worldWidth, m_worldHeight;

	int m_diameter;
	
	int m_r, m_g, m_b;

	std::weak_ptr<Partition> m_parent;
};

#endif