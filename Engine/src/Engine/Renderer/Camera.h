#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "RendererCommand.h"
namespace Engine
{

	struct ClippingPlanes
	{
		float Near, Far;//裁剪空间
		ClippingPlanes(float nearPlane, float farPlane)
			:Near(nearPlane), Far(farPlane)
		{}
	};

	struct ViewportRect
	{
		unsigned int X, Y, Width, Height;
		ViewportRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
			:X(x), Y(y), Width(width), Height(height)
		{}
	};
	class VeiwMatrix
	{
		friend class Camera;
	public:
		VeiwMatrix()
			:m_Position(glm::vec3(0, 0, 3)), m_CameraDirection(glm::vec3(0, 0, -1)), m_RotationAngle(0)
		{}

		const glm::mat4& GetVeiwMatrix()
		{
			if (m_UpdateFlag)
				UpdateMatrix();
			return m_VeiwMatrix;
		}
	protected:
		bool m_UpdateFlag = true;
		glm::vec3 m_Position;
		glm::vec3 m_CameraDirection;
		float m_RotationAngle;
	private:
		void UpdateMatrix()
		{
			m_UpdateFlag = false;
			glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_CameraDirection));
			glm::vec4 up = glm::vec4(glm::cross(m_CameraDirection, cameraRight), 1.0);
			up = (glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationAngle), m_CameraDirection) * up);
			glm::vec3 cameraUp = glm::vec3(up.x, up.y, up.z);

			m_VeiwMatrix = glm::lookAt(m_Position, m_Position + m_CameraDirection, cameraUp);
		}

		glm::mat4 m_VeiwMatrix;
	};


	class ProjectionMatrix
	{
		friend class Camera;
	public:
		ProjectionMatrix()
			:m_PerspectiveFlag(true), m_AspectRatio(1280.0f / 720.0f), m_FieldOfView(45.0f), m_ClippingPlanes(0.0f, 100.0f)
		{}


		const glm::mat4& GetProjectionMatrix()
		{
			if (m_UpdateFlag)
				UpdateMatrix();
			return m_PerspectiveMatrix;
		}
	protected:
		bool m_PerspectiveFlag;
		float m_AspectRatio;//横纵比
		float m_FieldOfView;//透视模式下为视野角度，正交模式下为缩放等级
		ClippingPlanes m_ClippingPlanes;//裁剪空间
		bool m_UpdateFlag = true;
	private:
		void UpdateMatrix()
		{
			m_UpdateFlag = false;
			if (m_PerspectiveFlag)
			{
				m_PerspectiveMatrix = glm::perspective(glm::radians(m_FieldOfView), m_AspectRatio, m_ClippingPlanes.Near, m_ClippingPlanes.Far);
			}
			else
			{
				m_PerspectiveMatrix = glm::ortho(-m_AspectRatio * m_FieldOfView, m_AspectRatio * m_FieldOfView,
					-m_FieldOfView, m_FieldOfView, m_ClippingPlanes.Near, m_ClippingPlanes.Far);
			}

		}

		glm::mat4 m_PerspectiveMatrix;

	};


	class Camera
	{
	public:
		Camera()
			:m_ClearFlag(true), m_ViewportRect(0, 0, 1280, 720), m_ClearColor(glm::vec4(0.0f))
		{}

		void SetClearFlag(bool flag)
		{
			m_ClearFlag = flag;
		}
		bool GetClearFlag() const
		{
			return m_ClearFlag;
		}


		void SetViewportRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			m_ViewportRect.X = x;
			m_ViewportRect.Y = y;
			m_ViewportRect.Width = width;
			m_ViewportRect.Height = height;
		}
		const ViewportRect& GetViewportRect()
		{
			return m_ViewportRect;
		}
		void SetClearColor(glm::vec4 color)
		{
			m_ClearColor = color;
		}
		const glm::vec4& GetClearColor()
		{
			return m_ClearColor;
		}


		//VeiwMatrix设置函数
		void SetPosition(const glm::vec3& position)
		{
			m_UpdateFlag = true;
			m_VeiwMatrix.m_UpdateFlag = true;
			m_VeiwMatrix.m_Position = position;
		}
		const glm::vec3& GetPosition()
		{
			return m_VeiwMatrix.m_Position;
		}

		void SetDirection(const glm::vec3& direction)
		{
			m_UpdateFlag = true;
			m_VeiwMatrix.m_UpdateFlag = true;
			m_VeiwMatrix.m_CameraDirection = direction;
		}
		const glm::vec3& GetDirection()
		{
			return m_VeiwMatrix.m_CameraDirection;
		}

		void SetRotation(float angle)
		{
			m_UpdateFlag = true;
			m_VeiwMatrix.m_UpdateFlag = true;
			m_VeiwMatrix.m_RotationAngle = angle;
		}
		float GetRotation() const
		{
			return m_VeiwMatrix.m_RotationAngle;
		}

		//ProjectionMatrix设置函数

		void SetPerspectiveFlag(bool flag)
		{
			m_UpdateFlag = true;
			m_ProjectionMatrix.m_UpdateFlag = true;
			m_ProjectionMatrix.m_PerspectiveFlag = flag;
		}
		bool GetPerspectiveFlag() const
		{
			return m_ProjectionMatrix.m_PerspectiveFlag;
		}

		void SetAspectRatio(float aspectRatio)
		{
			m_UpdateFlag = true;
			m_ProjectionMatrix.m_UpdateFlag = true;
			m_ProjectionMatrix.m_AspectRatio = aspectRatio;
		}
		float GetAspectRatio() const
		{
			return m_ProjectionMatrix.m_AspectRatio;
		}

		void SetFieldOfView(float fieldOfView)
		{
			m_UpdateFlag = true;
			m_ProjectionMatrix.m_UpdateFlag = true;
			m_ProjectionMatrix.m_FieldOfView = fieldOfView;
		}
		float GetFieldOfView() const
		{
			return m_ProjectionMatrix.m_FieldOfView;
		}

		void SetClippingPlanes(float nearPlane, float farPlane)
		{
			m_UpdateFlag = true;
			m_ProjectionMatrix.m_UpdateFlag = true;
			m_ProjectionMatrix.m_ClippingPlanes.Near = nearPlane;
			m_ProjectionMatrix.m_ClippingPlanes.Far = farPlane;
		}
		const ClippingPlanes& GetClippingPlanes() const
		{
			return m_ProjectionMatrix.m_ClippingPlanes;
		}


		void ViewportActivated() const
		{
			RendererCommand::SetViewport(m_ViewportRect.X, m_ViewportRect.Y, m_ViewportRect.Width, m_ViewportRect.Height);
			//RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			//if (m_ClearFlag)
				//RendererCommand::Clear();
		}

		const glm::mat4& GetViewProjectionMatrix()
		{
			if (m_UpdateFlag)
				UpdateMatrix();
			return m_ViewProjectionMatrix;
		}
	private:
		//Viewport
		bool m_ClearFlag;
		ViewportRect m_ViewportRect;
		glm::vec4 m_ClearColor;

		//View
		VeiwMatrix m_VeiwMatrix;
		//perspective
		ProjectionMatrix m_ProjectionMatrix;
		void UpdateMatrix()
		{
			m_UpdateFlag = false;
			m_ViewProjectionMatrix = m_ProjectionMatrix.GetProjectionMatrix() * m_VeiwMatrix.GetVeiwMatrix();
		}
		bool m_UpdateFlag = true;
		glm::mat4 m_ViewProjectionMatrix;

	};
	class CameraLibrary
	{
	public:
		std::shared_ptr<Camera> AddOrthographicCamera(const std::string& name)
		{
			ENGINE_CORE_ASSERT(!IsExists(name), "Camera already exists!");
			auto camera = std::make_shared<Camera>();
			camera->SetPerspectiveFlag(false);
			camera->SetFieldOfView(5.0f);
			m_Cameras[name] = camera;
			return camera;
		}
		std::shared_ptr<Camera> AddPerspectiveCamera(const std::string& name)
		{
			ENGINE_CORE_ASSERT(!IsExists(name), "Camera already exists!");
			auto camera = std::make_shared<Camera>();
			m_Cameras[name] = camera;
			return camera;
		}
		std::shared_ptr<Camera> Get(const std::string& name)
		{
			ENGINE_CORE_ASSERT(IsExists(name), "Camera not found!");
			return m_Cameras[name];
		}
		bool IsExists(const std::string& name) const
		{
			return m_Cameras.find(name) != m_Cameras.end() && !m_Cameras.empty();
		}
	private:
		std::unordered_map<std::string, std::shared_ptr<Camera>> m_Cameras;
	};
}