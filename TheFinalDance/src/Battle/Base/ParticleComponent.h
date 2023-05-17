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
	//�����ʼ������
	virtual void Init() override
	{}

	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) override
	{
		m_ParticleSystem.OnUpdate(ts);
	}

	//������Ⱦ����
	//ʵ�������Ⱦ
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override
	{
		m_ParticleSystem.OnRender(camera);
	}
	//����UI��Ⱦ
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