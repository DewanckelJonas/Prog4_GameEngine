#pragma once
#include "BaseComponent.h"
#include "Transform.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent(){};
	void SetPosition(const glm::vec3& pos) { m_Transform.Position = pos; }
	glm::vec3 GetPosition() { return m_Transform.Position; }

private:
	Transform m_Transform{};
};

