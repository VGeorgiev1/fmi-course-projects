#ifndef XML_H
#define XML_H
#include <string>
#include <fstream>
#include <stack>
#include "Node.h"
#include "./Operations/headers/Operation.h"

class XMLParser {
private:
    std::vector<Operation*> operations;
    int current_id;
    Node* parent_node;
    bool operatable;
    void create_branch(std::stack<Node*>& stack);
    bool id_exists(std::string const &id, Node* node);
    void move_to_text(std::string line, int& idx);
    void move_to_symbol(std::string& line, int& idx,const char* symbols, int symbols_lenght);
    std::string generate_unique_id(std::string& cur_id);
    void delete_nodes(Node* parent);
    void remove_children(Node* node);
    void generate_ids(Node* node);
public:
    XMLParser();
    ~XMLParser();
    void print_recursion(int tabs, std::ostream& stream, Node* node);
    Node* get_parent();
    void set_operatable(bool state);
    bool is_operatable();
    void add_operation(Operation* op);
    Operation* find_operation(std::string name);
    void remove_nodes();
    Node* parse(std::string name);
    void print(std::ostream& stream);

    Node* const& recursive_search(Node* const& n, std::string id);
};
#endif