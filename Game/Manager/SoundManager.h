#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include "../common/Vector3.h"

#define lpSoundMng SoundManager::GetInstance()

class SoundManager
{
public:
	static SoundManager& GetInstance(void) {
		Create();
		return *sInstance_;
	}
	static void Create(void) {
		if (sInstance_ != nullptr) {
			return;
		}
		sInstance_ = new SoundManager();
	}
	static void Destroy(void) {
		if (sInstance_ == nullptr) {
			return;
		}
		delete sInstance_;
		sInstance_ = nullptr;
	}
	// サウンドハンドルを作る
	bool CreateHandle(std::string name, std::string filename,float radius = 256.0f);
	// 音の出る位置の設定
	bool CreateSoundPos(std::string name,Float3 pos);
	// 音を再生する
	bool CreatePlaySound(std::string name,int playtype = DX_PLAYTYPE_BACK);
	// 座標を指定してそこに再生する
	bool CreatePosPlaySound(std::string name, Float3 pos, int playtype = DX_PLAYTYPE_BACK);
	// 読み込みから再生まで一括で行う
	bool CreateSound(std::string filename, std::string name, Float3 pos, int playtype = DX_PLAYTYPE_BACK);
private:
	static SoundManager* sInstance_;
	SoundManager();
	~SoundManager();
	// サウンドハンドル
	std::map<std::string,int> soundhandle_;
};

