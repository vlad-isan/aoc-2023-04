//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    std::vector<Card> cards;
    std::string line;

    while (std::getline(file, line)) {
        cards.emplace_back(line);
    }

    uint32_t sum = 0;

    for (const auto &card: cards) {
        uint32_t matches = card.get_matches_no();

        if (matches > 0) {
            sum += std::pow(2, matches - 1);
        }
    }

    return sum;
}

int do_puzzle_2(std::ifstream &file) {
    std::vector<Card> cards;
    std::string line;

    while (std::getline(file, line)) {
        cards.emplace_back(line);
    }

    return get_total_scratchcards(cards, cards);
}

Card::Card(const std::string &line) {
    size_t colon_pos = line.find(':');
    size_t bar_pos = line.find('|');

    std::istringstream card_id_stream{line.substr(0, colon_pos)};
    std::istringstream winning_stream{line.substr(colon_pos + 2, bar_pos - colon_pos - 2)};
    std::istringstream no_stream{line.substr(bar_pos + 2)};

    std::string discard;
    card_id_stream >> discard >> this->id;

    this->parse_set(this->winning_numbers, winning_stream);
    this->parse_set(this->numbers, no_stream);
}

void Card::parse_set(std::vector<uint32_t> &set, std::istringstream &stream) {
    std::string token;

    while (getline(stream, token, ' ')) {
        auto [beg, end] = std::ranges::remove(token, ' ');
        token.erase(beg, end);

        if (token.empty()) {
            continue;
        }

        set.emplace_back(std::stoi(token));
    }
}

uint32_t Card::get_matches_no() const {
    return std::ranges::count_if(this->numbers, [&](auto &no) {
        return std::ranges::find(this->winning_numbers, no) != this->winning_numbers.end();
    });
}

uint32_t get_total_scratchcards(const std::vector<Card> &original_cards, const std::vector<Card> &copy_cards) {
    static uint32_t total = 0;
    total += copy_cards.size();

    std::vector<Card> copies;

    for(auto &card: copy_cards) {
        auto matches = card.get_matches_no();
        auto begin = original_cards.begin() + card.id;
        auto end = begin + matches;

        copies.insert(copies.end(), begin, end);

        if (copies.size() > 0) {
            get_total_scratchcards(original_cards, copies);
        }

        copies.clear();
    }

    return total;
}
