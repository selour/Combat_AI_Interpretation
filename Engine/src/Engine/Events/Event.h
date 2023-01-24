#pragma once
#include "Engine/Core.h"
#include <functional>
#include <sstream>
namespace Engine
{

	//�¼�ϵͳ
	//���ڴ���Ӧ�ó���ʹ����¼��Ľ���

	//���������¼�������
	enum class EventType
	{ 
		None = 0,
		//�����¼�
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, 
		//ѭ���¼�
		AppTick, AppUpdate, AppRender,
		//�����¼�
		KeyPressed, KeyReleased, KeyTyped,
		//����¼�
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	//�¼�����
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
	
	
	//�¼�����
	class Event
	{
	public:


		//�¼��Ƿ��ѱ�����
		bool m_Handled = false;

		//��ȡ�¼�����
		virtual EventType GetEventType() const = 0;
		//��ȡ���˱�ʶ
		virtual int GetCategoryFlags() const = 0;
		//��ȡ�¼�����
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
		//�жϸ��¼��Ƿ񱻹���
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		
	};
	//�¼�������
	
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function <bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{}
		//����
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