#ifndef XML_H
#define XML_H
#include <string>
#include <fstream>
#include "Node.h"
#include "Operation.h"
class XMLParser {
private:
    std::vector<Operation*> operations;
    int current_id;
    Node* parent_node;
    bool operatable;
    void create_branch(std::vector<Node*>& stack);
    bool id_exists(std::string id, std::vector<Node*> vec);
    void move_to_text(std::string line, int& idx);
    void move_to_symbol(std::string line, int& idx,const char* symbols, int symbols_lenght);
    std::string generate_unique_id(std::string cur_id, std::vector<Node*> all_nodes);
    void delete_nodes(Node* parent);
    void remove_children(Node* node);
    void print_recursion(int tabs, std::ostream& stream);
public:
    Node* get_parent();
    void set_operatable(bool state);
    bool is_operatable();
    void add_operation(Operation* op);
    Operation* find_operation(std::string name);
    void remove_nodes();
    XMLParser();
    ~XMLParser();
    Node* parse(std::string name);
    void print(std::ostream& stream);
};
#endif