add_executable(gbx_main main.cpp)
target_link_libraries(gbx_main
	PRIVATE
	${CONAN_LIBS}
	database
	application)
	
