#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "BaseCommand.h"

namespace dae
{

	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(const glm::vec3& pos){ m_Transform.Position = pos; };
		void SetPosition(const glm::vec3& pos) { m_Transform.Position = pos; }
		glm::vec3 GetPosition() const { return m_Transform.Position; }
		glm::vec2 GetScale() const { return m_Transform.Scale; }
		void SetScale(const glm::vec2& scale) { m_Transform.Scale = scale; }
		void SetRotation(float angle) { m_Transform.Rotation = angle; }
		float GetRotation() const { return m_Transform.Rotation; }
		void Translate(const glm::vec3& translation) { m_Transform.Position += translation; }


		virtual void Initialize() override {};
		virtual void Update(float) override {};
		virtual void Render() const override {};

	private:
		Transform m_Transform{};
	};

	class MoveCmd : public BaseCommand
	{
	public:
		MoveCmd(glm::vec3 direction, float speed) : m_Direction(direction), m_Speed(speed) {}
		void Execute() override { GetActor().lock()->GetComponent<TransformComponent>().lock()->Translate(m_Speed * m_Direction); }

	private:
		float m_Speed;
		glm::vec3 m_Direction;
	};
}



