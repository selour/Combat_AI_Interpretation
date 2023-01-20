#pragma once
#include "Event.h"
namespace Engine
{

	//窗口关闭事件
	class ENGINE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent:";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	//窗口尺寸改变事件
	class ENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height)
		{}
		inline unsigned int GetWidth() const
		{
			return m_Width;
		}
		inline unsigned int GetHeight() const
		{
			return m_Height;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent:" << m_Width << "," << m_Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		//重设的窗口尺寸
		unsigned int m_Width, m_Height;
	};


	//窗口获得焦点事件
	class ENGINE_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent()
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent:";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//窗口失去焦点事件
		class ENGINE_API WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent()
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent:";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	
	//窗口移动事件
	class ENGINE_API WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(float x, float y)
			: m_WindowX(x), m_WindowY(y) {}

		inline float GetX() const
		{
			return m_WindowX;
		}

		inline float GetY() const
		{
			return m_WindowY;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent:" << m_WindowX << ", " << m_WindowY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		//移动的距离
		float m_WindowX, m_WindowY;

	};

	//AppTick事件
	class ENGINE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent()
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "AppTickEvent:";
			return ss.str();
		}
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	//App更新事件
	class ENGINE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent()
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "AppUpdateEvent:";
			return ss.str();
		}
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	//App渲染事件
	class ENGINE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent()
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "AppRenderEvent:";
			return ss.str();
		}
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}