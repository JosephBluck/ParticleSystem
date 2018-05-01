#ifndef _PARTITION_H_
#define _PARTITION_H_

#include <SDL.h>
#include <list>
#include <memory>
#include <vector>
#include "Particle.h"

class Particle;

class Partition
{
public:
	Partition(SDL_Renderer* _renderer, int _x, int _y, int _w, int _h);
	~Partition();

	void Update(float _deltaTime);
	void Draw(bool _showBoundaries);

	// Set / Add functions
	void AddNeighbour(std::weak_ptr<Partition> _partition) { m_neighbours.push_back(_partition); }
	void AddParticle(std::shared_ptr<Particle> _particle) { m_particles.push_back(_particle); }

	// Get functions
	bool IsInBoundary(int _x, int _y);
	SDL_Rect& GetBoundaries() { return m_boundaries; }
	std::vector<std::weak_ptr<Partition>>& GetNeighbours() { return m_neighbours; }
	std::list<std::shared_ptr<Particle>>& GetParticles() { return m_particles; }

private:
	SDL_Renderer* m_renderer;
	std::vector<std::weak_ptr<Partition>> m_neighbours;
	std::list<std::shared_ptr<Particle>> m_particles;

	bool m_isEdge = false; // Is the partition on the edge / corner of the screen? If so, check that particles bounce off sides
	
	SDL_Rect m_boundaries; // Use SDL Rect to store location and draw boundary
};

#endif