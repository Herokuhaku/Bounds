#include "SoundManager.h"

SoundManager* SoundManager::sInstance_ = nullptr;


bool SoundManager::CreateHandle(std::string name, std::string filename,float radius)
{
	SetCreate3DSoundFlag(true);
	soundhandle_.emplace(name,LoadSoundMem(filename.c_str()));
	SetCreate3DSoundFlag(false);
	// �����������鋗����ݒ肷��
	Set3DRadiusSoundMem(radius, soundhandle_[name]);
	return true;
}

bool SoundManager::CreateSoundPos(std::string name, Float3 pos)
{
	if (soundhandle_.find(name) == soundhandle_.end()) {
		return false;
	}
	// ���̍Đ��ʒu��ݒ�
	Set3DPositionSoundMem(pos.toVECTOR(),soundhandle_[name]);
	return true;
}

bool SoundManager::CreatePlaySound(std::string name, int playtype)
{
	if (soundhandle_.find(name) == soundhandle_.end()) {
		return false;
	}
	// ���̍Đ����J�n
	PlaySoundMem(soundhandle_[name],playtype);
	return true;
}

bool SoundManager::CreatePosPlaySound(std::string name, Float3 pos, int playtype)
{
	if (soundhandle_.find(name) == soundhandle_.end()) {
		return false;
	}
	CreateSoundPos(name, pos);
	CreatePlaySound(name,playtype);
	return true;
}

bool SoundManager::CreateSound(std::string filename, std::string name, Float3 pos, int playtype)
{
	CreateHandle(name, filename);
	CreateSoundPos(name, pos);
	CreatePlaySound(name, playtype);
	return true;
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}
