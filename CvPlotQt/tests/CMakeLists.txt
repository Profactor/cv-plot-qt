# CvPlotQt - https://github.com/Profactor/cv-plot-qt
# Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

set(target CvPlotQtTests)
project(${target} CXX)
cmake_minimum_required (VERSION 3.9)
add_executable(${target}
    main.cpp
    test_plotqt.cpp
)
target_link_libraries(${target} CvPlotQt::CvPlotQt Catch2::Catch2)
