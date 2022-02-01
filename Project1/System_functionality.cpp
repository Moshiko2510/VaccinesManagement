#include "System_functionality.h"


#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW


System_functionality::System_functionality()
{
	pq_quarantine.set_sort_method(2);
	pq_before_vaccine.set_sort_method(2);
};

System_functionality::~System_functionality()
{
	//delete q1
	for (int i = 0; i < pq_quarantine.get_size(); i++)
	{
		delete pq_quarantine.get_data()[i];
	}

	//delete q2
	for (int i = 0; i < pq_before_vaccine.get_size(); i++)
	{
		delete pq_before_vaccine.get_data()[i];
	}

	//delete citizens map
	map<int, Citizen*>::iterator citizens_itr;
	for (citizens_itr = Citizens_map.begin(); citizens_itr != Citizens_map.end(); citizens_itr++)
	{
		delete citizens_itr->second;
		//Citizens_map.erase(citizens_itr->first);
	}

	//delete users map
	map<string, User*>::iterator users_itr;
	for (users_itr = Users_map.begin(); users_itr != Users_map.end(); users_itr++)
	{
		delete users_itr->second;
		//Users_map.erase(users_itr->first);
	}
};

bool  System_functionality::create_user(int permission, string full_name, int id,string password)   //create user by hierarchy - official 1 or manager 2
{
	User* user = nullptr;
	try
	{
		if (permission == 1)
		{
			user = new Official(id, full_name, password);
		}
		else
		{
			user = new Manager(id, full_name, password);
		}

		if (user == nullptr)
		{
			throw("operation failed");
		}

		//Users_map[user->get_name()] = user;
		Users_map.insert({user->get_name(), user });
		return true;
	}
	catch (...)
	{
		cout << "operation failed" << endl;
		return false;
	}
}
		
User* System_functionality::get_user(string full_name)
{
	//map<string, User*>::iterator itr = Users_map.find(full_name);
	if (Users_map.count(full_name))
		return Users_map[full_name];
	else
	{
		cout << "Can't find this user" << endl;
		return nullptr;
	}
}

void System_functionality::delete_user(string full_name)
{
	if (Users_map.count(full_name))
	{
		delete Users_map[full_name];
		Users_map.erase(full_name);
		cout << "User deleted" << endl;
		return;
	}
	cout << "User not found" << endl;
	return;
	
}

bool System_functionality::create_Citizen(string first_name, string last_name, int id, int age, bool is_covid,string medical_history,Date quarantine, Date vaccine,bool invited)
{
	Citizen* citizen = nullptr;

	try
	{
		citizen = new Citizen(first_name, last_name, id, age, is_covid, medical_history, quarantine,vaccine,invited);
		//cout << citizen->get_End_of_quarantine();
		if (citizen == nullptr)
		{
			throw("operation failed");
		}
		citizens_count += 1;
		if (is_covid == true)										//send to quarantine					
		{
			citizen->set_vaccine(0);
			if (quarantine.get_year()==0)
			citizen->set_End_of_quarantine();
			//cout << citizen->get_End_of_quarantine();
			pq_quarantine.push(citizen);
			if(!pq_quarantine.empty())
			sort_push_by_date(pq_quarantine.get_size()-1);
			
		}
		else if (is_covid == 0 && citizen->get_is_invited()==0)													    //send to waiting
		{
			citizen->set_vaccine(0);
			pq_before_vaccine.push(citizen);
			if (!pq_before_vaccine.empty())
				sort_push_by_age(pq_before_vaccine.get_size() - 1);
		}
		else if (citizen->get_is_invited() == 1 && citizen->get_Vaccine_day().get_year()>0)				//invited and vaccinated- send to map
		{
			vaccinated_count += 1;
			citizen->set_vaccine(1);
			Citizens_map.insert({ citizen->get_id(),citizen });
		}
		else if (citizen->get_is_invited() == 1 && citizen->get_Vaccine_day().get_year() == 0)				//only invited-send to map
		{
			citizen->set_vaccine(0);
			Citizens_map.insert({ citizen->get_id(),citizen });
		}

		return true;
			
	}
	catch (...)
	{
		cout << "operation failed" << endl;
		return false;
	}
}

