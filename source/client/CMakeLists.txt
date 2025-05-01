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
	${DETOURS_INCLUDE_DIRS}
	
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
	${DETOURS_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Library

hook_add_dll(client "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
