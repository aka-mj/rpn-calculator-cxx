cmake_minimum_required(VERSION 3.24)
project(rpncalc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "--static ${CMAKE_CXX_FLAGS}")

add_executable(rpncalc
	rpncalc.cxx
)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/fmt)

target_include_directories(rpncalc PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rpncalc PRIVATE fmt::fmt)

enable_testing()
add_subdirectory(test)
add_test(NAME TestEval COMMAND test_eval)
