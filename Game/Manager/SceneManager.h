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

// シーン管理用
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

	// デルタタイムの取得
	float GetDeltaTime(void);
	
	bool SetCamera(std::shared_ptr<Camera> camera);

	Float3 GetCameraAngle(void);
	// カメラの取得
	std::shared_ptr<Camera> GetCamera(void);

	void DebugDraw(void);
	
	// デバッグの文字位置調整
	int AddDebugY(void);

	// デバッグ文字位置の初期化
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

	// デルタタイム
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
	// 読み込む時に大きさを指定する。
	int effectResourceHandle;

	// 何でもいいので画像を読み込む。
	int grBackgroundHandle;
	int time = 0;
	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;
	int pshandle;
	int vshandle;
};