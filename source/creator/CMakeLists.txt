# -----------------------------------------------------------------------------
# Define Include Directories

set(INC
	# Internal Include Directories
	PUBLIC .
	
	# External Include Directories
	${DETOURS_INCLUDE_DIRS}
	
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
	${DETOURS_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Library

hook_add_dll(predator "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
