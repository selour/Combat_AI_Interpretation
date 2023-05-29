#pragma once
#include <glm/glm.hpp>
#include "Engine.h"
#include "Object.h"
#include "ResourceManager.h"
#include <memory>
#include <vector>

class ObjectList
{
friend class ObjectManager;
protected:
	void Add(const std::shared_ptr<GameObject>& object);
	void SetPost(const std::shared_ptr<PostObject>& object);
	void SetCamera(const std::shared_ptr<Engine::Camera>& camera);
	void Update(float ts);
	void Render();
	void OnImGuiRender();
private:
	std::shared_ptr<Engine::Camera> m_Camera = nullptr;
	std::shared_ptr<PostObject> m_Post = nullptr;
	std::vector<std::shared_ptr<GameObject>> m_Objects;

};

class ObjectManager
{
public:
	void Reset(int max);
	void Add(int index, const std::shared_ptr<GameObject>& object);
	void AddLogic(const std::shared_ptr<GameObject>& object);
	void SetPost(int index, const std::shared_ptr<PostObject>& object);
	void SetCamera(int index, const std::shared_ptr<Engine::Camera>& camera);


	bool IsOverflow(int index) const;

	void Update(float ts);
	void Render();
	void OnImGuiRender();


	void SetResourceManager(ResourceManager* resourceManager)
	{
		m_ResourceManager = resourceManager;
	}
	void SetCameraLibrary(Engine::CameraLibrary* cameraLibrary)
	{
		m_CameraLibrary = cameraLibrary;
	}
	ResourceManager* GetResourceManager()
	{
		return m_ResourceManager;
	}

	Engine::CameraLibrary* GetCameraLibrary()
	{
		return m_CameraLibrary;
	}
	SoundSourceLibrary* GetSoundSourceLibrary()
	{
		return m_ResourceManager->GetSoundSourceLibrary();
	}
	Engine::ShaderLibrary* GetShaderLibrary()
	{
		return m_ResourceManager->GetShaderLibrary();
	}
	Engine::Texture2DArrayLibrary* GetTextureLibrary()
	{
		return m_ResourceManager->GetTextureLibrary();
	}
private:

	std::vector<std::shared_ptr<GameObject>> m_LogicObjects;
	std::vector<ObjectList> m_ObjectLayers;
	int m_MaxIndex = 0;

	ResourceManager* m_ResourceManager = nullptr;
	Engine::CameraLibrary* m_CameraLibrary = nullptr;
};

