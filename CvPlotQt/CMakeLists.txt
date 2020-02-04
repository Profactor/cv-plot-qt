# CvPlotQt - https://github.com/Profactor/cv-plot-qt
# Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

cmake_minimum_required (VERSION 3.9)
set(target CvPlotQt)
project (${target})

add_library(${target}
    inc/CvPlotQt/AxesView.h
    inc/CvPlotQt/DrawableQuick.h
    inc/CvPlotQt/ImageQuick.h
    inc/CvPlotQt/libdef.h
    inc/CvPlotQt/registerQtTypes.h
    inc/CvPlotQt/SeriesQuick.h
    inc/CvPlotQt/version.h
    inc/CvPlotQt/Internal/declareQtTypes.h
    src/AxesView.cpp
    src/ImageQuick.cpp
    src/registerQtTypes.cpp
    src/SeriesQuick.cpp
    src/version.cpp
)
add_library(${target}::${target} ALIAS ${target})
target_compile_definitions(${target} PRIVATE CVPLOTQT_BUILDING)
if(BUILD_SHARED_LIBS)
	target_compile_definitions(${target} PUBLIC CVPLOTQT_SHARED)
endif()
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#CvPlot
if(NOT TARGET CvPlot::CvPlot)
    find_package(CvPlot REQUIRED)    
endif()
target_link_libraries(${target} CvPlot::CvPlot)

#Qt
find_package(Qt5 COMPONENTS Quick)
target_link_libraries(${target} Qt5::Quick)
set_target_properties(${target} PROPERTIES AUTOMOC ON AUTORCC ON)

#Tests and Examples
option(CVPLOTQT_WITH_TESTS "Build with tests" ON)
option(CVPLOTQT_WITH_EXAMPLES "Build with examples" ON)
if(CVPLOTQT_WITH_TESTS OR CVPLOTQT_WITH_EXAMPLES)
    add_subdirectory(ext/catch2 catch2)
endif()
if(CVPLOTQT_WITH_TESTS)
    add_subdirectory(tests)
endif()
if(CVPLOTQT_WITH_EXAMPLES)
    add_subdirectory(examples)
endif()

