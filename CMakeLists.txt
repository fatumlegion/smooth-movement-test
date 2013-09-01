project (smTest)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set (smTest_SRCS
	src/main.cpp
	src/Application.cpp
	src/Player.cpp
	src/TestWorld.cpp	
)

set (smTest_LIBS
	sfml-graphics
	sfml-window
	sfml-audio
	sfml-system
)

add_executable(smt ${smTest_SRCS})
target_link_libraries(smt ${smTest_LIBS})