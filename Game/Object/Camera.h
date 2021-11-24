#pragma once
#include <DxLib.h>
#include <utility>
#include "../common/Vector3.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Init(void);
	void Update(void);
	std::pair<bool, double> Update(Float3 pos);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	Float3 GetPos(void);
	Float3 GetAngles(void);
	void SetPos(Float3 pos);
	void SetAngles(Float3 angle);
	VECTOR GetDxlibAngles(void);
private:
	// �J�����̈ʒu
	Float3 pos_;
	// �J�����̊p�x(rad)
	Float3 angles_;
};

