#include <chrono>
#include <EffekseerForDXLib.h>
//#include "DxLib.h"
#include "../Object/MiniCamera.h"
#include "../AsoUtility.h"
#include "SceneManager.h"
#include "../AllControl/XboxController.h"
#include "../AllControl/KeyBoardCtl.h"
#include "../Scene/GameScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/ResultScene.h"
#include "../Scene/StageSelectScene.h"

void SceneManager::Init()
{
	debugy_ = 10;
	plusdebugy_ = 20;

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// �V�[������ɃJ���������
	camera_ = std::make_unique<Camera>();
 
	scene_ = std::make_unique<TitleScene>();

	scene_->DrawDebug();


	//mMiniCamera = new MiniCamera(mCamera);
	//mMiniCamera->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	mTickCount = std::chrono::system_clock::now();

	// 3D�̐ݒ�
	Init3D();

	// ���삷����̂����
	//maincontroller_ = std::make_unique<XboxController>();
	maincontroller_ = std::make_unique<KeyBoard>();
	maincontroller_->SetUp(0);

	nextdeltatime = GetNowCount();
	effekseerimg_ = LoadGraph("Model/FloorTile01.jpg");
}

void SceneManager::Init3D(void)
{
	// �A�e������
	SetUseLighting(false);
	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);
	
	// Z�o�b�t�@�̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);
	
	// �o�b�N�J�����O(���ʂȕ`������Ȃ�)��L���ɂ���
	SetUseBackCulling(true);
	ChangeLightTypePoint(VECTOR(), 1000, 1, 1, 1);

	// ���C�g�̐ݒ�
	ChangeLightTypeDir({ 0.3f,-0.7f,0.8 });
	//ChangeLightTypeDir(camera_->GetAngles().toVECTOR());

	// 3D�̔w�i�F
	SetBackgroundColor(5,5,5);

	MV1SetLoadModelUsePhysicsMode(DX_LOADMODEL_PHYSICS_REALTIME);
	//MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);
	SetLightPosition(VECTOR());
	//// ���_�V�F�[�_�[�o�C�i���R�[�h�̓ǂݍ���
	//vshandle = LoadVertexShader("ShaderPolygon3DTestVS.vso");

	//// �s�N�Z���V�F�[�_�[�o�C�i���R�[�h�̓ǂݍ���
	//pshandle = LoadPixelShader("ShaderPolygon3DTestPS.pso");

	//// �g�p���钸�_�V�F�[�_�[���Z�b�g
	//SetUseVertexShader(vshandle);

	//// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	//SetUsePixelShader(pshandle);

	//MV1SetUseOrigShader(true);

		//
}

void SceneManager::Update(void)
{
	(*maincontroller_)();
	// �f���^�^�C��
	auto tickCount = std::chrono::system_clock::now();
	deltatime_ = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - mTickCount).count() / 1000000000.0f;
	mTickCount = tickCount;
	// �`���O���t�B�b�N�̈�̎w��
// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();



	SceneChange();
	// �~�j�J����
	//mMiniCamera->Update();
	//mMiniCamera->DrawScreen();
	SetCameraNearFar(50.0f, 10000.0f);
	Effekseer_Sync3DSetting();
	//SetCameraPositionAndAngle({0.0f,200.0f,-500.0f},);

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B

	UpdateEffekseer3D();
	//DrawEffekseer3D_Begin();
	

	// �`��
	//DrawGraph(0, 0, effekseerimg_, TRUE);
	DebugDraw();

	//fader_->Draw();

	camera_->Update();
	scene_->Draw();
	camera_->Draw();

	//fader_->Update();
	// �~�j�J����
	//mMiniCamera->Draw();


	// �J�����̃N���b�v�����̐ݒ� 1:Near 2:Far
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
	scene_->RealDraw();
	//DrawEffekseer3D_End();
	// 1�t���[��16.66ms����
	nextdeltatime += 16.66;
	// 1�t���[���̌��E�l 16.66ms (1�b�Ԃ�60�t���[���̏ꍇ) �������������ɓ��B���Ă����炻�̕��҂�
	if (nextdeltatime > GetNowCount()) {
		WaitTimer(static_cast<int>(nextdeltatime) - GetNowCount());
	}

	if (scene_ == nullptr)
	{
		return;
	}

}

