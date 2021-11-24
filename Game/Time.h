#pragma once

class Time {
public:
	static constexpr int Sexagesimal = 60;
	Time();
	void Update(void);
	// 合計時間(秒)
	double sum_;
	// 時間
	int hour_;
	// 分
	int minute_;
	// 秒
	int second_;
};
