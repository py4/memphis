#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <map>
#include <vector>

using namespace std;
class Node
{
	friend class XML;
public:
	Node();
	Node(string, string = "");
	void add_node(Node*);
	void add_node(string, string = "");
	string operator[](string);
  vector<Node*>& get_children();
	Node* get_parent();
	void set_attribute(string,string);
	void set_attributes(map<string,string>&);
	void set_value(string);
	string dump();
	
	Node* get_child_node(string);
private:
	string name;
	map <string,string> attributes;
	vector <Node*> children;
	Node* parent;
	string value;
};
#endif
