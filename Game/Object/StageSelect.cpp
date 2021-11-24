#include <DxLib.h>
#include <string>
#include "StageSelect.h"

StageSelect::StageSelect(Int2 pos, Int2 size, StageID stageno)
{
	pos_ = pos;
	stageno_ = stageno;
	windowSize_ = size;
	Init();
}

StageSelect::~StageSelect()
{
}

bool StageSelect::Update(void)
{
	Int2 mouse;
	GetMousePoint(&mouse.x, &mouse.y);
	if (pos_.x < mouse.x && mouse.x < windowSize_.x + pos_.x &&
		pos_.y < mouse.y && mouse.y < windowSize_.y + pos_.y)
	{
		selectflag_ = true;
		if ((GetMouseInput() == MOUSE_INPUT_LEFT) != 0)
		{
			return true;
		}
	}
	else { selectflag_ = false; }
	return false;
}

void StageSelect::Draw(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	int before = GetFontSize();
	SetFontSize(24);
	int font_ = 24;
	DrawBox(0,0,windowSize_.x,windowSize_.y,0x99ff99,true);
	std::string str = std::to_string(static_cast<int>(stageno_));
	//std::string str = "%d";
	DrawFormatString(windowSize_.x/2 - ((str.size()*(font_/2)) /2),windowSize_.y/2-(font_),0x0,str.c_str());
	if (selectflag_)
	{
		for (int i = 0;i < 5;i++)
		{
			DrawBox(0+i, 0+i, windowSize_.x-i, windowSize_.y-i, 0xff0000, false);
		}
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(pos_.x,pos_.y,screen_,true);

	SetFontSize(before);
}

StageID StageSelect::GetNo(void)
{
	return stageno_;
}

void StageSelect::Init()
{
	//windowSize_ = {300,200};
	screen_ = MakeScreen(windowSize_.x,windowSize_.y);
	selectflag_ = false;
}
