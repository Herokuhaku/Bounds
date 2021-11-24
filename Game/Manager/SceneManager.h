#pragma once
#include <chrono>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "../Fader.h"
#include "../Object/Camera.h"
#include "../common/Vector2.h"
#include "../AllControl/Control.h"
#include "../Scene/SceneBase.h"
class MiniCamera;
//class SceneBase;
#define lpSceneMng SceneManager::GetInstance()

// �V�[���Ǘ��p
enum class SCENE_ID
{
	NONE, 
	TITLE,
	STAGESELECT,
	GAME,
	RESULT,
};

class SceneManager
{
public:
	static SceneManager& GetInstance(void) {
		static SceneManager sInstance_;
		return sInstance_;
	}
	void Init(void);
	void Init3D(void);
	void Update(void);
	void Release(void);
	void SetScreenSize(Float2 size);

	void ChangeScene(SCENE_ID nextId, bool isFading);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void);
	
	bool SetCamera(std::shared_ptr<Camera> camera);

	Float3 GetCameraAngle(void);
	// �J�����̎擾
	std::shared_ptr<Camera> GetCamera(void);

	void DebugDraw(void);
	
	// �f�o�b�O�̕����ʒu����
	int AddDebugY(void);

	// �f�o�b�O�����ʒu�̏�����
	void ResetDebugY(void);

	void AddDebug(Float3 pos);
	void AddDebug(std::string,Float2 pos);

	std::shared_ptr<Control> GetController(void);
	Float2 GetScreenSize(void);
	void SetMouseCenter(void);
private:

	void SceneChange();

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;
	
	Float2 screensize_;
	std::unique_ptr<SceneBase> scene_;
	std::unique_ptr<Fader> fader_;
	std::shared_ptr<Camera>camera_;
	//SceneBase* scene_;
//	Fader* fader_;
//	Camera* camera_;
	MiniCamera* mMiniCamera;

	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point mTickCount;
	float deltatime_;

	void DoChangeScene(void);
	std::shared_ptr<Camera> savecamera_;

	std::vector<Float3> debugdraw_;
	std::map<std::string, Float2> debug2ddraw_;
	int debugy_;
	int plusdebugy_;

	std::shared_ptr<Control> maincontroller_;

	double nextdeltatime;

	int effekseerimg_;
	// �ǂݍ��ގ��ɑ傫�����w�肷��B
	int effectResourceHandle;

	// ���ł������̂ŉ摜��ǂݍ��ށB
	int grBackgroundHandle;
	int time = 0;
	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int playingEffectHandle = -1;
	int pshandle;
	int vshandle;
};