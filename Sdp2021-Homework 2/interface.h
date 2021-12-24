#pragma once
#pragma warning(disable : 4146)

#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <functional>
#include <stack>
class Hierarchy
{
public:
    class ENode {
    private:
        std::string name;
        std::vector<ENode*> employees;
        
    public:
        ENode(std::string name_, ENode*);
        void addEmployee(ENode* emp);
        std::string getName();
        ENode* parent;
        std::vector<ENode*> getEmployees();
    };
    class Iter {
    private:
        void goNext();
        std::queue<ENode*> q;
    public:
        ENode* root;
        ENode* r_root;
        Iter(ENode* root);
        ENode* operator*() const;
        ENode* operator->() const;
        Iter& operator++();
        bool operator== (const Iter& other);
        bool operator!= (const Iter& other);
    };
    Iter begin() const;
    Iter end() const;


    void iterate(ENode* root, std::function<void(ENode*)> lambda) const;
    Hierarchy(Hierarchy&& r) noexcept;
    Hierarchy(const Hierarchy& r);
    Hierarchy(const std::string& data);
    Hierarchy(ENode* ceo_);

    ~Hierarchy() noexcept;
    void operator=(const Hierarchy&) = delete;

    std::string print()const;

    int longest_chain() const;
    bool find(const std::string& name) const;
    int num_employees() const;
    int num_overloaded(int level) const;
   
    int getEmployeeLevel(const std::string& who) const;
    std::string manager(const std::string& name) const;
    int num_subordinates(const std::string& name) const;
    unsigned long getSalary(const std::string& who) const;

    bool fire(const std::string& who);
    bool hire(const std::string& who, const std::string& boss);

    void incorporate();
    void modernize();
    
    Hierarchy join(const Hierarchy& right) const;

    //If you need it - add more public methods here
private:
    //Add whatever you need here
    void destroy_hierarchy(ENode* cur) const;
    int maxDepth(ENode* root) const;
    Hierarchy join_step(const Hierarchy& right, bool joined_right) const;
    int getHierarchyLevel(ENode* searched, int cur_level) const;
    ENode* find_employee(std::string name) const;
    int number_of_employyes;
    ENode* ceo;
};
