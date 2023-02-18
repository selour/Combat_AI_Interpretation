#include "stdafx.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Engine
{
	OrthographicCamera::OrthographicCamera(float aspectRatio, float zoomLevel)
		:m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_ProjectionMatrix(glm::ortho(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top, -1.0f, 1.0f)), m_VeiwMatrix(glm::mat4(1.0f))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_VeiwMatrix;
	}

	void OrthographicCamera::SetProjection(float aspectRatio, float zoomLevel)
	{
		m_AspectRatio = aspectRatio;
		m_ZoomLevel = zoomLevel;
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_ProjectionMatrix = glm::ortho(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top, -1.0f, 1.0f);
		
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_VeiwMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_VeiwMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_VeiwMatrix;
	
	}

}