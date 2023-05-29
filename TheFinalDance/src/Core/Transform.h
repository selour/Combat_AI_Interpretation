#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <unordered_map>

class Transform
{
public:
	Transform()
		:m_TransformFlag(true),m_Father(nullptr)
	{
	}
	const glm::vec3& GetPostion() const
	{
		return m_Position;
	}
	const glm::vec4& GetRotate() const
	{
		return m_Rotation;
	}
	const glm::vec3& GetScale() const
	{
		return m_Scale;
	}
	
	glm::mat4 GetMatrix()
	{
		UpdateMatrix();
		return m_TransformMatrix;
	}
	void SetPostion(const glm::vec3& position)
	{
	
		SetTransformFlag();
		m_Position = position;
		
	}
	//轴角法,前三位为旋转轴，后一位为角度
	void SetRotation(const glm::vec4& rotation)
	{
		
		SetTransformFlag();
		m_Rotation = rotation;

	}

	void SetScale(const glm::vec3& scale)
	{
		SetTransformFlag();
		m_Scale = scale;
	}

	void SetTransformFlag()
	{
		if (!m_TransformFlag)
		{
			SetChildrenFlag();
			m_TransformFlag = true;
		}
		
	}
	void SetFather(Transform* father)
	{
		father->AddChild(this);
		if (m_Father)
		{
			m_Father->DeleteChild(this);
		}

		m_Father = father;
		SetTransformFlag();
	}

	bool HasFather() const
	{
		if (m_Father)
			return true;
		else
			return false;
	}
protected:	
	void AddChild(Transform* childern)
	{
		m_Children.push_back(childern);
	}


	void DeleteChild(Transform* childern)
	{
		for (auto itor = m_Children.begin(); itor != m_Children.end(); itor++)
		{
			if (*itor == childern)
			{
				m_Children.erase(itor);
				break;
			}
		}
	}
private:

	bool m_TransformFlag = true;

	glm::vec3 m_Position = { 0, 0, 0 };
	glm::vec4 m_Rotation = { 0, 0, 1, 0 };;//轴角法,前三位为旋转轴，后一位为角度
	glm::vec3 m_Scale = { 1.0,1.0,1.0 };

	glm::mat4 m_TransformMatrix;

	Transform* m_Father;
	std::vector<Transform*> m_Children;
	void UpdateMatrix()
	{
		if (m_TransformFlag)
		{
	
			m_TransformMatrix = glm::translate(glm::mat4(1.0f), m_Position);
			m_TransformMatrix = glm::rotate(m_TransformMatrix, m_Rotation.w, glm::vec3(m_Rotation));
			m_TransformMatrix = glm::scale(m_TransformMatrix, m_Scale);
			if (m_Father)
				m_TransformMatrix = m_Father->GetMatrix() * m_TransformMatrix ;
			m_TransformFlag = false;
		}
	}
	void SetChildrenFlag()
	{
		if (!m_Children.empty())
		{
			for (int i = 0; i < m_Children.size(); i++)
			{
				m_Children[i]->SetTransformFlag();
			}
		}
	}
	
};

