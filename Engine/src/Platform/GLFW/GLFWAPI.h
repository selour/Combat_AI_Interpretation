#pragma once
#include "Engine/Core/PlatformAPI.h"
namespace Engine
{
	class GLFW_API : public PlatformAPI
	{
	public:
		virtual float GetTime() override;
	};

}

