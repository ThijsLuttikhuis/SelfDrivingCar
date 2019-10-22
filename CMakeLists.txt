cmake_minimum_required( VERSION 3.14 )
set( CMAKE_CXX_STANDARD 14 )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project( SelfDrivingCar )
find_package( OpenCV REQUIRED )
find_package( Threads REQUIRED )

add_executable( SelfDrivingCar main.cpp

        ImageProcessor.cpp
        ImageProcessor.h
        Drawer.cpp
        Drawer.h
        Timer.cpp
        Timer.h
        dataStructures/Segmentation.h
        dataStructures/Segmentation.cpp
        dataStructures/ColumnSegment.h
        dataStructures/RowCol.h dataStructures/Line.cpp dataStructures/Line.h dataStructures/LineFinder.cpp dataStructures/LineFinder.h)

target_link_libraries( SelfDrivingCar ${OpenCV_LIBS} )
target_link_libraries( SelfDrivingCar ${CMAKE_THREAD_LIBS_INIT} )
