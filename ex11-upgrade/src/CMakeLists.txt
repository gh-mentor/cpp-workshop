set(ROBOKIT_SOURCES
    robot.cpp
    kinematics.cpp
    planner.cpp
    sensor.cpp
    control_loop.cpp
    logging.cpp
    config.cpp
    math_util.cpp
)

add_library(robokit STATIC ${ROBOKIT_SOURCES})
target_include_directories(robokit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(robokit PRIVATE ROBOKIT_VERSION="${PROJECT_VERSION}")

add_executable(robokit_demo main.cpp)
target_link_libraries(robokit_demo PRIVATE robokit)
