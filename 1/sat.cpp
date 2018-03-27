#include <iostream>

#include <vtkm/cont/DataSetBuilderUniform.h>
#include <vtkm/cont/DataSetFieldAdd.h>
#include <vtkm/cont/DataSet.h>

void print_mat(std::vector<std::vector<int>>& mat);
void generate_mat(vtkm::cont::DataSet *mat, int rows, int cols);

int main(int argc, char* argv[]) {
    // suppress warnings
    (void)argc; (void)argv;

    int cols, rows;

    vtkm::cont::DataSetBuilderUniform dataSetBuilder;

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

    vtkm::cont::DataSet mat = dataSetBuilder.Create(vtkm::Id3(rows+1, cols+1, 2));

    generate_mat(&mat, rows, cols);

    std::cout << "Hello World" << std::endl;
    return 0;
}

void generate_mat(vtkm::cont::DataSet *mat, int rows, int cols) {
    vtkm::cont::DataSetFieldAdd dataSetFieldAdd;
    std::vector<vtkm::UInt32> values;

    srand(time(NULL));

    for (vtkm::Id yIndex = 0; yIndex < rows; yIndex++) {
        for (vtkm::Id xIndex = 0; xIndex < cols; xIndex++) {
            values.push_back(rand() % 256);
        }
    }

    dataSetFieldAdd.AddPointField(*mat, "value", values);
    
}