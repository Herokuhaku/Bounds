#pragma once

class Time {
public:
	static constexpr int Sexagesimal = 60;
	Time();
	void Update(void);
	// ���v����(�b)
	double sum_;
	// ����
	int hour_;
	// ��
	int minute_;
	// �b
	int second_;
};
