#include "Node.h"
#include "XMLparser.h"

void XMLParser::create_branch(std::vector<Node*>& stack) {
    int size = stack.size();
    if (size > 1) {
        Node* last_node = stack.back();
        stack.pop_back();
        stack.back() -> add_child(last_node);
    }
    if (stack.size() == 0) {
        //error
    }
}
std::string XMLParser::generate_unique_id(std::string cur_id, std::vector<Node*> all_nodes) {
    int id_suffix = 1;
    while (id_exists(cur_id + "_" + std::to_string(id_suffix), all_nodes)) {
        id_suffix++;
    };
    return (cur_id += "_" + std::to_string(id_suffix));
}
void XMLParser::print(std::ostream& stream) {
    print_recursion(0, stream);
};

void XMLParser::print_recursion(int tabs, std::ostream& stream) {
    for (int i = 0; i < tabs; i++) {
        stream << '\t';
    }

    stream << '<' << parent_node->get_name();

    std::vector<Attribute> atrs = parent_node->get_attributes();

    for (std::vector<Attribute>::iterator it = atrs.begin(); it != atrs.end(); ++it) {
        stream << ' ' << it->get_name() << "=" << "\"" << it->get_value() << "\"";
    }

    stream << "> ";

    if (parent_node->get_value() == "") {
        stream << std::endl;
    }
    else {
        stream << parent_node->get_value().substr(0, parent_node->get_value().size() - 1);
    }

    if (!parent_node->has_children()) {
        stream << "<\/" << parent_node->get_name() << ">" << std::endl;
        return;
    }

    std::vector<Node*> children = parent_node->get_children();


    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        print_recursion(tabs + 1, stream);
    }

    for (int i = 0; i < tabs; i++) {
        stream << '\t';
    }

    stream << "</" << parent_node->get_name() << ">" << std::endl;
};


bool XMLParser::id_exists(std::string id, std::vector<Node*> vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i]->get_id() == id) {
            return true;
        }
    }
    return false;
}
XMLParser::XMLParser() {
    parent_node = nullptr;
    current_id = 0;
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
        delete* it;
    }
}
void XMLParser::move_to_text(std::string line, int& idx) {
    while (line[idx] == ' ' && idx < line.size() - 1) { idx++; };
}
void XMLParser::move_to_symbol(std::string line, int& idx,const char* symbols,  int symbols_lenght) {
    bool break_loop = false;

    while (idx < line.size() - 1) {
        for(int i = 0;i < symbols_lenght; i++) {
           if(line[idx] == symbols[i]) {
                break_loop = true;
                break;
           }
        }
        if(break_loop) {
            break;
        };
        idx++;
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

void XMLParser::remove_nodes() {
    remove_children(parent_node);
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
    std::ifstream file;

    file.open(name);


    if (!file.is_open()) {
        throw std::invalid_argument("File cannot be opened!");
    }

    int idx = 0;
    std::vector<Node*> n_stack;
    std::vector<Node*> all_nodes;

    bool in_attr_def = false;
    bool name_done = false;

    for (std::string line; getline(file, line);) {
        int idx = 0;
        if (line.size() == 0) continue;

        while (idx < line.size() - 1) {
            move_to_text(line, idx);
            if (line[idx] == '>') {
                in_attr_def = false;
                idx++;
            }

            if (line[idx] == '<') {
                if (line[idx + 1] == '/') {
                    idx++;
                    int start = idx + 1;
                    move_to_symbol(line, idx, " >", 2);
                    std::string name = line.substr(start, idx - start);

                    if (n_stack.back()->get_name() != name) {
                        throw std::invalid_argument("Closing tag mismatch!");
                    }

                    if (n_stack.back()->get_id() == "") {
                        std::string id = generate_unique_id(std::to_string(current_id), all_nodes);
                        current_id++;
                        all_nodes.back()->set_id(id);
                        n_stack.back()->set_id(id);
                        n_stack.back()->add_attribute("id", id);
                    }
                    create_branch(n_stack);
                }
                else {
                    in_attr_def = true;
                    move_to_text(line, idx);
                    int start = idx + 1;
                    move_to_symbol(line, idx, " >", 2);
                    std::string name = line.substr(start, idx - start);
                    if (line[idx] == '>') {
                        in_attr_def = false;
                    }
                    Node* new_node = new Node(name);

                    n_stack.push_back(new_node);
                    all_nodes.push_back(new_node);
                }
            }
            else {
                if (in_attr_def) {
                    if (line.find('=') == -1) {
                        throw std::invalid_argument("Invalid attributes!");
                    }
                    int start = idx;
                    move_to_symbol(line, idx, "=", 1);
                            
                    std::string attr_name = line.substr(start, idx - start);
                    move_to_symbol(line, idx, "\"", 1);
                    if (line[idx] != '"') {
                        throw std::invalid_argument("Invalid attribute value!");
                    }
                    idx++;
                    start = idx;
                    move_to_symbol(line, idx, "\"", 1);

                    std::string attr_value = line.substr(start, idx - start);
                    if (attr_name == "id") {
                        if (id_exists(attr_value, all_nodes)) {
                            attr_value = generate_unique_id(attr_value, all_nodes);
                        }
                        n_stack.back()->set_id(attr_value);
                        all_nodes.back()->set_id(attr_value);
                    }
                    n_stack.back()->add_attribute(attr_name, attr_value);
                    if (line[idx + 1] == '>') {
                        in_attr_def = false;
                    }
                    idx++;
                }
                else {
                    int start = idx;
                    move_to_symbol(line, idx, "<", 1);
                    if (idx == line.size()) {
                        idx++;
                    }
                    std::string text = line.substr(start, idx - start);
                    n_stack.back()->set_value(text + '\n');
                }
            }
        }
    }

    parent_node = n_stack.back();
    return parent_node;
}