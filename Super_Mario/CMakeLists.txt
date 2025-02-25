# CMakeList.txt : CMake project for Super_Mario, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Super_Mario "Super_Mario.cpp" "Super_Mario.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Super_Mario PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
