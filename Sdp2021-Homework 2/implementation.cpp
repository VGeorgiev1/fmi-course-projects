#include "interface.h"
#include <iostream>

int Hierarchy::num_overloaded(int level = 10) const {
   return level;
};
Hierarchy::Hierarchy(Hierarchy&& r) noexcept
{
    ceo = r.ceo;
    number_of_employyes = r.number_of_employyes;
}
Hierarchy::Hierarchy(const Hierarchy& r) {
    ceo = r.ceo;
    number_of_employyes = r.number_of_employyes;
};
Hierarchy::Hierarchy(const std::string& data) {
    std::stringstream ss(data);
    std::string line;
    ceo = new ENode("Uspeshnia", NULL);
    number_of_employyes = 0;

    int employees = 0;
    while (std::getline(ss, line, '\n')) {
        std::stringstream line_s(line);
        std::string token;
        int token_count = 0;
        ENode* manager = NULL;
        while (std::getline(line_s, token, '-')) {
            std::string::iterator end_pos = std::remove(token.begin(), token.end(), ' ');
            token.erase(end_pos, token.end());

            if (token_count == 0) {
               manager = find_employee(token);
            }
            else {
                if (manager == NULL) {
                    std::cout << "Ivalid data!";
                }
                employees++;
                manager->addEmployee(new ENode(token, manager));
            }
            token_count++;
        }
        if (token_count != 2) {
            std::cout << "Ivalid data!";
        }
    }
    number_of_employyes = employees + 1;
    
};

Hierarchy::Iter::Iter(ENode* root_) {
    root = root_;
    r_root = root_;
    q.push(root_);
}

Hierarchy::ENode* Hierarchy::Iter::operator*() const {
    return root;
}
Hierarchy::ENode* Hierarchy::Iter::operator->() const {
    return root;
}
Hierarchy::Iter& Hierarchy::Iter::operator++() {
    goNext();
    return *this;
}
bool Hierarchy::Iter::operator==(const Hierarchy::Iter& other) {
    if (root == NULL && other.root != NULL
        || root != NULL && other.root == NULL) {
        return false;
    }
    if (root == NULL && other.root == NULL) {
        return true;
    }
    return root->getName() == other.root->getName();
}
bool Hierarchy::Iter::operator!=(const Hierarchy::Iter& other) {
    return !(*this == other);
}
Hierarchy::Iter Hierarchy::begin() const{
    return Iter(ceo);
}
Hierarchy::Iter Hierarchy::end() const{
    return NULL;
}
void Hierarchy::Iter::goNext() {
    ENode* r = q.front();
    q.pop();
    for (ENode* emp : r->getEmployees()) {
        q.push(emp);
    }
    if (q.empty()) {
        root = NULL;
        return;
    }
    root = q.front();
}

void Hierarchy::ENode::addEmployee(ENode* emp) {
    employees.push_back(emp);
}
Hierarchy::ENode::ENode(std::string name_, ENode* parent_) {
    name = name_;
    parent = parent_;
};
std::vector<Hierarchy::ENode*> Hierarchy::ENode::getEmployees() {
    return employees;
};
std::string Hierarchy::ENode::getName() {
    return name;
};
Hierarchy::~Hierarchy() noexcept
{
    destroy_hierarchy(ceo);
};

std::string Hierarchy::print() const {
    std::string full = "";
    for (Hierarchy::Iter it = begin(); it != end(); ++it) {
        for (ENode* emp : it->getEmployees()) {
            full += it->getName() + "-" + emp->getName() + '\n';
        }
    }
    return full;
};
int Hierarchy::getEmployeeLevel(const std::string& who) const {
    ENode* searched = find_employee(who);
    return getHierarchyLevel(searched, 0);
}
int Hierarchy::getHierarchyLevel(ENode* searched, int cur_level = 0) const {
    if (searched->parent == NULL) {
        return cur_level;
    }
    return getHierarchyLevel(searched->parent, cur_level += 1);
}
int Hierarchy::maxDepth(ENode* root)  const {
    if (root == NULL) {
        return -1;
    }
    int max = 0;
    for (ENode* emp : root->getEmployees()) {
        int child_depth = maxDepth(emp);
        if (child_depth > max) {
            max = child_depth;
        }
    }

    return (max + 1);
}
int Hierarchy::longest_chain() const {
    return maxDepth(ceo);
};
void Hierarchy::destroy_hierarchy(ENode* cur) const
{
    for (ENode* emp : cur->getEmployees()) {
        destroy_hierarchy(emp);
    }
    delete cur;
}
Hierarchy::ENode* Hierarchy::find_employee(std::string name) const {

    for (Hierarchy::Iter it = begin(); it != end(); ++it) {
        if (name == it->getName()) {
            return *it;
        }
    }
    return NULL;
}

