set(LIB "network-uri")
set(NETWORK_URI_LIBRARY ${LIB} PARENT_SCOPE)

set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src//uri.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//uri_builder.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//uri_errors.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//detail/uri_parse.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//detail/uri_parse_authority.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//detail/uri_advance_parts.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//detail/uri_normalize.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src//detail/uri_resolve.cpp"
  )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_definitions("-DNETWORK_URI_EXTERNAL_BOOST")

add_library(${LIB} STATIC ${SOURCES})
