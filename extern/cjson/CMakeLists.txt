# -----------------------------------------------------------------------------
# Declare Include Directories

set(INC
	# Common Include Directories
	PUBLIC .
	
	# Internal Include Directories
	
)

# -----------------------------------------------------------------------------
# Declare System Include Directories

set(INC_SYS
	# External Include Directories

)

# -----------------------------------------------------------------------------
# Declare Source Files

set(SRC
	cjson.h
	cjson.c
)

# -----------------------------------------------------------------------------
# Declare Library Dependencies

set(LIB
	# Internal Include Directories
	
	# External Include Directories
	
)

# -----------------------------------------------------------------------------
# Declare Library

hook_add_lib(cjson "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(hook::extern::cjson ALIAS cjson)
