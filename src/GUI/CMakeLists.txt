#message("GUI is not supported yet")

CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
project(SETestKCL_GUI)

##############################################################################
# Include libraries
#-----------------------------------------------------------------------------
# Qt5
find_package(Qt5Widgets REQUIRED)
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})

##############################################################################
# Locations for other source files, and runtime and shared libraries
#-----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/SETestKCL_GUI)

#Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC TRUE)
FILE(GLOB QT_UI_FILES *.ui)
QT5_WRAP_UI(QTUISrcs ${QT_UI_FILES})
FILE(GLOB QRC_FILES res/*.qrc)
QT5_ADD_RESOURCES(QTQRCSrcs ${QRC_FILES})

file(GLOB LOCAL_CXX "*.cpp")
file(GLOB LOCAL_HEADERS "*.h")

set(ALL_CXX_FILES ${CORE_CXX} ${LOCAL_CXX})
set(ALL_H_FILES ${CORE_H} ${LOCAL_HEADERS})

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

##############################################################################
# Link libraries and add executable
#-----------------------------------------------------------------------------
ADD_EXECUTABLE(SETestKCL_GUI main.cpp ${ALL_CXX_FILES} ${ALL_H_FILES} ${QTUISrcs} ${QTQRCSrcs})

set(QTX_Libraries Qt5::Widgets)
TARGET_LINK_LIBRARIES(SETestKCL_GUI ${QTX_Libraries})
