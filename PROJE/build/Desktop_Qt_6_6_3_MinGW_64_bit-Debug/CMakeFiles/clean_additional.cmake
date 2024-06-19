# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\My3DProject_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\My3DProject_autogen.dir\\ParseCache.txt"
  "My3DProject_autogen"
  )
endif()
