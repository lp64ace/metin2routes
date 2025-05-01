# -----------------------------------------------------------------------------
# Define Include Directories

set(INC
	# Internal Include Directories
	PUBLIC .
	
	# External Include Directories
	
)

# -----------------------------------------------------------------------------
# Define Source Files

set(SRC
	main.c
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	hook::extern::cjson
	hook::intern::guardedalloc
	hook::source::hooklib
	hook::source::kernel
	hook::source::launch
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Library

add_executable(creator "${SRC}")

hook_target_link_libraries(creator "${LIB}")
hook_target_include_dirs(creator "${INC}")
