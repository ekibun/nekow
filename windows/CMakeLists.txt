cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "nekow")
project(${PROJECT_NAME} LANGUAGES CXX)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(${PROJECT_NAME}
  "main.cpp"
)
target_link_libraries(${PROJECT_NAME} 
  "${CMAKE_CURRENT_SOURCE_DIR}/webview/WebView2LoaderStatic.lib"
  version
)