cmake_minimum_required(VERSION 3.13.4)

project(cppquiz-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  ./src/Question.cpp
  ./test/QuestionTestCase.cpp
)

add_executable(
  cppquiz
  ./src/Question.cpp
  ./src/chatgpt_api.cpp
  ./src/main.cpp
  ./src/lib/tinyxml.cpp
)
target_link_libraries(
  cppquiz
  curl
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  CPPQuizTest
  ./src/Question.cpp
  ./test/QuestionTestCase.cpp
)
target_link_libraries(
  CPPQuizTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(CPPQuizTest)

