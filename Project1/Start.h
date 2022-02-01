#ifndef START_H
#define START_H

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include "symbolics.h"
#include "utils.h"
#include <string>
#include <iostream>
using namespace std;

#include "framework.h"

#include "System_functionality.h"
#include "System_menu.h"



void start()
{
	setcolor(0, 15);
	System_functionality* vacc = new System_functionality();
	try
	{
		bool x=0, y=0;
		x=vacc->load_users("Users_map.txt");
		y=vacc->load_citizens("citizens.txt");
		if (x == false || y == false)
			throw "unexpected error";
		System_menu system(vacc);
		system.entering_screen();
	}
	catch (...)
	{
		cout << "unexpected error" << endl;
	}

	delete vacc;
}

#endif


