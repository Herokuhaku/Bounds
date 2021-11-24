#include "StageSelectScene.h"
#include "../KeyCheck.h"
#include "../Manager/SceneManager.h"
#include "../Object/Camera.h"
#include "../Stage.h"
#include "../AsoUtility.h"
#include "../Object/Player.h"
#include "../Object/StageSelect.h"

StageSelectScene::StageSelectScene()
{
	Init();
}

StageSelectScene::~StageSelectScene()
{
	for (auto stage : stageselect_) {
		delete stage;
	}
}

void StageSelectScene::Init(void)
{
	stageselect_.emplace_back(new StageSelect(Int2(300, 150), Int2(200, 150), StageID::STAGE2));
}

void StageSelectScene::Update(void)
{
	auto control = lpSceneMng.GetController();
	auto data = control->GetCntData();

	for (auto stage : stageselect_) {
		if (stage->Update()) {
			stageid_ = stage->GetNo();
			lpSceneMng.ChangeScene(SCENE_ID::GAME, false);
			return;
		}
	}
}

void StageSelectScene::Draw(void)
{
	for (auto stage : stageselect_) {
		stage->Draw();
	}
}

void StageSelectScene::RealDraw(void)
{
}

void StageSelectScene::DrawDebug(void)
{
}
