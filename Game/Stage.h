#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include <chrono>
#include "Object/Player.h"
#include "common/Vector3.h"
#include "Object/TargetBall.h"
#include "Time.h"

class Stage
{
public:
	Stage(std::string stagename, std::list<Float3> targetlist);
	//Stage(std::shared_ptr<Player> player);
	~Stage();
	void Init(std::string stagename,std::list<Float3> targetlist);
	bool Update(void);
	void TimeCreate();
	void Draw(void);
	void RealDraw(void);
	void Release(void);
	void AddTargetBall(Float3 pos);
	void DeleteCheckTargetBall(void);
	// ターゲットの現在数
	int GetTargetNum(void);
	// ターゲットの破壊した数
	int GetDestroyTargetCount(void);
	// 初期ターゲット数
	int GetTargetCount(void);
	// 経過時間の取得
	Time GetElapsedTime(void);
private:
	//Player* pl_;
	std::shared_ptr<Player> player_;

	// モデルのハンドルID
	int modelid_;
	// 
	Float3 pos_;

	std::vector<std::unique_ptr<TargetBall>> targetvector_;
	std::vector<Float3> targetball_;
	int targetcount_;
	int destroytargetcount_;

	// 経過時間
	std::chrono::system_clock::time_point  start_, end_;
	Time time_;
};

