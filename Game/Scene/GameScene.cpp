#include "DxLib.h"
#include "../KeyCheck.h"
#include "../Manager/SceneManager.h"
#include "GameScene.h"
#include "../Object/Camera.h"
#include "../Stage.h"
#include "../AsoUtility.h"
#include "../Manager/SoundManager.h"

GameScene::GameScene(StageID stageid) : SceneBase()
{
	stageid_ = stageid;
	Init();
}

void GameScene::Init(void)
{
	lpSceneMng.GetController()->ChangeScenePushed();
	// マウスカーソルを消す
	SetMouseDispFlag(false);
	Stage2();
	lpSceneMng.GetCamera()->SetAngles(Float3{ static_cast<float>(AsoUtility::Deg2Rad(30)),0.0f,0.0f });
	stage_ = std::make_unique<Stage>(stageinfo_[stageid_].first, stageinfo_[stageid_].second);
	lpSoundMng.CreateHandle("Bomb", "Sound/bomb1.mp3");
}

void GameScene::Update(void)
{
	auto control = lpSceneMng.GetController();
	auto data = control->GetCntData();
	if(!stage_->Update())
	{
		ClearTime_ = stage_->GetElapsedTime();
		lpSceneMng.ChangeScene(SCENE_ID::RESULT,true);
	}

	lpSceneMng.SetMouseCenter();
}

void GameScene::Draw(void)
{
	stage_->Draw();
}

void GameScene::RealDraw(void)
{
	stage_->RealDraw();
}

void GameScene::DrawDebug(void)
{
	auto camera = lpSceneMng.GetCamera();

	Float3 pos = camera->GetPos();
	Float3 angles = camera->GetAngles();
	lpSceneMng.AddDebug(pos);
	lpSceneMng.AddDebug(angles);
	Float2 screensize_ = lpSceneMng.GetScreenSize();
	DrawCircle(screensize_.x / 2, screensize_.y / 2, 5, 0x0000ff, true, true);

	std::string str = "目標ターゲット %d/%d";
	int size = GetFontSize();
	SetFontSize(size*2);
	DrawFormatString(screensize_.x - (GetFontSize() * (str.size()*2/3)), screensize_.y - (GetFontSize()), 0xffffff,str.c_str(), stage_->GetDestroyTargetCount(), stage_->GetTargetCount());

	str = "経過時間 %02d:%02d:%02d";
	DrawFormatString(screensize_.x - (GetFontSize() * (str.size() * 2 / 3)),(GetFontSize()), 0xffffff, str.c_str(), stage_->GetElapsedTime().hour_, stage_->GetElapsedTime().minute_,stage_->GetElapsedTime().second_);
	SetFontSize(size);
}

void GameScene::Stage2(void)
{
	std::list<Float3> list;
	list.emplace_back(Float3(0, 800, 0));

	list.emplace_back(Float3(1340, 780, -2700));
	list.emplace_back(Float3(1540, 700, -2570));
	list.emplace_back(Float3(1600, 920, -2400));
	list.emplace_back(Float3(1400, 1200, -1700));

	list.emplace_back(Float3(1340, 780, 2700));
	list.emplace_back(Float3(1540, 700, 2570));
	list.emplace_back(Float3(1600, 920, 2400));
	list.emplace_back(Float3(1400, 1200, 1700));
	list.emplace_back(Float3(-500, 1300, 930));

	// 囲われてるやつ
	list.emplace_back(Float3(3120, 1060, -3000));

	list.emplace_back(Float3(5000, 1060, -2700));
	list.emplace_back(Float3(4950, 860, -3000));
	list.emplace_back(Float3(4650, 1200, -3150));

	// 反射連続のとこ
	list.emplace_back(Float3(3600, 1060, 2700));
	list.emplace_back(Float3(3800, 860, 3000));
	list.emplace_back(Float3(4000, 1200, 3150));
	list.emplace_back(Float3(4120, 580, 2850));

	// 三角形のとこ

	list.emplace_back(Float3(4800, 1060, -200));
	list.emplace_back(Float3(4800, 1400, -100));
	list.emplace_back(Float3(4900, 680, -300));
	list.emplace_back(Float3(5000, 590, -180));

	NameAndTarget nametarget = { "Model/stage002.mv1", list };
	stageinfo_.emplace(StageID::STAGE2,nametarget);
}
