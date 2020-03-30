#
# Targets
#

add_library(vtsbls 
    LibVTSBls.cpp
)

target_include_directories(vtsbls PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${INSTALL_CMAKE_DIR}/include>"
)

target_link_libraries(vtsbls PUBLIC
    ff pthread zm gmp gmpxx
)

include(FindOpenMP)
if(OPENMP_FOUND)
    target_link_libraries(vtsbls PUBLIC gomp)
endif()

#target_link_libraries(vtsbls PUBLIC Threads::Threads)

#
# Installation
# TODO: Add <Package>Config[Version].cmake files so this package can be easily imported?
# (See https://cmake.org/cmake/help/git-master/manual/cmake-packages.7.html#creating-packages)
#

# This creates the <Package>Config.cmake file and installs it
install(TARGETS vtsbls EXPORT vtsblsConfig 
   ARCHIVE DESTINATION lib)
install(EXPORT vtsblsConfig DESTINATION lib/cmake/vtsbls)

# This installs the static or (/and?) dynamic library
install(TARGETS vtsbls 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# This installs the headers
# WARNING: Don't add / at the end. No slash means vtsbls/ directory is created in the destination path
install(DIRECTORY include/vtsbls DESTINATION include)
