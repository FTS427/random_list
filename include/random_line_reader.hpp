#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>

class RandomLineReader {
public:
    explicit RandomLineReader(const std::string& file_path);
    
    std::string getRandomLine() const;
    
    std::vector<std::string> getRandomLines(size_t count) const;
    
    size_t getTotalLines() const { return lines_.size(); }
    
    bool isEmpty() const { return lines_.empty(); }

private:
    std::vector<std::string> lines_;
    static std::random_device rd_;
    static std::mt19937 gen_;
    
    size_t getRandomNumber(size_t begin, size_t end) const;
    
    void readFile(const std::string& file_path);
};