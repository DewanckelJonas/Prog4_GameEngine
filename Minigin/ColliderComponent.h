#pragma once
#include "Shapes.h"
#include "BaseComponent.h"
#include <string>
#include <vector>
namespace dae
{
	class TransformComponent;
	class ColliderComponent;
	struct Collision
	{
		ColliderComponent* otherCollider;
		Rect intersection;
	};
	class ColliderComponent : public BaseComponent
	{
	public:
		ColliderComponent(const Rect& shape, const std::string& tag);
		~ColliderComponent();
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override {};
		void CheckCollision(ColliderComponent& collider);
		const std::vector<Collision>& GetCollisions();
		void ClearCollisions();
		glm::vec2 GetWorldPosition() { return m_Shape.pos; }
		glm::vec2 GetLocalPosition() { return m_LocalPos; }
		void SetLocalPosition(const glm::vec2& pos) { m_LocalPos = pos; }
		float GetWidth() { return m_Shape.width; }
		float GetHeight() { return m_Shape.height; }
		const std::string& GetTag() { return m_Tag; }
		void SetTag(const std::string& tag) { m_Tag = tag; }

	private:
		Rect m_Shape;
		std::string m_Tag;
		std::vector<Collision> m_Collisions;
		std::weak_ptr<TransformComponent> m_pTransform;
		glm::vec2 m_LocalPos;
	};
}

