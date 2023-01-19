#pragma once
#include "Event.h"
namespace Engine
{

	//�����¼�����
	class ENGINE_API KeyEvent : public Event
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
		//��Ӧ�ļ�λ
		int m_KeyCode;

	};
	//���������¼�
	class ENGINE_API KeyPressedEvent : public KeyEvent
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
		//�¼��ظ��Ĵ���
		int m_RepeatCount;
	};
	//�����ɿ��¼�
	class ENGINE_API KeyReleasedEvent : public KeyEvent
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


}