#include "EventQueue.h"

EventQueue::EventQueue(ObjectManager* objects)
	:m_Objects(objects)
{
	
}

void EventQueue::OnUpdate()
{
	while(!m_EventQueue.empty())
	{
		ObjectEvent event = m_EventQueue.top();
		m_EventQueue.pop();
		switch (event.Type)
		{
		case Awake:
			m_Objects->Get(event.ObjectName)->Awake();
			break;
		case Trigger:
			m_Objects->Get(event.ObjectName)->Trigger();
			break;
		case Enable:
			m_Objects->Get(event.ObjectName)->Enable();
			break;
		case DisEnable:
			m_Objects->Get(event.ObjectName)->DisEnable();
			break;
		case Change:
			m_Objects->Get(event.ObjectName)->Change();
			break;
		case Reset:
			m_Objects->Get(event.ObjectName)->Reset();
			break;
		case Destroy:
			m_Objects->Get(event.ObjectName)->Destroy();
			break;
		case BeatCounterReset:
			m_Objects->GetBeatCounter()->Reset(atoi(event.ObjectName.c_str()));
		}
	}
		
}

void EventQueue::Emit(ObjectEvent event)
{
	m_EventQueue.push(event);
}

void EventQueue::Emit(std::string objectName, EventType type)
{
	m_EventQueue.push(ObjectEvent(objectName, type));
}
