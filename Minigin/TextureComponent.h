#pragma once
#include "BaseComponent.h"

namespace dae
{

	class Texture2D;

	class TextureComponent  final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filePath);
		~TextureComponent() = default;
		void Initialize() override{};
		void Update(float) override {}
		void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_spTexture;
	};

}
