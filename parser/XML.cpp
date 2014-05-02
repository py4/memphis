#include "XML.h"
#include <iostream>
using namespace std;

XML::XML()
{
	root_node = new Node("root");
	root_node->parent = root_node;
	current_node = root_node;
}

XML::~XML()
{
	cout << "destructor of XML" << endl;
	delete_node(root_node);
}

void XML::delete_node(Node* node)
{
	for(int i = 0; i < node->children.size(); i++)
		delete_node(node->children[i]);
	node->children.clear();
	node->attributes.clear();
	delete node;
}

void XML::load(string file_name)
{
	delete_node(root_node);
	root_node = new Node("root");
	current_node = root_node;
	raw_data.open(file_name.c_str());
}

void XML::parse()
{
	string line;
	int depth = 0;
	while(getline(raw_data,line))
	{
		trim(line);
		if(is_tag(line))
		{
			current_node->add_node(get_tag_name(line));
			current_node = current_node->children.back();
			map <string,string> result = get_attributes(line);
			current_node->set_attributes(result);
			depth++;
		}
		else if(is_closing_tag(line))
		{
			current_node = current_node->parent;
			depth--;
		}
		else if(line.length() > 0)
			current_node->set_value(line);
	}
}

string XML::dump()
{
	return root_node->dump();
}

Node* XML::get_node(string name)
{
	return root_node->get_child_node(name);
}

Node* XML::operator[](string name)
{
	return get_node(name);
}


