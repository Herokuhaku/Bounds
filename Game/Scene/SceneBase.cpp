#include "SceneBase.h"
#include "../Manager/SceneManager.h"

SceneBase::SceneBase(){
	Init();
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init(void)
{
	stageid_ = StageID::NON;
}

void SceneBase::Update(void)
{
}

void SceneBase::Draw(void)
{
}

void SceneBase::RealDraw(void)
{
}

void SceneBase::Release(void)
{
}

void SceneBase::DrawDebug(void)
{
}

StageID SceneBase::GetStageID(void)
{
	return stageid_;
}

Time SceneBase::GetClearTime(void)
{
	return ClearTime_;
}

//StageID SceneBase::GetStageID(void)
//{
//	return stageid_;
//}
