// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdint>
#include "tree.h"

int main() {
    std::cout << "Пример для n=3" << std::endl;
    std::vector<char> chars3 = {'1', '2', '3'};
    PMTree tree3(chars3);
    auto perms = getAllPerms(tree3);
    std::cout << "Все перестановки (" << perms.size() << "):" << std::endl;
    for (const auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "\n getPerm1 и getPerm2" << std::endl;
    for (int i = 1; i <= 6; ++i) {
        auto p1 = getPerm1(tree3, i);
        auto p2 = getPerm2(tree3, i);
        std::cout << "№" << i << ": getPerm1=";
        for (char c : p1) std::cout << c;
        std::cout << " getPerm2=";
        for (char c : p2) std::cout << c;
        std::cout << std::endl;
    }
    std::cout << "\nВычислительный эксперимент" << std::endl;
    std::cout << "n\tgetAllPerms(μs)\tgetPerm1(μs)\t"
    << "getPerm2(μs)\tПерестановок" << std::endl;
    for (int n = 1; n <= 9; ++n) {  // Вектор символов от '1' до 'n'
        std::vector<char> chars;
        for (int i = 1; i <= n; ++i) {
            chars.push_back('0' + i);
        }
        PMTree tree(chars);
        auto start = std::chrono::high_resolution_clock::now();//Измер. getAllPerms
        auto all = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        int64_t timeAll = std::chrono::duration_cast
        <std::chrono::microseconds>(end - start).count();
        std::random_device rd;  // Случайный номер перестановки
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, all.size());
        int randNum = dist(gen);
        start = std::chrono::high_resolution_clock::now(); // Измерение getPerm1
        auto p1 = getPerm1(tree, randNum);
        end = std::chrono::high_resolution_clock::now();
        int64_t time1 = std::chrono::duration_cast
        <std::chrono::microseconds>(end - start).count();
        start = std::chrono::high_resolution_clock::now(); // Измерение getPerm2
        auto p2 = getPerm2(tree, randNum);
        end = std::chrono::high_resolution_clock::now();
        int64_t time2 = std::chrono::duration_cast
        <std::chrono::microseconds>(end - start).count();
        std::cout << n << "\t" << timeAll << "\t\t" 
        << time1 << "\t\t" << time2 << "\t\t" << all.size() << std::endl;
    }
    return 0;
}
