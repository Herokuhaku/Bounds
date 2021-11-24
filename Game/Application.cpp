#include <EffekseerForDXLib.h>

#include "GameCommon.h"
#include "KeyCheck.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Application.h"
#include "common/Vector2.h"

bool Application::Init(void)
{

	// �V�X�e������
	SetWindowText("Project");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib �̏��������s");
		return false;
	}

	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// ���ӂ��������̏�����
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	KeyInit();
	lpSceneMng.Init();
	lpSceneMng.SetScreenSize(Float2(SCREEN_SIZE_X,SCREEN_SIZE_Y));
	// �f�o�b�O
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	return true;

}

void Application::Run(void)
{
	double nextdeltatime = GetNowCount();
	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		_dbgStartDraw();

		CheckKeyList();

		lpSceneMng.Update();

		_dbgAddDraw();


		// 1�t���[��16.66ms����
		nextdeltatime += 16.66;
		// 1�t���[���̌��E�l 16.66ms (1�b�Ԃ�60�t���[���̏ꍇ) �������������ɓ��B���Ă����炻�̕��҂�
		if (nextdeltatime > GetNowCount()) {
			WaitTimer(static_cast<int>(nextdeltatime) - GetNowCount());
		}

		ScreenFlip();

	}
}

bool Application::Release(void)
{
	//lpSceneMng.Release();

	// Effekseer���I������B
	Effkseer_End();

	// DX���C�u�������I������B
	DxLib_End();

	return true;
}
