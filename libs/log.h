#ifndef LOG_H_
#define LOG_H_

#include <string>
using namespace std;

class Log
{
public:
	Log();
Log(string u, string m) : username(u) , message(m) {}
	string username;
	string message;
};

#endif
