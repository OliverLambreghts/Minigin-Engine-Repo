#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float elapsedSec)
{
	for(auto& object : m_Objects)
	{
		object->Update(elapsedSec);
	}
}

void Scene::Render() const
{
	for (const auto& renderData : m_RenderData)
	{
		renderData();
	}
}

void Scene::AddRenderData(std::function<void()>& fcnPtr)
{
	m_RenderData.push_back(fcnPtr);
}