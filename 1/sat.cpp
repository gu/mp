#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef VTKM_DEVICE_ADAPTER
#define VTKM_DEVICE_ADAPTER VTKM_DEVICE_ADAPTER_SERIAL
#endif

#include <vtkm/cont/ArrayHandlePermutation.h>
#include <vtkm/cont/DeviceAdapter.h>
#include <vtkm/cont/DeviceAdapterAlgorithm.h>

void print_data(std::vector<vtkm::UInt32>& mat,
                    std::vector<vtkm::Id>& key_rowMajor, std::vector<vtkm::Id>& key_colMajor,
                    std::vector<vtkm::Id>& key_permuteRtC);
void print_mat(std::vector<vtkm::UInt32>& sat, int rows, int cols);
void generate_data(std::vector<vtkm::UInt32>& mat, int cols, int rows,
                    std::vector<vtkm::Id>& key_rowMajor, std::vector<vtkm::Id>& key_colMajor,
                    std::vector<vtkm::Id>& key_permuteRtC);
void generate_data(std::vector<vtkm::UInt32>& mat, std::vector<vtkm::Id>& keys, int cols);
void generate_sat(std::vector<vtkm::UInt32>& mat, std::vector<vtkm::UInt32>& sat,
                    std::vector<vtkm::Id>& key_rowMajor, std::vector<vtkm::Id>& key_colMajor,
                    std::vector<vtkm::Id>& key_permuteRtC);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int cols, rows;
    std::vector<vtkm::UInt32> mat;
    std::vector<vtkm::Id> key_rowMajor;
    std::vector<vtkm::Id> key_colMajor;
    std::vector<vtkm::Id> key_permuteRtC;
    std::vector<vtkm::UInt32> sat;

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

    mat.resize(rows*cols);
    key_rowMajor.resize(rows*cols);
    key_colMajor.resize(rows*cols);
    key_permuteRtC.resize(rows*cols);
    sat.resize(rows*cols);
    
    generate_data(mat, cols, rows, key_rowMajor, key_colMajor, key_permuteRtC);
    // print_data(mat, key_rowMajor, key_colMajor, key_permuteRtC);
    // print_mat(mat, rows, cols);

    generate_sat(mat, sat, key_rowMajor, key_colMajor, key_permuteRtC);
    // print_mat(sat, rows, cols);

    // std::cout << "Hello World" << std::endl;
    return 0;
}

void print_mat(std::vector<vtkm::UInt32>& mat, int rows, int cols) {

    std::vector<vtkm::UInt32>::iterator s;
    std::cout << "MAT: " << std::endl;
    int ctr = 0;
    for (s = mat.begin(); s != mat.end(); ++s, ctr++) {
        std::cout << *s << " ";
        if (ctr % cols == (cols-1)) {
            std::cout << std::endl;
        }
    }
}

