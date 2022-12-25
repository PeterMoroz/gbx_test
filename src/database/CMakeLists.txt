add_library(database database.cpp users_db.cpp)
target_include_directories(database PUBLIC include)
target_link_libraries(database
	PRIVATE
	${CONAN_LIBS})
	
