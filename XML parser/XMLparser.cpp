#include "Node.h"
#include "XMLparser.h"
#include "XMLParserException.h"

void XMLParser::create_branch(std::stack<Node*>& stack) {
    int size = stack.size();
    if (size > 1) {
        Node* last_node = stack.top();
        stack.pop();
        stack.top() -> add_child(last_node);
    }
    if (stack.size() == 0) {
        throw XMLParserException("Parsing error!");
    }
}

Node* const& XMLParser::recursive_search(Node* const& n, std::string id) {
    if (n == nullptr) {
        return nullptr;
    }
    
    if (n->get_id() == id) {
        return n;
    }
    if (!n->has_children()) {
        return nullptr;
    }
    std::vector<Node* > children = n->get_children();
    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        Node* temp = recursive_search((*it), id);

        if (temp != nullptr) {
            return temp;
        }
    }
    return nullptr;
}

void XMLParser::print(std::ostream& stream) {
    print_recursion(0, stream, parent_node);
};

void XMLParser::print_recursion(int tabs, std::ostream& stream, Node* node) {
    for (int i = 0; i < tabs; i++) {
        stream << '\t';
    }

    stream << '<' << node->get_name();

    std::vector<Attribute> atrs = node->get_attributes();

    for (std::vector<Attribute>::iterator it = atrs.begin(); it != atrs.end(); ++it) {
        stream << ' ' << it->get_name() << "=" << "\"" << it->get_value() << "\"";
    }

    stream << "> ";

    if (node->get_value() == "") {
        stream << std::endl;
    }
    else {
        stream << node->get_value();
    }

    if (!node->has_children()) {
        stream << "<\/" << node->get_name() << ">" << std::endl;
        return;
    }

    std::vector<Node*> children = node->get_children();


    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        print_recursion(tabs + 1, stream, (*it));
    }

    for (int i = 0; i < tabs; i++) {
        stream << '\t';
    }

    stream << "</" << node->get_name() << ">" << std::endl;
};

XMLParser::XMLParser() {
    parent_node = nullptr;
    current_id = 0;
    operatable = false;
};

void XMLParser::delete_nodes(Node* parent) {
    if (!parent->has_children()) {
        return;
    }

    std::vector<Node* > children = parent->get_children();

    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        delete_nodes((*it));
    }

    delete parent;
};

XMLParser::~XMLParser() {
    for (std::vector<Operation*>::iterator it = operations.begin(); it != operations.end(); ++it) {
        delete *it;
    }
    operations.clear();

    remove_nodes();
}

void XMLParser::move_to_text(std::string line, int& idx) {
    while ((line[idx] == ' ' || line[idx] == '\t' || line[idx] == '\n') && idx < line.size() - 1) { idx++; };
}
void XMLParser::move_to_symbol(std::string& line, int& idx,const char* symbols,  int symbols_lenght) {
    bool break_loop = false;
    bool move_text = true;


    while (idx < line.size() - 1) {
        for(int i = 0;i < symbols_lenght; i++) {
            if(line[idx] == symbols[i]) {
                if (line[idx] == ' ') {
                    move_text = false;
                }
                break_loop = true;
                break;
            }
        }
        if(break_loop) {
            break;
        };
        idx++;
    }
    
    if (move_text) {
        move_to_text(line, idx);
    }
}

void XMLParser::add_operation(Operation* op) {
    operations.push_back(op);
}

Operation* XMLParser::find_operation(std::string name) {
    for(std::vector<Operation*>::iterator it = operations.begin(); it != operations.end(); ++it) {
       if((*it)->get_name() == name) {
           return *it;
       }
    }
    return nullptr;
}

void XMLParser::remove_children(Node* node) {

    if (node == nullptr) {
        return;
    }

    if (!node->has_children()) {
        return;
    }

    std::vector<Node*> children = node->get_children();

    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        remove_children(*it);
        delete* it;
    }


    children.clear();
 
}

std::string XMLParser::generate_unique_id(std::string& cur_id) {
    int id_suffix = 1;
    std::string current = cur_id + "_" + std::to_string(id_suffix);
    while (id_exists(current, parent_node)) {
        id_suffix++;
    };
    return (cur_id += "_" + std::to_string(id_suffix));
}

