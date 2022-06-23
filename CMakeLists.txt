cmake_minimum_required(VERSION 3.1)

# https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md#cmake-toolchain-file
set(CMAKE_TOOLCHAIN_FILE /vcpkg/scripts/buildsystems/vcpkg.cmake)

# For creating a static standalone executable without dynamic linking
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(project_name todo) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/StatusController.cpp
        src/controller/StatusController.hpp
        src/dto/DTOs.hpp
)

## link libs

find_package(oatpp            1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)
find_package(oatpp-swagger    1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
        # test/app/StatusApiTestClient.hpp
        )
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

# add_executable(${project_name}-test
#         test/tests.cpp
#         test/app/TestComponent.hpp
#         test/app/StatusApiTestClient.hpp
#         test/StatusControllerTest.cpp
#         test/StatusControllerTest.hpp
# )

# target_link_libraries(${project_name}-test ${project_name}-lib)
# add_dependencies(${project_name}-test ${project_name}-lib)

# set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
#         CXX_STANDARD 11
#         CXX_EXTENSIONS OFF
#         CXX_STANDARD_REQUIRED ON
# )

# enable_testing()
# add_test(project-tests ${project_name}-test)