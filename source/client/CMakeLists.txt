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
	
	intern/CRaventor.h
	intern/CRaventor.c
	intern/CActorInstance.h
	intern/CActorInstance.cc
	intern/CNetworkActorManager.h
	intern/CNetworkActorManager.cc
	intern/CString.h
	intern/CString.cc
	intern/CAccountConnector.h
	intern/CAccountConnector.c
	intern/CPythonApplication.h
	intern/CPythonApplication.c
	intern/CPythonMinimap.h
	intern/CPythonMinimap.c
	intern/CPythonNetworkStream.h
	intern/CPythonNetworkStream.c
	intern/CNetworkStream.h
	intern/CNetworkStream.c
	intern/Packet.h
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	hook::intern::guardedalloc
	hook::source::hooklib
	hook::source::kernel
	
	# External Library Dependencies
	${DETOURS_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Library

hook_add_dll(client "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(hook::source::client ALIAS client)
