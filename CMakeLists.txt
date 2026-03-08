cmake_minimum_required(VERSION 3.20)

project(misis2026s-25-00-polevoi-d-v)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}bin.relwithdbg)

set(CMAKE_CXX_STANDARD 20)

include_directories(prj.labs prj.thirdparty)

add_subdirectory(prj.labs)
add_subdirectory(prj.test)

find_package(Doxygen) # REQUIRED - todo later
option(BUILD_DOCUMENTATION "Create HTML based documentation (requires Doxygen)" 0) # ${DOXYGEN_FOUND})

if (BUILD_DOCUMENTATION)
  message("Doxygen build added.")
  configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in"
      "${CMAKE_CURRENT_BINARY_DIR}/doxyfile"
      @ONLY
  )
  doxygen_add_docs(
      doc # Name of the custom target
      ${CMAKE_CURRENT_SOURCE_DIR}/prj.labs # Input directory
      ${CMAKE_CURRENT_SOURCE_DIR}/prj.test # Input directory
      ALL # Generate documentation for all files
  )
  add_custom_target(doxygen_docs ALL DEPENDS doc)
else(BUILD_DOCUMENTATION)
  message("DOXYGEN_FOUND=${DOXYGEN_FOUND}")
endif(BUILD_DOCUMENTATION)
