cmake_minimum_required(VERSION 3.1)
project(CallGraphProject)
add_library(CallGraph MODULE
    # List your source files here.
        CallGraph.cpp  Graph.cpp Graph.h PointerAnalysis.cpp PointerAnalysis.h)
target_link_libraries(CallGraph)
# Use C++11 to compile our pass (i.e., supply -std=c++11).
target_compile_features(CallGraph PRIVATE cxx_range_for cxx_auto_type)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# LLVM is (typically) built with no C++ RTTI. We need to match that.
# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
# LLVM is (typically) built with no C++ RTTI. We need to match that.
set_target_properties(CallGraph PROPERTIES
        COMPILE_FLAGS "-fno-rtti"
        )
if(APPLE)
    set_target_properties(CallGraph PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
set( EXECUTABLE_OUTPUT_PATH "build/")
