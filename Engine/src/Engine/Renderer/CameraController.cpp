#include "stdafx.h"
#include "CameraController.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"

namespace Engine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	
	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);

		if (m_Rotation)
		{
			if (Engine::Input::IsKeyPoressed(ENGINE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Engine::Input::IsKeyPoressed(ENGINE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}
		
		
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizedEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
