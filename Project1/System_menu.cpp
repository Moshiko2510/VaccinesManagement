#include "System_menu.h"

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include "symbolics.h"
#include "utils.h"


System_menu::System_menu(System_functionality* vacc):Vacc(vacc)
{
	user = nullptr;
	today.set_today_date();
}

System_menu::~System_menu()
{

}

void System_menu::display_date()
{
	cout << today << endl;
}

void System_menu::Manager_menu()
{
	while (true)
	{
		int manager_selection,id;
		string name;
		system("cls");
		display_date();
		cout << setfill('*') << setw(15) << "*" << endl;
		cout << setfill('*') << setw(11) << " Manager menu" << setfill('*') << setw(11) << endl;
		cout << setfill('*') << setw(15) << "*" << endl << endl << endl;
		cout << "Choose an option: " << endl;
		cout << "1.  Invite for vaccine" << endl;
		cout << "2.  Set end of quarantine" << endl;
		cout << "3.  Show citizen details" << endl;
		cout << "4.  Show citizens in quarantine" << endl;
		cout << "5.  Show citizens waiting for vaccine" << endl;
		cout << "6.  Show vaccinated citizens" << endl;
		cout << "7.  Display results" << endl;
		cout << "8.  Invite specific citizen for vaccine" << endl;
		cout << "9.  Delete user" << endl;
		cout << "10. Show existing users" << endl;
		//cout << "11. Load/Save data" << endl;
		cout << "11. Sign out" << endl<<endl;

		cout << "Your selection is: ";
		cin >> manager_selection;
		switch (manager_selection)
		{
		case 1:
			Vacc->call_for_vaccine();
			system("PAUSE");
			break;
		case 2:
			Vacc->is_quarantine_over();
			system("PAUSE");
			break;
		case 3:

			search_screen();
			system("PAUSE");
			break;
		case 4:
			Vacc->show_citizens_quarantine_queue();
			system("PAUSE");
			break;
		case 5:
			Vacc->show_citizens_waiting_queue();
			system("PAUSE");
			break;
		case 6:
			Vacc->show_citizens_map();
			system("PAUSE");
			break;
		case 7:
			Vacc->show_Percentage_of_vaccinated();
			system("PAUSE");
			break;
		case 8:
			cout << "Enter citizen id: ";
			cin >> id;
			Vacc->change_queue_priority(id);
			system("PAUSE");
			break;
		case 9:
			cout << "Enter user name to delete: ";
			cin >> name;
			Vacc->delete_user(name);
			system("PAUSE");
			break;
		case 10:
			Vacc->show_Users_map();
			system("PAUSE");
			break;
		case 11:
			system("cls");
			save_data();
			sign_out();
			system("PAUSE");
			break;
		}
		if (manager_selection == 11)
		{
				break;
		}
	}
}

void System_menu::search_screen()
{
	while (true)
	{
		int selection,id;
		string first_name,last_name;
		system("cls");
		display_date();
		cout << setfill('*') << setw(16) << "*" << endl;
		cout << setfill('*') << setw(11) << " Search citizen" << setfill('*') << setw(11) << endl;
		cout << setfill('*') << setw(16) << "*" << endl << endl << endl;
		cout << "Choose an option: " << endl;
		cout << "1. Search by name" << endl;
		cout << "2. Search by ID" << endl;
		cout << "3. Previous screen" << endl << endl;
		cout << "Your selection is: ";
		cin >> selection;
		switch (selection)
		{
		case 1:
			cout << "Enter first and last name: ";
			cin >> first_name>>last_name;
			Vacc->show_citizen_details(first_name,last_name);
 			system("PAUSE");
			break;
		case 2:
			cout << "Enter citizen id: ";
			cin >> id;
			Vacc->show_citizen_details(id);
			system("PAUSE");
			break;
		case 3:
			//Manager_menu();
			break;
		}
		if (selection == 3)
			break;
	}
}


void System_menu::save_data()
{
	system("cls");
	cout << "Saving data...please wait" << endl<<endl;
	cout << "Save citizens map..." ;
	if (Vacc->save_citizens_map("citizens_map.txt"))
		cout << "Map saved!" << endl;
	else
		cout << "Saving failed" << endl;
	if(Vacc->save_citizens_quarantine_queue("citizens_quarantine.txt"))
		cout << "Quarantine list saved!" << endl;
	else
		cout << "Saving failed" << endl;
	if(Vacc->save_citizens_waiting_queue("citizens_waiting.txt"))
		cout << "Waiting list saved!" << endl;
	else
		cout << "Saving failed" << endl;
	if(Vacc->save_citizens_database("citizens.txt"))
		cout << "Citizens database saved!" << endl << endl;
	else
		cout << "Saving failed" << endl;
	cout << "Save users map..." ;
	if(Vacc->save_users("users_map.txt"))
		cout << "Map saved!" << endl<<endl;
	else
		cout << "Saving failed" << endl;
	cout << "All data has been saved" << endl<<endl;

}

