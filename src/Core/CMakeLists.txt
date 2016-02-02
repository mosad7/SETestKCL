
file(GLOB_RECURSE tmp_CXX "*.cpp")
set(CORE_CXX ${tmp_CXX} PARENT_SCOPE)

file(GLOB_RECURSE tmp_HEADERS "*.h")
set(CORE_H ${tmp_HEADERS} PARENT_SCOPE)

set(INCLUDE_DIRS "")
foreach(_headerFile ${tmp_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list(APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)
set(SETestKCL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)