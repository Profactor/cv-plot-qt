# CvPlotQt - https://github.com/Profactor/cv-plot-qt
# Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

set(target CvPlotQtExamples)
project(${target} CXX)
cmake_minimum_required (VERSION 3.9)
add_executable(${target}
    inc/Helpers.h
    qrc/DemoOneMinute.qml
    qrc/DemoProperties.qml
    qrc/DemoSync.qml
    qrc/DemoTwoMinutes.qml
    qrc/ui.qrc
    src/main.cpp
    src/examples.cpp
    src/Helpers.cpp
)
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${target} CvPlotQt::CvPlotQt Catch2::Catch2)

#data
function(copyfile file)
	add_custom_command(TARGET ${target} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy 
			${CMAKE_CURRENT_SOURCE_DIR}/${file} 
			$<TARGET_FILE_DIR:${target}>/${file}
		COMMENT "copy ${file}..."
	)
endfunction()
copyfile(exampledata/Lenna.jpg)

#Qt resources
set_target_properties(${target} PROPERTIES AUTOMOC ON AUTORCC ON)

#visual studio working directory
get_target_property(outdir ${target} RUNTIME_OUTPUT_DIRECTORY)
set_target_properties(${target} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${outdir})

