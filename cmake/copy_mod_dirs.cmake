# Copy all mods under runtime/mod with their versions.
# Example: mod "core" version 1.2.3 is copied to mod/core-1.2.3
#
# Arguments
# =========
# mod_root_dir   The source folder.
# target         The destination folder.


file(GLOB mod_dirs ${mod_root_dir}/*)
foreach(mod_dir IN LISTS mod_dirs)
  get_filename_component(mod_id ${mod_dir} NAME)
  set(manifest_file ${mod_dir}/mod.json)
  if(EXISTS ${manifest_file})
    file(READ ${manifest_file} manifest)
    if(${manifest} MATCHES "version: \"([^\"]*)\"")
      set(mod_version ${CMAKE_MATCH_1})
      set(new_dir_name ${mod_id}-${mod_version})
      message(STATUS "Copy mod: ${new_dir_name}")
      execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${mod_dir} ${target}/${new_dir_name})
    else()
      message(FATAL_ERROR "Failed to get mod version: ${manifest}")
    endif()
  endif()
endforeach()
