#pragma once
#include "../Engine/Core/System.h"

namespace nc
{
	class Renderer : public System
	{
	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		bool Create(const std::string& name, int width, int height);
		void BeginFrame();
		void EndFrame();

		friend class Texture;
		//SDL_Renderer* GetSDLRenderer() { return m_renderer; }

	protected:
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}