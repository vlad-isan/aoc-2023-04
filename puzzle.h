//
// Created by Vlad Isan on 05/12/2023.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include "fmt/core.h"

struct Card {
    uint32_t id;
    std::vector<uint32_t> winning_numbers;
    std::vector<uint32_t> numbers;

    explicit Card(const std::string &line);

    void parse_set(std::vector<uint32_t> &set, std::istringstream &stream);
    uint32_t get_matches_no() const;
};

int puzzle_sample_1(const std::string &base_file_path);

int puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

int puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

int do_puzzle_2(std::ifstream &file);

uint32_t get_total_scratchcards(const std::vector<Card> &original_cards, const std::vector<Card> &copy_cards);

#endif //PUZZLE_H
