#pragma once
#include "Control.h"
#include "../common/Vector2.h"

#define XINPUT_THUMBL_X 0		// L�X�e�B�b�N�̉�
#define XINPUT_THUMBL_Y 1		// L�X�e�B�b�N�̏c
#define XINPUT_THUMBR_X 2		// R�X�e�B�b�N�̉�
#define XINPUT_THUMBR_Y 3		// R�X�e�B�b�N�̏c

#define XINPUT_LOOK_UP 18
#define XINPUT_LOOK_DOWN 19
#define XINPUT_LOOK_LEFT 20
#define XINPUT_LOOK_RIGHT 21

// �X�e�B�b�N�擾�p
#define THUMB_LEFT  0
#define THUMB_RIGHT 1


class XboxController :
	public Control
{
	static constexpr float MIN_COUNT = 0.0f;
	ControlType GetType(void)override;
	bool SetUp(int no)override;
	void Update(void)override;
private:
	void StickUp(void);

	XINPUT_STATE input = {};

	char pad_ = {};
	int id_ = {};
	static int count_;
};

