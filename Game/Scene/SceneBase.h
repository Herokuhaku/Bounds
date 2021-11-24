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

	// 初期化処理
	virtual void Init(void);

	// 更新ステップ
	virtual void Update(void);

	// 描画処理
	virtual void Draw(void);
	virtual void RealDraw(void);
	// 解放処理
	virtual void Release(void);

	// デバッグ描画
	virtual void DrawDebug(void);
	
	StageID GetStageID(void);
	Time GetClearTime(void);
protected:
	StageID stageid_;
	Time ClearTime_;
};

