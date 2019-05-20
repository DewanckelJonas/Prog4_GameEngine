#pragma once
namespace dae
{
	class GameObject;
	class BaseCommand
	{
	public:
		BaseCommand() {}
		virtual void SetActor(const std::weak_ptr<GameObject>& pGameObject) { m_pActor = pGameObject; };
		virtual void Execute() = 0;
		virtual ~BaseCommand() = default;
	protected:
		const std::weak_ptr<GameObject>& GetActor() { return m_pActor; }
	private:
		std::weak_ptr<GameObject> m_pActor;
	};
}

