# CMake for WWIV
include_directories(../deps/cl342)
include_directories(../deps/cereal/include)
Include(FindWWIVCurses)

set(COMMON_SOURCES 
 bgetch.cpp
 bputch.cpp
 checka.cpp
 com.cpp
 context.cpp
 datetime.cpp
 full_screen.cpp
 input.cpp
 input_range.cpp
 iobase.cpp
 macro_context.cpp
 menu_data_util.cpp
 message_editor_data.cpp
 output.cpp
 pause.cpp
 printfile.cpp
 quote.cpp
 remote_io.cpp
 remote_socket_io.cpp
 workspace.cpp
)

add_library(
  common 
  ${COMMON_SOURCES} 
) 

target_link_libraries(
  common 
  fmt::fmt-header-only
  local_io 
  core 
  sdk 
)

set_max_warnings()

target_include_directories(common PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
