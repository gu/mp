#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

void print_mat(std::vector<std::vector<int>>& mat);

void generate_mat(std::vector<std::vector<int>>& mat, int rows, int cols);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int cols, rows;
    std::vector<std::vector<int>> mat;

    // Check for valid argument input.
    if (argc != 3) {
        std::cout << "Invalid input. Example Usage: " << std::endl;
        std::cout << "\t./sat [matrix-cols] [matrix-rows]" << std::endl;
        return 0;
    }

    std::istringstream ss(argv[1]);
    if (!(ss >> cols)) {
        std::cerr << "Invalid cols parameter " << argv[1] << '\n';
    }
    ss.clear();
    ss.str(argv[2]);
    if (!(ss >> rows)) {
        std::cerr << "Invalid rows parameter " << argv[2] << '\n';
    }


    // Fill matrix with random bytes
    generate_mat(mat, rows, cols);

    // Debug print
    print_mat(mat);



    return 0;
}

void generate_mat(std::vector<std::vector<int>>& mat, int rows, int cols) {
    srand(time(NULL));

    mat.resize(cols, std::vector<int>(rows));
    std::vector< std::vector<int> >::iterator r;
    std::vector<int>::iterator c;
    for (r = mat.begin(); r != mat.end(); ++r) {
        for (c = r->begin(); c != r->end(); ++c) {
            *c = rand() % 256;
        }
    }
}

void print_mat(std::vector<std::vector<int>>& mat) {

    std::vector< std::vector<int> >::iterator r;
    std::vector<int>::iterator c;

    std::cout << "[" << std::endl;
    for (r = mat.begin(); r != mat.end(); ++r) {
        std::cout << "[ ";
        for (c = r->begin(); c != r->end(); ++c) {
            std::cout << *c << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;

}
