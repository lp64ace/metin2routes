# -----------------------------------------------------------------------------
# Launch Options

set(LAUNCH_BIN
	launch.json
)

set(LAUNCH_INC
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)

set(LAUNCH_SRC
	
)

foreach(BINARY ${LAUNCH_BIN})
	data_to_c_simple(${BINARY} LAUNCH_SRC)
endforeach()

hook_add_lib(launch "${LAUNCH_SRC}" "${LAUNCH_INC}" "" "")
add_library(hook::source::launch ALIAS launch)

set(CONTENT_H
	""
)
foreach(BINARY ${LAUNCH_BIN})
	get_filename_component(BINARY_FILE_NAME ${BINARY} NAME)
	string(REPLACE "." "_" BINARY_FILE_NAME_UNDERSCORES ${BINARY_FILE_NAME})
	string(APPEND CONTENT_H "BINARY\(datatoc_${BINARY_FILE_NAME_UNDERSCORES}, \"${BINARY_FILE_NAME}\", \"${BINARY}\"\)\n")
endforeach()

set(LAUNCH_H
	"${CMAKE_CURRENT_BINARY_DIR}/launch.h"
)
file(GENERATE OUTPUT ${LAUNCH_H} CONTENT "${CONTENT_H}")