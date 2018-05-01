#include "Partition.h"

Partition::Partition(SDL_Renderer* _renderer, int _x, int _y, int _w, int _h)
{
	m_renderer = _renderer;

	m_boundaries.x = _x;
	m_boundaries.y = _y;
	m_boundaries.w = _w;
	m_boundaries.h = _h;

	// Create some random particles for testing
	for (int i = 0; i < 4; i++)
	{
		m_particles.push_back(std::make_shared<Particle>(m_renderer, m_boundaries.x + rand() % m_boundaries.w, m_boundaries.y + rand() % m_boundaries.h, 1600, 900));
	}
}

Partition::~Partition()
{

}

void Partition::Update(float _deltaTime)
{
	if (m_particles.size() == 0) { return; }


	int x, y;
	for (std::list<std::shared_ptr<Particle>>::iterator i = m_particles.begin(); i != m_particles.end(); ++i)
	{
		(*i)->Update(_deltaTime);

		// Check if particle has left partition boundaries
		x = (*i)->GetX();
		y = (*i)->GetY();

		if (x < m_boundaries.x || x >= m_boundaries.x + m_boundaries.w || y < m_boundaries.y || y >= m_boundaries.y + m_boundaries.h)
		{
			for (size_t p = 0; p < m_neighbours.size(); p++)
			{
				if (m_neighbours.at(p).lock()->IsInBoundary(x, y))
				{
					m_neighbours.at(p).lock()->AddParticle(std::make_shared<Particle>(*(*i)));

					// (i).reset();    // Can someone for the love of god tell me how you reset a shared_ptr from a list

					i = m_particles.erase(i);
					break;
				}
			}
		}

		if (m_particles.size() == 0) { break; }
		if (i == m_particles.end()) { break; }
	}
}

void Partition::Draw(bool _showBoundaries)
{
	// Drawing particles is so digustingly expensive, RIP framerate 
	for (std::list<std::shared_ptr<Particle>>::const_iterator i = m_particles.begin(); i != m_particles.end(); ++i)
	{
		(*i)->Draw();
	}

	if (_showBoundaries)
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, 0);
		SDL_RenderDrawRect(m_renderer, &m_boundaries);
	}
}

bool Partition::IsInBoundary(int _x, int _y)
{
	return !(_x < m_boundaries.x || _x >= m_boundaries.x + m_boundaries.w || _y < m_boundaries.y || _y >= m_boundaries.y + m_boundaries.h);
}