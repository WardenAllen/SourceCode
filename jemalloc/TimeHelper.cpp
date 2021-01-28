#include "TimeHelper.h"

#include <sstream>
#include <iomanip>

using namespace std::chrono;

constexpr int second = 1;
constexpr int minute = 60;
constexpr int hour = 3600;
constexpr int day = 86400;

constexpr int time_zone_extra_hour = 8;

CTimeHelper::CTimeHelper()
{
	ResetTimer();
}

CTimeHelper::~CTimeHelper()
{
}

void CTimeHelper::ResetTimer()
{
	m_TimePoint = system_clock::time_point();
}

int64_t CTimeHelper::StartTimer()
{
	m_TimePoint = system_clock::now();
	return m_TimePoint.time_since_epoch().count();
}

int64_t CTimeHelper::LapTimer()
{
	return (system_clock::now() - m_TimePoint).count();
}

int64_t CTimeHelper::EndTimer()
{
	system_clock::time_point start = m_TimePoint;
	m_TimePoint = system_clock::now();
	return (m_TimePoint - start).count();
}

int64_t CTimeHelper::GetNowSec()
{
	return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

int64_t CTimeHelper::GetNowMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int64_t CTimeHelper::GetNowUS()
{
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

int64_t CTimeHelper::GetNowNS()
{
	return system_clock::now().time_since_epoch().count();
}

std::string CTimeHelper::GetTodayString()
{
	std::string time;
	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm = *localtime(&tt);

	std::stringstream sstream;
	sstream << local_tm.tm_year + 1900;
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_mon + 1;
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_mday;

	sstream >> time;
	return time;
}

std::string CTimeHelper::GetNowStampString()
{
	time_t t = (time_t)GetNowSec();
	tm local_tm = *localtime(&t);

	std::string date;
	std::string time;

	std::stringstream sstream;
	sstream << local_tm.tm_year + 1900 << "-";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_mon + 1 << "-";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_mday;
	sstream >> date;

	sstream.clear();
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_hour << ":";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_min << ":";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_sec;

	sstream >> time;

	return date + " " + time;
}

std::string CTimeHelper::GetStampString(int ts)
{
	time_t t = (time_t)ts;
	tm local_tm = *localtime(&t);

	std::string date;
	std::string time;

	std::stringstream sstream;
	sstream << local_tm.tm_year + 1900 << "-";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_mon + 1 << "-";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_mday;
	sstream >> date;

	sstream.clear();
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_hour << ":";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_min << ":";
	sstream << std::setfill('0') << std::setw(2) << local_tm.tm_sec;

	sstream >> time;

	return date + " " + time;
}

int CTimeHelper::GetYear()
{
	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_year;
}

int CTimeHelper::GetMonth()
{
	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_mon;
}

int CTimeHelper::GetDay()
{
	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_mday;
}

int CTimeHelper::GetWeekDay()
{
	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_wday;
}

int CTimeHelper::GetYearDay()
{
	time_t tt = system_clock::to_time_t(system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_yday;
}

int CTimeHelper::GetHour()
{
	return (int)GetNowSec() % day / hour + time_zone_extra_hour;
}

int CTimeHelper::GetAimSec(int day, int hour, int minute, int sec)
{
	time_t now = time(NULL);

	tm local_tm = *localtime(&now);
	local_tm.tm_mday = day;
	local_tm.tm_hour = hour;
	local_tm.tm_min = minute;
	local_tm.tm_sec = sec;

	time_t future = mktime(&local_tm);

	return static_cast<int>(future - now);
}

int CTimeHelper::GetAimSecExtra(int extra_day, int hour, int minute, int sec)
{
	time_t now = time(NULL);

	tm local_tm = *localtime(&now);
	local_tm.tm_mday += extra_day;
	local_tm.tm_hour = hour;
	local_tm.tm_min = minute;
	local_tm.tm_sec = sec;

	time_t future = mktime(&local_tm);

	return static_cast<int>(future - now);
}

int CTimeHelper::GetAimStamp(int day, int hour, int minute, int sec)
{
	time_t now = time(NULL);

	tm local_tm = *localtime(&now);
	local_tm.tm_mday = day;
	local_tm.tm_hour = hour;
	local_tm.tm_min = minute;
	local_tm.tm_sec = sec;

	return static_cast<int>(mktime(&local_tm));
}

int CTimeHelper::GetAimStampExtra(int extra_day, int hour, int minute, int sec)
{
	time_t now = time(NULL);

	tm local_tm = *localtime(&now);
	local_tm.tm_mday += extra_day;
	local_tm.tm_hour = hour;
	local_tm.tm_min = minute;
	local_tm.tm_sec = sec;

	return static_cast<int>(mktime(&local_tm));
}

int CTimeHelper::GetAimStampExtraWithStartTime(int start, int extra_day, int hour, int minute, int sec)
{
	time_t t = (time_t)start;
	tm local_tm = *localtime(&t);
	local_tm.tm_mday += extra_day;
	local_tm.tm_hour = hour;
	local_tm.tm_min = minute;
	local_tm.tm_sec = sec;

	return static_cast<int>(mktime(&local_tm));
}

bool CTimeHelper::IsTodayValid(uint8_t Week)
{
	return Week & (1 << static_cast<uint8_t>(GetWeekDay()));
}
