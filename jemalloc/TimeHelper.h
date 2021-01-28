#pragma once

/*
 * Copyright (C) WardenAllen
 * Copyright (C) 2020.8.6
 */


#include <chrono>
#include <string>

class CTimeHelper
{
public:
	CTimeHelper();
	~CTimeHelper();

public:
	void ResetTimer();
	int64_t StartTimer();
	int64_t LapTimer();
	int64_t EndTimer();

public:
	static int64_t GetNowSec();
	static int64_t GetNowMS();
	static int64_t GetNowUS();
	static int64_t GetNowNS();

	/**
	* @brief  20200805
	*/
	static std::string GetTodayString();
	static std::string GetNowStampString();
	static std::string GetStampString(int ts);

	static int GetYear();
	static int GetMonth();
	static int GetDay();
	static int GetWeekDay();
	static int GetYearDay();
	static int GetHour();

	static int GetAimSec(int day, int hour, int minute = 0, int sec = 0);
	static int GetAimSecExtra(int extra_day, int hour, int minute = 0, int sec = 0);

	static int GetAimStamp(int day, int hour, int minute = 0, int sec = 0);
	static int GetAimStampExtra(int extra_day, int hour, int minute = 0, int sec = 0);
	static int GetAimStampExtraWithStartTime(int start, int extra_day, int hour, int minute = 0, int sec = 0);

	/**
	* @param  Week	[0-6]
	*/
	static bool IsTodayValid(uint8_t Week);

private:
	std::chrono::system_clock::time_point m_TimePoint;
};