Citizen* System_functionality::find_citizen(int citizen_id)
{
	if (Citizens_map.count(citizen_id))
		return Citizens_map[citizen_id];
	else
	{
		for (int i = 0; i < pq_before_vaccine.get_size(); i++)
		{
			if (pq_before_vaccine.get_data()[i]->get_id() == citizen_id)
			return pq_before_vaccine.get_data()[i];
		}

		for (int i = 0; i < pq_quarantine.get_size(); i++)
		{
			if (pq_quarantine.get_data()[i]->get_id() == citizen_id)
				return pq_quarantine.get_data()[i];
		}
	}
	
		cout << "Citizen not found" << endl;
		return nullptr;
}

Citizen* System_functionality::find_citizen(string first_name,string last_name)
{
	map<int, Citizen*>::iterator citizens_itr;
	for (citizens_itr = Citizens_map.begin(); citizens_itr != Citizens_map.end(); citizens_itr++)
	{
		if (citizens_itr->second->get_first_name() == first_name && citizens_itr->second->get_last_name() == last_name)
			cout << "Citizen found" << endl;
			return citizens_itr->second;
	}

	for (int i = 0; i < pq_before_vaccine.get_size(); i++)
	{
		if (pq_before_vaccine.get_data()[i]->get_first_name() == first_name && pq_before_vaccine.get_data()[i]->get_last_name() == last_name)
			return pq_before_vaccine.get_data()[i];
	}

	for (int i = 0; i < pq_quarantine.get_size(); i++)
	{
		if (pq_quarantine.get_data()[i]->get_first_name() == first_name && pq_quarantine.get_data()[i]->get_last_name() == last_name)
			return pq_quarantine.get_data()[i];
	}
	cout<< "Citizen not found" << endl;
	return nullptr;

}

void System_functionality::show_citizen_details(int citizen_id)
{
	Citizen* citizen= find_citizen(citizen_id);
	if (citizen)
		cout << *citizen << endl;
}

void System_functionality::show_citizen_details(string first_name, string last_name)
{
	Citizen* citizen = find_citizen( first_name,  last_name);
	if (citizen)
		cout << *citizen << endl;
}

void System_functionality::show_citizens_quarantine_queue()
{
	cout << pq_quarantine.get_size() << " Citizens in quarantine:" << endl;
	for (int i = 0; i < pq_quarantine.get_size(); i++)
		cout << "ID: " << pq_quarantine.get_data()[i]->get_id() << " Name: " << pq_quarantine.get_data()[i]->get_first_name() << " " <<
		pq_quarantine.get_data()[i]->get_last_name() << endl << "End of quarantine date: " << pq_quarantine.get_data()[i]->get_End_of_quarantine() << endl << endl;
}

void System_functionality::show_citizens_waiting_queue()
{
	cout << pq_before_vaccine.get_size() << " Citizens waiting for vaccine:" << endl;
	for (int i = 0; i < pq_before_vaccine.get_size(); i++)
		cout << "ID: " << pq_before_vaccine.get_data()[i]->get_id() << " Name: " << pq_before_vaccine.get_data()[i]->get_first_name() << " " <<
		pq_before_vaccine.get_data()[i]->get_last_name() << endl << endl;
}

void System_functionality::show_citizens_map()
{
	cout << "There are " << vaccinated_count << " citizans vaccinated:"<<endl;
	map<int, Citizen*>::iterator citizens_itr;
	for (citizens_itr = Citizens_map.begin(); citizens_itr != Citizens_map.end(); citizens_itr++)
	{

		if(citizens_itr->second->get_Vaccine_day().get_year()>0)
		cout << "ID: " << citizens_itr->first << " Name: " << citizens_itr->second->get_first_name() << " " << citizens_itr->second->get_last_name() << endl;
	}
	cout << endl;
	
}

