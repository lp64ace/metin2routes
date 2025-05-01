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
	${PTHREADS_INCLUDE_DIRS}
	${DETOURS_INCLUDE_DIRS}
	
)

# -----------------------------------------------------------------------------
# Define Source Files

set(SRC
	KER_global.h
	KER_main.h
	
	intern/global.c
	intern/global_launch_json.c
	intern/main.c
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	hook::extern::cjson
	hook::intern::guardedalloc
	hook::source::hooklib
	hook::source::launch
	
	# External Library Dependencies
	PUBLIC ${PTHREADS_LIBRARIES}
	PUBLIC ${DETOURS_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Library

hook_add_lib(kernel "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(hook::source::kernel ALIAS kernel)

# -----------------------------------------------------------------------------
# Define Include Directories (Test)

set(INC
	# Internal Include Directories
	PUBLIC .
	
	# External Include Directories
	
)

# -----------------------------------------------------------------------------
# Define System Include Directories (Test)

set(INC_SYS
	# External System Include Directories
	
)

# -----------------------------------------------------------------------------
# Define Source Files (Test)

set(TEST
)

# -----------------------------------------------------------------------------
# Define Library Dependencies (Test)

set(LIB
	# Internal Library Dependencies
	hook::intern::guardedalloc
	hook::source::kernel
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Test

# hook_add_test_executable(kernel "${TEST}" "${INC}" "${INC_SYS}" "${LIB}")
