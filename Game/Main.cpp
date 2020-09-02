#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{
	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("Scene.txt", document);
	scene.Create(&engine);
	scene.Read(document);

	nc::TileMap tileMap;
	nc::json::Load("tileMap.txt", document);
	tileMap.Read(document);
	tileMap.Create(&scene);

	/*
	for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("BoxPro");
		gameObject->m_transform.angle = nc::random(0, 360);
		gameObject->m_transform.position = nc::Vector2{ nc::random(0, 50), nc::random(0,10) };
		scene.AddGameObject(gameObject);
	}
	for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("NukePro");
		gameObject->m_transform.position = nc::Vector2{ nc::random(0, 50), nc::random(0,20) };
		scene.AddGameObject(gameObject);
	}
	for (size_t i = 0; i < 6; i++)
	{
		float y = i * 2.8f;
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("WallPro");
		gameObject->m_transform.position = nc::Vector2{ 0.0f, y };
		scene.AddGameObject(gameObject);
	}
	for (size_t i = 0; i < 7; i++)
	{
		float y = i * 2.8f;
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("WallPro");
		gameObject->m_transform.position = nc::Vector2{ 40.0f, y };
		scene.AddGameObject(gameObject);
	}
	*/

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
				quit = true;
				break;
		}

		//UPDATE
		engine.Update();
		scene.Update();

		//esc - QUIT
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		//DRAW
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();

	return 0;
}

