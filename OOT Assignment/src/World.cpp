#include "World.h"
#include <iostream> // Console debugging

World::World(SDL_Renderer* _renderer)
{
	m_renderer = _renderer;
	m_font = TTF_OpenFont("resources\\arial.ttf", 32);

	m_textSprite = NULL;

	m_textRect.x = 0;
	m_textRect.y = 0;
	m_textRect.w = 200;
	m_textRect.h = 100;

	m_textCol.r = 255;
	m_textCol.g = 0;
	m_textCol.b = 0;
	m_textCol.a = 0;

	// By default, split world into 10 x 10 partition grid
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			m_partitions.push_back(std::make_shared<Partition>(m_renderer, x * 100, y * 100, 100, 100));
		}
	}

	int particleCount = 0;

	// Neighbour partitions (and count starting particles)
	for (size_t i = 0; i < m_partitions.size(); i++)
	{
		SDL_Rect rect = m_partitions.at(i)->GetBoundaries();
		particleCount += m_partitions.at(i)->GetParticles().size();

		for (size_t p = 0; p < m_partitions.size(); p++)
		{
			if (p == i) { continue; } // Don't test self
			SDL_Rect temp = m_partitions.at(p)->GetBoundaries();

			if (abs(rect.x - temp.x) <= temp.w && abs(rect.y - temp.y) <= temp.h)
			{
				m_partitions.at(i)->AddNeighbour(std::weak_ptr<Partition>(m_partitions.at(p)));
			}

		}

		//std::cout << "Partition " << (int)i << " has " << m_partitions.at(i)->GetNeighbours().size() << " neighbours!\n";
	}
	std::cout << "There are " << particleCount << " particles spawned...\n";

}

World::~World()
{
	if (m_textSprite != NULL) { SDL_DestroyTexture(m_textSprite); }
}

void World::Update(float _deltaTime)
{
	for (size_t i = 0; i < m_partitions.size(); i++)
	{
		m_partitions.at(i)->Update(_deltaTime);
	}
}

void World::Draw(bool _showPartitions)
{
	if (_showPartitions)
	{
		for (size_t i = 0; i < m_partitions.size(); i++){ m_partitions.at(i)->Draw(true); }
	}
}

void World::GetPartitionInfo(int _x, int _y)
{
	std::weak_ptr<Partition> part;
	bool found = false;

	for (size_t i = 0; i < m_partitions.size(); i++)
	{
		SDL_Rect temp = m_partitions.at(i)->GetBoundaries();
		if (_x >= temp.x && _x < temp.x + temp.w && _y >= temp.y && _y < temp.y + temp.h)
		{
			part = m_partitions.at(i);
			found = true;
			break;
		}
	}

	if (!found) { return; }

	if (m_textSprite != NULL)
	{
		SDL_DestroyTexture(m_textSprite);
	}

	m_textRect.x = _x;
	m_textRect.y = _y;

	if (_x > 1600 - m_textRect.w) { m_textRect.x = 1600 - m_textRect.w; }
	
	m_text = "Neighbours: " + std::to_string(part.lock()->GetNeighbours().size()) + "  Particles: " + std::to_string(part.lock()->GetParticles().size());
	SDL_Surface* temp = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), m_textCol, m_textRect.w);

	m_textSprite = SDL_CreateTextureFromSurface(m_renderer, temp);
	SDL_FreeSurface(temp);

	SDL_RenderCopy(m_renderer, m_textSprite, NULL, &m_textRect);
}