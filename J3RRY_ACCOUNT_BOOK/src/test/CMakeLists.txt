cmake_minimum_required(VERSION 3.8)

set(test_project_name J3RRY_ACCOUNT_BOOK_TEST)

file(GLOB souce_files
        *.cpp)
add_executable(${test_project_name} ${souce_files})

target_link_libraries(${test_project_name} PUBLIC
        gtest_main # gtest_main is from google_test
        )

add_test(
        NAME ${test_project_name}
        COMMAND ${test_project_name}
)