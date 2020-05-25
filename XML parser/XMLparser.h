#ifndef XML_H
#define XML_H
#include <string>
#include <fstream>
#include "Node.h"
#include "Operation.h"
class XMLParser {
private:
    std::string filename;
    std::ifstream file;
    std::vector<Operation*> operations;
    int current_id;
    void create_branch(std::vector<Node>& stack);
    bool id_exists(std::string id, std::vector<Node> vec);
    void move_to_text(std::string line, int& idx);
    void move_to_symbol(std::string line, int& idx,const char* symbols, int symbols_lenght);
    std::string generate_unique_id(std::string cur_id, std::vector<Node> all_nodes);
public:
    void add_operation(Operation* op);
    Operation* get_operation(std::string name);
    XMLParser(std::string filename);
    Node parse();
};
#endif