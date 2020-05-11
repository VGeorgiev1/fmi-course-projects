#include<stdio.h>
#include<iostream>
#include<string>
#include <vector>
#include <fstream>
#include "Node.h"
#include "XMLparser.h"

using namespace std;



void print_tree(Node vec) {
    if (!vec.has_children()) {
        return;
    }
    vector<Node> childs = vec.get_children();

    for (int i = 0; i < childs.size(); i++) {
        cout << childs[i].get_name() << endl;
        vector<Attribute> attrs = childs[i].get_attributes();
        for (int i = 0; i < attrs.size(); i++) {
            cout << attrs[i].get_name() << " = " << attrs[i].get_value() << endl;
        }
        cout << childs[i].get_value() << endl;
        print_tree(childs[i]);
    }

}
int main() {
    XMLParser xml("text.xml");

    Node parent = xml.parse();

    print_tree(parent);
}