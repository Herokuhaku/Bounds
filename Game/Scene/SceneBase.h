#pragma once
#include <memory>
#include <vector>
#include "../common/Vector3.h"
#include "../Time.h"

enum class StageID {
	NON,
	STAGE1,
	STAGE2,
	STAGE3
};

class SceneBase
{
public:

	SceneBase();
	virtual ~SceneBase();

	// ����������
	virtual void Init(void);

	// �X�V�X�e�b�v
	virtual void Update(void);

	// �`�揈��
	virtual void Draw(void);
	virtual void RealDraw(void);
	// �������
	virtual void Release(void);

	// �f�o�b�O�`��
	virtual void DrawDebug(void);
	
	StageID GetStageID(void);
	Time GetClearTime(void);
protected:
	StageID stageid_;
	Time ClearTime_;
};

