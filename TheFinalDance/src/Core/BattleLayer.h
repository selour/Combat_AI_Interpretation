#pragma once
#include "Engine.h"
#include "Audio/SoundEngine.h"
#include "Delay.h"
#include "ResourceManager.h"
#include "Object.h"
#include "BeatCounter.h"
#include <memory>

class BattleLayer :public Engine::Layer
{
public:
	BattleLayer(const std::string& name)
		:Layer(name)
	{}
};


struct Block
{
	glm::vec2 Position = { 0.0f, 0.0f };
	int Step = 0;
	bool Awake = false;
	bool Danger = false;
	bool Render = false;
	Block* Link[4] = { nullptr, nullptr, nullptr, nullptr };
};
//-------Link----------
//       [3]
//    [0]   [1]
//       [2]

class BattleStage : public Object
{
public:
	BattleStage(ResourceManager* resourceManager);
	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update(float ts) override;
	virtual void BufferRender() override;
	virtual void Render()override;
	virtual void Reset() override;
	virtual void Destroy() override;


	virtual void OnBeat() override;


	void ClearStep();

	std::vector<Block>* GetStage()
	{
		return &m_Stage;
	}
private:
	std::vector<Block> m_Stage;
	ResourceManager* m_ResourceManager;
	Engine::OrthographicCamera m_Camera;
};
class TutorialBoss : public Object
{
public:
	TutorialBoss(const std::shared_ptr<BattleStage> stage, Engine::ParticleSystem* particleSystem, ResourceManager* resourceManager);
	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update(float ts) override;
	virtual void BufferRender() override;
	virtual void Render()override;
	virtual void Reset() override;
	virtual void Destroy() override;


	virtual void OnBeat() override;

	void OnHit(int step);
	
	Block* GetCurrent()
	{
		return m_Current;
	}
private:
	glm::vec2 m_Position;
	glm::vec4 m_Color = { 0.0f, 1.0f, 1.0f, 1.0f };

	Block* m_Current = nullptr;
	DelaySwitch m_BeatFlag;
	DelaySwitch m_HitFlag;

	int m_BeatCount = 0;
	DelaySwitch m_BeatTip;
	DelaySwitch m_BeatCheck;

	std::shared_ptr<BattleStage> m_Stage;

	Engine::ParticleSystem* m_ParticleSystem;
	Engine::ParticleProps m_Particle;

	ResourceManager* m_ResourceManager;


	Engine::OrthographicCamera m_Camera;

};

class BattlePlayer : public Object
{
public:
	BattlePlayer(std::shared_ptr<BattleStage> stage, std::shared_ptr<TutorialBoss> boss, Engine::ParticleSystem* particleSystem, ResourceManager* resourceManager);

	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update(float ts) override;
	virtual void BufferRender() override;
	virtual void Render()override;
	virtual void Reset() override;
	virtual void Destroy() override;

	virtual void OnBeat() override;

	

	enum State
	{
		Free = 0, Move = 1, Beat = 2
	};

private:
	void InputCheck();
//-------Link----------
//       [3]
//    [0]   [1]
//       [2]
	void MoveTo(int forward);
	void MoveError(const glm::vec2 direction);
	float m_Time = 0.0f;
	State m_State;
	glm::vec2 m_Position;
	glm::vec4 m_Color = { 0.0f, 1.0f, 1.0f, 1.0f };
	int m_Step  = 0;


	DelaySwitch m_MoveFlag;
	DelaySwitch m_ErrorFlag;
	DelaySwitch m_BeatFlag;

	glm::vec2 m_ErrorDirection = { 0.0f, 0.0f };
	Block* m_Current = nullptr;
	Block* m_Next = nullptr;

	std::shared_ptr<BattleStage> m_Stage;
	std::shared_ptr<TutorialBoss> m_Boss;

	Engine::ParticleSystem* m_ParticleSystem;
	Engine::ParticleProps m_Particle;

	ResourceManager* m_ResourceManager;
	
	
	Engine::OrthographicCamera m_Camera;
	

};

class Heart : public Object
{
public:
	Heart(ResourceManager* resourceManager);
	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update(float ts) override;
	virtual void BufferRender() override;
	virtual void Render()override;
	virtual void Reset() override;
	virtual void Destroy() override;


	virtual void OnBeat() override;

	float* GetPos1()
	{
		return &m_Postion1.x;
	}
	float* GetPos2()
	{
		return &m_Postion2.x;
	}
	float* GetPos3()
	{
		return &m_Postion3.x;
	}
	float* GetPos4()
	{
		return &m_Postion4.x;
	}
	float* GetPos5()
	{
		return &m_Postion5.x;
	}
	float* GetSize()
	{
		return &m_Size;
	}

private:
	glm::vec2 m_Postion1 = { 0.045f, -0.571f };
	glm::vec2 m_Postion2 = { -0.711f, 0.044f };
	glm::vec2 m_Postion3 = { 0.4f, 0.22f };
	glm::vec2 m_Postion4 = { 0.177f, 0.7f };
	glm::vec2 m_Postion5 = { -0.356f, 0.747f };
	float m_Size = 1.3f;

	DelaySwitch m_Beat;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
	ResourceManager* m_ResourceManager;
	Engine::OrthographicCamera m_Camera;
	
};
class TutorialPost : public Object
{
public:
	TutorialPost(ResourceManager* resourceManager);
	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update(float ts) override;
	virtual void BufferRender() override;
	virtual void Render()override;
	virtual void Reset() override;
	virtual void Destroy() override;

	virtual void OnBeat() override;

	std::shared_ptr<Engine::FrameBuffer> GetFBO()
	{
		return m_FBO;
	}

private:
	float m_Time = 0.0f;
	int m_BeatCount = 0;
	DelaySwitch m_Noise, m_Rhythm;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
	ResourceManager* m_ResourceManager;

};

class TutorialResourceManager : public ResourceManager
{
public:
	virtual void Init() override;
};
class TutorialBattle : public BattleLayer
{
public:
	TutorialBattle();
	//层生命周期函数
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	int m_Bpm = 100;
	float m_Volume = 1.0f;
	int m_FPS;
	
	BeatCounter m_BeatCounter;
	//物体列表
	std::shared_ptr<BattlePlayer> m_Player;
	std::shared_ptr<TutorialBoss> m_Boss;
	std::shared_ptr<BattleStage> m_Stage;
	
	ObjectManager m_Objects;
	Engine::ParticleSystem m_ParticleSystem;
	TutorialResourceManager m_ResourceManager;
	
	Engine::OrthographicCamera m_Camera;
	
	
};
