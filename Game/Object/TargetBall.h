#pragma once
#include <vector>
#include <string>
#include "../common/Vector3.h"

class TargetBall
{
public:
	TargetBall(Float3 pos,std::vector<Float3>* ballbox,int bornNo);
	~TargetBall();

	void Init(void);
	void Update(std::vector<Float3> posvec);
	void Draw(void);

	bool isDead(void) { return dead_; };

	bool HitCheck(Float3& bullet);
	Float3 GetPos(void);
private:
	int model_;
	int effectResourceHandle;
	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle;
	Float3 pos_;
	Float3 rot_;
	// 弾の大きさ
	float size_;

	// trueになれば弾が消える
	bool dead_;
	bool deadanim_;
	std::vector<Float3>* ballbox_;
	int bornNo_;

};

