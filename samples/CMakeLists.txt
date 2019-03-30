#automatically find and include all samples (all subdirectories)

#file(GLOB LST "." "*")
#PREG_REMOVE("${LST}" "\\\\." L) #exclude filenames and hidden directories
#foreach(h ${L})
#	get_filename_component(c "${h}" NAME)
#	add_subdirectory("${c}")
#endforeach(h)

add_subdirectory("array")
add_subdirectory("full")
add_subdirectory("image")
add_subdirectory("lina")
add_subdirectory("optimization")





