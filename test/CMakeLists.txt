include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

add_executable(test_eval
	test_eval.cxx
)

target_link_libraries(test_eval
	PRIVATE Catch2::Catch2WithMain
	PRIVATE fmt::fmt
)
target_include_directories(test_eval
	PRIVATE ${PROJECT_SOURCE_DIR}
	PUBLIC ${PROJECT_SOURCE_DIR}/vendor/fmt/include
)
