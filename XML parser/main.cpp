#include<stdio.h>
#include<iostream>
#include<string>
#include <vector>
#include <fstream>
#include "Node.h"
#include "XMLparser.h"
#include "Operations/Operations.h"
#include "XMLException.h"

using namespace std;


int main() {
    XMLParser xml;

    Node* parent = xml.get_parent();

    xml.add_operation(new Select(xml));
    xml.add_operation(new XPATH(xml));
    xml.add_operation(new Select(xml));
    xml.add_operation(new Set(xml));
    xml.add_operation(new Childn(xml));
    xml.add_operation(new Children(xml));
    xml.add_operation(new Text(xml));
    xml.add_operation(new Delete(xml));
    xml.add_operation(new Newchild(xml));
    xml.add_operation(new XPATH(xml));

    xml.add_operation(new Open(xml));
    xml.add_operation(new Print(xml));
    xml.add_operation(new Save(xml));
    xml.add_operation(new Saveas(xml));
    xml.add_operation(new Close(xml));
    xml.add_operation(new Help(xml));

    std::string op_name;

    while(op_name != "exit") {

        std::cin >> op_name;

        Operation* op = xml.find_operation(op_name);

        if (op_name != "open" && !xml.is_operatable()) {
            continue;
        }

        if(op != nullptr) {
            try {
                op->execute();
            }
            catch (XMLException err) {
                std::cout << err.what() <<std::endl;
            }
        }

    }
}