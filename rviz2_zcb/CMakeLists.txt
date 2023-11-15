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


# source code [mesh loader]
file(GLOB MESH_LOADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/mesh_loader/*")

# source code [rviz common]
file(GLOB RVIZ_COMMON_FILES "${CMAKE_CURRENT_SOURCE_DIR}/rviz_common/*")



add_executable(${PROJECT_NAME} ${MESH_LOADER_FILES} ${RVIZ_COMMON_FILES} main.cpp)
 
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt::Core Qt::Gui Qt::Widgets ${OGRE_LIBRARIES}
  ${ASSIMP_LIBRARIES}
  ${CURL_LIBRARIES}
  )
target_include_directories(${PROJECT_NAME} PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
  )

