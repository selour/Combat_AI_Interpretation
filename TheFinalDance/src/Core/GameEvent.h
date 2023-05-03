#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include "Engine.h"

template<typename Prototype> class GameEvent;
template<typename ReturnType, typename...Args>
class GameEvent<ReturnType(Args...)>
{
public:
	inline void operator +=(const std::function<ReturnType(Args...)>& func)
	{
		AddDelegate(func);
	}
	virtual void AddDelegate(const std::function<ReturnType(Args...)>& func)
	{
		std::shared_ptr<Delegate> pDelegate = std::make_shared<Delegate>(func);
		ENGINE_ASSERT(pDelegate != nullptr, "Function is nullptr!");
		m_Delegates.push_back(std::move(pDelegate));
	}
	inline void operator ()(Args ...args)
	{
		Trigger(args...);
	}
	void Trigger(Args ...args)
	{
		for (int i = 0; i < m_Delegates.size(); ++i)
		{
			m_Delegates[i]->Invoke(args...);
		}
	}

private:
	class Delegate
	{
	public:
		Delegate(const std::function<ReturnType(Args...)>& func)
		{
			m_Handler = func;
		}
		void Invoke(Args ...args)
		{
			m_Handler(args...);
		}
	private:
		std::function<ReturnType(Args...)> m_Handler;
	};
	std::vector<std::shared_ptr<Delegate>> m_Delegates;
};
