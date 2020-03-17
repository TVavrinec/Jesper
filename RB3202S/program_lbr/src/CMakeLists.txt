# Warning! This code was automatically generated for projects
# without default 'CMakeLists.txt' file.

set(app_sources
	"RB3202_DRV8833.cpp"
	"RB3202_PID.cpp"
	"RB3202_driver.cpp"
	"RB3202_encoder.cpp"
	"RB3202_set.cpp"
	"RB3202_stepdriver.cpp"
	"RB3202_user_interface.cpp"
	"main.cpp"
)

idf_component_register(SRCS ${app_sources})
