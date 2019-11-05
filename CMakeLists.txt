cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project(SelfDrivingCar)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

# The GPIO part is only needed when running on the Pi
set(USE_PI 0)

if(USE_PI)
    add_definitions(-DUSE_PI=1)
    message("Raspberry Pi set")
    find_library(wiringPi_LIB wiringPi REQUIRED)
else()
    message("Ubuntu set")
endif()

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
        IMAGE_PROCESSING/dataStructures/RoadLine.cpp
        IMAGE_PROCESSING/dataStructures/RoadLine.h

        # Helper structures
        IMAGE_PROCESSING/dataStructures/Filters.h
        IMAGE_PROCESSING/dataStructures/Pixel.h
        IMAGE_PROCESSING/dataStructures/ThreadArgs.h
        IMAGE_PROCESSING/dataStructures/Filters.cpp
        IMAGE_PROCESSING/image_processing.h
        )

set(CONTROL_SOURCES
        CONTROL/CarPositionBuffer.cpp
        CONTROL/CarPositionBuffer.h
        )

set(GPIO_SOURCES
        )

add_executable(SelfDrivingCar
        main.cpp
        node.cpp
        node.h
        CarPosition.h

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
        GPIO/gpio.cpp
        GPIO/gpio.h
        ${GPIO_SOURCES}
        )

target_link_libraries(SelfDrivingCar ${OpenCV_LIBS})
target_link_libraries(SelfDrivingCar ${CMAKE_THREAD_LIBS_INIT})

if (USE_PI)
    target_link_libraries(SelfDrivingCar ${wiringPi_LIB})
endif()