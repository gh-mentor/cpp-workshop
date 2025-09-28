add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(robokit_tests ${TEST_SOURCES})
target_link_libraries(robokit_tests PRIVATE robokit doctest)

add_test(NAME robokit_unit COMMAND robokit_tests)
