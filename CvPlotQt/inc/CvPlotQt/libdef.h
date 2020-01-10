// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#pragma once

#ifdef _WIN32
	#ifdef CVPLOTQT_SHARED
		#ifdef CVPLOTQT_BUILDING
			#define CVPLOTQT_LIBRARY_INTERFACE __declspec(dllexport)
		#else
			#define CVPLOTQT_LIBRARY_INTERFACE __declspec(dllimport)
		#endif
	#else
		//static
		#define CVPLOTQT_LIBRARY_INTERFACE
	#endif
#else
	//non-windows
	#define CVPLOTQT_LIBRARY_INTERFACE
#endif
