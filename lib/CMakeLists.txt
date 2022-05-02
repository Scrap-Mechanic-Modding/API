add_library(steam_api64 SHARED IMPORTED "${CMAKE_SOURCE_DIR}/lib/steam_api64.lib")
add_library(lz4 STATIC IMPORTED "${CMAKE_SOURCE_DIR}/lib/lz4.lib")
add_library(mygui SHARED IMPORTED "${CMAKE_SOURCE_DIR}/lib/MyGUIEngine.lib")
add_library(luajit SHARED IMPORTED "${CMAKE_SOURCE_DIR}/lib/lua51.lib")