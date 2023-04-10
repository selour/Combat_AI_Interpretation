#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>
void Transform::Reset()
{
	m_Postion = { 0,0,0 };
	m_Rotation = { 0,0,0 };
	m_Scale = { 0,0,0 };
	m_TransformFlag = true;
}



void Transform::UpdateMatrix()
{
	if (m_TransformFlag)
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Postion);
		glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotation = rotateZ * rotateY * rotateX;
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
		m_TransformMatrix = translation * rotation * scale;
	}
}
