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
	datatoc.c
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	hook::intern::guardedalloc
	hook::source::hooklib
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Executable

add_executable(datatoc ${SRC})
add_executable(hook::source::datatoc ALIAS datatoc)

hook_target_link_libraries(datatoc "${LIB}")
hook_target_include_dirs(datatoc "${INC}")