void generate_sat(std::vector<vtkm::UInt32>& mat, std::vector<vtkm::UInt32>& sat,
                    std::vector<vtkm::Id>& key_rowMajor, std::vector<vtkm::Id>& key_colMajor,
                    std::vector<vtkm::Id>& key_permuteRtC) {


    using DeviceAdapter = VTKM_DEFAULT_DEVICE_ADAPTER_TAG;

    vtkm::cont::ArrayHandle<vtkm::UInt32> matHandle = vtkm::cont::make_ArrayHandle(mat);
    vtkm::cont::ArrayHandle<vtkm::Id> key_rowMajorHandle = vtkm::cont::make_ArrayHandle(key_rowMajor);
    vtkm::cont::ArrayHandle<vtkm::Id> key_colMajorHandle = vtkm::cont::make_ArrayHandle(key_colMajor);
    vtkm::cont::ArrayHandle<vtkm::Id> key_permuteRtCHandle = vtkm::cont::make_ArrayHandle(key_permuteRtC);

    vtkm::cont::ArrayHandle<vtkm::UInt32> sat_firstRunHandle;
    vtkm::cont::DeviceAdapterAlgorithm<DeviceAdapter>::ScanInclusiveByKey(key_rowMajorHandle, matHandle, sat_firstRunHandle);

    vtkm::cont::ArrayHandlePermutation<vtkm::cont::ArrayHandle<vtkm::Id>, 
                                       vtkm::cont::ArrayHandle<vtkm::UInt32>> sat_permutedRtC(
                                            key_permuteRtCHandle, sat_firstRunHandle);

    vtkm::cont::ArrayHandle<vtkm::UInt32> sat_secondRunHandle;
    vtkm::cont::DeviceAdapterAlgorithm<DeviceAdapter>::ScanInclusiveByKey(key_colMajorHandle, sat_permutedRtC, sat_secondRunHandle);

    vtkm::cont::ArrayHandlePermutation<vtkm::cont::ArrayHandle<vtkm::Id>, 
                                       vtkm::cont::ArrayHandle<vtkm::UInt32>> satHandle(
                                            key_permuteRtCHandle, sat_secondRunHandle);

    using PortalConstType = typename vtkm::cont::ArrayHandlePermutation<vtkm::cont::ArrayHandle<vtkm::Id>, 
                                       vtkm::cont::ArrayHandle<vtkm::UInt32>>::PortalConstControl;

    PortalConstType satPortal = satHandle.GetPortalConstControl();

    std::copy(vtkm::cont::ArrayPortalToIteratorBegin(satPortal), vtkm::cont::ArrayPortalToIteratorEnd(satPortal), sat.begin());
}

void generate_data(std::vector<vtkm::UInt32>& mat, int cols, int rows,
                    std::vector<vtkm::Id>& key_rowMajor, std::vector<vtkm::Id>& key_colMajor,
                    std::vector<vtkm::Id>& key_permuteRtC) {
    srand(time(NULL));

    std::vector<vtkm::UInt32>::iterator m;
    std::vector<vtkm::Id>::iterator k_rowMajor;
    std::vector<vtkm::Id>::iterator k_colMajor;
    std::vector<vtkm::Id>::iterator k_permuteRtC;
    int ctr;
    for (ctr = 0, m = mat.begin(), 
         k_rowMajor = key_rowMajor.begin(), k_colMajor = key_colMajor.begin(),
         k_permuteRtC = key_permuteRtC.begin(); 
         m != mat.end(); ++m, ++k_rowMajor, ++k_colMajor, ++k_permuteRtC, ctr++) {
        *m = rand() % 256;
        *k_rowMajor = floor(ctr / cols);
        *k_colMajor = floor(ctr / rows);
        *k_permuteRtC = (ctr % rows) * cols + (floor(ctr/cols));
    }
}

void print_data(std::vector<vtkm::UInt32>& mat,
                    std::vector<vtkm::Id>& key_rowMajor, std::vector<vtkm::Id>& key_colMajor,
                    std::vector<vtkm::Id>& key_permuteRtC) {
    std::vector<vtkm::UInt32>::iterator m;
    std::vector<vtkm::Id>::iterator k_rowMajor;
    std::vector<vtkm::Id>::iterator k_colMajor;
    std::vector<vtkm::Id>::iterator k_permuteRtC;

    std::cout << "Vals: ";
    for (m = mat.begin(); m != mat.end(); ++m) {
        std::cout << *m << " ";
    }
    std::cout << std::endl;
    std::cout << "k_rowMajor: ";
    for (k_rowMajor = key_rowMajor.begin(); k_rowMajor != key_rowMajor.end(); ++k_rowMajor) {
        std::cout << *k_rowMajor << " ";
    }
    std::cout << std::endl;
    std::cout << "k_colMajor: ";
    for (k_colMajor = key_colMajor.begin(); k_colMajor != key_colMajor.end(); ++k_colMajor) {
        std::cout << *k_colMajor << " ";
    }
    std::cout << std::endl;
    std::cout << "k_permuteRtC: ";
    for (k_permuteRtC = key_permuteRtC.begin(); k_permuteRtC != key_permuteRtC.end(); ++k_permuteRtC) {
        std::cout << *k_permuteRtC << " ";
    }
    std::cout << std::endl;
}