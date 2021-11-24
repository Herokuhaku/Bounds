#include "XboxController.h"

int XboxController::count_ = 0;

ControlType XboxController::GetType(void)
{
	return ControlType::XBOX_CONTROLLER;
}

bool XboxController::SetUp(int no)
{
	keylist_.try_emplace(INPUT_ID::UP, XINPUT_BUTTON_DPAD_UP);
	keylist_.try_emplace(INPUT_ID::DOWN, XINPUT_BUTTON_DPAD_DOWN);
	keylist_.try_emplace(INPUT_ID::LEFT, XINPUT_BUTTON_DPAD_LEFT);
	keylist_.try_emplace(INPUT_ID::RIGHT, XINPUT_BUTTON_DPAD_RIGHT);

	keylist_.try_emplace(INPUT_ID::LOOK_UP, XINPUT_LOOK_UP);
	keylist_.try_emplace(INPUT_ID::LOOK_DOWN, XINPUT_LOOK_DOWN);
	keylist_.try_emplace(INPUT_ID::LOOK_LEFT, XINPUT_LOOK_LEFT);
	keylist_.try_emplace(INPUT_ID::LOOK_RIGHT, XINPUT_LOOK_RIGHT);

	keylist_.try_emplace(INPUT_ID::FIRE, XINPUT_BUTTON_LEFT_SHOULDER);
	keylist_.try_emplace(INPUT_ID::ESC,XINPUT_BUTTON_BACK);
	keylist_.try_emplace(INPUT_ID::JUMP, XINPUT_BUTTON_X);
	keylist_.try_emplace(INPUT_ID::ADS, XINPUT_BUTTON_RIGHT_SHOULDER);
	keylist_.try_emplace(INPUT_ID::RUN,XINPUT_BUTTON_LEFT_THUMB);
	keylist_.try_emplace(INPUT_ID::FREE, XINPUT_BUTTON_A);

	id_ = count_++;
	return true;
}

void XboxController::Update(void)
{
	GetJoypadXInputState(id_+1, &input);
	// 更新
	for (auto id : INPUT_ID())
	{
		data_[id][static_cast<int>(Trg::Old)] = data_[id][static_cast<int>(Trg::Now)];
		data_[id][static_cast<int>(Trg::Now)] = input.Buttons[keylist_[id]];
	}
	StickUp();
}

void XboxController::StickUp(void)
{
	// 左スティックのX軸
	if (input.ThumbLX > 30000)
	{
		data_[INPUT_ID::RIGHT][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input.ThumbLX < -30000)
	{
		data_[INPUT_ID::LEFT][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		data_[INPUT_ID::LEFT][static_cast<int>(Trg::Now)] = 0;
		data_[INPUT_ID::RIGHT][static_cast<int>(Trg::Now)] = 0;
	}
	// 左スティックのY軸
	if (input.ThumbLY > 30000)
	{
		data_[INPUT_ID::UP][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input.ThumbLY < -30000)
	{
		data_[INPUT_ID::DOWN][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		data_[INPUT_ID::DOWN][static_cast<int>(Trg::Now)] = 0;
		data_[INPUT_ID::UP][static_cast<int>(Trg::Now)] = 0;
	}

	// 左スティックのX軸
	if (input.ThumbRX > MIN_COUNT)
	{
		data_[INPUT_ID::LOOK_RIGHT][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		data_[INPUT_ID::LOOK_RIGHT][static_cast<int>(Trg::Now)] = 0;
	}
	if (input.ThumbRX < -MIN_COUNT)
	{
		data_[INPUT_ID::LOOK_LEFT][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		data_[INPUT_ID::LOOK_LEFT][static_cast<int>(Trg::Now)] = 0;
	}


	// 左スティックのY軸
	if (input.ThumbRY > MIN_COUNT)
	{
		data_[INPUT_ID::LOOK_UP][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		data_[INPUT_ID::LOOK_UP][static_cast<int>(Trg::Now)] = 0;
	}

	if(input.ThumbRY < -MIN_COUNT)
	{
		data_[INPUT_ID::LOOK_DOWN][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		data_[INPUT_ID::LOOK_DOWN][static_cast<int>(Trg::Now)] = 0;
	}
}
