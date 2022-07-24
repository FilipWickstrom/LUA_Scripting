#pragma once
#include "Unordered_vec3_map.h"

class Gridsystem
{
private:
	irr::core::vector2di	m_size;
	irr::video::SColor		m_color;
	irr::scene::ISceneNode* m_gridNode;
	irr::scene::IMesh*		m_hoverMesh;
	irr::scene::ISceneNode* m_hoverNode;

	// Key: irr::core::vector3di | Value: unsigned int
	unodered_vec3_map m_vec3ToID;	
	std::unordered_map<unsigned int, irr::core::vector3di> m_idToVec3;
	
private:
	void LoadGrid();
	bool OutOfBounds(const irr::core::vector2di& vec);

public:
	Gridsystem(const irr::core::vector2di& size = { 25, 25 });
	~Gridsystem();

	// Resize or change the size of the grid
	void SetSize(const irr::core::vector2di& size);

	// Update the hover tile every frame so that it is on the right tile
	void UpdateHoverEffect();

	// Check if there is anything on this tile
	bool IsTileOccupied(const int& layer, irr::core::vector3di& tilePos);

	// Add a tile to in the grid on a specific layer
	bool AddTileAtMouse(const unsigned int& id, const int& depth = 0);	//TODO: Return position
	irr::core::vector3df GetTilePosition(const unsigned int& id) const;

	bool AddTile(const unsigned int& id, const irr::core::vector3df& pos);

	// Return id of the removed tile
	int RemoveTile(const int& depth = 0);

	// Reset all the maps 
	void ResetGrid();
};