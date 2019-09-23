#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
 
##################################################################
# Support macro to use a precompiled header
# Usage:
#   use_precompiled_header(TARGET HEADER_FILE SRC_FILE)
##################################################################
 
macro (add_precompiled_header TARGET HEADER_FILE SRC_FILE)
  get_filename_component (HEADER ${HEADER_FILE} NAME)
  if (MSVC)
    add_definitions (/Yu"${HEADER}")
    set_source_files_properties (${SRC_FILE} PROPERTIES COMPILE_FLAGS /Yc"${HEADER}")
  endif ()
endmacro (add_precompiled_header)