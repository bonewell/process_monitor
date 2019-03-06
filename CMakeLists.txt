cmake_minimum_required(VERSION 3.1.3)

project(process_monitor)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "runner.cpp"
    "dirreader.cpp"
    "process.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::log4cplus
    pthread
)

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
add_executable(${PROJECT_TEST_NAME}
    "process.cpp"
    "dirreader.cpp"
    "process_test.cpp"
)
target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_TEST_NAME}
    CONAN_PKG::gtest
    CONAN_PKG::log4cplus
)
add_test(NAME ${PROJECT_TEST_NAME} COMMAND ${PROJECT_TEST_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${PROJECT_NAME}.service DESTINATION lib/systemd/system)
install(FILES log4cplus.ini DESTINATION etc/process_monitor)