void System_functionality::show_Users_map()
{
	cout << "There are " << Users_map.size() << " registered users:" << endl;
	map<string, User*>::iterator users_itr;
	for (users_itr = Users_map.begin(); users_itr != Users_map.end(); users_itr++)
	{
		cout  << users_itr->first << endl;
	}
	cout << endl;
}

void  System_functionality::show_Percentage_of_vaccinated()
{
	cout << "We already have " << vaccinated_count << " out of " << citizens_count << " citizens vaccinated." << endl
		<< "Total of: " << (double)((double)vaccinated_count / (double)citizens_count) * 100 << "%" << endl;
}

void System_functionality::sort_push_by_date(int index)//for q1
{
	int cmp_ndx = index - 1;
	if (index > 0 && pq_quarantine.get_data()[index]->get_End_of_quarantine().get_day_number() < pq_quarantine.get_data()[cmp_ndx]->get_End_of_quarantine().get_day_number())
	{
		pq_quarantine.swap(pq_quarantine.get_data()[index], pq_quarantine.get_data()[cmp_ndx]);
		index -= 1;
		sort_push_by_date(index);
	}
}

void System_functionality::sort_pop_by_date(int index)//for q1
{
	int cmp_ndx = index + 1;
	if (index < pq_quarantine.get_size() - 1 && pq_quarantine.get_data()[index]->get_End_of_quarantine().get_day_number() > pq_quarantine.get_data()[cmp_ndx]->get_End_of_quarantine().get_day_number())
	{
		pq_quarantine.swap(pq_quarantine.get_data()[index], pq_quarantine.get_data()[cmp_ndx]);
		index += 1;
		sort_pop_by_date(index);
	}
}

void System_functionality::sort_push_by_age(int index) //for q2
{
	
	int cmp_ndx = index - 1;
	if ((index > 0) && (pq_before_vaccine.get_data()[index]->get_age() > pq_before_vaccine.get_data()[cmp_ndx]->get_age()))
	{
		pq_before_vaccine.swap(pq_before_vaccine.get_data()[index], pq_before_vaccine.get_data()[cmp_ndx]);
		index -= 1;
		sort_push_by_age(index);
	}
}

void System_functionality::sort_pop_by_age(int index)  //for q2
{
	int cmp_ndx = index + 1;
	if (index < pq_before_vaccine.get_size() - 1 && pq_before_vaccine.get_data()[index]->get_age() < pq_before_vaccine.get_data()[cmp_ndx]->get_age())
	{
		pq_before_vaccine.swap(pq_before_vaccine.get_data()[index], pq_before_vaccine.get_data()[cmp_ndx]);
		index += 1;
		sort_pop_by_age(index);
	}
}

bool System_functionality::change_queue_priority(int citizen_id) //give priority to selected citizen and insert to citizens map-- manager operation
{
	for (int i = 0; i < pq_before_vaccine.get_size(); i++)
		if (pq_before_vaccine.get_data()[i]->get_id() == citizen_id)
		{
			//if(i!= pq_before_vaccine.get_size() - 1)
			//pq_before_vaccine.swap(pq_before_vaccine.get_data()[i], pq_before_vaccine.get_data()[pq_before_vaccine.get_size() - 1]);
			Citizen* cp = pq_before_vaccine.pop(i);
			cp->set_is_invited(1);
			//cp->get_Vaccine_day().set_today_date();
			Citizens_map.insert({ cp->get_id(),cp });
			sort_pop_by_age(i);
			cout << "Citizen "<<cp->get_first_name()<<" "<<cp->get_last_name()<<" invited for vaccine" << endl;
			return true;
		}
	cout << "Can't find citizen" << endl;
	return false;
}

