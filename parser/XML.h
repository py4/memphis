#ifndef XML_H_
#define XML_H_

#include <fstream>
#include <string>
#include "parser.h"

class Node;

class XML
{
public:
	XML();
	~XML();
	void load(std::string);
	void parse();
	string dump();

	Node* operator[](string);
	Node* get_node(string);
private:
	std::ifstream raw_data;
	Node* root_node;
	Node* current_node;

	void delete_node(Node*);

	void dump_node(Node*,string&);
};
#endif
