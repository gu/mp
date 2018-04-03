#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

void readBmp(char* filename, vector<vector<int>> &mat, vector<vector<int>> &bin_mat, vector<vector<int>> &sat);
void generateBoundaries(int bins, vector<pair<int, int>> &boundaries);
void generateBinMat(int bin, vector<pair<int,int>> boundaries, 
                    vector<vector<int>> &mat, vector<vector<int>> &bin_mat);
void generate_sat(vector<vector<int>>& mat, vector<vector<int>>& sat);
bool validate_roi(int r1, int r2, int c1, int c2, int rows, int cols);
int sum_roi(int r1, int r2, int c1, int c2, vector<vector<int>>& sat);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int bins;
    vector<vector<int>> mat;
    vector<vector<int>> sat;
    vector<vector<int>> bin_mat;
    vector<pair<int, int>> boundaries;
    vector<int> hist;

    // Check for valid argument input.
    if (argc != 3) {
        cout << "Invalid input. Example Usage: " << endl;
        cout << "\t./sat [file-name.bmp] [bin-count]" << endl;
        return 0;
    }    
    
    istringstream ss(argv[2]);
    if (!(ss >> bins)) {
        cerr << "Invalid bins parameter " << argv[1] << '\n';
    }
    ss.clear();

    generateBoundaries(bins, boundaries);
    hist.resize(bins);
    readBmp(argv[1], mat, bin_mat, sat);

    int r1, r2, c1, c2;

    cout << "Enter coordinates (r1, c1, r2, c2) for ROI: ";
    cin >> r1 >> c1 >> r2 >> c2;
    while (!validate_roi(r1, r2, c1, c2, mat.size(), mat[0].size())) {
        // cout << "Sum of ROI is: " << sum_roi(r1, r2, c1, c2, sat) << endl;
        cout << "Unvalid coordinates." << endl;
        cout << "Enter coordinates (r1, c1, r2, c2) for ROI: ";
        cin >> r1 >> c1 >> r2 >> c2;
    }

    // cout << mat[0][0] << endl;
    // cout << mat[256][256] << endl;
    // cout << mat[511][511] << endl;

    // for (int i = 0; i < bins; i++) {
    //     cout << boundaries[i].first << " " << boundaries[i].second << endl;
    // }

    for (int bin = 0; bin < bins; bin++) {
        generateBinMat(bin, boundaries, mat, bin_mat);
        generate_sat(bin_mat, sat);
        int sum = sum_roi(r1, r2, c1, c2, sat);
        hist[bin] = sum;
    }

    for (vector<int>::size_type i = 0; i < hist.size(); i++) {
        cout << hist[i] << " ";
    }


    return 0;
}

void generateBinMat(int bin, vector<pair<int,int>> boundaries, vector<vector<int>> &mat, vector<vector<int>> &bin_mat) {
    int low = boundaries[bin].first;
    int high = boundaries[bin].second;

    for(vector<int>::size_type r = 0; r != mat.size(); r++) {
        for (vector<int>::size_type c = 0; c != mat.size(); c++) {
            if (mat[r][c] >= low && mat[r][c] <= high) {
                bin_mat[r][c] = 1;
            } else {
                bin_mat[r][c] = 0;
            }
        }
    }
}

void generateBoundaries(int bins, vector<pair<int, int>> &boundaries) {
    int width = ceil(256 / bins);
    int counter = 0;

    boundaries.resize(bins, pair<int, int>(0, 0));

    for (int i = 0; i < bins; i++) {
        boundaries[i].first = counter;
        counter += width;
        boundaries[i].second = counter - 1;
    }

    if (boundaries[bins-1].second != 255) {
        boundaries[bins-1].second = 255;
    }
}

void readBmp(char* filename, vector<vector<int>> &mat, vector<vector<int>> &bin_mat, vector<vector<int>> &sat) {
    
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    mat.resize(height, vector<int>(width));
    bin_mat.resize(height, vector<int>(width));
    sat.resize(height, vector<int>(width));

    vector<vector<int>>::iterator r;
    vector<int>::iterator c;
    int h, w;
    for (r = mat.begin(), h = 0; r != mat.end(); ++r, ++h) {
        for (c = r->begin(), w = 0; c != r->end(); ++c, ++w) {
            *c = (int) data[h*width + w];
        }
    }

}

int sum_roi(int r1, int r2, int c1, int c2, vector<vector<int>>& sat) {
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

void generate_sat(vector<vector<int>>& mat, vector<vector<int>>& sat) {
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