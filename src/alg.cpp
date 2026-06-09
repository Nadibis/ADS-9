// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& chars) {
    root = new Node('\0');
    buildTree(root, chars);
}
PMTree::~PMTree() {
    deleteTree(root);
}
void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    std::sort(remaining.begin(), remaining.end());
    for (size_t i = 0; i < remaining.size(); ++i) {
        Node* child = new Node(remaining[i]);
        node->children.push_back(child);
        std::vector<char> newRemaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) newRemaining.push_back(remaining[j]);
        }
        buildTree(child, newRemaining);
    }
}
void PMTree::collectPerms(Node* node, std::vector<char>& current,
                          std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        current.push_back(node->value);
    }
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (Node* child : node->children) {
            collectPerms(child, current, result);
        }
    }
    if (node->value != '\0') {
        current.pop_back();
    }
}
std::vector<std::vector<char>> PMTree::getAllPerms() {
    if (!allPerms.empty()) {
        return allPerms;
    }
    std::vector<char> current;
    collectPerms(root, current, allPerms);
    return allPerms;
}
int PMTree::factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}
void PMTree::deleteTree(Node* node) {
    if (node == nullptr) return;
    for (Node* child : node->children) {
        deleteTree(child);
    }
    delete node;
}
void PMTree::printTree() {
    if (!root) return;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();
            if (current->value != '\0') {
                std::cout << current->value << " ";
            } else {
                std::cout << "* ";
            }
            for (Node* child : current->children) {
                q.push(child);
            }
        }
        std::cout << std::endl;
    }
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    return tree.getAllPerms();
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num < 1) return {};
    auto all = getAllPerms(tree);
    if (num > static_cast<int>(all.size())) return {};
    return all[num - 1];
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num < 1) {
        return std::vector<char>();
    }
    std::vector<char> result;
    std::vector<char> available = tree.getRootChildren();  // < используем метод
    std::sort(available.begin(), available.end());
    int n = available.size();
    int totalPerms = 1;
    for (int i = 2; i <= n; ++i) totalPerms *= i;
    if (num > totalPerms) {
        return std::vector<char>();
    }
    int remainingNum = num - 1;
    for (int i = 0; i < n; ++i) {
        int fact = 1;
        for (int j = 2; j <= n - i - 1; ++j) fact *= j;
        int index = remainingNum / fact;
        result.push_back(available[index]);
        available.erase(available.begin() + index);
        remainingNum = remainingNum % fact;
    }
    return result;
}
