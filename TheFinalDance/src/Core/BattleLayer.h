#pragma once
#include "Engine.h"
#include "Audio/SoundEngine.h"
#include "Delay.h"
#include "ResourceManager.h"
#include "EventQueue.h"
#include <memory>

class BattleLayer :public Engine::Layer
{
public:
	BattleLayer(const std::string& name)
		:Layer(name)
	{}
};



//---------------------------------------------------------------------------
//*																			*
//*								教程战斗 节拍器								*
//*																			*
//---------------------------------------------------------------------------
// 
//----------------------------------地砖------------------------------------------
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
//---------------------

//-----------------------------------舞台---------------------------------------
class BattleStage : public GameObject
{
public:
	BattleStage()
	{
		m_Stage.resize(7 * 7);
	}

	virtual void Init() override;

	virtual void Awake() override;

	virtual void Reset() override;

	virtual void Update(float ts) override;
	//渲染
	virtual void Render()override;

	//清空舞台
	void ClearStep();

	


	std::vector<Block>* GetStage()
	{
		return &m_Stage;
	}
	
	void SetCamera(Engine::OrthographicCamera* camera)
	{
		m_Camera = camera;
	}
private:
	std::vector<Block> m_Stage;
	Engine::OrthographicCamera* m_Camera;


	DelaySwitch m_AwakeFlag;
};
//--------------------------------Boss:<节拍器>---------------------------------------
class TutorialBoss : public GameObject
{
public:
	TutorialBoss()
	{
	}
	virtual void Init() override;
	virtual void Awake() override;
	virtual void Trigger() override;
	virtual void Change() override;
	virtual void Reset() override;
	//更新
	virtual void Update(float ts) override;
	virtual void OnBeat() override;
	//渲染
	virtual void Render()override;

	//被击中
	void OnHit(int step);
	
	void SetStage(const std::shared_ptr<BattleStage> stage)
	{
		m_Stage = stage;
	}

	Block* GetCurrent()
	{
		return m_Current;
	}
	void SetCamera(Engine::OrthographicCamera* camera)
	{
		m_Camera = camera;
	}
private:
	glm::vec2 m_Position;
	glm::vec4 m_Color = { 0.0f, 1.0f, 1.0f, 1.0f };

	bool m_FirstHit = false;

	Block* m_Current = nullptr;
	DelaySwitch m_BeatFlag;
	DelaySwitch m_HitFlag;

	int m_BeatCount = 0;
	DelaySwitch m_BeatTip;
	DelaySwitch m_BeatCheck;

	std::shared_ptr<BattleStage> m_Stage;

	Engine::ParticleProps m_Particle;

	Engine::OrthographicCamera* m_Camera;


};
//-------------------------------战斗玩家----------------------------------------------
class BattlePlayer : public GameObject
{
public:
	BattlePlayer()
	{
	}
	virtual void Init() override;

	virtual void Awake() override;

	virtual void Enable() override;
	virtual void DisEnable() override;

	virtual void Change() override;
	virtual void Reset() override;
	//更新
	virtual void OnBeat() override;
	virtual void Update(float ts) override;
	//渲染
	virtual void Render()override;

	void SetStage(std::shared_ptr<BattleStage> stage)
	{
		m_Stage = stage;
	}
	void SetBoss(std::shared_ptr<TutorialBoss> boss)
	{
		m_Boss = boss;
	}
	void SetCamera(Engine::OrthographicCamera* camera)
	{
		m_Camera = camera;
	}

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

	bool m_Enable = true;

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

	Engine::ParticleProps m_Particle;
	
	Engine::OrthographicCamera* m_Camera;

	DelaySwitch m_AwakeFlag;
	

};
//-----------------------------------背景的心脏-------------------------------------------
class Heart : public GameObject
{
public:
	Heart()
	{
		Engine::FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_FBO = Engine::FrameBuffer::Create(fbSpec);
	}
	virtual void Init() override;
	//出现
	virtual void Awake() override;

	virtual void Update(float ts) override;
	virtual void OnBeat() override;


	virtual void BufferRender() override;
	virtual void Render()override;

