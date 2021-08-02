#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <map>

struct Node {
    int val;
    std::vector<Node*> childs;
};

void val_swap(Node* left, Node* right) {
    int val_left = left->val;
    left->val = right->val;
    right->val = val_left;
}

void roots_swap(Node* left, Node* right) {
    std::vector<Node*> min_vector;
    if (left->childs.size() > right->childs.size()) {
        min_vector = right->childs;
        right->childs = left->childs;
        left->childs = min_vector;
    }
    else {
        min_vector = left->childs;
        left->childs = left->childs;
        right->childs = min_vector;
    }

}
void exercise1() {
    std::map<int, std::vector<std::pair<int, int>>> matrix;

    int N, M;
    std::string line;
    std::cout << "Enter N (columns): " << std::endl;
    std::cin >> N;
    std::cout << "Enter M (rows): " << std::endl;
    std::cin >> M;
    std::cin.ignore();
    while (std::getline(std::cin, line)) {
        std::istringstream input(line);

        int c_idx, r_idx, val;

        input >> c_idx >> r_idx >> val;

        if (c_idx >= N) {
            std::cout << "Invalid column index!" << std::endl;
        }

        if (r_idx >= M) {
            std::cout << "Invalid row index!" << std::endl;
        }

        std::pair<int, int> idx_pair = { r_idx, val };

        matrix[val].push_back(idx_pair);
    }

    for (std::map<int, std::pair<int, int>>::const_iterator it = matrix.begin(); it != matrix.end(); ++it) {
        
    }
}
int main()
{
    std::string line;
    
    Node* cur_root = new Node();
    std::vector<Node*> previous_childs = { cur_root };
    std::vector<Node*> next_childs;

    exercise1();
    while (line != "stop") {
        std::getline(std::cin, line);

        int idx = 0;

        int start_token_idx = idx;
        int end_token_idx = idx;
        int prev_child_idx = 0;

        std::vector<Node*> current_children;

        while (idx != line.size()) {
            if (line[idx] != ' ') {
                end_token_idx++;
            }

            if (line[idx] == ' ' || idx + 1 == line.size()) {
                std::string token = line.substr(start_token_idx, end_token_idx - start_token_idx);
                start_token_idx = end_token_idx + 1;
                end_token_idx = start_token_idx;
                if(token != "|") {
                    int numeric_val;
                    try {
                        numeric_val = std::stoi(token);
                        Node* node = new Node({ std::stoi(token), std::vector<Node*>() });
                        current_children.push_back(node);
                        next_childs.push_back(node);
                    }
                    catch (std::invalid_argument err) {
                        std::cout << "Ivalid node data!" << std::endl;
                        break;
                    }
                }
                if (token == "|" || idx + 1 == line.size()) {

                    if (previous_childs.size() <= prev_child_idx) {
                        std::cout << "Invalid structure!" << std::endl;
                        break;
                    }

                    previous_childs[prev_child_idx]->childs = current_children;
                    current_children.clear();
                    prev_child_idx++;
                }
            }
            idx++;
        }
        previous_childs = next_childs;
        next_childs.clear();
    }
    std::cout << "Done parsing!" << std::endl;
}
