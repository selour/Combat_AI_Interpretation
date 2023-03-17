#include "EventQueue.h"

std::string EventTypeToString(EventType type)
{
	switch (type)
	{
	case Awake:
		return "Awake";
	case Trigger:
		return "Trigger";
	case Enable:
		return "Enable";
	case DisEnable:
		return "DisEnable";
	case Change:
		return "Change";
	case Reset:
		return "Reset";
	case Destroy:
		return "Destroy";
	case BeatCounterReset:
		return "BeatCounterReset";
	}
}

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
		ENGINE_TRACE("Event Handle:" + EventTypeToString(event.Type) + "," + event.ObjectName);
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
			break;
		}
	}
		
}

void EventQueue::Emit(ObjectEvent event)
{
	ENGINE_TRACE("Event Emit:"+EventTypeToString(event.Type) + "," + event.ObjectName);
	m_EventQueue.push(event);
}

void EventQueue::Emit(std::string objectName, EventType type)
{
	ENGINE_TRACE("Event Emit:" + EventTypeToString(type) + "," + objectName);
	m_EventQueue.push(ObjectEvent(objectName, type));
}
