if(NOT EXISTS ${destinationfile})
  execute_process(COMMAND ${CMAKE_COMMAND}
  -E copy ${sourcefile} ${destinationfile})
endif()
