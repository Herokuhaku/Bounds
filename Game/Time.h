#pragma once

class Time {
public:
	static constexpr int Sexagesimal = 60;
	Time();
	void Update(void);
	// ‡ŒvŠÔ(•b)
	double sum_;
	// ŠÔ
	int hour_;
	// •ª
	int minute_;
	// •b
	int second_;
};
