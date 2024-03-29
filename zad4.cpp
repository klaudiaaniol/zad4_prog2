#include "pch.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include<ctime>


using namespace std;

class Chempion
{

public:
	static vector<Chempion*> Team;

	Chempion(string us, vector<int>ch_vec)

	{
		first_Name = us.substr(0, ch_vec[0]);
		last_Name = us.substr(ch_vec[0] + 1, ch_vec[1] - ch_vec[0] - 1);
		height = stoi(us.substr(ch_vec[1] + 1));
		skills.push_back("Attack");
		skills.push_back("Hiding");
		skills.push_back("Sneaking");
		skills.push_back("Just Power");
		skills.push_back("Offensive");

		Team.push_back(this);
	}

	Chempion(string first_ch, string last_ch, int weight_ch, int height_ch)
	{
		first_Name = first_ch; //firstname
		last_Name = last_ch;  //lastname
		//weight = weight_ch;
		height = height_ch;
		skills.push_back("Attack");
		skills.push_back("Hiding");
		skills.push_back("Sneaking");
		skills.push_back("Just Power");
		skills.push_back("Offensive");

		Team.push_back(this);
	}

	Chempion(const Chempion &ch_const)
	{
		first_Name = ch_const.first_Name;
		last_Name = ch_const.last_Name;
		height = ch_const.height;
		skills = ch_const.skills;
	}

	string write_first_Name()
	{
		return first_Name;
	}

	string write_last_Name()
	{
		return last_Name;
	}

	int write_height()
	{
		return height;
	}

	void change_last_Name(string last)//lastname
	{
		last_Name = last;
	}
	void change_first_Name(string first) //firstname
	{
		first_Name = first;
	}
	void change_height(int h) //height
	{
		height = h;
	}
	void change_weight(int wei)//weight
	{
		height = wei;
	}

	void add_Skill(string s)//skill
	{
		skills.push_back(s);
	}

	string showInfo()
	{
		//ostringstream we;
		//we << weight;
		ostringstream he;
		he << height;
		string skillsToReturn = "\n";

		for (int i = 0; i < skills.size(); i++)
		{
			skillsToReturn += skills[i] + "\n";
		}

		return "Chempion list : " + first_Name + " " + last_Name + "\nheight: " + he.str() + "\nskills: " + skillsToReturn;

	}

private:
	int height;
	string first_Name;
	string last_Name;
	vector<string>skills;

};

vector<Chempion*> Chempion::Team;

class Team
{
	static int max_player_in_teamfight;
	static int created_team;
	string team_name;

public:

	vector<Chempion*> player_in_team;
	Team(string t)
	{
		team_name = t;

		for (int i = (created_team * 5); i < max_player_in_teamfight + (5 * created_team); i++) {
			player_in_team.push_back(Chempion::Team[i]);
		}
		created_team++;
	}

	Team(string t, ifstream& f)
	{

		string text_line;
		vector<int> parametrs;
		team_name = t;



		while (getline(f, text_line))
		{
			for (int i = 0; i < text_line.length(); i++)
			{

				if (text_line[i] == ';')
				{
					parametrs.push_back(i);
				}
			}

			Chempion *p = new Chempion(text_line, parametrs);
			player_in_team.push_back(p);
			parametrs.clear();
		}
		created_team++;
	}


	Team(const Team &t)
	{
		team_name = t.team_name;
		player_in_team = t.player_in_team;
	}

	void change_team_name(string tn)
	{
		team_name = tn;
	}

	string t_info()
	{
		string return_to;
		return_to += team_name + "! \nPlayers: ";

		for (int i = 0; i < player_in_team.size(); i++)
		{
			return_to += "\n" + player_in_team[i]->write_first_Name() + " " + player_in_team[i]->write_last_Name();
		}

		return return_to;
	}

	void write_doc()
	{
		string seconds;
		string minutes;
		string hour;
		time_t now = time(0);
		tm *time = localtime(&now);

		if (stoi(to_string(time->tm_hour)) < 10)
		{
			hour = "0" + to_string(time->tm_hour);
		}
		else
		{
			hour = to_string(time->tm_hour);
		}

		if (stoi(to_string(time->tm_min)) < 10)
		{
			minutes = "0" + to_string(time->tm_min);
		}
		else
		{
			minutes = to_string(time->tm_min);
		}

		if (stoi(to_string(time->tm_sec)) < 10)
		{
			seconds = "0" + to_string(time->tm_sec);
		}
		else
		{
			seconds = to_string(time->tm_sec);
		}

		ofstream f;
		string file_name = "druzyna" + team_name + hour + minutes + seconds + ".txt";
		f.open(file_name);

		for (int i = 0; i < (player_in_team.size()); i++)
		{
			f << player_in_team[i]->write_first_Name() + ":" << player_in_team[i]->write_last_Name() + ":" + to_string(player_in_team[i]->write_height()) + "\n";
		}
	}


};

int Team::max_player_in_teamfight = 5;
int Team::created_team = 0;

int main()
{

	Chempion p1("Tony", "Stark", 90, 190);
	Chempion p2("Virginia Pepper", "Potts", 103, 199);
	Chempion p3("James", "Rhodes", 79, 176);
	Chempion p4("Howard", "Stark", 89, 189);
	Chempion p5("Bruce", "Banner", 120, 204);
	Chempion p6("Natasha", "Romanoff", 102, 187);
	Chempion p7("Ho", "Yinsen", 115, 193);
	Chempion p8("J.A.R", "V.I.S", 91, 189);
	Chempion p9("Nick", "Fury", 92, 193);
	Chempion p10("Anton", "Vanko", 88, 178);
	

	Team team_1("Team fight I");
	Team team_2("Team fight II");
	Team team_3 = team_2;
	team_3.change_team_name("Team fight III");

	ifstream file("chempionsIV.txt");
	Team team_4("Team IV", file);

	cout << team_1.t_info() << endl << endl;
	cout << team_2.t_info() << endl << endl;
	cout << team_3.t_info() << endl;
	cout << team_4.t_info() << endl;

	cout << team_1.t_info() << endl << endl;
	cout << team_2.t_info() << endl << endl;
	cout << team_3.t_info() << endl << endl;
	cout << team_4.t_info() << endl << endl;

	team_1.write_doc();
	team_2.write_doc();
	team_3.write_doc();
	team_4.write_doc();

	return 0;
}