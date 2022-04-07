#include <iostream>
#include "pugixml.hpp"

using namespace std;
using namespace pugi;

int main(){
	xml_document doc;
	// load the XML file
	if (!doc.load_file("sample.xml")) return -1;

	xml_node tools = doc.child("Database").child("Table");

	for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
	{
		cout << "Columns:";

		for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
		{
			cout << " " << ait->name() << "=" << ait->value();
		}
		cout << endl;
	}
	cout << endl;
   
	return 0;
}
