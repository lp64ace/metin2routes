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
	
)

# -----------------------------------------------------------------------------
# Define Source Files

set(SRC
	LIB_assert.h
	LIB_listbase.h
	LIB_memory.h
	LIB_string.h
	LIB_sys_types.h
	LIB_utildefines.h
	LIB_utildefines_variadic.h
	
	algorithm/rabin_karp.c
	algorithm/rabin_karp.h
	
	intern/assert.c
	intern/listbase.c
	intern/memory.c
	intern/string.c
	intern/utildefines.c
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	hook::intern::guardedalloc
	
	# External Library Dependencies
	PUBLIC ${PTHREADS_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Library

hook_add_lib(hooklib "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(hook::source::hooklib ALIAS hooklib)

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
	${PTHREADS_INCLUDE_DIRS}
	
)

# -----------------------------------------------------------------------------
# Define Source Files (Test)

set(TEST
	test/listbase.cc
	test/string.cc
)

# -----------------------------------------------------------------------------
# Define Library Dependencies (Test)

set(LIB
	# Internal Library Dependencies
	hook::intern::guardedalloc
	hook::source::hooklib
	
	# External Library Dependencies
	${PTHREADS_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Test

hook_add_test_executable(hooklib "${TEST}" "${INC}" "${INC_SYS}" "${LIB}")
