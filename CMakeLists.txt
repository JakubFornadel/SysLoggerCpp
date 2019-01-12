cmake_minimum_required( VERSION 3.2 )
add_compile_options("-Wall" "-Werror")
set( CMAKE_CXX_STANDARD 17 )

add_library(SysLoggerCpp SHARED SysLogger.cpp)
target_include_directories(SysLoggerCpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

install(TARGETS
   SysLoggerCpp

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


option(SYSLOGGERCPP_BUILD_EXAMPLES "Build examples." OFF)
if (SYSLOGGERCPP_BUILD_EXAMPLES)
    # add the basic example executable
    add_executable(SyslogExample examples/SyslogExample.cpp)
    target_link_libraries(SyslogExample SysLoggerCpp)

else (SYSLOGGERCPP_BUILD_EXAMPLES)
    message(STATUS "SYSLOGGERCPP_BUILD_EXAMPLES OFF")
endif (SYSLOGGERCPP_BUILD_EXAMPLES)
