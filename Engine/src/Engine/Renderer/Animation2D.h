#pragma once
#include "Engine/Core/TimeStep.h"

namespace Engine
{
	struct Animation2DFrame
	{
		float TexCoordZ;
		float Playtime;
		Animation2DFrame(float texCoordZ, float playtime)
			:TexCoordZ(texCoordZ),Playtime(playtime)
		{}
	};
	class Animation2D
	{
	public:
		Animation2D(unsigned int indexMax, bool loop);
		~Animation2D() {};


		void OnUpdate(TimeStep ts);


		void AutoGenerateFrames(float offset, float playtime);
		void PushBackFrame(float texCoordZs, float playtime);
		void Play();
		const float GetTexCoordZs() const { return m_Aniamtion[m_Index].TexCoordZ; }

		void SetLoop(bool loop) { m_Loop = loop; }
		void Reset();

	private:
		bool m_Loop;
		bool m_Play;
		float m_Time;
		unsigned int m_Index;
		unsigned int m_IndexMax;
		
		std::vector<Animation2DFrame> m_Aniamtion;
	};

}