	void SetCamera(Engine::OrthographicCamera* camera)
	{
		m_Camera = camera;
	}

private:
	glm::vec2 m_Postion[5] = { 
		{0.045f, -0.571f},
		{ -0.711f, 0.044f },
		{ 0.4f, 0.22f },
		{ 0.177f, 0.7f },
		{ -0.356f, 0.747f } };
	float m_Size = 1.3f;

	DelaySwitch m_Beat;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;

	Engine::OrthographicCamera* m_Camera;
	
};
//----------------------------------后期特效处理------------------------------
class TutorialPost : public GameObject
{
public:
	TutorialPost()
	{
	}
	virtual void Init() override;
	//闪烁后进入故障特效
	virtual void Awake() override;
	virtual void Trigger() override;
	virtual void Update(float ts) override;
	virtual void OnBeat() override;
	virtual void Render()override;


	std::shared_ptr<Engine::FrameBuffer> GetFBO()
	{
		return m_FBO;
	}

private:
	float m_Time = 0.0f;
	int m_BeatCount = 0;
	DelaySwitch m_Noise, m_Rhythm;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;


};
//--------------------------舞台摄像机控制-------------------------
class TutorialCameraControl : public GameObject
{
public:
	virtual void Trigger() override;
	virtual void Update(float ts) override;

	void SetCamera(Engine::OrthographicCamera* camera)
	{
		m_Camera = camera;
	}
private:
	DelaySwitch m_Focus;
	DelaySwitch m_DelayIn;
	DelaySwitch m_DelayOut;

	const glm::vec2 m_Pos = { 0.0f, 0.0f };
	const float m_ZoomLevel = 5.0f;

	const glm::vec2 m_FocusPos = {0.0f, -2.0f};
	const float m_FocusZoomLevel = 2.0f;

	Engine::OrthographicCamera* m_Camera;
};
//--------------------------开场-------------------------
class TutorialStartUp : public GameObject
{
public:
	virtual void Awake() override;
	virtual void Update(float ts) override;
	virtual void Render() override;

	float* GetPosition(int index)
	{
		return &m_Position[index].x;
	}
	float* GetSize(int index)
	{
		return &m_Size[index];
	}
	void SetCamera(Engine::OrthographicCamera* camera)
	{
		m_Camera = camera;
	}
private:
	glm::vec2 m_Position[6] = {
		{-2.6f,-2.7f},
		{ 1.1f, 2.6f},
		{-2.6f, 0.2f},
		{-0.4f,-2.3f},
		{ 1.9f, 2.8f},
		{ 5.0f,-2.0f}
	};
	float m_Size[2] = {
		3.2f,6.0f
	};
	float m_Alpha[2] = {
		1.0f,0.3f
	};
	glm::vec2 m_StartPosition[4] =
	{
		{-8.0f, 0},
		{-4.0f, 0},
		{ 4.0f, 0},
		{ 8.0f, 0}
	};
	int m_State = 0;
	DelaySwitch m_Delay;
	DelaySwitch m_Time;
	Engine::OrthographicCamera* m_Camera;
};
//-------------------------音乐和判定圈控制--------------------------------------------
class TutorialMusic : public GameObject
{
public:
	virtual void Change() override;
	virtual void Update(float ts) override;
	virtual void OnBeat() override;
private:
	int m_BeatCount = 0;
	int m_State = 0;
	DelaySwitch m_Delay;
};
//-------------------------资源管理器--------------------------------------------
class TutorialResourceManager : public ResourceManager
{
public:
	virtual void Init() override;
};
//-------------------------关卡主程序--------------------------------------------
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

	int m_FPS = 0;

	glm::vec2 m_Position = glm::vec2(0.0f);
	float m_ZoomLevel = 5.0f;

	std::shared_ptr<TutorialStartUp> m_StartUp;

	BeatCounter m_BeatCounter;
	ObjectManager m_Objects;
	EventQueue m_EventQueue;

	Engine::ParticleSystem m_ParticleSystem;
	TutorialResourceManager m_ResourceManager;
	
	Engine::OrthographicCamera m_Camera;
	Engine::OrthographicCamera m_UICamera;
	
};
