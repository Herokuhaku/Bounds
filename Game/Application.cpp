#include <EffekseerForDXLib.h>

#include "GameCommon.h"
#include "KeyCheck.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Application.h"
#include "common/Vector2.h"

bool Application::Init(void)
{

	// システム処理
	SetWindowText("Project");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib の初期化失敗");
		return false;
	}

	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// えふぇくしあの初期化
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	KeyInit();
	lpSceneMng.Init();
	lpSceneMng.SetScreenSize(Float2(SCREEN_SIZE_X,SCREEN_SIZE_Y));
	// デバッグ
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	return true;

}

void Application::Run(void)
{
	double nextdeltatime = GetNowCount();
	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		_dbgStartDraw();

		CheckKeyList();

		lpSceneMng.Update();

		_dbgAddDraw();


		// 1フレーム16.66ms足す
		nextdeltatime += 16.66;
		// 1フレームの限界値 16.66ms (1秒間に60フレームの場合) よりも早くここに到達していたらその分待つ
		if (nextdeltatime > GetNowCount()) {
			WaitTimer(static_cast<int>(nextdeltatime) - GetNowCount());
		}

		ScreenFlip();

	}
}

bool Application::Release(void)
{
	//lpSceneMng.Release();

	// Effekseerを終了する。
	Effkseer_End();

	// DXライブラリを終了する。
	DxLib_End();

	return true;
}
