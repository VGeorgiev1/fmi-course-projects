#ifndef XML_H
#define XML_H
#include <string>
#include <fstream>
#include "Node.h"
class XMLParser {
private:
    std::string filename;
    std::ifstream file;
    int current_id;
    void create_branch(std::vector<Node>& stack);
    bool id_exists(std::string id, std::vector<Node> vec);
    void move_to_text(std::string line, int& idx);
    void move_to_ws_or_closing_arrow(std::string line, int& idx);
    void move_to_endl_or_opening_arrow(std::string line, int& idx);
    void move_to_euqal(std::string line, int& idx);
    void move_to_quote(std::string line, int& idx);
    std::string generate_unique_id(std::string cur_id, std::vector<Node> all_nodes);
public:
    XMLParser(std::string filename);
    Node parse();
};
#endif