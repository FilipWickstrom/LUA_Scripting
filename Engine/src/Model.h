#pragma once

class Model
{
private:
	//ID counter that increases for every added model
	static unsigned int s_idCounter;

	irr::scene::ISceneNode* m_node;

	// This could potentially be used with the script to identify which model is linked to which table.
	unsigned int m_id = 0;

	void LoadMesh(const std::string& meshName);

public:

	Model();
	Model(const std::string& meshName);
	~Model() = default;

	void SetID(unsigned int id);
	unsigned int GetID() const;

	void SetPosition(const irr::core::vector3df& pos);
	void SetScale(const float& scale);

	void Update();

	void Drop();
};