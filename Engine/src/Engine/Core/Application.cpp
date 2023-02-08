#include "stdafx.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Core/Random.h"
namespace Engine
{

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		ENGINE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));
		
		Renderer::Init();

		//Random::Init();
		m_ImGuiLayer = new ImGuiLayer();
		AppPushOverlay(m_ImGuiLayer);
		
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timeStep);
				}



			}
			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowResize));
		//ENGINE_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
		{
			
			if (e.m_Handled)
				break;
			(*it)->OnEvent(e);
		}

	}

	void Application::AppPushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::AppPushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizedEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}