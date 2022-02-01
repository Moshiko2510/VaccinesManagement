#include "User.h"

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW



//************************User************************

User::User(int id, string full_name, string password) :m_Id(id), m_Full_name(full_name),m_Password(password){}
User::~User(){}

int User::get_id() const
{
	return m_Id;
}

const string& User::get_name() const
{
	return m_Full_name;
}

const string& User::get_Password() const
{
	return m_Password;
}

const int User::get_Level_of_permissions() const
{
	return m_Level_of_permissions;
}



//************************Manager************************
Manager::Manager(int id, string full_name,string password) :User(id, full_name,password)
{
	
}

Manager ::~Manager(){}

const int Manager::get_Level_of_permissions() const
{
	return m_Level_of_permissions;
}


//************************Official************************
Official::Official(int id, string full_name, string password) :User(id, full_name,password){}

Official ::~Official(){}

const int Official::get_Level_of_permissions() const
{
	return m_Level_of_permissions;
}