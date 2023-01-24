#pragma once
#include "Engine/Core.h"
#include <functional>
#include <sstream>
namespace Engine
{

	//事件系统
	//用于处理应用程序和窗口事件的交互

	//用于描述事件的类型
	enum class EventType
	{ 
		None = 0,
		//窗口事件
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, 
		//循环事件
		AppTick, AppUpdate, AppRender,
		//按键事件
		KeyPressed, KeyReleased, KeyTyped,
		//鼠标事件
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	//事件过滤
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)

	};

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	
	
	//事件基类
	class Event
	{
	public:


		//事件是否已被处理
		bool m_Handled = false;

		//获取事件类型
		virtual EventType GetEventType() const = 0;
		//获取过滤标识
		virtual int GetCategoryFlags() const = 0;
		//获取事件名称
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
		//判断该事件是否被过滤
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		
	};
	//事件调度器
	
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function <bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{}
		//调度
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}


	private:
		Event& m_Event;

	};
	










}