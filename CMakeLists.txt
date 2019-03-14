cmake_minimum_required(VERSION 3.1.3)

project(process_monitor)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME}
    "general/process_info.cpp"
    "loop/loop.cpp"
    "loop/process.cpp"
    "main.cpp"
    "monitor/memory_monitor.cpp"
    "monitor/status_monitor.cpp"
    "proc/proc_memory.cpp"
    "proc/proc_reader.cpp"
    "utils/signals.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::log4cplus
    pthread
)

enable_testing()
set(UNIT_TEST ${PROJECT_NAME}_unittest)
add_executable(${UNIT_TEST}
    "general/process_info.cpp"
    "monitor/memory_monitor.cpp"
    "monitor/memory_monitor_test.cpp"
    "monitor/status_monitor.cpp"
    "monitor/status_monitor_test.cpp"
)
target_compile_features(${UNIT_TEST} PRIVATE cxx_std_11)
target_include_directories(${UNIT_TEST} PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(${UNIT_TEST}
    CONAN_PKG::gtest
)
add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})

set(AUTO_TEST ${PROJECT_NAME}_autotest)
add_executable(${AUTO_TEST}
    "general/process_info.cpp"
    "proc/proc_memory.cpp"
    "proc/proc_memory_test.cpp"
    "proc/proc_reader.cpp"
    "proc/proc_reader_test.cpp"
)
target_compile_features(${AUTO_TEST} PRIVATE cxx_std_11)
target_include_directories(${AUTO_TEST} PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(${AUTO_TEST}
    CONAN_PKG::gtest
)
add_test(NAME ${AUTO_TEST} COMMAND ${AUTO_TEST})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${PROJECT_NAME}.service DESTINATION lib/systemd/system)
install(FILES log4cplus.ini DESTINATION etc/process_monitor)
