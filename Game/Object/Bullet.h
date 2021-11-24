#pragma once
#include <utility>
#include "../common/Vector3.h"

using HitNormal = std::pair<bool, Float3>;

class Bullet
{
public:
	// 反射するまでの時間
	static constexpr float REF_INTERVAL = 0.0f;
	// 反射した瞬間のベクトルの係数
	static constexpr float REF_POW = 3.0f;
	Bullet(Float3 pos,Float3 vec,int stage,int player);
	~Bullet();

	void Init(void);
	void Update(float delta);
	void Draw(void);

	// Hitしたらtrueと法線ベクトルを返す Hitしなかったらfalseと{0,0,0}が返る
	HitNormal HitCheckStage(Float3& end);
	bool isDead(void) { return dead_;};
	Float3 GetPos(void) { return pos_; };
private:
	Float3 pos_;
	// 進んでいる量
	Float3 vec_;
	// 向いてる向き
	Float3 angle_;
	// 弾の大きさ
	float size_;
	// 毎フレーム反射してベクトルがバグらないように間隔をあける
	float time_;

	// モデルのハンドル情報
	int stagemodel_;
	int playermodel_;
	// trueになれば弾が消える
	bool dead_;
	int count;
};

