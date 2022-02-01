#ifndef _USER_H_
#define _USER_H_

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include<iostream>
#include<string>
using namespace std;


#define USER_PERMISSION	 0
#define OFFICIAL_PERMISSION	 1
#define MANAGER_PERMISSION	 2


//************************User************************
class User
{
protected:
	const int m_Level_of_permissions = USER_PERMISSION;
	const string m_Full_name;		
	const int m_Id;				
	const string m_Password;

public:
	User(int id, string full_name, string password); //Ctor
	virtual ~User() = 0; //Dtor

	int get_id() const;
	const string& get_name() const;
	const string& get_Password() const;
	virtual const int get_Level_of_permissions() const=0;

};


//************************Manager************************
class Manager : public User
{
private:
	const int m_Level_of_permissions = MANAGER_PERMISSION;
public:
	Manager(int id, string full_name, string password); //Ctor
	~Manager(); //Dtor

	const int get_Level_of_permissions() const;

};


//************************Official************************
class Official : public User
{
private:
	const int m_Level_of_permissions = OFFICIAL_PERMISSION;
public:
	Official(int id, string full_name, string password); //Ctor
	~Official(); //Dtor

	const int get_Level_of_permissions() const;

};

#endif