#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "PuzzleData.h"
#include "Timer.h"
#include "Counter.h"

// 管理游戏的状态，使用单例模式
class StateManager {
public:
	static StateManager& getInstance() {
		static StateManager instance;
		return instance;
	}
	PuzzleData puzzleData;
	Timer timer;
	Counter counter;
private:
	StateManager(){}
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;
};

#endif // !STATE_MANAGER_H
