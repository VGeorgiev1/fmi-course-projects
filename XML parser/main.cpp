#include<stdio.h>
#include<iostream>
#include<string>
#include <vector>
#include <fstream>
#include "Node.h"
#include "XMLparser.h"
#include "Select.h"
#include "XPath.h"
#include "Print.h"

using namespace std;


int main() {
    XMLParser xml;

    Node* parent = xml.get_parent();

    xml.add_operation(new Select(parent));
    xml.add_operation(new XPATH(parent));


    xml.add_operation(new Print(xml));

    while(true) {
        std::string op_name;

        std::cin >> op_name;

        Operation* op = xml.find_operation(op_name);

        if (op_name != "open" && !xml.is_operatable()) {
            continue;
        }

        if(op != nullptr) {
            op->execute();
        }

    }
}