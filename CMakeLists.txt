cmake_minimum_required(VERSION 3.1)

# https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md#cmake-toolchain-file
set(CMAKE_TOOLCHAIN_FILE /vcpkg/scripts/buildsystems/vcpkg.cmake)

set(project_name todo) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/ErrorHandler.hpp
        src/ErrorHandler.cpp
        src/ServiceComponent.hpp
        src/SwaggerComponent.hpp
        src/controller/TodoController.hpp
        src/dto/TodoDto.hpp
        src/dto/StatusDto.hpp
        src/dto/ConfigDto.hpp
        src/service/TodoService.hpp
        src/service/TodoService.cpp
        src/db/TodoDb.hpp
)

## link libs

find_package(oatpp            1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)
find_package(oatpp-swagger    1.3.0 REQUIRED)
find_package(OpenSSL 3.0.3 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
        PRIVATE OpenSSL::SSL OpenSSL::Crypto
)


add_definitions(
        # Path to swagger-ui resources #
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        # Path to config file #
        -DCONFIG_PATH="${CMAKE_CURRENT_LIST_DIR}/resources/config.json"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

target_include_directories(${project_name}-lib PUBLIC src)
## add executables

add_executable(${project_name}-exe
        src/App.cpp
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