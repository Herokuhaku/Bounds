#include "KeyBoardCtl.h"
#include "../Manager/SceneManager.h"
#include "../common/Vector2.h"
#include <DxLib.h>

ControlType KeyBoard::GetType(void)
{
	return ControlType::KEY;
}

bool KeyBoard::SetUp(int no)
{
	keylist_.try_emplace(INPUT_ID::UP,KEY_INPUT_W);
	keylist_.try_emplace(INPUT_ID::DOWN, KEY_INPUT_S);
	keylist_.try_emplace(INPUT_ID::LEFT, KEY_INPUT_A);
	keylist_.try_emplace(INPUT_ID::RIGHT, KEY_INPUT_D);
	keylist_.try_emplace(INPUT_ID::LOOK_UP,KEY_INPUT_UP);
	keylist_.try_emplace(INPUT_ID::LOOK_DOWN,KEY_INPUT_DOWN);
	keylist_.try_emplace(INPUT_ID::LOOK_LEFT,KEY_INPUT_LEFT);
	keylist_.try_emplace(INPUT_ID::LOOK_RIGHT,KEY_INPUT_RIGHT);
	keylist_.try_emplace(INPUT_ID::FIRE, KEY_INPUT_Q);
	keylist_.try_emplace(INPUT_ID::ESC, KEY_INPUT_K);
	keylist_.try_emplace(INPUT_ID::JUMP, KEY_INPUT_SPACE);
	keylist_.try_emplace(INPUT_ID::ADS, KEY_INPUT_1);
	keylist_.try_emplace(INPUT_ID::RUN,KEY_INPUT_LSHIFT);
	keylist_.try_emplace(INPUT_ID::FREE, KEY_INPUT_R);

	_keyData.fill(0);
	return true;
}

void KeyBoard::Update(void)
{
	GetHitKeyStateAll(_keyData.data());
	for (auto id : INPUT_ID())
	{
		if (id == INPUT_ID::FIRE || id == INPUT_ID::ADS) {
			continue;
		}
		data_[id][static_cast<int>(Trg::Old)] = data_[id][static_cast<int>(Trg::Now)];
		data_[id][static_cast<int>(Trg::Now)] = _keyData[keylist_[id]];
	}
	// マウスのトリガー処理

	int left = (GetMouseInput() & MOUSE_INPUT_LEFT);
	data_[INPUT_ID::FIRE][static_cast<int>(Trg::Old)] = data_[INPUT_ID::FIRE][static_cast<int>(Trg::Now)];
	data_[INPUT_ID::FIRE][static_cast<int>(Trg::Now)] = left;

	data_[INPUT_ID::ADS][static_cast<int>(Trg::Old)] = data_[INPUT_ID::ADS][static_cast<int>(Trg::Now)];
	data_[INPUT_ID::ADS][static_cast<int>(Trg::Now)] = (GetMouseInput() & MOUSE_INPUT_RIGHT);
	
}
