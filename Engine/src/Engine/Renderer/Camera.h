#pragma once
#include <glm/glm.hpp>
namespace Engine
{
	struct OrthographicCameraBounds
	{
		float Left, Right, Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float aspectRatio, float zoomLevel);

		void SetProjection(float aspectRatio, float zoomLevel);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		const float GetRotation() const { return m_Rotation; }

		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4 GetVeiwMatrix() const { return m_VeiwMatrix; }
		const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

		

		float m_AspectRatio;//横纵比
		float m_ZoomLevel = 1.0f;//缩放等级

		OrthographicCameraBounds m_Bounds;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_VeiwMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;

	};


}

