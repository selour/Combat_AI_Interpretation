#pragma once
#include "Object.h"
#include <stack>
enum EventType
{
	Awake = 0, Trigger = 1, Enable = 2, DisEnable = 3, Change = 4, Reset = 5, Destroy = 6,
	BeatCounterReset = 7
};
struct ObjectEvent
{
	std::string ObjectName;
	EventType Type;
	ObjectEvent(std::string objectName, EventType type)
		:ObjectName(objectName), Type(type)
	{}
};
class EventQueue
{
public:
	EventQueue(ObjectManager* objects);
	void OnUpdate();
	void Emit(ObjectEvent event);
	void Emit(std::string objectName, EventType type);
	
private:
	std::stack<ObjectEvent> m_EventQueue;
	ObjectManager* m_Objects;
};

