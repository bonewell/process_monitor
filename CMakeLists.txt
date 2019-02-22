cmake_minimum_required(VERSION 2.8)

project(process_monitor)
add_executable(${PROJECT_NAME}
    "main.cpp"
    "runner.cpp"
    "logger.cpp"
    "process.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME} pthread)
