# cppckeck integration support, requires *cppcheck* package installed.
function(AddCppCheck target)
	find_program(CPPCHECK_PATH cppcheck REQUIRED)
	set_target_properties(${target}
		PROPERTIES CXX_CPPCHECK
		"${CPPCHECK_PATH};--enable=warning")
endfunction()
