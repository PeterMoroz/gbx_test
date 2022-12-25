add_executable(database_test database_test.cpp)

target_link_libraries(database_test
	PRIVATE
	${CONAN_LIBS}
	database)
	
add_test(
	NAME database_test
	COMMAND database_test)