void System_menu::Official_menu()
{
	while (true)
	{
		int official_selection,id;
		system("cls");
		display_date();
		cout << setfill('*') << setw(16) << "*" << endl;
		cout << setfill('*') << setw(11) << " Official menu" << setfill('*') << setw(11) << endl;
		cout << setfill('*') << setw(16) << "*" << endl << endl << endl;
		cout << "Choose an option: " << endl;
		cout << "1. Invite for vaccine" << endl;
		cout << "2. Set end of quarantine" << endl;
		cout << "3. Show citizen details" << endl;
		cout << "4. Show citizens in quarantine" << endl;
		cout << "5. Show citizens waiting for vaccine" << endl;
		cout << "6. Show vaccinated citizens" << endl;
		cout << "7. Display results" << endl;
		cout << "8. Sign out" << endl<<endl;
		cout << "Your selection is: ";
		cin >> official_selection;
		switch (official_selection)
		{
		case 1:
			Vacc->call_for_vaccine();
			system("PAUSE");
			break;
		case 2:
			Vacc->is_quarantine_over();
			system("PAUSE");
			break;
		case 3:
			search_screen();
			system("PAUSE");
			break;
		case 4:
			Vacc->show_citizens_quarantine_queue();
			system("PAUSE");
			break;
		case 5:
			Vacc->show_citizens_waiting_queue();
			system("PAUSE");
			break;
		case 6:
			Vacc->show_citizens_map();
			system("PAUSE");
			break;
		case 7:
			Vacc->show_Percentage_of_vaccinated();
			system("PAUSE");
			break;
		case 8:
			save_data();
			sign_out();
			system("PAUSE");
			//entering_screen();
			break;

		}
		if (official_selection == 8)
		{
			//exit_system();
				break;
		}
	}
}

int System_menu::sign_in(int cnt)
{
	if (cnt == 4)
	{
		cout << "too many attempts, try again later" << endl;
		system("PAUSE");
		return 3;
	}
	system("cls");
	string name, password;
	int pass_cnt = 0;
	cout << "Hello, please sign in to continue:" << endl;
	cout << "User name: ";
	cin >> name;
	if (Vacc->get_user(name))
	{
		cout << endl << "Enter password: ";
		
		while (pass_cnt <= 3)
		{
			if (pass_cnt == 3)
			{
				cout << "too many attempts, try again later" << endl;
				system("PAUSE");
				return 3;
			}
			cin >> password;
			if (Vacc->get_user(name)->get_Password() == password)
			{
				cout << endl << "You are now logged in as " << name << ", redirecting to main menu..." << endl;
				system("PAUSE");
				user = Vacc->get_user(name);
				break;
			}
			else
			{
				pass_cnt++;
				if (pass_cnt == 3)
					cout << "Wrong password!" << endl;
				else
				cout << endl << "Wrong password, try again: "<<endl;
				//system("PAUSE");
			}
		}

		if (user->get_Level_of_permissions() == 1)
			return 1;
		else return 2;
	}
	else
	{
		if (cnt == 3)
		{
			cout << "Wrong user name!" << endl;
			return sign_in(++cnt);
		}
		else
		cout << endl << "Wrong user name, try again"<<endl;
		system("PAUSE");
		return sign_in(++cnt);
	}
}

void System_menu::sign_out()
{
	user = nullptr;
	cout << "You are now disconnected, redirecting to main menu..." << endl;
}

void System_menu::exit_system()
{
	
	if(user)
		cout << "Have a nice day " << endl<<endl;
	else
	cout << "Good bye! "<<endl<<endl;
}

int System_menu::guest_selection()
{
	int select,user_select=0;
	cout << "Please choose an option:" << endl;
	cout << "1. It's my Vaccine day" << endl;
	cout << "2. Sign in" << endl;
	cout << "3. Exit" << endl << endl;;
	cout << "Your selection is: ";
	cin >> select;
	if (select == 2)
	{
		user_select = sign_in(1);
	}

	if (user_select == 3)
		return 5;
	else if (user_select == 2)
		return 3;
	else if(user_select == 1)
		return 2;

	if (select == 3)
		return 4;
	else if (select == 1)
		return 1;
	else
		return 5;
}

void System_menu::citizen_menu()
{
	system("cls");
	int id;
	cout << "Please enter your ID: ";
	cin >> id;
	if (Vacc->do_vaccine(id))
	{
		cout << "Thank you, have a nice day" << endl;
		system("PAUSE");
	}
	else
	{
		system("PAUSE");
	}
}

void System_menu::entering_screen()
{
	while (1)
	{
	system("cls");
	setcolor(BLACK, WHITE);
	int selection = 0;
	display_date();
	cout << endl;
	setcolor(BLACK, WHITE);
	cout << setfill('*') << setw(25) << "*" << endl;
	cout << setfill('*') << setw(11) << "Vaccines Managment System" << setfill('*') << setw(11) << endl;
	cout << setfill('*') << setw(25) << "*" << endl << endl << endl;
		selection = guest_selection();
		switch (selection)
		{
		case 1:
			citizen_menu();
			break;
		case 2:
			Official_menu();
			break;
		case 3:
			Manager_menu();
			break;
		case 4:
			//exit_system();
			break;
		case 5:
			break;
		}
		if (selection == 4)
		{
			//system("cls");
			save_data();
			exit_system();
				break;
		}
	}
}