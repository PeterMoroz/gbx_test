add_library(application application.cpp handlers.cpp handlers_factory.cpp)
target_include_directories(application PUBLIC include)
target_link_libraries(application
	PRIVATE
	database
	${CONAN_LIBS})
