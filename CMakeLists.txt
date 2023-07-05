cmake_minimum_required (VERSION 3.20)
project (kami)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

#find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
#find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
#find_library(APPLE_FWK_METAL Metal REQUIRED)

file(GLOB SRC_FILES CONFIGURE_DEPENDS
        "src/*/*.cpp"
        "src/*.cpp"
        )

add_executable(app ${SRC_FILES})

#target_include_directories(app
#  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/metal-cpp
#  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}
#)

#target_link_libraries(metal_cpp_rocks
#  ${APPLE_FWK_FOUNDATION}
#  ${APPLE_FWK_QUARTZ_CORE}
#  ${APPLE_FWK_METAL}
#)