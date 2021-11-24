#pragma once
#include "../common/Vector3.h"
class Gravity
{
public:
	Gravity(Float3& pos, bool& jump,bool& fall,double& time,int stagemodel);
	void Init(void);

	void Update(float delta);
	bool CheckStage(Float3& vec,Float3& pos);
private:
	Float3& pos_;

	// 重力
	float gravity_;
	// ジャンプ判定
	bool& jump_;
	// 落ちてる判定
	bool& fall_;

	// 重力を適用するかどうか
	bool gravitybool_;
	// 現在のジャンプ力
	float jumppow_;
	// 最初の加速度
	float v1;
	// ジャンプしてどのくらいの時間たったか
	double& time_;

	// 当たり判定用ステージモデル
	int stagemodel_;
};

