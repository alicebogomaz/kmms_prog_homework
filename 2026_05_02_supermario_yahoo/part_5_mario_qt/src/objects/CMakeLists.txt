target_sources(${PROJECT_NAME}
	PRIVATE
		full_box.cpp
		enemy.cpp
		mario.cpp
		money.cpp
		moving_platforms.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
