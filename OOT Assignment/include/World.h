#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL_ttf.h>
#include <memory>
#include <vector>
#include <string>
#include "Partition.h"

class World
{
public:
	World(SDL_Renderer* _renderer);
	~World();

	void Update(float _deltaTime);
	void Draw(bool _showPartitions);

	// Debug and informative functions
	void GetPartitionInfo(int _x, int _y);

private:
	SDL_Renderer* m_renderer;
	std::vector<std::shared_ptr<Partition>> m_partitions;

	SDL_Color m_textCol;
	SDL_Texture* m_textSprite;
	TTF_Font* m_font;
	SDL_Rect m_textRect;
	std::string m_text;
};

#endif