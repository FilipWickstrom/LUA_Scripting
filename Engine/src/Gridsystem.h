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
	int						m_layer;

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
	bool IsTileOccupied(irr::core::vector3di& tilePos);

	// Get the object at tilepos if it is used
	int GetTileObject(irr::core::vector3di& tilePos);

	void UpdateTilePos(const unsigned int& id);

	// Add a tile to the grid at the mouse position
	bool AddTileAtMouse(const unsigned int& id);
	
	// Add a tile with an id and a position manually
	bool AddTile(const unsigned int& id, const irr::core::vector3df& pos);

	// Get the position of a specific tile
	irr::core::vector3df GetTilePosition(const unsigned int& id) const;

	// Return id of the removed tile
	int RemoveTile();

	// Reset all the maps 
	void ResetGrid();

	void ChangeLayer(const int& layer);
};