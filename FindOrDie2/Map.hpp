#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <mutex>

#include "SFML/Graphics.hpp"

#include "AssetManager.hpp"
#include "TileBlock.hpp"

struct Key
{
	int x;
	int y;

	bool operator==(const Key &other) const
	{
		return (x == other.x && y == other.y);
	}
};

namespace std {

  template <>
  struct hash<Key>
  {
    std::size_t operator()(const Key& k) const
    {
      using std::size_t;
      using std::hash;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(k.x)
               ^ (hash<int>()(k.y) << 1)) >> 1);
    }
  };

}

class Map
{
private:
	Map() noexcept;
	Key GetKey(sf::Vector2f coords);
	std::vector<Key> GetNeighbors(Key key, unsigned int levels);

public:
	static Map* GetInstance()
	{
		static Map instance;
		return &instance;
	}
	~Map();

	void CleanUp();
	void GenerateMap();
	void Draw(sf::RenderWindow* pWindow);
	void SetView(sf::View* pView);

public:
	static const unsigned int tileSize = 64;

private:
	sf::View* m_pCurrentView = nullptr; // no view created here, do not free it
	unsigned long long m_MatrixTileSize = 100;
	sf::FloatRect m_ViewRectBounds;
	sf::Vector2f m_ViewSize = { 0.f, 0.f };
	std::unordered_map < Key, TileBlock* > m_TileBlocks;
	sf::Vector2<int> m_BlockMaxTiles = { 0,0 };
	sf::Vector2<int> m_BlockSize = { 0,0 };

	std::mutex m_mtx;
};

