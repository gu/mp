cmake_minimum_required(VERSION 3.10)

find_package(VTKm REQUIRED
    OPTIONAL_COMPONENTS Serial TBB
)

add_executable(sat sat.cpp)
target_include_directories(sat PRIVATE ${VTKm_INCLUDE_DIRS})
target_link_libraries(sat PRIVATE ${VTKm_LIBRARIES})
target_compile_options(sat PRIVATE ${VTKm_COMPILE_OPTIONS})

if(VTKm_TBB_FOUND)
    add_executable(satTBB satTBB.cpp)
    target_include_directories(satTBB PRIVATE ${VTKm_INCLUDE_DIRS})
    target_link_libraries(satTBB PRIVATE ${VTKm_LIBRARIES})
    target_compile_options(satTBB PRIVATE ${VTKm_COMPILE_OPTIONS})
endif()