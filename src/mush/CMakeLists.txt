file(GLOB_RECURSE SOURCES "*.c")

add_executable(mush ${SOURCES})
target_include_directories(
    mush
    PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src/mush"
    )
