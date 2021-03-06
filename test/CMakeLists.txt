cmake_minimum_required (VERSION 2.8)
project (xLinqTests)

include_directories("../include")

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
    add_definitions(-Wall)
    add_definitions(-Wpedantic)
endif()

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

message("Detecting tests...")
file(GLOB xLinqTestsSrcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*test.cpp" )
add_executable(xlinq_test_runner "xlinq_test_runner.cpp" ${xLinqTestsSrcs})
target_link_libraries(xlinq_test_runner ${GTEST_BOTH_LIBRARIES})
#add_test(xlinq_test_runner xlinq_test_runner)
foreach (test ${xLinqTestsSrcs})
	file(READ "${test}" contents)
	string(REGEX MATCHALL "TEST\\(([a-zA-Z]|_)*,( )*([a-zA-Z]|_)*" matches ${contents})
	foreach (match ${matches})
		string(REPLACE "TEST(" "" match "${match}")
		string(REGEX REPLACE ",( )*" "." match "${match}")
		#message("Adding test: xlinq_test_runner --gtest_filter=${match}")
		add_test("${match}" xlinq_test_runner --gtest_filter=${match})
	endforeach()
endforeach()