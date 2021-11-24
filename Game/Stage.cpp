#include "Stage.h"
//#include <DxLib.h>
#include <EffekseerForDXLib.h>
Stage::Stage(std::string stagename, std::list<Float3> targetlist)
{
	Init(stagename,targetlist);
}
Stage::~Stage()
{
}

void Stage::Init(std::string stagename, std::list<Float3> targetlist)
{
	modelid_ = MV1LoadModel(stagename.c_str());
	player_ = std::make_shared<Player>(modelid_);

	MV1SetupCollInfo(modelid_, -1, 8, 8, 8);

	pos_ = Float3{ 0.0f,0.0f,0.0f };

	// モデルの座標を設定
	MV1SetPosition(modelid_, pos_.toVECTOR());
	MV1GetFrameNum(modelid_);

	targetcount_ = targetlist.size();
	for (auto& target : targetlist) {
		AddTargetBall(target);
	}
	destroytargetcount_ = 0;
	start_ = std::chrono::system_clock::now(); // 計測開始時間
	end_ = start_;
}

bool Stage::Update(void)
{
	TimeCreate();

	player_->Update();
	auto posvec = player_->GetBulletsPos();
	for (auto& target : targetvector_) {
		target->Update(posvec);
	}
	if (targetvector_.size() <= 0) {
		return false;
	}
	DeleteCheckTargetBall();
	return true;
}

void Stage::TimeCreate()
{
	time_.sum_ = std::chrono::duration_cast<std::chrono::seconds>(end_ - start_).count(); //処理に要した時間を秒に変換

	time_.Update();

	end_ = std::chrono::system_clock::now(); // 計測開始時間
}

void Stage::Draw(void)
{
	Float3 plpos = player_->GetPos();
	DrawFormatString(0, 75, 0xfffff, "プレイヤー座標 : X %.1f , Y %.1f , Z %.1f ",plpos.x,plpos.y,plpos.z);

	for (auto& target : targetvector_) {
		target->Draw();
	}

	player_->Draw();
	//MV1SetUseZBuffer(modelid_,true);
	//MV1SetWriteZBuffer(modelid_,false);
	//MV1DrawModel(modelid_);
	for (int i = 0; i < MV1GetFrameNum(modelid_); i++) {
		if (!MV1GetFrameSemiTransState(modelid_,i)) {
			MV1SetUseZBuffer(modelid_, true);
			MV1SetWriteZBuffer(modelid_, true);
			MV1DrawFrame(modelid_, i);
		}
	}
}

void Stage::RealDraw(void)
{
	for (int i = 0; i < MV1GetFrameNum(modelid_); i++) {
		if (MV1GetFrameSemiTransState(modelid_, i)) {
			MV1SetUseZBuffer(modelid_, true);
			MV1SetWriteZBuffer(modelid_, true);
			MV1DrawFrame(modelid_, i);
		}
	}
}

void Stage::Release(void)
{
	MV1DeleteModel(modelid_);
}

void Stage::AddTargetBall(Float3 pos)
{
	targetball_.emplace_back(pos);
	targetvector_.emplace_back(std::make_unique<TargetBall>(pos,&targetball_,targetball_.size()));
}

void Stage::DeleteCheckTargetBall(void)
{
	int count_ = 0;
	for (auto it = targetvector_.begin(); it != targetvector_.end();) {
		// 条件一致した要素を削除する
		if ((*it)->isDead()) {
			// 削除された要素の次を指すイテレータが返される。
			it = targetvector_.erase(it);
			targetball_.erase(targetball_.begin() + count_);
			destroytargetcount_++;
		}
		// 要素削除をしない場合に、イテレータを進める
		else {
			++it;
			count_++;
		}
	}
}

int Stage::GetTargetNum(void)
{
	return targetvector_.size();
}

int Stage::GetDestroyTargetCount(void)
{
	return destroytargetcount_;
}

int Stage::GetTargetCount(void)
{
	return targetcount_;
}

Time Stage::GetElapsedTime(void)
{
	return time_;
}
