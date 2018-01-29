file(GLOB_RECURSE SOURCES "*.c")
add_executable(mush-as ${SOURCES})
target_include_directories(
    mush-as
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/include")
