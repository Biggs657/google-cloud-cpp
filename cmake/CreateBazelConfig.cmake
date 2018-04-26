# Copyright 2018 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Generate a Bazel configuration file with the headers and sources for
# a given target. The generated file can be loaded from a BUILD file
# to create the corresponding targets in Bazel.
function(create_bazel_config TARGET)
  if (NOT TARGET ${TARGET})
    message(FATAL_ERROR "create_bazel_config requires a target name: ${TARGET}")
  endif ()
  set(filename "${TARGET}.bzl")
  set(H)
  set(CC)
  get_target_property(sources ${TARGET} SOURCES)
  foreach (src ${sources})
    string(FIND "${src}" "${CMAKE_CURRENT_BINARY_DIR}" in_binary_dir)
    if ("${in_binary_dir}" EQUAL 0)
      # Skip files in the binary directory, they are generated and
      # handled differently by our Bazel BUILD files.
    elseif ("${src}" MATCHES "\.h$")
      list(APPEND H ${src})
    elseif ("${src}" MATCHES "\.cc$")
      list(APPEND CC ${src})
    endif ()
  endforeach ()
  file(WRITE "${filename}" "# DO NOT EDIT -- GENERATED CODE\n")
  file(APPEND "${filename}" "${TARGET}_HDRS = [\n")
  foreach (src ${H})
    file(APPEND "${filename}" "    \"${src}\",\n")
  endforeach ()
  file(APPEND "${filename}" "]\n\n")
  file(APPEND "${filename}" "${TARGET}_SRCS = [\n")
  foreach (src ${CC})
    file(APPEND "${filename}" "    \"${src}\",\n")
  endforeach ()
  file(APPEND "${filename}" "]\n\n")
endfunction()

# Export a list to a .bzl file, mostly used to export names of unit tests.
function(export_list_to_bazel filename VAR)
  file(WRITE "${filename}" "# DO NOT EDIT -- GENERATED CODE\n")
  file(APPEND "${filename}" "${VAR} = [\n")
  foreach (item ${${VAR}})
    file(APPEND "${filename}" "    \"${item}\",\n")
  endforeach ()
  file(APPEND "${filename}" "]\n\n")
endfunction()
