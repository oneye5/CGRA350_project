add_library(imgui
	imconfig.h
	imgui.h
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_internal.h
	imgui_widgets.cpp
	imgui_tables.cpp
)

target_include_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR}/ext/imgui")
