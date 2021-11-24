#pragma once
#include <DxLib.h>
#include <map>
#include <memory>
#include <array>
#include <mutex>
#include "INPUT_ID.h"

enum class ControlType
{
	KEY,
	MOUSE,
	XBOX_CONTROLLER,
	MAX
};
enum class Trg
{
	Now,
	Old,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<INPUT_ID, TrgBool>;

struct Control
{
	void operator()() {
		Update();
	}
	const CntData& GetCntData(void)
	{
		return data_;
	}
	virtual ControlType GetType(void) = 0;
	virtual bool SetUp(int no) = 0;
	bool GetTrg(INPUT_ID id) {
		return data_[id][static_cast<int>(Trg::Now)] && !data_[id][static_cast<int>(Trg::Now)];
	};
	void ChangeScenePushed(void) {
		for (auto& data : data_) {
			data.second[static_cast<int>(Trg::Now)] = 1;
			data.second[static_cast<int>(Trg::Old)] = 1;
	}
	};
private:
	virtual void Update() = 0;
protected:
	CntData data_ = {};
	std::map<INPUT_ID, int> keylist_ = {};
};