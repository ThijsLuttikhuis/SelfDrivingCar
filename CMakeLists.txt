cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project(SelfDrivingCar)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

set(IMAGE_PROCESSING_SOURCES
        IMAGE_PROCESSING/imageProcessing/ImageProcessor.cpp
        IMAGE_PROCESSING/imageProcessing/ImageProcessor.h

        # Processing parts
        IMAGE_PROCESSING/imageProcessing/Segmentation.h
        IMAGE_PROCESSING/imageProcessing/Segmentation.cpp
        IMAGE_PROCESSING/imageProcessing/LineFinder.cpp
        IMAGE_PROCESSING/imageProcessing/LineFinder.h
        IMAGE_PROCESSING/imageProcessing/LinePositionFinder.cpp
        IMAGE_PROCESSING/imageProcessing/LinePositionFinder.h
        IMAGE_PROCESSING/imageProcessing/CarPositionFinder.cpp
        IMAGE_PROCESSING/imageProcessing/CarPositionFinder.h
        )

set(UTILITIES_SOURCES
        IMAGE_PROCESSING/utilities/Drawer.cpp
        IMAGE_PROCESSING/utilities/Drawer.h
        IMAGE_PROCESSING/utilities/Timer.cpp
        IMAGE_PROCESSING/utilities/Timer.h
        )

set(DATA_STRUCTURES_SOURCES
        IMAGE_PROCESSING/dataStructures/RowCol.h
        IMAGE_PROCESSING/dataStructures/ColumnSegment.h
        IMAGE_PROCESSING/dataStructures/Line.cpp
        IMAGE_PROCESSING/dataStructures/Line.h
        IMAGE_PROCESSING/imageProcessing/RoadLine.cpp
        IMAGE_PROCESSING/imageProcessing/RoadLine.h
        CarPosition.h

        # Helper structures
        IMAGE_PROCESSING/dataStructures/Filters.h
        IMAGE_PROCESSING/dataStructures/Pixel.h
        IMAGE_PROCESSING/dataStructures/ThreadArgs.h
        IMAGE_PROCESSING/dataStructures/Filters.cpp
        IMAGE_PROCESSING/image_processing.h
        )

set(CONTROL_SOURCES
        node.cpp node.h)

add_executable(SelfDrivingCar
        main.cpp

        # Image Processing
        IMAGE_PROCESSING/image_processing.cpp
        IMAGE_PROCESSING/image_processing.h

        ${IMAGE_PROCESSING_SOURCES}
        ${UTILITIES_SOURCES}
        ${DATA_STRUCTURES_SOURCES}

        # Control
        CONTROL/control.cpp
        CONTROL/control.h

        ${CONTROL_SOURCES}

        # GPIO

        )

target_link_libraries(SelfDrivingCar ${OpenCV_LIBS})
target_link_libraries(SelfDrivingCar ${CMAKE_THREAD_LIBS_INIT})
