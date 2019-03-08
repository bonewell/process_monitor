cmake_minimum_required(VERSION 3.1.3)

project(process_monitor)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME}
    "loop.cpp"
    "main.cpp"
    "proc_reader.cpp"
    "process.cpp"
    "signals.cpp"
    "status_monitor.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::log4cplus
    pthread
)

enable_testing()
set(UNIT_TEST ${PROJECT_NAME}_unittest)
add_executable(${UNIT_TEST}
    "status_monitor.cpp"
    "status_monitor_test.cpp"
)
target_compile_features(${UNIT_TEST} PRIVATE cxx_std_11)
target_link_libraries(${UNIT_TEST}
    CONAN_PKG::gtest
)
add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})

set(AUTO_TEST ${PROJECT_NAME}_autotest)
add_executable(${AUTO_TEST}
    "proc_reader.cpp"
    "proc_reader_test.cpp"
)
target_compile_features(${AUTO_TEST} PRIVATE cxx_std_11)
target_link_libraries(${AUTO_TEST}
    CONAN_PKG::gtest
    CONAN_PKG::log4cplus
)
add_test(NAME ${AUTO_TEST} COMMAND ${AUTO_TEST})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${PROJECT_NAME}.service DESTINATION lib/systemd/system)
install(FILES log4cplus.ini DESTINATION etc/process_monitor)
