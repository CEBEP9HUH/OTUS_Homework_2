cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.42)
endif()

configure_file(description.json.in description.json)

add_library(ip_filter_lib STATIC ip_filter_lib.cpp)
add_executable(ip_filter_tests ip_filter_tests.cpp) 
add_executable(ip_filter ip_filter.cpp)

set_target_properties(ip_filter ip_filter_lib ip_filter_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(ip_filter_tests ${GTEST_LIBRARIES} pthread ip_filter_lib)

if(MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_tests PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
else()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
    target_compile_options(ip_filter_tests PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()
add_test(ip_filter_tests ip_filter_tests)