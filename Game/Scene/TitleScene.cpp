#include "TitleScene.h"
#include "../KeyCheck.h"
#include "../Manager/SceneManager.h"
#include "../Object/Camera.h"
#include "../Stage.h"
#include "../AsoUtility.h"
#include "../Object/Player.h"

TitleScene::TitleScene()
{
	Init();
}

void TitleScene::Init(void)
{
}

void TitleScene::Update(void)
{
	auto control = lpSceneMng.GetController();
	auto data = control->GetCntData();

	if (data[INPUT_ID::JUMP][static_cast<int>(Trg::Now)] && !data[INPUT_ID::JUMP][static_cast<int>(Trg::Old)])
	{
 		lpSceneMng.ChangeScene(SCENE_ID::STAGESELECT, true);
	}
}

void TitleScene::Draw(void)
{
}

void TitleScene::RealDraw(void)
{
}

void TitleScene::DrawDebug(void)
{
}
