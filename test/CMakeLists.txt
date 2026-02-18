#set(GLOB SRC_TESTS"*.cpp")  # в переменную SRC_TESTS записываем все файлы по маске
set(SRC_TESTS test_main.cpp test_polinom_arithmetic.cpp test_unordered_map.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gtest)

add_executable(test test_main.cpp test_polinom_arithmetic.cpp test_ordered_map.cpp)
target_link_libraries(test gtest) #прилинковали к test.ехе библиотеку 