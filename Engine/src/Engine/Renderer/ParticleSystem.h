#pragma once
#include "Engine/Core/TimeStep.h"
#include "Texture.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
namespace Engine
{
	struct ParticleProps
	{
		glm::vec3 Position;
		glm::vec3 Velocity, VelocityVariation;
		glm::vec4 ColorBegin, ColorEnd;
		float SizeBegin, SizeEnd;
		float LifeTime = 1.0f;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem();

		void OnUpdate(TimeStep ts);

		void OnRender(OrthographicCamera& camera, const std::shared_ptr<Texture2DArray> teture = nullptr);

		void Emit(const ParticleProps& particleProps);

	private:
		struct Particle
		{
			glm::vec3 Position;
			glm::vec3 Velocity;
			glm::vec4 ColorBegin, ColorEnd;
			float Rotation = 0.0f;
			float SizeBegin, SizeEnd;

			float LifeTime = 1.0f;
			float LifeRemaining = 0.0f;

			bool Active = false;
		};
		std::vector<Particle> m_ParticlePool;
		unsigned int m_PoolIndex = 0;

		unsigned int m_QuadVAO = 0;
	};
}

