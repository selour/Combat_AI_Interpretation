#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Engine/Core/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine
{

	class GLFWWindow: public Window
	{
	public:
		GLFWWindow(const WindowProps& props);
		virtual ~GLFWWindow();
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }


		//窗口属性设置
		void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; };

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		GraphicsContext* m_Context;
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			//回调函数
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};


}


