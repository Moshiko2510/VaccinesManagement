#ifndef _Date_H_
#define _Date_H_


#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include <iostream>
#include<ctime>
using namespace std;



//************************Date************************
class Date {
private:
	int m_Day, m_Month;
	int m_Year;
	unsigned long m_Day_number; // days since 1/1/0001
public:
	Date(); //Constructor
	Date(const Date&); // Copy Constructor

	long get_day_number(void)const; // return day_number
	int get_year(void)const;
	int get_month(void)const;
	int get_day(void)const;

	void show()const; //print Date
	void calc_end_of_quarantine( );
	void restart_date();
	void set_today_date();

	void set_day_number();
	void set_day(int day);
	void set_month(int month);
	void set_year(int year);


	//operators
	bool operator<(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator!=(const Date& d) const;
	friend ostream& operator<<(ostream& os, const Date& d);
};



#endif
