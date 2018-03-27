#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

void readBmp(char* filename, vector<vector<unsigned char>> &mat);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int bins;
    vector<vector<unsigned char>> mat;

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

    readBmp(argv[1], mat);

    // cout << (int) mat[0][0] << endl;
    // cout << (int) mat[256][256] << endl;
    // cout << (int) mat[511][511] << endl;


    return 0;
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