# -----------------------------------------------------------------------------
# Define Include Directories

set(INC
	# Internal Include Directories
	PUBLIC .
	
	# External Include Directories
	
)

# -----------------------------------------------------------------------------
# Define System Include Directories

set(INC_SYS
	# External System Include Directories
	
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
	hook::intern::guardedalloc
	hook::source::hooklib
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Library

add_executable(target "${SRC}")

hook_target_link_libraries(target "${LIB}")
hook_target_include_dirs(target "${INC}")
