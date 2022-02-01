#ifndef _SYSTEM_MENU_H_
#define _SYSTEM_MENU_H_

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

#include "User.h"
#include "Citizen.h"
#include "System_functionality.h"


class System_menu
{
private:
	System_functionality* Vacc;
	User* user;
	Date today;

public:
	System_menu(System_functionality* vacc);
	~System_menu();

	void display_date();
	void Manager_menu();
	void Official_menu();
	void entering_screen();
	int sign_in(int cnt);
	int guest_selection();
	void sign_out();
	void citizen_menu();
	void search_screen();
	void save_data();
	void exit_system();

};
#endif