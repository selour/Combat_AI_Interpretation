#pragma once

// 给游戏提供引擎的API

//---------核心层------------------------
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Core/Layer.h"
#include "Engine/Core/Random.h"
#include "Engine/ImGui/ImGuiLayer.h"
//--------------------------------------


//----------渲染层-----------------------
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RendererPostProcessing.h"
#include "Engine/Renderer/Animation2D.h"
#include "Engine/Renderer/RendererCommand.h"
#include "Engine/Renderer/ParticleSystem.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/FrameBuffer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Camera.h"
//--------------------------------------

 