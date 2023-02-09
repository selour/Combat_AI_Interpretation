#pragma once
#include "Engine/Core/TimeStep.h"

namespace Engine
{
	class Animation2D
	{
	public:
		Animation2D(unsigned int indexMax, bool loop);
		~Animation2D() {};


		void OnUpdate(TimeStep ts);


		void AutoGenerateFrames(float offset, float playtime);
		void pushBackFrame(float texCoordZs, float playtime);

		const float GetTexCoordZs() const { return m_TexCoordZs[m_index]; }

		void SetLoop(bool loop) { m_Loop = loop; }
		void Reset();

	private:
		bool m_Loop;
		bool m_Play;
		float m_Time;
		unsigned int m_index;
		unsigned int m_indexMax;
		std::vector<float> m_TexCoordZs;
		std::vector<float> m_Playtime;

	};

}

