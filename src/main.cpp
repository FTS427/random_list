#include "random_line_reader.hpp"
#include <cstdio>

int main(int argc, char* args[]) {
    if (argc < 2) {
        printf("Error: Please provide a file path\n");
        return 1;
    }

    try {
        RandomLineReader reader(args[1]);
        printf("Total lines: %zu\n", reader.getTotalLines());

        if (argc >= 3) {
            try {
                size_t count = std::stoull(args[2]);
                auto random_lines = reader.getRandomLines(count);
                
                if (random_lines.size() < count) {
                    printf("Warning: Requested %zu lines, but only %zu lines are available.\n", count, random_lines.size());
                }
                for (size_t i = 0; i < random_lines.size(); ++i) {
                    printf("\033[33m%zu\033[0m content:\n%s\n", i+1,random_lines[i].c_str());
                }
            } catch (const std::exception& e) {
                printf("Error: Invalid number format\n");
                return 1;
            }
        }
        else {
            auto random_line = reader.getRandomLine();
            printf("Random line content:\n%s\n", random_line.c_str());
        }
    }
    catch (const std::exception& e) {
        printf("Error: %s\n", e.what());
        return 1;
    }

    return 0;
}