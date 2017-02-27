cmake_minimum_required(VERSION 2.8.3)
project(cyborg_idle)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	actionlib_msgs
	actionlib
	cyborg_controller
)

find_package(Boost REQUIRED COMPONENTS 
	system
)

catkin_package(
	CATKIN_DEPENDS message_runtime
	CATKIN_DEPENDS actionlib_msgs
	CATKIN_DEPENDS roslib roscpp actionlib message_generation
)

include_directories(${catkin_INCLUDE_DIRS})

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(cyborg_idle 
				src/main.cpp         	
)

add_dependencies(cyborg_idle cyborg_controller_generate_messages_cpp ${catkin_EXPORTED_TARGETS})

target_link_libraries(cyborg_idle ${catkin_LIBRARIES})

install(TARGETS cyborg_idle
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
	DESTINATION  ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
