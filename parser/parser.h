#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <string>

using namespace std;

map <string,string> parse_book(string);
string get_value_of_tag(string);
string get_shelf_name(string);

bool is_tag(string);
bool is_closing_tag(string);
string get_tag_name(string);
map <string,string> get_attributes(string);


void trim(string&);
#endif
