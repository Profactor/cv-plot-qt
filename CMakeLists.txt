# CvPlotQt - https://github.com/Profactor/cv-plot-qt
# Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

cmake_minimum_required (VERSION 3.9)
project (cv-plot-qt)

option(BUILD_SHARED_LIBS "Build shared libs" ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(CvPlotQt)
