#include "PCH.h"
#include "Gridsystem.h"

Gridsystem::Gridsystem(const irr::core::vector2di& size)
{
	m_size = size;
    // Green grid
    m_color = irr::video::SColor(255, 0, 255, 0);
    m_gridNode = nullptr;
    this->LoadGrid();

    // Reserve some memory
    m_idToVec3.reserve(static_cast<size_t>(m_size.X) * m_size.Y * 3);
    m_vec3ToID.reserve(static_cast<size_t>(m_size.X) * m_size.Y * 3);

    // Prepare the hover effecter
    m_hoverMesh = Graphics::GetGeometryCreator()->createPlaneMesh({ TILE_SIZE, TILE_SIZE });
    m_hoverNode = Graphics::GetSceneManager()->addMeshSceneNode(m_hoverMesh);
    m_hoverNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    m_hoverNode->setMaterialType(irr::video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ADD_COLOR);
    m_hoverNode->setVisible(false);
}

Gridsystem::~Gridsystem()
{
    this->ResetGrid();
}

void Gridsystem::LoadGrid()
{
    irr::core::dimension2du dimension(m_size.X, m_size.Y);
    irr::scene::IMesh* mesh = Graphics::GetGeometryCreator()->createPlaneMesh({ TILE_SIZE, TILE_SIZE }, dimension);
    m_gridNode = Graphics::GetSceneManager()->addMeshSceneNode(mesh);
    irr::core::vector2df gridPos;

    // Even width
    if (dimension.Width % 2 == 0)
        gridPos.X = TILE_SIZE / 2.f;
    // Even height
    if (dimension.Height % 2 == 0)
        gridPos.Y = TILE_SIZE / 2.f;

    // Align it to be in the background
    m_gridNode->setPosition({ gridPos.X, -10, gridPos.Y });

    // Change color of the mesh
    Graphics::GetSceneManager()->getMeshManipulator()->setVertexColors(mesh, m_color);

    m_gridNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    m_gridNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_WIREFRAME, true);
}

bool Gridsystem::OutOfBounds(const irr::core::vector2di& vec)
{
    int right   =  m_size.X / 2;
    int left    = -m_size.X / 2;
    int top     =  m_size.Y / 2;
    int bottom  = -m_size.Y / 2;

    // Special cases when even
    if (m_size.X % 2 == 0)
        left++;
    if (m_size.Y % 2 == 0)
        bottom++;

    if (vec.X > right || vec.X < left) 
        return true;
    else if (vec.Y > top || vec.Y < bottom)
        return true;
    else
        return false;
}

void Gridsystem::SetSize(const irr::core::vector2di& size)
{
    m_size = size;
    this->ResetGrid();

    // Reserve some memory
    m_idToVec3.reserve(static_cast<size_t>(m_size.X) * m_size.Y * 3);
    m_vec3ToID.reserve(static_cast<size_t>(m_size.X) * m_size.Y * 3);

    this->LoadGrid();
}

void Gridsystem::UpdateHoverEffect()
{
    bool occupied = false;

    // If we are out of bounds - set visibility to false

    // If tile is occupied - set visibility to true and mesh to red

    // If tile is not occupied - set visibility to true and mesh to green


    //m_hoverNode->setPosition({ vec.X * TILE_SIZE, 4, vec.Z * TILE_SIZE });
    if (occupied)
        Graphics::GetSceneManager()->getMeshManipulator()->setVertexColors(m_hoverMesh, irr::video::SColor(10, 255, 0, 0));
    else 
        Graphics::GetSceneManager()->getMeshManipulator()->setVertexColors(m_hoverMesh, irr::video::SColor(10, 0, 255, 0));
}

bool Gridsystem::IsTileOccupied(const int& layer, irr::core::vector3di& tilePos)
{
    irr::core::vector3df position = SceneHandler::GetWorldCoordFromScreen();

    tilePos.X = static_cast<int>(std::round(position.X / TILE_SIZE));
    tilePos.Y = layer;
    tilePos.Z = static_cast<int>(std::round(position.Z / TILE_SIZE));

    if (this->OutOfBounds({ tilePos.X, tilePos.Z }))
        return true;

     // Return true if this tile was occupied
     return m_vec3ToID.find(tilePos) != m_vec3ToID.end();
}

bool Gridsystem::AddTileAtMouse(const unsigned int& id, const int& depth)
{
    irr::core::vector3di tile;

    if (IsTileOccupied(depth, tile))
        return false;

    // Add the tile to the map
    m_vec3ToID[tile] = id;
    m_idToVec3[id] = tile;
    return true;
}

irr::core::vector3df Gridsystem::GetTilePosition(const unsigned int& id) const
{
    irr::core::vector3df pos;

    if (m_idToVec3.find(id) != m_idToVec3.end())
    {
        irr::core::vector3di tile = m_idToVec3.at(id);

        pos.X = static_cast<float>(tile.X * TILE_SIZE);
        pos.Y = static_cast<float>(tile.Y);
        pos.Z = static_cast<float>(tile.Z * TILE_SIZE);
    }
    return pos;
}

bool Gridsystem::AddTile(const unsigned int& id, const irr::core::vector3df& pos)
{
    irr::core::vector3di tilePos;
    tilePos.X = static_cast<irr::s32>(pos.X / TILE_SIZE);
    tilePos.Y = static_cast<irr::s32>(pos.Y);
    tilePos.Z = static_cast<irr::s32>(pos.Z / TILE_SIZE);
    
    if (m_vec3ToID.find(tilePos) == m_vec3ToID.end())
    {
        m_idToVec3[id] = tilePos;
        m_vec3ToID[tilePos] = id;
        return true;
    }
    else
    {
        return false;
    }
}

int Gridsystem::RemoveTile(const int& depth)
{
    int id = -1;
    irr::core::vector3di tile;

    // Do we have a tile where the mouse is?
    if (IsTileOccupied(depth, tile))
    {
        // Out of bounds check
        if (m_vec3ToID.find(tile) != m_vec3ToID.end())
        {
            id = static_cast<int>(m_vec3ToID.at(tile));
            m_vec3ToID.erase(tile);

            if (m_idToVec3.find(id) != m_idToVec3.end())
                m_idToVec3.erase(id);
        }
    }
    return id;
}

void Gridsystem::ResetGrid()
{
    m_vec3ToID.clear();
    m_idToVec3.clear();
}
