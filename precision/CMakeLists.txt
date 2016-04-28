include_directories("${CMAKE_SOURCE_DIR}")

set(HEADER_FILES 
  bilinear_interpolation.hxx
  point.hxx
  point3d.hxx
  tie_point.hxx
  evaluation_measurements.hxx
  math.hxx
  vector.hxx
  vector_utils.hxx
  vector_normalizer.hxx
  interpolation.hxx
)

set(SRC_FILES
  bilinear_interpolation.cxx
  point.cxx
  point.cxx
  tie_point.cxx
  evaluation_measurements.cxx
  math.cxx
  vector.cxx
  vector_utils.cxx
  vector_normalizer.cxx
)

add_library(precision SHARED
  ${HEADER_FILES}
  ${SRC_FILES}
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_link_libraries(precision dl)
endif()

# target_link_libraries(precision rt)

install(TARGETS precision
  RUNTIME DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")

install(FILES ${HEADER_FILES} 
  DESTINATION "include/precision")