bool XMLParser::id_exists(std::string const &id, Node* node) {

    Node* search = recursive_search(parent_node, id);

    return search != nullptr && node != search;
}

void XMLParser::generate_ids(Node* node) {

    if (node->get_id() == "") {
        while (id_exists(std::to_string(current_id), node)) {
            current_id++;
        }
        node->set_id(std::to_string(current_id));
    }
    else if(id_exists(node->get_id(), node)) {
        int id_suffix = 1;

        while (id_exists(node->get_id() + "_" + std::to_string(id_suffix), node)) {
            id_suffix++;
        }
        node->set_id(node->get_id() + "_" + std::to_string(id_suffix));
    }

    if (!node->has_children()) {
        return;
    }

    std::vector<Node*> children = node->get_children();

    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        generate_ids((*it));
    }

    
}

void XMLParser::remove_nodes() {
    remove_children(parent_node);
    if (parent_node != nullptr) {
        delete parent_node;
        parent_node = nullptr;
    }
};

Node* XMLParser::get_parent() {
    return parent_node;
}

bool XMLParser::is_operatable(){
    return operatable;
}

void XMLParser::set_operatable(bool state) {
    operatable = state;
}

Node* XMLParser::parse(std::string name) {
    std::fstream file;

    file.open(name, std::ios::in);


    if (!file.is_open()) {
        file.open(name, std::fstream::out | std::fstream::in | std::fstream::trunc);

        if (!file.is_open()) {
            throw XMLParserException("File cannot be created or opened opened!");
        }

        std::cout << "File " << name << "was created!" << std::endl;
        return nullptr;
    }

    if (file.peek() == std::fstream::traits_type::eof()) {
        parent_node == nullptr;
        return parent_node;
    }

    int idx = 0;
    std::stack<Node*> n_stack;

    bool in_attr_def = false;
    bool name_done = false;

    parent_node = nullptr;
    std::string line;

    while(getline(file, line)) {
        int idx = 0;
        if (line.size() == 0) continue;

        while (idx < line.size() - 1) {
            move_to_text(line, idx);
            if (line[idx] == '>') {
                in_attr_def = false;
                idx++;
            }

            if (line[idx] == '<') {
                move_to_text(line, idx);
                if (line[idx + 1] == '/') {
                    idx++;
                    int start = idx + 1;
                    move_to_symbol(line, idx, " >", 2);
                    std::string name = line.substr(start, idx - start);

                    if (n_stack.top()->get_name() != name) {
                        throw XMLParserException("Closing tag mismatch!");
                    }
                    create_branch(n_stack);
                    continue;
                }

                in_attr_def = true;
                move_to_text(line, idx);

                int start = idx + 1;
                move_to_symbol(line, idx, " >", 2);

                std::string name = line.substr(start, idx - start);
                if (line[idx] == '>') {
                    in_attr_def = false;
                }

                Node* new_node = new Node(name);

                n_stack.push(new_node);

                continue;
            }
           
            if (in_attr_def) {


                if (line.find('=') == -1) {
                    throw XMLParserException("Invalid attributes!");
                }

                int start = idx;
                move_to_symbol(line, idx, "=", 1);
                std::string attr_name = line.substr(start, idx - start);
                
                move_to_symbol(line, idx, "\"", 1);
                if (line[idx] != '"') {
                    throw XMLParserException("Invalid attribute value!");
                }

                idx++;
                start = idx;

                move_to_symbol(line, idx, "\"", 1);

                std::string attr_value = line.substr(start, idx - start);

                if (attr_name == "id") {
                    n_stack.top()->set_id(attr_value);
                }
                //else {
                n_stack.top()->add_attribute(attr_name, attr_value);
                //}

                move_to_text(line, idx);
                if (line[idx + 1] == '>') {
                    in_attr_def = false;
                }
                idx++;
                continue;
            }

            int start = idx;
            move_to_symbol(line, idx, "<", 1);
            if (idx == line.size()) {
                idx++;
            }

            std::string text = line.substr(start, idx - start);
            n_stack.top()->set_value(text);

        }
    }


    if (n_stack.size() > 1) {
        throw XMLParserException("Parsing error!");
    }

    parent_node = n_stack.top();

    generate_ids(parent_node);

    return parent_node;
}