#pragma once
namespace dae
{
	class GameObject;
	class BaseCommand
	{
	public:
		BaseCommand() {}
		virtual void SetActor(GameObject* pGameObject) { m_pActor = pGameObject; };
		virtual void Execute() = 0;
		virtual ~BaseCommand() = default;
	protected:
		GameObject* GetActor() { return m_pActor; }
	private:
		GameObject* m_pActor;
	};
}

