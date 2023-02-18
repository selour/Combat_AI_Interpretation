#pragma once
#include "PlatformAPI.h"
namespace Engine
{
	class PlatformCommand
	{
	public:
		inline static float GetTime()
		{
			return s_PlatformAPI->GetTime();
		}
	private:
		static PlatformAPI* Creat();
		static PlatformAPI* s_PlatformAPI;
	};
}


