#pragma once
#include <DxLib.h>
#include <memory>
#include <list>
#include <vector>
#include "../common/Vector3.h"
#include "Camera.h"
#include "Bullet.h"
#include "../AllControl/Control.h"
#include "Laserbeam.h"
#include "Gravity.h"

class Transform {
public:
	// 座標
	Float3 pos_;
	// 角度(rad)
	Float3 angles_;
};

// mv1の順番
enum class ANIM {
	Idle = 0,
	Jump = 1,
	Run = 2,

};

enum class JUMP {
	STAY,
	JUMP,
	FALL
};

class Player
{
public:
	Player();
	Player(int stagemodelid);
	~Player();
	// アニメーション速度
	static constexpr float SPEED_ANIM = 20.0f;
	// 徐々に回転する量
	static constexpr float SPEED_ROT = 5.0f;
	// 徐々に回転する量(RAD)
	static constexpr float SPEED_ROT_RAD = SPEED_ROT * (DX_PI_F / 180.0f);
	// 
	//static constexpr float FOWARD_VEC = 5.0f;
	// 横移動の時のチェックする量
	static constexpr float CHECK_POW = 20.0f;
	// 横移動する時に判定が地面に埋まらないように高さをつける
	static constexpr float CHECK_HEIGHT = 20.0f;
	// 弾の最大数
	static constexpr int FIRE_MAX = 30;

	// 弾を撃つ間隔(秒)
	static constexpr float FIRE_INTERVAL = 1.0f;
	void Init(void);
	void Update(void);
	// 移動処理
	void Move(CntData data);
	// 弾を撃つ、ADS処理
	void FireFunc(CntData& data, float deltatime, Float3& dxangle);
	// ジャンプ
	void Jump(CntData& data);
	void SetBeforeDraw(void);
	void Draw(void);

	Float3 GetPos(void);
	Float3 GetAngles(void);
	// X軸回転
	Float3 GetRotateX(Float3 pos);
	// Y軸回転
	Float3 GetRotateY(Float3 pos);
	// Z軸回転
	Float3 GetRotateZ(Float3 pos);

	// 当たり判定チェック(自分の動くベクトル)移動を含む
	bool HitCheck(Float3 vec);
	// 当たり判定チェック(判定のみ)
	bool Hit(Float3 vec);
	// 当たり判定処理(LINE)
	bool HitLine(Float3 vec);
	// 閾値の設定
	void AskThreshold(Float3 cangle, float rotRad);
	// 閾値を使って回転処理
	void Threshold(float diff, float aroundDir, float radMoveAngleY);

	void ChangeAnimation(ANIM anim);

	std::vector<Float3> GetBulletsPos(void);
private:
	// 弾のスピード係数
	static constexpr float BULLET_SPEED_POW = 20.0f;
	//float time_;
	// プレイヤーモデルのハンドルID
	int modelid_;
	// ステージモデルのハンドルID
	int stagemodelid_;
	// 座標と角度
	Transform trans_;
	Float3 eyeoffset_;
	//渡しまくるからshared
	std::shared_ptr<Camera> camera_;
	// 生成番号
	int playerid_;
	// 生成番号を決める
	static int id_;
	// アニメーションの総再生時間
	float timeTotalAnim_;

	// アニメーション用の更新ステップ
	float stepanim_;

	float anim_;
	// 今のアニメーション
	ANIM nowanim_;
	// キャラのアングル
	Float3 localangles_;
	// 移動時のスピード
	float movepow_;
	std::list<std::unique_ptr<Bullet>> bullets_;
	Float3 eyepos_;
	//コントローラー
	//std::unique_ptr<Control>controller_;

	double jumptime_;
	bool jumpflag_;
	bool fallflag_;
	
	// 撃った球数
	int firecount_;
	// 1発うった後にもう一度撃てるようになるまでの間隔
	float firetime_;
	// 予測線
	std::unique_ptr<Laserbeam> laser_;

	// ジャンプ
	std::unique_ptr<Gravity> gravity_;

	// カメラアングル保存
	Float3 cangles_;
	Float3 cfowardvec_;
	// デバッグ用
	VECTOR line_[2];
	VECTOR fallline_[2];
};