bool System_functionality::is_quarantine_over() //if yes pop from q1 and push to q2-- official and manager operation
{
	Date today;
	today.set_today_date();
	if (pq_quarantine.get_data()[0]->get_End_of_quarantine() < today)
	{
		Citizen* cw = pq_quarantine.get_data()[0];
		//cw->get_End_of_quarantine().restart_date();
		//cout<< cw->get_End_of_quarantine()<<endl;
		cout << pq_quarantine.get_data()[0]->get_first_name() << " " << pq_quarantine.get_data()[0]->get_last_name() << " quarantine period is over" << endl;
		pq_quarantine.get_data()[0]->get_End_of_quarantine().restart_date();
		pq_quarantine.get_data()[0]->set_Is_covid(0);
		pq_before_vaccine.push(pq_quarantine.pop(0));
		sort_pop_by_date(0);
		sort_push_by_age(pq_before_vaccine.get_size() - 1);
		
		return true;
	}
	else
		cout << pq_quarantine.get_data()[0]->get_first_name() << " " << pq_quarantine.get_data()[0]->get_last_name() << " quarantine period is not over" << endl;
		return false;
}

bool System_functionality::call_for_vaccine()  //pop from q2 and insert to map--   official and manager operation
{
	try
	{
		if (pq_before_vaccine.empty())
		{
			cout << "All citizens were invited" << endl;
			return false;
		}
		Citizen* cp = pq_before_vaccine.pop(0);
		sort_pop_by_age(0);
		cp->set_is_invited(1);
		Citizens_map.insert({ cp->get_id(),cp });
		cout << "Citizen " << cp->get_first_name() << " " << cp->get_last_name() << " invited for vaccine" << endl;
		return true;
	}
	catch (...)
	{
		cout << "operation failed" << endl;
		return false;
	}
}

bool System_functionality::do_vaccine(int id)
{
	Citizen* citizen = find_citizen(id);
	if (citizen && citizen->get_Vaccine_day().get_year()==0 && citizen->get_vaccine() == 0&& citizen->get_is_invited()==1)
	{
		citizen->set_Vaccine_day();
		citizen->set_vaccine(1);
		vaccinated_count += 1;
		return true;
	}
	else if (citizen && citizen->get_Vaccine_day().get_year() >0 && citizen->get_vaccine() == 1)
	{
		cout << "You are already vaccinated" << endl;
		return false;
	}
	else
	{
		cout << "Please be patient, we will call you soon" << endl;
		return false;
	}

		
}

bool System_functionality::save_users(const string& file_name)
{
	map<string, User*>::iterator users_itr;
	try
	{
		ofstream myfile(file_name);
		if (!myfile.good())
		{
			throw "can't create file";
		}
		//myfile << "Existing users in the system: " << endl;
		for (users_itr = Users_map.begin(); users_itr != Users_map.end(); users_itr++)
		{
			myfile << users_itr->first <<" "<< users_itr->second->get_id()<<" "<< users_itr->second->get_Password()<<" "<< users_itr->second->get_Level_of_permissions() << endl;
		}
		myfile.close();
		return true;
	}
	catch(...)
	{
		cout << "cant create file" << endl;
		return false;
	}
}

