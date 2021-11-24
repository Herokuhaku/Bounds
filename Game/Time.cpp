#include "Time.h"

Time::Time()
{
}

void Time::Update(void)
{
	double sum = sum_;
	hour_ = sum / Sexagesimal / Sexagesimal;

	sum -= hour_ * Sexagesimal * Sexagesimal;
	minute_ = sum / Sexagesimal;

	sum -= minute_ * Sexagesimal;
	second_ = sum;
}
