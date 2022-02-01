#ifndef _SYSTEM_FUNCTIONALITY_H_
#define _SYSTEM_FUNCTIONALITY_H_

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include<iostream>
#include<string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>  
using namespace std;

#include "User.h"
#include "Citizen.h"
#include "PriorityQueue.h"




//************************System_functionality************************
class System_functionality
{
private:

	int citizens_count = 0;
	int vaccinated_count = 0;

	//Users map 
	map<string, User*> Users_map;

	//Citizens quarantine queue before Vaccine- priority by quarantine days
	PriorityQueue<Citizen*> pq_quarantine;

	//Citizens queue before Vaccine- priority by age
	PriorityQueue<Citizen*> pq_before_vaccine;

	//Citizens map after Vaccine
	map<int, Citizen*> Citizens_map;

public:

	System_functionality(); //Ctor
	~System_functionality(); //Dtor

	bool create_user(int permission, string full_name, int id,string password);   //create user by hierarchy - official or manager
	User* get_user(string full_name);
	void delete_user(string full_name);

	
	bool create_Citizen(string first_name, string last_name, int id, int age, bool is_covid, string medical_history,Date quarantine, Date vaccine,bool invited);
	Citizen* find_citizen(int citizen_id);
	Citizen* find_citizen(string first_name, string last_name);

	void show_citizen_details(int citizen_id);
	void show_citizen_details(string first_name, string last_name);
	void show_citizens_quarantine_queue();
	void show_citizens_waiting_queue();
	void show_citizens_map();
	void show_Users_map();
	void show_Percentage_of_vaccinated();

	//queue sorting methods
	void sort_push_by_date(int index);   //for q1
	void sort_pop_by_date(int index);	 //for q1
	void sort_push_by_age(int index);	 //for q2
	void sort_pop_by_age(int index);	 //for q2

	bool do_vaccine(int id);								   //for citizen who wants to vaccine
	bool change_queue_priority(int citizen_id);			      //insert to q2--  manager operation
	bool is_quarantine_over();		  						 //if yes pop from q1 and push to q2-- official and manager operation
	bool call_for_vaccine();		 						//pop from q2 and insert to map--   official and manager operation
	 
	//Serialization/Deserialization
	bool save_users(const string& file_name);									//users map
	bool save_citizens_quarantine_queue(const string& file_name);				//quarantine_queue
	bool save_citizens_waiting_queue(const string& file_name);					//waiting_queue
	bool save_citizens_map(const string& file_name);							//citizens map
	bool save_citizens_database(const string& file_name);						//citizens database

	bool load_users(const string& file_name);
	bool load_citizens(const string& file_name);							
	
};

#endif