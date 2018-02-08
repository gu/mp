#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

void print_mat(std::vector<std::vector<int>>& mat);

void generate_mat(std::vector<std::vector<int>>& mat);
void generate_sat_naive(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& sat);
void generate_sat(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& sat);
bool validate_roi(int r1, int r2, int c1, int c2, int rows, int cols);
int sum_roi(int r1, int r2, int c1, int c2, std::vector<std::vector<int>>& sat);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int cols, rows;
    std::vector<std::vector<int>> mat;
    std::vector<std::vector<int>> sat_naive;
    std::vector<std::vector<int>> sat;

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

    mat.resize(cols, std::vector<int>(rows));
    sat_naive.resize(cols, std::vector<int>(rows));
    sat.resize(cols, std::vector<int>(rows));

    // Fill matrix with random bytes
    generate_mat(mat);
    std::cout << "Original Matrix: " << std::endl;
    print_mat(mat);

    // generate_sat_naive(mat, sat_naive);
    // std::cout << "Original Matrix: " << std::endl;
    // print_mat(sat_naive);

    generate_sat(mat, sat);
    std::cout << "Summed-Area Table: " << std::endl;
    print_mat(sat);

    int r1, r2, c1, c2;


    std::cout << "Enter coordinates (r1, c1, r2, c2) for ROI: ";
    std::cin >> r1 >> c1 >> r2 >> c2;
    while (validate_roi(r1, r2, c1, c2, rows, cols)) {
        std::cout << "Sum of ROI is: " << sum_roi(r1, r2, c1, c2, sat) << std::endl;
        std::cout << "Enter coordinates (r1, c1, r2, c2) for ROI: ";
        std::cin >> r1 >> c1 >> r2 >> c2;
    }

    return 0;
}

int sum_roi(int r1, int r2, int c1, int c2, std::vector<std::vector<int>>& sat) {
    int w, x, y, z;
    
    w = r1 == 0 || c1 == 0 ? 0 : sat[r1-1][c1-1];
    x = r1 == 0 ? 0 : sat[r1-1][c2];
    y = c1 == 0 ? 0 : sat[r2][c1-1];
    z = sat[r2][c2];

    return w + z - x - y;
}

bool validate_roi(int r1, int r2, int c1, int c2, int rows, int cols) {
    int ret = true;
    if (r1 < 0 || r1 >= rows) ret = false;
    if (r2 < 0 || r2 >= rows) ret = false;
    if (c1 < 0 || c1 >= cols) ret = false;
    if (c2 < 0 || c2 >= cols) ret = false;
    return ret;
}

void generate_sat_naive(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& sat) {
    int rows = (int) mat.size();
    int cols = (int) mat[0].size();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int sum = 0;
            for (int r2 = 0; r2 <= r; r2++) {
                for (int c2 = 0; c2 <= c; c2++) {
                    sum += mat[r2][c2];
                }
            }
            sat[r][c] = sum;
        }
    }
}

void generate_sat(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& sat) {
    int rows = (int) mat.size();
    int cols = (int) mat[0].size();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int w, x, y, z;
            w = r == 0 || c == 0 ? 0 : sat[r-1][c-1];
            x = r == 0 ? 0 : sat[r-1][c];
            y = c == 0 ? 0 : sat[r][c-1];
            z = mat[r][c];
            sat[r][c] = (x + y) - w + z;
        }
    }
}

void generate_mat(std::vector<std::vector<int>>& mat) {
    srand(time(NULL));

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

    // std::cout << "[" << std::endl;
    for (r = mat.begin(); r != mat.end(); ++r) {
        std::cout << "[ ";
        for (c = r->begin(); c != r->end(); ++c) {
            std::cout << *c << " ";
        }
        std::cout << "]" << std::endl;
    }
    // std::cout << "]" << std::endl;
    std::cout << std::endl;

}