bool System_functionality::save_citizens_database(const string& file_name)
{
	map<int, Citizen*>::iterator citizens_itr;
	try
	{
		ofstream myfile(file_name);
		if (!myfile.good())
		{
			throw "cant create file";

		}
		
		for (citizens_itr = Citizens_map.begin(); citizens_itr != Citizens_map.end(); citizens_itr++)
		{
			myfile  << citizens_itr->second->get_first_name() << " " << citizens_itr->second->get_last_name() <<" "
				<< citizens_itr->second->get_id()  << " " << citizens_itr->second->get_age() << " " << citizens_itr->second->get_covid()<<" "<< citizens_itr->second->get_medical_history()<<
				" "<< citizens_itr->second->get_End_of_quarantine().get_day()<<"/"<< citizens_itr->second->get_End_of_quarantine().get_month() << "/" << citizens_itr->second->get_End_of_quarantine().get_year()
				<<" "<< citizens_itr->second->get_Vaccine_day().get_day() << "/" << citizens_itr->second->get_Vaccine_day().get_month() << "/" << citizens_itr->second->get_Vaccine_day().get_year() <<" "<< citizens_itr->second->get_is_invited()<<endl;
		}

		for (int i = 0; i < pq_quarantine.get_size(); i++)
		{
			myfile << pq_quarantine.get_data()[i]->get_first_name() << " " << pq_quarantine.get_data()[i]->get_last_name() << " "
				<< pq_quarantine.get_data()[i]->get_id() << " " << pq_quarantine.get_data()[i]->get_age() << " " << pq_quarantine.get_data()[i]->get_covid() << " " << pq_quarantine.get_data()[i]->get_medical_history() <<
				" " << pq_quarantine.get_data()[i]->get_End_of_quarantine().get_day() <<"/"<< pq_quarantine.get_data()[i]->get_End_of_quarantine().get_month() << "/" << pq_quarantine.get_data()[i]->get_End_of_quarantine().get_year()<<
				" " << pq_quarantine.get_data()[i]->get_Vaccine_day().get_day() << "/" << pq_quarantine.get_data()[i]->get_Vaccine_day().get_month() << "/" << pq_quarantine.get_data()[i]->get_Vaccine_day().get_year()<<" "<< pq_quarantine.get_data()[i]->get_is_invited() << endl;
		}

		for (int i = 0; i < pq_before_vaccine.get_size(); i++)
		{
			myfile << pq_before_vaccine.get_data()[i]->get_first_name() << " " << pq_before_vaccine.get_data()[i]->get_last_name() << " "
				<< pq_before_vaccine.get_data()[i]->get_id() << " " << pq_before_vaccine.get_data()[i]->get_age() << " " << pq_before_vaccine.get_data()[i]->get_covid() << " " << pq_before_vaccine.get_data()[i]->get_medical_history() <<
				" " << pq_before_vaccine.get_data()[i]->get_End_of_quarantine().get_day() << "/" << pq_before_vaccine.get_data()[i]->get_End_of_quarantine().get_month() << "/" << pq_before_vaccine.get_data()[i]->get_End_of_quarantine().get_year() <<
				" " << pq_before_vaccine.get_data()[i]->get_Vaccine_day().get_day() << "/" << pq_before_vaccine.get_data()[i]->get_Vaccine_day().get_month() << "/" << pq_before_vaccine.get_data()[i]->get_Vaccine_day().get_year() << " " << pq_before_vaccine.get_data()[i]->get_is_invited() << endl;
		}

		myfile.close();
		return true;
	}
	catch (...)
	{
		cout << "cant create file" << endl;
		return false;
	}
}

bool System_functionality::save_citizens_quarantine_queue(const string& file_name)
{
	try
	{
		ofstream myfile(file_name);
		if (!myfile.good())
		{
			throw "cant create file";
		}
		myfile << "Citizens in quarantine: " << endl;
		for (int i = 0; i < pq_quarantine.get_size(); i++)
		{
			myfile << "Name: " << pq_quarantine.get_data()[i]->get_first_name() << " " << pq_quarantine.get_data()[i]->get_last_name() << endl
				<< "ID: " << pq_quarantine.get_data()[i]->get_id() << endl << "Age: " << pq_quarantine.get_data()[i]->get_age() <<endl<<"End of quarantine: " 
				<< pq_quarantine.get_data()[i]->get_End_of_quarantine().get_day() << "/" << pq_quarantine.get_data()[i]->get_End_of_quarantine().get_month() << "/" << pq_quarantine.get_data()[i]->get_End_of_quarantine().get_year()<< endl << endl;
		}
		myfile.close();
		return true;
	}
	catch (...)
	{
		cout << "cant create file" << endl;
		return false;
	}
}

