if(${USE_LAPACK})
	add_subdirectory(ivl-lina)
endif()
if(${USE_OPENCV})
	add_subdirectory(ivl-cv)
endif()
if(${USE_QT})
	add_subdirectory(ivl-qt)
endif()


