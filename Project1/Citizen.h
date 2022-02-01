#ifndef _CITIZEN_H_
#define _CITIZEN_H_

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include<iostream>
#include<string>
using namespace std;

#include "Date.h"


//************************Citizen************************
class Citizen 
{
private:
	string m_First_name;
	string m_Last_name;
	int m_Id;
	int m_Age;
	bool m_Vaccine;
	bool m_Invited;
	string m_Medical_history;   
	bool m_Is_covid;			 //if true- after quarantine over set to false
	Date m_Vaccine_day;          //only after vaccine done
	Date m_End_of_quarantine;    //if covid is true user will request to start quarantine with the current date of reading+14 days of quarantine.

public:
	Citizen( string first_name, string last_name, int id, int age,bool is_covid,string medical_history,Date quarantine,Date vaccine,bool invited); //Ctor
	Citizen(); //ctor
	~Citizen(); //Dtor

	
	const string& get_first_name()  const;
	const string& get_last_name()   const;
	int get_id() const;
	int get_age() const;
	Date get_Vaccine_day()const;
	Date get_End_of_quarantine()const;
	string get_medical_history() const;
	void show_medical_history();
	void set_Vaccine_day();
	void set_End_of_quarantine();
	void set_Is_covid(bool n);
	void set_vaccine(bool n);
	bool get_covid()const;
	bool get_vaccine()const;
	bool get_is_invited()const;
	void set_is_invited(bool n);

	friend ostream& operator<<(ostream& os, const Citizen& a);

};

#endif