bool Hierarchy::find(const std::string& name) const {
    return find_employee(name) != NULL;
};
int Hierarchy::num_employees() const {
    return number_of_employyes;
};

std::string Hierarchy::manager(const std::string& name) const {
    for (Hierarchy::Iter it = begin(); it != end(); ++it) {
        if (it->getName() == name) {
            return it->parent->getName();
        }
    }
    return NULL;
};
int Hierarchy::num_subordinates(const std::string& name) const {
    ENode* manager_node = find_employee(name);
    if (manager_node == NULL) {
        return 0;
    }
    size_t subordinates = manager_node->getEmployees().size();
    return static_cast<int>(subordinates);

};
unsigned long Hierarchy::getSalary(const std::string& who) const {
    ENode* manager_node = find_employee(who);
    int initial_salary = static_cast<int>(manager_node->getEmployees().size()) * 500;

    int all_workers = 0;

    for (Hierarchy::Iter it = Hierarchy::Iter(manager_node); it != end(); ++it) {
        all_workers++;
    }

    //Since we iterated over the boos and his directly subordinates we need to remove them from the calucation

    all_workers = all_workers - 1 - static_cast<int>(manager_node->getEmployees().size());

    return initial_salary + 50 * all_workers;

};

bool Hierarchy::fire(const std::string& who) {
    ENode* emp = find_employee(who);
    ENode* manager = emp->parent;

    for (std::vector<ENode*>::iterator it = manager->getEmployees().begin(); it != manager->getEmployees().end(); ++it) {
        if ((*it)->getName() == who) {
            manager->getEmployees().erase(it, it + 1);
            return true;
        }
    }
    return false;

};
bool Hierarchy::hire(const std::string& who, const std::string& boss) {
    ENode* previous_position = find_employee(who);
    if (previous_position != NULL) {
        fire(who);
    };

    ENode* manager = find_employee(boss);
    if (manager == NULL) {
        return false;
    }
    manager->addEmployee(new ENode(who, manager));
    return true;
};
Hierarchy::Hierarchy(ENode* ceo_) {
    ceo = ceo_;
    number_of_employyes = 1;
}
void Hierarchy::incorporate() {
    
};
void Hierarchy::modernize() {
};
Hierarchy Hierarchy::join_step(const Hierarchy& right, bool joined_right) const {
    Hierarchy left_joined = Hierarchy(new ENode("Uspeshnia", NULL));

    for (Hierarchy::Iter it = begin(); it != end(); ++it) {
        if (it->getName() == "Uspeshnia") {
            continue;
        }
        ENode* poistion_in_right = right.find_employee(it->getName());

        if (poistion_in_right == NULL) {
            left_joined.hire(it->getName(), it->parent->getName());
            continue;
        }
        std::string manager_name = it->parent->getName();
        if (it->parent->getName() != poistion_in_right->parent->getName()) {
            int current_manager_level = getEmployeeLevel(it->parent->getName());
            int right_manager_level = right.getEmployeeLevel(poistion_in_right->parent->getName());
            if (current_manager_level > right_manager_level) {
                manager_name = poistion_in_right->parent->getName();
            }
            else {
                if (it->parent->getName() > poistion_in_right->parent->getName()) {
                    manager_name = poistion_in_right->parent->getName();
                }
            }
        }

        std::vector<ENode*> left_employees = it->getEmployees();
        
        for (ENode* emp_in_right : poistion_in_right->getEmployees()) {
            if (emp_in_right->getName() == it->parent->getName()) {
                return Hierarchy(new ENode("Uspeshnia", NULL));
            }
            bool found = false;
            for (ENode* left_emp : left_employees) {
                if (left_emp->getName() == emp_in_right->getName()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                left_employees.push_back(emp_in_right);
            }

        }
        left_joined.hire(it->getName(), manager_name);
    }
    if (joined_right) {
        return left_joined;
    }
    return right.join_step(left_joined, true);
};
Hierarchy Hierarchy::join(const Hierarchy& right) const {
    return join_step(right, false);
}

