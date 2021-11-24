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
	// �T�E���h�n���h�������
	bool CreateHandle(std::string name, std::string filename,float radius = 256.0f);
	// ���̏o��ʒu�̐ݒ�
	bool CreateSoundPos(std::string name,Float3 pos);
	// �����Đ�����
	bool CreatePlaySound(std::string name,int playtype = DX_PLAYTYPE_BACK);
	// ���W���w�肵�Ă����ɍĐ�����
	bool CreatePosPlaySound(std::string name, Float3 pos, int playtype = DX_PLAYTYPE_BACK);
	// �ǂݍ��݂���Đ��܂ňꊇ�ōs��
	bool CreateSound(std::string filename, std::string name, Float3 pos, int playtype = DX_PLAYTYPE_BACK);
private:
	static SoundManager* sInstance_;
	SoundManager();
	~SoundManager();
	// �T�E���h�n���h��
	std::map<std::string,int> soundhandle_;
};

