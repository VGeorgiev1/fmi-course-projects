#include "XPath.h"
#include <iostream>
#include <sstream>

XPATH::XPATH(Node* h)
	: XMLOperation(h, "xpath") {};

void XPATH::execute() {
	std::string query;

	std::cin >> query;
    std::string token;

    std::stringstream str(query);

    std::vector<std::string> tokens;

    while (std::getline(str, token, '/'))
    {
        tokens.push_back(token);
    }
    std::vector<Node*> results;

    xpath_recursive_search(parent_node, tokens.begin(), tokens.end(), INT_MAX, results);

    for (std::vector<Node*>::iterator it = results.begin(); it != results.end(); ++it) {
        std::cout << (*it)->get_name() << " " << (*it)->get_id();
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

    int prop_start = current_name.find('(');
    int prop_end = current_name.find(')');

    std::string props;

    if (prop_start != std::string::npos) {
        props = current_name.substr(prop_start + 1, prop_start - prop_end);

        if (props[0] == '@') {

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