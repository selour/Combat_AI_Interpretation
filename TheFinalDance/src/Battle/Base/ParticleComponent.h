#pragma once
#include "Core/ObjectManager.h"
#include "Engine/Renderer/ParticleSystem.h"
class ParticleCompomemt : public GameObject
{
public:
	ParticleCompomemt()
		:m_ParticleSystem(500)
	{
		m_Particle.SizeBegin = 0.2f;
		m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 0.5f;
		m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Particle.VelocityVariation = glm::vec3(5.0f, 5.0f, 0.0f);
	}
	//对象初始化函数
	virtual void Init() override
	{}

	//更新函数
	//基于时间的更新
	virtual void Update(float ts) override
	{
		m_ParticleSystem.OnUpdate(ts);
	}

	//对象渲染函数
	//实际输出渲染
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override
	{
		m_ParticleSystem.OnRender(camera);
	}
	//调试UI渲染
	virtual void OnImGuiRender() override
	{

	}
	void EmitParticle(unsigned int number, glm::vec3 Position, glm::vec3 Color)
	{
		m_Particle.ColorBegin = glm::vec4(Color,1.0f);
		m_Particle.ColorEnd = glm::vec4(Color, 0.0f);
		m_Particle.Position = Position;
		for (int i = 0; i < number; i++)
			m_ParticleSystem.Emit(m_Particle);
	}
protected:
	Engine::ParticleProps m_Particle;
	Engine::ParticleSystem m_ParticleSystem;
};