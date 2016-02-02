
##############################################################################
# Include libraries
#-----------------------------------------------------------------------------


##############################################################################
# Locations for other source files, and runtime and shared libraries
#-----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/SETestKCL)

file(GLOB LOCAL_CXX "*.cpp")
file(GLOB LOCAL_HEADERS "*.h")

set(ALL_CXX_FILES ${CORE_CXX} ${LOCAL_CXX})
set(ALL_H_FILES ${CORE_H} ${LOCAL_HEADERS})

##############################################################################
# Link libraries and add executable
#-----------------------------------------------------------------------------
ADD_EXECUTABLE(SETestKCL main.cpp ${ALL_CXX_FILES} ${ALL_H_FILES})





