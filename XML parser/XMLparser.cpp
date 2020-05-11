#include "Node.h"
#include "XMLparser.h"

void XMLParser::create_branch(std::vector<Node>& stack) {
    int size = stack.size();
    if (size > 1) {
        Node last_node = stack.back();
        stack.pop_back();
        stack.back().add_child(last_node);
    }
    if (stack.size() == 0) {
        //error
    }
}
std::string XMLParser::generate_unique_id(std::string cur_id, std::vector<Node> all_nodes) {
    int id_suffix = 1;
    while (id_exists(cur_id + "_" + std::to_string(id_suffix), all_nodes)) {
        id_suffix++;
    };
    return (cur_id += "_" + std::to_string(id_suffix));
}
bool XMLParser::id_exists(std::string id, std::vector<Node> vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i].get_id() == id) {
            return true;
        }
    }
    return false;
}
XMLParser::XMLParser(std::string filename) {
    this->filename = filename;
    current_id = 0;
};
void XMLParser::move_to_text(std::string line, int& idx) {
    while (line[idx] == ' ' && idx < line.size() - 1) { idx++; };
}
void XMLParser::move_to_ws_or_closing_arrow(std::string line, int& idx) {
    while (line[idx] != ' ' && line[idx] != '>' && idx < line.size() - 1) {
        idx++;
    }
}
void XMLParser::move_to_endl_or_opening_arrow(std::string line, int& idx) {
    while (line[idx] != '<' && idx < line.size() - 1) {
        idx++;
    }
}
void XMLParser::move_to_euqal(std::string line, int& idx) {
    while (line[idx++] != '=' && idx < line.size() - 1);
}
void XMLParser::move_to_quote(std::string line, int& idx) {
    while (line[idx++] != '"' && idx < line.size() - 1);
}
Node XMLParser::parse() {
    this->file.open(this->filename);

    if (this->file.is_open()) {

        std::vector<Node> n_stack;
        std::vector<Node> all_nodes;

        bool in_attr_def = false;
        bool name_done = false;

        for (std::string line; getline(this->file, line);) {
            int idx = 0;

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
                        move_to_ws_or_closing_arrow(line, idx);
                        std::string name = line.substr(start, idx - start);
                        if (n_stack.back().get_name() == name) {
                            if (n_stack.back().get_id() == "") {
                                std::string id = generate_unique_id(std::to_string(current_id), all_nodes);
                                current_id++;
                                all_nodes.back().add_attribute("id", id);
                                n_stack.back().add_attribute("id", id);
                            }
                            create_branch(n_stack);
                        }
                        else {
                            throw std::invalid_argument("Closing tag mismatch!");
                        }
                    }
                    else {
                        in_attr_def = true;
                        move_to_text(line, idx);
                        int start = idx + 1;
                        move_to_ws_or_closing_arrow(line, idx);
                        std::string name = line.substr(start, idx - start);
                        if (line[idx] == '>') {
                            in_attr_def = false;
                        }

                        Node new_node(name);

                        n_stack.push_back(new_node);
                        all_nodes.push_back(new_node);
                    }
                }
                else {
                    if (in_attr_def) {
                        if (line.find('=') == -1) {
                            throw std::invalid_argument("Invalid attributes!");
                        }
                        else {
                            int start = idx;
                            move_to_euqal(line, idx);
                            std::string attr_name = line.substr(start, idx - start - 1);
                            move_to_text(line, idx);
                            if (line[idx] != '"') {
                                throw std::invalid_argument("Invalid attribute value!");
                            }
                            else {
                                idx++;
                                start = idx;
                                move_to_quote(line, idx);
                                std::string attr_value = line.substr(start, idx - start - 1);

                                if (attr_name == "id") {
                                    if (id_exists(attr_value, all_nodes)) {
                                        attr_value = generate_unique_id(attr_value, all_nodes);
                                    }
                                    n_stack.back().set_id(attr_value);
                                    all_nodes.back().set_id(attr_value);
                                }
                                n_stack.back().add_attribute(attr_name, attr_value);
                                if (line[idx] == '>') {
                                    in_attr_def = false;
                                }
                            }
                        }
                    }
                    else {
                        int start = idx;
                        move_to_endl_or_opening_arrow(line, idx);
                        if (idx == line.size() - 1) {
                            idx++;
                        }
                        std::string text = line.substr(start, idx - start);
                        n_stack.back().set_value(text + '\n');
                    }
                }
            }

        }

        return n_stack.back();
    }
}