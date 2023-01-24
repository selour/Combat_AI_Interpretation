#pragma once
#include "Engine/Core.h"
#include "Engine/Events/Event.h"
namespace Engine
{

	class Layer
	{
	public:	
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		//层生命周期函数
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		

	protected:
		std::string m_DebugName;
	};


}


