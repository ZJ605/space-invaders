cmake_minimum_required ( VERSION 3.21.2 )

project (
  space_invaders
  VERSION 1.0
  LANGUAGES C
)

add_executable (space_invaders src/main.c src/game.c src/ship.c src/list.c src/debugger_logger.c src/alphabet.c)

target_include_directories (space_invaders PRIVATE src)

set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS} -fsanitize=address -Wall")

############## SDL
add_subdirectory (dependencies/SDL)

set( SDL_TEST OFF CACHE BOOL "" FORCE )
set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )

include_directories(dependencies/SDL/include)
target_link_libraries (space_invaders SDL2main SDL2-static)
############## END SDL

############## SDL IMAGE
add_subdirectory (dependencies/SDL_image)

include_directories (dependencies/SDL_image)

target_link_libraries (space_invaders SDL2_image)
############## END SDL IMAGE

############## COPY IMAGES
if (NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
	FILE (COPY res/ship1.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/enemy1.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/blast1.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/blast2.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/missile.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/smallblast.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/space.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/white_rectangle.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/green_rectangle.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/alphabet.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/alphabet2.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/white_button.png DESTINATION "${CMAKE_BINARY_DIR}/res")
	FILE (COPY res/blue_rectangle.png DESTINATION "${CMAKE_BINARY_DIR}/res")
endif()



