#pragma once
#include "Engine/Renderer/Camera.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/WindowEvent.h"
namespace Engine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);


		float m_AspectRatio;//横纵比
		float m_ZoomLevel = 1.0f;//缩放等级
		
		OrthographicCamera m_Camera;
		bool m_Rotation;//旋转
		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_CameraRotation = 0.0f;
		float m_CameraMoveSpeed = 1.0f, m_CameraRotationSpeed = 10.0f;

	};

}


