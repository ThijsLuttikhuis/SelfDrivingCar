cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project(SelfDrivingCar)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

set(IMAGE_PROCESSING_SOURCES
        imageProcessing/ImageProcessor.cpp
        imageProcessing/ImageProcessor.h
        imageProcessing/Segmentation.h
        imageProcessing/Segmentation.cpp
        )

set(UTILITIES_SOURCES
        utilities/Drawer.cpp
        utilities/Drawer.h
        utilities/Timer.cpp
        utilities/Timer.h
        )

set(DATA_STRUCTURES_SOURCES
        dataStructures/ColumnSegment.h
        dataStructures/RowCol.h
        dataStructures/Line.cpp
        dataStructures/Line.h
        imageProcessing/LineFinder.cpp
        imageProcessing/LineFinder.h
        dataStructures/Filters.h dataStructures/Pixel.h dataStructures/ThreadArgs.h)

add_executable(SelfDrivingCar
        main.cpp
        ${IMAGE_PROCESSING_SOURCES}
        ${UTILITIES_SOURCES}
        ${DATA_STRUCTURES_SOURCES}
        )

target_link_libraries(SelfDrivingCar ${OpenCV_LIBS})
target_link_libraries(SelfDrivingCar ${CMAKE_THREAD_LIBS_INIT})
