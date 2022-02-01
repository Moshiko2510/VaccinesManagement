#include "Date.h"


#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW


Date::Date() //Constructor
{
	m_Day = 0;
	m_Month = 0;
	m_Year = 0;
	m_Day_number = 0;
}

Date::Date(const Date& d)
{
	m_Day = d.m_Day;
	m_Month = d.m_Month;
	m_Year = d.m_Year;
	m_Day_number = d.m_Day_number;
}

void Date::restart_date()
{
	m_Day = 0;
	m_Month = 0;
	m_Year = 0;
	m_Day_number = 0;
}

void Date::set_today_date()
{
	time_t now;
	struct tm nowLocalDate;
	time(&now);
	localtime_s(&nowLocalDate, &now);
	m_Day = nowLocalDate.tm_mday;
	m_Month = nowLocalDate.tm_mon + 1;
	m_Year = nowLocalDate.tm_year + 1900;
	m_Day_number = (m_Year - 1) * 360 + (m_Month - 1) * 30 + (m_Day - 1);
}

void Date::set_day(int day)
{
	m_Day = day;
}

void Date::set_month(int month)
{
	m_Month = month;
}

void Date::set_year(int year)
{
	m_Year = year;
}


void Date::show()const
{
	cout << (int)m_Day << "/" << (int)m_Month << "/" << m_Year << endl;
}



long Date::get_day_number(void)const
{
	return m_Day_number;
}

int Date::get_year(void)const
{
	return m_Year;
}

int Date::get_month(void)const
{
	return m_Month;
}

int Date::get_day(void)const
{
	return m_Day;
}

void Date::set_day_number()
{
	m_Day_number = (m_Year - 1) * 360 + (m_Month - 1) * 30 + (m_Day - 1);
}


void Date::calc_end_of_quarantine()
{
	m_Day_number += 14;
	m_Day += 14;
	if (m_Month==2)
	{
		if (m_Day > 28)
		{
			m_Day = m_Day % 28;
			m_Month += 1;
		}
	}
	else if (m_Month % 2 == 0)
	{
		if (m_Day > 30)
		{
			m_Day = m_Day % 30;
			m_Month += 1;
		}
	}
	else if(m_Month % 2 == 1)
	{
		if (m_Day > 31)
		{
			m_Day = m_Day % 31;
			m_Month += 1;
		}
	}

	if (m_Month > 12)
	{
		m_Month = m_Month % 12;
		m_Year += 1;
	}
	m_Day_number = (m_Year - 1) * 360 + (m_Month - 1) * 30 + (m_Day - 1);

}

ostream& operator<<(ostream& os, const Date& d)
{
	d.show();
	return os;
}



bool Date::operator<(const Date& d) const
{
	if (m_Day_number < d.m_Day_number)
		return true;
	else
		return false;
}

bool Date::operator==(const Date& d) const
{
	if (m_Day_number == d.m_Day_number)
		return true;
	else
		return false;
}

bool Date::operator>(const Date& d) const
{
	if (m_Day_number > d.m_Day_number)
		return true;
	else
		return false;
}

bool Date::operator>=(const Date& d) const
{
	if (m_Day_number >= d.m_Day_number)
		return true;
	else
		return false;
}

bool Date::operator!=(const Date& d) const
{
	if (m_Day_number != d.m_Day_number)
		return true;
	else
		return false;
}