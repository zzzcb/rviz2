cmake_minimum_required(VERSION 3.16)

project(rviz2_zcb)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Default moc/uic/rcc to ON
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Woverloaded-virtual)
endif()

# find Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# find OGRE
if(UNIX AND NOT APPLE)
  set(OGRE_DIR "/opt/ogre_1.12.1/")
elseif(WIN32)
  set(OGRE_DIR "D:/dependency/ogre_1.12.1/")
elseif(APPLE)

endif()
find_package(OGRE REQUIRED)

# find assimp
find_package(assimp REQUIRED)

# find libcurl
find_package(CURL REQUIRED)

# find Eigen3
find_package(Eigen3 REQUIRED)

# ros dependency(will be remove later.)
# find rclcpp
find_package(rclcpp REQUIRED)







# #... 
# file(GLOB FILENAMES "${CMAKE_CURRENT_SOURCE_DIR}/*")
# #file(GLOB_RECURSE  rviz_common_files "${CMAKE_CURRENT_SOURCE_DIR}/rviz_common/*")
# #file(GLOB_RECURSE  rviz_rendering_files "${CMAKE_CURRENT_SOURCE_DIR}/rviz_rendering/*")
# qt_add_executable(rviz ${FILENAMES} ${rviz_common_files} ${rviz_rendering_files})

# target_link_libraries(rviz PUBLIC Qt6::Widgets ${OGRE_LIBRARIES} ${libcurl_LIBRARIES})

# target_include_directories(rviz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${assimp_INCLUDE_DIRS} ${libcurl_INCLUDE_DIRS} ${Eigen_INCLUDE_DIRS})
# target_link_libraries(rviz PUBLIC ${assimp_LIBRARIES})

# if(MSVC)
# 	set_property(TARGET rviz PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$ENV{OGRE_HOME}/bin")
# endif()


