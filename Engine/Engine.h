#pragma once
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Resources/ResourceManager.h"
#include "../Engine/Core/Timer.h"
#include "../Engine/Input/InputSystem.h"
#include <vector>

namespace nc
{
	class System;

	class Engine
	{
	public:
		bool Startup();
		void Shutdown();

		void Update();

		template<typename T>
		T* GetSystem();
		nc::FrameTimer& GetTimer() { return m_timer; }

	protected:
		std::vector<System*> m_systems;
		nc::FrameTimer m_timer;
	};

	template<typename T>
	inline T* Engine::GetSystem()
	{
		T* result{ nullptr };
		for (auto system : m_systems)
		{
			result = dynamic_cast<T*>(system);
			if (result)break;
		}
		return result;
	}
}