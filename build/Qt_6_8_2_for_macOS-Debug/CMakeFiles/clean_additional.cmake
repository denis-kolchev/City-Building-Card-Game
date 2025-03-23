# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CityBuildingCardGame_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CityBuildingCardGame_autogen.dir/ParseCache.txt"
  "CityBuildingCardGame_autogen"
  )
endif()
