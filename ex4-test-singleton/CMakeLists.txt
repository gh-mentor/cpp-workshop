cmake_minimum_required(VERSION 3.10)
project(Singleton)

set(CMAKE_CXX_STANDARD 11)

# Add the library target with the shared code
add_library(logger_lib src/logger.cpp src/logger.h)
target_include_directories(logger_lib PUBLIC src)

# Add the main executable
add_executable(logger_app src/main.cpp)

# Link the main executable with the library
target_link_libraries(logger_app logger_lib)

# Add the test executable
add_executable(test_logger tests/test_logger.cpp)

# Link the test executable with the library
target_link_libraries(test_logger logger_lib)

# Install rules
install(TARGETS logger_lib logger_app
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)