void SceneManager::Release(void)
{
}

void SceneManager::SetScreenSize(Float2 size)
{
	screensize_ = size;
}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{
	waitSceneId_ = nextId;

	if (isFading)
	{
		fader_->SetFade(Fader::FADE_STATE::FADE_OUT);
		isSceneChanging_ = true;
	}
	else 
	{
		DoChangeScene();
	}

}

float SceneManager::GetDeltaTime(void)
{
	return deltatime_;
}

bool SceneManager::SetCamera(std::shared_ptr<Camera> camera)
{
	savecamera_ = camera_;
	camera_ = camera;
	if (camera_ == nullptr) {
		camera_ = std::make_shared<Camera>();
		return false;
	}
	return true;
}

Float3 SceneManager::GetCameraAngle(void)
{
	return camera_->GetAngles();
}

std::shared_ptr<Camera> SceneManager::GetCamera(void)
{
	return camera_;
}

void SceneManager::DebugDraw(void)
{
	scene_->DrawDebug();
	for (auto& draw : debugdraw_) {
		DrawFormatString(0, AddDebugY(), 0xfffff, " X %.1f , Y %.1f , Z %.1f ", draw.x, draw.y, draw.z);
	}
	for (auto& draw : debug2ddraw_) {
		DrawString(draw.second.x, draw.second.y, draw.first.c_str(), 0x0000ff, true);
	}
	debugy_ = 0;
	debugdraw_.clear();
}

int SceneManager::AddDebugY(void)
{
	return debugy_ += plusdebugy_;
}

void SceneManager::ResetDebugY(void)
{
}

void SceneManager::AddDebug(Float3 pos)
{
	debugdraw_.emplace_back(pos);
}

void SceneManager::AddDebug(std::string str, Float2 pos)
{
	debug2ddraw_.try_emplace(str,pos);
}

std::shared_ptr<Control> SceneManager::GetController(void)
{
	return maincontroller_;
}

Float2 SceneManager::GetScreenSize(void)
{
	return screensize_;
}

void SceneManager::SetMouseCenter(void)
{
	SetMousePoint(screensize_.x/2,screensize_.y/2);
}

void SceneManager::SceneChange()
{
	if (isSceneChanging_)
	{
		DoChangeScene();		// �J�����̐ݒ�
		camera_->SetBeforeDraw();
		scene_->Update();
		isSceneChanging_ = false;
		Fader::FADE_STATE fState = fader_->GetState();
		//switch (fState)
		//{
		//case Fader::FADE_STATE::FADE_IN:
		//	if (fader_->IsEnd())
		//	{
		//		fader_->SetFade(Fader::FADE_STATE::NONE);
		//		isSceneChanging_ = false;
		//	}
		//	break;
		//case Fader::FADE_STATE::FADE_OUT:
		//	if (fader_->IsEnd())
		//	{
		//		fader_->SetFade(Fader::FADE_STATE::FADE_IN);
		//	}
		//	break;
		//default:
		//	break;
		//}
	}
	else
	{
		// �J�����̐ݒ�
		camera_->SetBeforeDraw();
		scene_->Update();
	}
}

void SceneManager::DoChangeScene(void)
{
	//scene_->Release();

	sceneId_ = waitSceneId_;

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = std::make_unique<TitleScene>();
		break;
	case SCENE_ID::STAGESELECT:
		scene_ = std::make_unique<StageSelectScene>();
		break;
	case SCENE_ID::GAME:
		scene_ = std::make_unique<GameScene>(scene_->GetStageID());
		break;
	case SCENE_ID::RESULT:
		scene_ = std::make_unique<ResultScene>(scene_->GetClearTime(),scene_->GetStageID());
	default:
		break;
	}

	//scene_->Init();

	waitSceneId_ = SCENE_ID::NONE;
	lpSceneMng.SetMouseCenter();
}



