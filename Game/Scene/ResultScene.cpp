#include "ResultScene.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "../KeyCheck.h"
#include "../Object/Camera.h"
#include "../Stage.h"
#include "../AsoUtility.h"
#include "../Object/Player.h"
#include "../Manager/SceneManager.h"

ResultScene::ResultScene()
{
	cleartime_.hour_ = 0;
	cleartime_.minute_ = 0;
	cleartime_.second_ = 0;
	cleartime_.sum_ = 0;
	Init();
}

ResultScene::ResultScene(Time cleartime, StageID stageid):cleartime_(cleartime)
{
	stageid_ = stageid;
	ChangeFont("Magneto");
	Init();
}

ResultScene::~ResultScene()
{
	ChangeFont("ＭＳ 明朝");
	SetMouseDispFlag(true);
}

void ResultScene::Init(void)
{
	scr_ = lpSceneMng.GetScreenSize();
	box_.pos = { scr_.x,50 };
	box_.size = { 700.0f,200.0f };
	newrecord_ = false;
	drawrecordtime_ = 1.0f;
	WriteClearTime();
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
}

void ResultScene::Update(void)
{
	auto control = lpSceneMng.GetController();
	auto data = control->GetCntData();
	// クリアタイム描画するとこ
	if (box_.pos.x + box_.size.x >= scr_.x) {
		box_.pos.x -= 10;
	}
	else {
		box_.flag = true;
	}
	if (data[INPUT_ID::JUMP][static_cast<int>(Trg::Now)] && !data[INPUT_ID::JUMP][static_cast<int>(Trg::Old)] && drawrecordtime_ < 0.0f)
	{
		lpSceneMng.ChangeScene(SCENE_ID::STAGESELECT, true);
	}
}

void ResultScene::Draw(void)
{
	DrawBox(box_.pos.x, box_.pos.y, box_.pos.x + box_.size.x, box_.pos.y + box_.size.y, 0xffffff, true);
	if (box_.flag) {
		int fs = GetFontSize();
		// クリアタイム表示
		SetFontSize(fs * 3);
		DrawString(box_.pos.x, box_.pos.y,"ClearTime",0x0000500,0xff0000);
		SetFontSize(fs * 7);
		DrawFormatString(box_.pos.x+box_.size.x/7, box_.pos.y + fs * 5, 0x0000ff, "%02d:%02d:%02d", cleartime_.hour_, cleartime_.minute_, cleartime_.second_);
		// ベストタイム表示
		if (drawrecordtime_ < 0.0f) {
			DrawFormatString(0, lpSceneMng.GetScreenSize().y - fs * 7, 0xffffff, "BestTime %02d:%02d:%02d", besttime_.hour_, besttime_.minute_, besttime_.second_);
			if (newrecord_) {
				DrawFormatString(0, lpSceneMng.GetScreenSize().y - fs * 14, 0xffff00, "NewRecord!!");
			}
		}
		drawrecordtime_ -= lpSceneMng.GetDeltaTime();
		SetFontSize(fs);
	}
}

void ResultScene::RealDraw(void)
{
}

void ResultScene::DrawDebug(void)
{
}

bool ResultScene::WriteClearTime()
{
	std::string str = "save/stage";
	str += std::to_string(static_cast<int>(stageid_));
	str += "cleartime.txt";
	const char* fileName = str.c_str();

	std::ifstream file(str);  // 読み込むファイルのパスを指定
	if (file) {
		std::string line;

		std::getline(file, line);

		int sum = atoi(line.c_str());
		if (sum > cleartime_.sum_) {
			std::ofstream ofs(fileName);
			newrecord_ = true;
			ofs << cleartime_.sum_ << std::endl;
			besttime_ = cleartime_;
		}
		else {
			besttime_.sum_ = sum;
		}
	}else{
	std::ofstream ofs(fileName);
	besttime_.sum_ = cleartime_.sum_;
		ofs << cleartime_.sum_ << std::endl;
		//return 0;
	}
	besttime_.Update();
	return true;
}
