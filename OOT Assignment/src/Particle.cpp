#include "Particle.h"
#include <cmath>

Particle::Particle(SDL_Renderer* _renderer, float _x, float _y, float _w, float _h)
{
	m_renderer = _renderer;
	m_x = _x;
	m_y = _y;

	m_worldWidth = _w;
	m_worldHeight = _h;

	m_xSpeed = -20 + (rand() % 41);
	m_ySpeed = -20 + (rand() % 41);
	m_diameter = 1+ (rand() % 20);

	m_r = rand() % 256;
	m_g = rand() % 256;
	m_b = rand() % 256;

	if (m_r + m_g + m_b < 50)
	{
		int add = 50 - (m_r + m_g + m_b);
		
		m_r += add / 3;
		m_g += add / 3;
		m_b += add / 3;
	}
}

Particle::~Particle()
{

}

void Particle::Update(float _deltaTime)
{
	m_x += m_xSpeed * _deltaTime;
	m_y += m_ySpeed * _deltaTime;

	// World boundary checking
	if (m_x - (m_diameter / 2.0f) < 0) { m_x = m_diameter / 2.0f; m_xSpeed *= -1; }
	else if (m_x + (m_diameter / 2.0f) > m_worldWidth) { m_x = m_worldWidth - m_diameter / 2.0f; m_xSpeed *= -1; }

	if (m_y - (m_diameter / 2.0f) < 0) { m_y = m_diameter / 2.0f; m_ySpeed *= -1; }
	else if (m_y + (m_diameter / 2.0f) > m_worldHeight) { m_y = m_worldHeight - m_diameter / 2.0f; m_ySpeed *= -1; }
}

void Particle::Draw()
{
	// Draw particle pls
	SDL_SetRenderDrawColor(m_renderer, m_r, m_g, m_b, 0);

	if (m_diameter > 1)
	{
		for (int x = m_x - (m_diameter / 2.0f); x < m_x + (m_diameter / 2.0f); x++)
		{
			for (int y = m_y - (m_diameter / 2.0f); y < m_y + (m_diameter / 2.0f); y++)
			{
				float xDiff = abs((float)x - m_x);
				float yDiff = abs((float)y - m_y);
				float dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2));

				if (dist <= (float)m_diameter / 2.0f) { SDL_RenderDrawPoint(m_renderer, x, y); }
			}
		}
	}
	else { SDL_RenderDrawPoint(m_renderer, m_x, m_y); }

	//SDL_RenderDrawPoint(m_renderer, m_x, m_y);
}