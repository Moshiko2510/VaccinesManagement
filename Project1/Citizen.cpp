#include "Citizen.h"
#include <bits.h>

Citizen::Citizen(string first_name, string last_name, int id, int age, bool is_covid, string medical_history, Date quarantine, Date vaccine, bool invited): m_First_name(first_name),
m_Last_name(last_name), m_Id(id),m_Age(age), m_Is_covid(is_covid), m_Medical_history(medical_history), m_End_of_quarantine(quarantine), m_Vaccine_day(vaccine), m_Invited(invited)
{
	//m_Vaccine_day.restart_date();
	//m_End_of_quarantine.restart_date();
}

Citizen::Citizen() {};

Citizen::~Citizen() {}; 


const string& Citizen::get_first_name()  const
{
	return m_First_name;
}

const string& Citizen::get_last_name()   const
{
	return m_Last_name;
}

int Citizen::get_id() const
{
	return m_Id;
}

int Citizen::get_age() const
{
	return m_Age;
}

Date Citizen::get_Vaccine_day() const
{
	return m_Vaccine_day;
}

Date Citizen::get_End_of_quarantine() const
{
	return m_End_of_quarantine;
}

bool Citizen::get_covid()const
{
	return m_Is_covid;
}

bool Citizen::get_vaccine()const
{
	return m_Vaccine;
}

void Citizen::set_Is_covid(bool n)
{
	m_Is_covid = n;
}

bool Citizen::get_is_invited()const
{
	return m_Invited;
}

void Citizen::set_is_invited(bool n)
{
	m_Invited = n;
}

void Citizen::set_vaccine(bool n)
{
	m_Vaccine = n;
}

void Citizen::set_Vaccine_day()
{
	m_Vaccine_day.set_today_date();
}

void Citizen::set_End_of_quarantine()
{
	m_End_of_quarantine.set_today_date();
	m_End_of_quarantine.calc_end_of_quarantine();
}

void Citizen::show_medical_history()
{
	cout<< m_Medical_history <<endl;    
}

string Citizen::get_medical_history() const
{
	return m_Medical_history;
}

ostream& operator<<(ostream& os, const Citizen& a)
{
	string covid;
	string vaccine;
	if (a.m_Is_covid == true)
		covid = "positive";
	else covid = "negative";

	cout <<"Name: "<< a.m_First_name<<" " <<a.m_Last_name<< endl<<"ID: "<< a.m_Id<<endl << "Age: " << a.m_Age << endl <<
		"Covid test: " << covid << endl << "Medical_history: " << a.m_Medical_history << endl << "Vaccine date: " << a.m_Vaccine_day << endl<<endl;
	return os;
}