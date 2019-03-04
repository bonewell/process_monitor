cmake_minimum_required(VERSION 3.1.3)

project(process_monitor)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "runner.cpp"
    "process.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::log4cplus
    pthread
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${PROJECT_NAME}.service DESTINATION lib/systemd/system)
install(FILES log4cplus.ini DESTINATION etc/process_monitor)
