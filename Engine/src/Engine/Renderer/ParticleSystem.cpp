#include "stdafx.h"
#include "ParticleSystem.h"
#include "Engine/Core/Random.h"
#include "Engine/Renderer/Renderer2D.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/compatibility.hpp"
namespace Engine
{
	std::mt19937 Random::s_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;

	ParticleSystem::ParticleSystem(int value)
	{
		m_ParticlePool.resize(value);
	}

	void ParticleSystem::OnUpdate(TimeStep ts)
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;
			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}
			particle.LifeRemaining -= ts;
			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.01f * ts;

		}

		
	}

	void ParticleSystem::OnRender(OrthographicCamera& camera, const std::shared_ptr<Texture2DArray> teture)
	{
		Renderer2D::BeginScene(camera, teture);
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;
			
			float life = particle.LifeRemaining / particle.LifeTime;
			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

	
			Renderer2D::DrawQuad(particle.Position,{ size, size }, particle.Rotation, color);
		
		}
		Renderer2D::EndScene();

	}

	void ParticleSystem::Emit(const ParticleProps& particleProps)
	{
		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.Position.x = particleProps.Position.x;
		particle.Position.y = particleProps.Position.y;
		particle.Position.z = particleProps.Position.z;
		particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

		particle.Velocity = particleProps.Velocity;
		particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
		particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);
		particle.Velocity.z += particleProps.VelocityVariation.z * (Random::Float() - 0.5f);

		particle.ColorBegin = particleProps.ColorBegin;
		particle.ColorEnd = particleProps.ColorEnd;

		particle.LifeTime = particleProps.LifeTime;
		particle.LifeRemaining = particleProps.LifeTime;
		particle.SizeBegin = particleProps.SizeBegin;
		particle.SizeEnd = particleProps.SizeEnd;

		m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
	}

}
