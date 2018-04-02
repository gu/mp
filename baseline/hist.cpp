#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

void readBmp(char* filename, vector<vector<unsigned char>> &mat);
void generateBoundaries(int bins, vector<pair<int, int>> &boundaries);
void generateBinMat(int bin, vector<pair<int,int>> boundaries, 
                    vector<vector<unsigned char>> &mat, vector<vector<unsigned char>> &bin_mat);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int bins;
    vector<vector<unsigned char>> mat;
    vector<vector<unsigned char>> bin_mat;
    vector<pair<int, int>> boundaries;

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
    readBmp(argv[1], mat);

    // cout << (int) mat[0][0] << endl;
    // cout << (int) mat[256][256] << endl;
    // cout << (int) mat[511][511] << endl;

    // for (int i = 0; i < bins; i++) {
    //     cout << boundaries[i].first << " " << boundaries[i].second << endl;
    // }

    int bin = 0;
    generateBinMat(bin, boundaries, mat, bin_mat);

    return 0;
}

void generateBinMat(int bin, vector<pair<int,int>> boundaries, vector<vector<unsigned char>> &mat, vector<vector<unsigned char>> &bin_mat) {
    int low = boundaries[bin].first;
    int high = boundaries[bin].second;

    vector<vector<unsigned char>>::iterator r;
    vector<unsigned char>::iterator c;
    int h, w;
    for (r = mat.begin(), h = 0; r != mat.end(); ++r, ++h) {
        for (c = r->begin(), w = 0; c != r->end(); ++c, ++w) {
            
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

void readBmp(char* filename, vector<vector<unsigned char>> &mat) {
    
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    mat.resize(height, vector<unsigned char>(width));

    vector<vector<unsigned char>>::iterator r;
    vector<unsigned char>::iterator c;
    int h, w;
    for (r = mat.begin(), h = 0; r != mat.end(); ++r, ++h) {
        for (c = r->begin(), w = 0; c != r->end(); ++c, ++w) {
            *c = data[h*width + w];
        }
    }

}