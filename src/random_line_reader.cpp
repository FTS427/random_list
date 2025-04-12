#include "random_line_reader.hpp"
#include <stdexcept>

std::random_device RandomLineReader::rd_;
std::mt19937 RandomLineReader::gen_(rd_());

RandomLineReader::RandomLineReader(const std::string& file_path) {
    readFile(file_path);
}

void RandomLineReader::readFile(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::in);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    file.seekg(0, std::ios::end);
    const auto file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    lines_.reserve(static_cast<std::size_t>(file_size) / 30); // predict the number of each line's words is 30
    
    std::string temp_line;
    temp_line.reserve(256);
    
    while (std::getline(file, temp_line)) {
        lines_.push_back(std::move(temp_line));
    }
    
    if (lines_.empty()) {
        throw std::runtime_error("Empty file: " + file_path);
    }
}

size_t RandomLineReader::getRandomNumber(size_t begin, size_t end) const {
    std::uniform_int_distribution<size_t> dist(begin, end);
    return dist(gen_);
}

std::string RandomLineReader::getRandomLine() const {
    if (lines_.empty()) {
        throw std::runtime_error("No lines available");
    }
    return lines_[getRandomNumber(0, lines_.size() - 1)];
}

std::vector<std::string> RandomLineReader::getRandomLines(size_t count) const {
    if (lines_.empty()) {
        throw std::runtime_error("No lines available");
    }
    
    count = std::min(count, lines_.size());
    
    std::vector<size_t> indices(lines_.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), gen_);
    
    std::vector<std::string> result;
    result.reserve(count);
    
    for (size_t i = 0; i < count; ++i) {
        result.push_back(lines_[indices[i]]);
    }
    
    return result;
}