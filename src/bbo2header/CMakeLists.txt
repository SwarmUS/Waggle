set(THIS bbo2header)

set(SOURCES
    bbo2header.cpp
)


add_library(${THIS} STATIC ${SOURCES})

#including headers
target_include_directories(${THIS} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#allows to include "spi.hpp" instead of "spi/spi.hpp"
target_include_directories(${THIS} PUBLIC ${PROJECT_SOURCE_DIR}/include/${THIS})

# Allows to automatically add the correct include directories with "target_link_libraries"
target_include_directories(${THIS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})