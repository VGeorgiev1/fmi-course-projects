#include "../headers/XPath.h"
#include <iostream>
#include <sstream>

XPATH::XPATH(XMLParser& xml)
	: XMLOperation(xml, "xpath") {};

void XPATH::execute() {
	std::string query;

    std::getline(std::cin, query);
    query = query.substr(1);
    
    std::string token;

    std::stringstream str(query);

    std::vector<std::string> tokens;

    while (std::getline(str, token, '/'))
    {
        tokens.push_back(token);
    }
    std::vector<Node*> results;

    xpath_recursive_search(xml.get_parent(), tokens.begin(), tokens.end(), INT_MAX, results);

    for (std::vector<Node*>::iterator it = results.begin(); it != results.end(); ++it) {
        xml.print_recursion(0, std::cout, (*it));
    }
}

void XPATH::xpath_recursive_search(Node* const& n, std::vector<std::string>::iterator next, std::vector<std::string>::iterator end, int index_of_results, std::vector<Node*>& results) {

	std::string current_name = *next;

    int idx = INT_MAX;


    int idx_start = current_name.find('[');
    int idx_end = current_name.find(']');
    if (idx_start != std::string::npos) {
        idx = std::stoi(current_name.substr(idx_start + 1, idx_end - idx_start));
        if (index_of_results != idx) return;
    };

    int cut_idx = idx_start == std::string::npos ? n->get_name().size() : idx_start;

    if (n->get_name() != current_name.substr(0, cut_idx)) return;


    std::vector<Attribute> attrs;

    int prop_start = current_name.find('(') + 1;
    int prop_end = current_name.find(')');

    std::vector<Attribute> atrs;
    if (prop_start != std::string::npos) {

        int cursor = prop_start;

        while (cursor < prop_end) {
            int cursor_start = cursor;

            if (current_name[cursor] != '@') {
                throw std::invalid_argument("XPath is wrong!");
            }

            cursor++;

            while (current_name[cursor] != '=' && current_name[cursor] != ')' && current_name[cursor] != ' ') {
                cursor++;
            }

            std::string atr_name = current_name.substr(cursor_start + 1, cursor - cursor_start - 1);

            char end = current_name[cursor];
            if (end != '=' && cursor != current_name.size() - 1) {
                throw std::invalid_argument("XPath is wrong!");
            }

            if (cursor == current_name.size()) break;
            cursor++;


            if (end != '=') {
                atrs.push_back(Attribute(atr_name, ""));
                continue;
            }


            int atr_value_start = cursor;

            while (current_name[cursor] != ')' && current_name[cursor] != ' ') {
                cursor++;
            }

            std::string atr_value = current_name.substr(atr_value_start, cursor - atr_value_start);

            atrs.push_back(Attribute(atr_name, atr_value));
            cursor++;
        }

    }

    if (atrs.size() != 0) {
        for (std::vector<Attribute>::iterator it = atrs.begin(); it != atrs.end(); ++it) {
            Attribute* atr = n->get_attribute(it->get_name());

            if (atr == nullptr) {
                return;
            }

            if (it->get_value() != "" && atr->get_value() != it->get_value()) {
                return;
            }
        }
    }

    if (next + 1 == end) {
        results.push_back(n);
    }
    next += 1;

    if (next == end) {
        return;
    }

    if (!n->has_children()) {
        return;
    }


    std::vector<Node* > children = n->get_children();

    int cur_idx = 0;

    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        xpath_recursive_search((*it), next, end, cur_idx, results);
        cur_idx++;
    }

}