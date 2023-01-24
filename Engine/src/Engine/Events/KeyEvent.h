#pragma once
#include "Event.h"
namespace Engine
{

	//按键事件基类
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const
		{
			return m_KeyCode;
		}
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode) 
		{}
		//对应的键位
		int m_KeyCode;

	};
	//按键按下事件
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount) 
		{}
		inline int GetRepeatCount() const
		{
			return m_RepeatCount;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	private:
		//事件重复的次数
		int m_RepeatCount;
	};
	//按键松开事件
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int repeatCount)
			:KeyEvent(keycode)
		{}
	
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	
	};
	//按键输入事件
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int codepoint)
			: KeyEvent(codepoint)
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:" << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};


}
