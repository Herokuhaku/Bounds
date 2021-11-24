#include "TargetBall.h"
#include <EffekseerForDXLib.h>
#include "../AsoUtility.h"
#include "../Manager/SoundManager.h"
#include "../Manager/SceneManager.h"

TargetBall::TargetBall(Float3 pos, std::vector<Float3>* ballbox,int bornNo)
{
	pos_ = pos;
	bornNo_ = bornNo;
	ballbox_ = ballbox;
	Init();
}

TargetBall::~TargetBall()
{
	MV1DeleteModel(model_);
}

void TargetBall::Init(void)
{
	size_ = 50;
	model_ = MV1LoadModel("Model/target.mv1");	
	effectResourceHandle = LoadEffekseerEffect("tktk01/Blow4.efkefc",70.0f);
	MV1SetupCollInfo(model_);
	//effectResourceHandle = LoadEffekseerEffect("tktk01/Laser01.efkefc",70.0f);
	// 再生中のエフェクトのハンドルを初期化する。
	playingEffectHandle = -1;
	rot_ = Float3(AsoUtility::Deg2Rad(90.0f),0.0f,0.0f);
}

void TargetBall::Update(std::vector<Float3> posvec)
{
	for (auto& pos : posvec) {
		if (HitCheck(pos) && !deadanim_) {
			//dead_ = true;
			deadanim_ = true;
			// エフェクトを再生する。
			playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
			// 音を再生する
			lpSoundMng.CreatePosPlaySound("Bomb",pos_);
		}
	}
	if (deadanim_ && IsEffekseer3DEffectPlaying(playingEffectHandle) == -1){
		dead_ = true;
		
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos_.x,pos_.y, pos_.z);
	rot_.y = rot_.y + AsoUtility::Deg2Rad(1);
	MV1SetRotationXYZ(model_, rot_.toVECTOR());
	MV1SetPosition(model_, pos_.toVECTOR());
	//DrawEffekseer3D();
	//DrawEffekseer3D_Draw(playingEffectHandle);
	MV1RefreshCollInfo(model_);
}

void TargetBall::Draw(void)
{
	//SetUseLighting(true);
	//DrawSphere3D(pos_.toVECTOR(), size_, 5, 0xffff00, 0xffff00, true);
	if (!deadanim_) {
		MV1DrawModel(model_);
	}
	// Effekseerにより再生中のエフェクトを描画する。
	//DrawEffekseer3D();
	//SetUseLighting(false);
}

bool TargetBall::HitCheck(Float3& bullet)
{
	//int hitpoly = HitCheck_Sphere_Sphere(pos_.toVECTOR(), size_,bullet.toVECTOR(), size_);
	auto HitPoly = MV1CollCheck_Sphere(model_, -1, bullet.toVECTOR(),25);
	//if (hitpoly) {
	//	return true;
	//}
	if (HitPoly.Dim != nullptr) {
		MV1CollResultPolyDimTerminate(HitPoly);
		return true;
	}
	MV1CollResultPolyDimTerminate(HitPoly);
	return false;
}

Float3 TargetBall::GetPos(void)
{
	return pos_;
}
