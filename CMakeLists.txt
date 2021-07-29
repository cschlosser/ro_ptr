cmake_minimum_required(VERSION 3.1)
project(ro_ptr
    VERSION 0.1
    DESCRIPTION "Readonly pointer wrapper"
    LANGUAGES CXX
)
include(GNUInstallDirs)

add_library(ptr INTERFACE)

add_library(readonly::ptr ALIAS ptr)

target_include_directories(ptr
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>  
        $<INSTALL_INTERFACE:include/>
)

install(TARGETS ptr
    EXPORT ro_ptr-export
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT ro_ptr-export
    FILE ro_ptrConfig.cmake
        NAMESPACE readonly::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ro_ptr
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
        FILES_MATCHING PATTERN "*.h")

option(BUILD_EXAMPLES "Build examples for ro_ptr" ON)

if(${BUILD_EXAMPLES})
    add_executable(showcase examples/showcase.cc)
    target_link_libraries(showcase PRIVATE readonly::ptr)
endif()