bool System_functionality::save_citizens_waiting_queue(const string& file_name)
{
	try
	{
		ofstream myfile(file_name);
		if (!myfile.good())
		{
			throw "cant create file";

		}
		myfile << "Citizens waiting for vaccine: " << endl;
		for (int i = 0; i < pq_before_vaccine.get_size(); i++)
		{
			myfile << "Name: " << pq_before_vaccine.get_data()[i]->get_first_name() << " " << pq_before_vaccine.get_data()[i]->get_last_name() << endl
				<< "ID: " << pq_before_vaccine.get_data()[i]->get_id() << endl << "Age: " << pq_before_vaccine.get_data()[i]->get_age() << endl <<endl;
		}
		myfile.close();
		return true;
	}
	catch (...)
	{
		cout << "cant create file" << endl;
		return false;
	}
}

bool System_functionality::save_citizens_map(const string& file_name)
{
	map<int, Citizen*>::iterator citizens_itr;
	try
	{
		ofstream myfile(file_name);
		if (!myfile.good())
		{
			throw "cant create file";
			
		}
		myfile << "Citizens map: " << endl;
		for (citizens_itr = Citizens_map.begin(); citizens_itr != Citizens_map.end(); citizens_itr++)
		{
			myfile << "Name: " << citizens_itr->second->get_first_name() << " " << citizens_itr->second->get_last_name() << endl
				<< "ID: " << citizens_itr->second->get_id() << endl << "Age: " << citizens_itr->second->get_age() << endl <<endl;
		}
		myfile.close();
		return true;
	}
	catch (...)
	{
		cout << "cant create file" << endl;
		return false;
	}

}

bool System_functionality::load_users(const string& file_name)
{
	string line, name,password;
	int id, permission;
	ifstream myfile(file_name);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			istringstream iss(line);
			iss >> name >> id >> password>> permission;
			if (Users_map.count(name))
				continue;
			create_user(permission, name, id,password);
		}
		myfile.close();
		cout << "Users loaded successfully" << endl;
		return true;
	}
	else
	{
		cout << "Unable to open file"<<endl;
		return false;
	}
}

bool System_functionality::load_citizens(const string& file_name) //before any sort
{
	string line, first_name, last_name, medical_history, date_q,date_v;
	int id, is_covid,age,invited;
	char c;
	
	Date quarantine,vaccine;
	ifstream myfile(file_name);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string day, month, year;
			string day2, month2, year2;
			int date_cnt = 0;
			int date_cnt2 = 0;
			istringstream iss(line);
			iss >> first_name>> last_name  >> id >> age >> is_covid>> medical_history>> date_q>> date_v>> invited;

			for (int i = 0; i < date_q.length(); i++)
			{
				if (date_q[i] != '/' && date_cnt == 0)
					day+= date_q[i];
				else if (date_q[i] != '/' && date_cnt == 1)
					month+= date_q[i];
				else if (date_q[i] != '/' && date_cnt == 2)
					year+= date_q[i];

				if (date_q[i] == '/')
					date_cnt += 1;

			}

			quarantine.set_day(stoi(day));
			quarantine.set_month(stoi(month));
			quarantine.set_year(stoi(year));
			quarantine.set_day_number();

			for (int i = 0; i < date_v.length(); i++)
			{
				if (date_v[i] != '/' && date_cnt2 == 0)
					day2 += date_v[i];
				else if (date_v[i] != '/' && date_cnt2 == 1)
					month2 += date_v[i];
				else if (date_v[i] != '/' && date_cnt2 == 2)
					year2 += date_v[i];

				if (date_v[i] == '/')
					date_cnt2 += 1;

			}

			vaccine.set_day(stoi(day2));
			vaccine.set_month(stoi(month2));
			vaccine.set_year(stoi(year2));
			vaccine.set_day_number();
			create_Citizen( first_name,  last_name,  id,  age,  is_covid,  medical_history, quarantine,vaccine, invited);
		}
		myfile.close();
		cout << "Citizens loaded successfully" << endl;
		return true;
	}
	else
	{
		cout << "Unable to open file" << endl;
		return false;
	}
	
}