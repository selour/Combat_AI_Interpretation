#pragma once
#include <glm/glm.hpp>
class Transform
{
public:
	Transform()
	{
		Reset();
	}
	
	glm::vec3 GetPostion() const
	{
		return m_Postion;
	}
	glm::vec3 GetRotation() const
	{
		return m_Rotation;
	}
	glm::vec3 GetScale() const
	{
		return m_Scale;
	}

	void SetPostion(const glm::vec3& postion)
	{
		m_TransformFlag = true;
		m_Postion = postion;
	}
	void SetRotation(const glm::vec3& rotation)
	{
		m_TransformFlag = true;
		m_Rotation = rotation;
	}
	void SetScale(const glm::vec3& scale)
	{
		m_TransformFlag = true;
		m_Scale = scale;
	}
	
	void SetTransformFlag()
	{
		m_TransformFlag = true;
	}
	void Reset();


	glm::mat4 GetMatrix() const
	{
		return m_TransformMatrix;
	}
	

private:
	glm::vec3 m_Postion;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	bool m_TransformFlag;
	glm::mat4 m_TransformMatrix;

	void UpdateMatrix();
};

