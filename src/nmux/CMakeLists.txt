add_executable(nmux nmux.cpp tsmpool.cpp)
target_link_libraries(nmux ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS nmux DESTINATION ${CMAKE_INSTALL_BINDIR})