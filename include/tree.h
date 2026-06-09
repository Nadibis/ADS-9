// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <iostream>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<Node*> children;
        explicit Node(char val) : value(val) {}
    };
    Node* root;
    std::vector<std::vector<char>> allPerms;
    void buildTree(Node* node, std::vector<char> remaining);
    void collectPerms(Node* node, std::vector<char>& current, 
                      std::vector<std::vector<char>>& result);
    void deleteTree(Node* node);
    int factorial(int n);

 public:
    explicit PMTree(const std::vector<char>& chars);
    ~PMTree();
    std::vector<std::vector<char>> getAllPerms();
    std::vector<char> getRootChildren() const {
        std::vector<char> result;
        for (Node* child : root->children) {
            result.push_back(child->value);
        }
        return result;
    }
    void printTree();
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
