#include "parser.h"
#include <sstream>
#include <iostream>
#include "../responder/responder.h"
using namespace std;

/* http://codereview.stackexchange.com/a/40158 */
void trim(string & str)
{
	const string whitespace = " \t\f\v\n\r";
	int start = str.find_first_not_of(whitespace);
	int end = str.find_last_not_of(whitespace);

	if(start == -1 or end == -1)
		str = "";
	else
	{
		str.erase(0,start);
		str.erase((end - start) + 1);
	}
}

map <string,string> parse_book(string line)
{
	istringstream in(line);
	string temp;
	map <string,string> result;
	string keys[4] = { "name", "author", "publisher", "year" };

	for(int i = 0; i < 4 and getline(in,temp,'/'); i++)
		result[keys[i]] = temp;

	return result;
}

string get_value_of_tag(string line)
{
	bool c = false;
	int first_index = 0, second_index = 0;
	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == '<')
		{
			c = true;
			first_index = i;
		}
		if(c)
		{
			if(line[i] == '>')
			{
				c = false;
				second_index = i;
				line.erase(line.begin()+first_index,line.begin()+second_index+1);
			}
		}	
	}

		return line;
}

string get_shelf_name(string line)
{
	string name;
	if(line.substr(0,6) == "<shelf")
	{
		for(int i = 13; i < line.length(); i++)
		{
			if(line[i] == '"')
				break;
			name += line[i];
		}
	}

	return name;
}

bool is_tag(string line)
{
	if(line[0] == '<' and line[1] != '/' and *(line.end()-1) == '>')
		return true;
	return false;
}

bool is_closing_tag(string line)
{
	if(line[0] == '<' and line[1] == '/' and *(line.end()-1) == '>')
		return true;
	return false;
}

string get_tag_name(string line)
{
	string result = "";
	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == '<' or line[i] == '/' or line[i] == '>')
			continue;
		if(line[i] != ' ')
			result += line[i];
		else
			break;
	}
	return result;
	
}

map<string,string> get_attributes(string line)
{
	bool check = false;
	string temp;
	map <string,string> result;
	stringstream in;
	
	for(int i = 0; i < line.length(); i++)
	{
		if(!check)
		{
			if(line[i] == ' ')
			{
				check = true;
			}
		}
		else
			in << line[i];
	}

	string key,value;
	for(int i = 0; getline(in,temp,'='); i++)
	{
		if(i % 2 == 0)
			key = temp;
		else
		{
			temp.erase(temp.begin());
			temp.erase(temp.end()-2,temp.end());
			result[key] = temp;
		}
	}
	return result;
}

string get_depth_tabs(int depth)
{
	string result = "";
	for(int i = 0; i < depth; i++)
		result += '\t';
	return result;
}

string get_command_name(string line)
{
	stringstream in(line);
	string temp;
	getline(in,temp,' ');
	return temp;
}

map <string,string> get_sign_up_params(string line)
{
	stringstream in(line);
	string temp, keys[] = {"username","password"};
	map <string,string> result;
	for(int i = 0; getline(in,temp,' '); i++)
	{
		if(i == 0)
			continue;
		if(i > 1)
			RespondTo::Failure::bad_input();
		else
			result[keys[i]] = temp;
	}
	return result;
}

void set_login_params(map<string,string>& params, string command)
{
	stringstream in(command);
	string temp;
	for(int i = 0; getline(in,temp,' '); i++)
	{
		if(i > 2)
			throw RespondTo::Failure::bad_input();
		if(i == 1)
			params["username"] = temp;
		if(i == 2)
			params["password"] = temp;
	}
}

void set_params(map<string,string>& params, string command)
{
	params.clear();
	stringstream in(command);
	string temp;

	getline(in,temp,' ');
	params["command"] = temp;
	
	if(temp == "register")
		set_login_params(params,command);
}




