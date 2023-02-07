#pragma once
#include "Engine/Renderer/Camera.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/WindowEvent.h"
namespace Engine
{
	struct OrthographicCameraBounds
	{
		float Left, Right, Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);


		float m_AspectRatio;//���ݱ�
		float m_ZoomLevel = 1.0f;//���ŵȼ�

		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;
		
		bool m_Rotation;//��ת
		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_CameraRotation = 0.0f;
		float m_CameraMoveSpeed = 1.0f, m_CameraRotationSpeed = 10.0f;

	};

}


