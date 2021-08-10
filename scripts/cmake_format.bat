
REM #####################################################################
REM #        Requires cmakelang to be installed and added to PATH       #
REM #####################################################################
pushd ..
cmake-format -i "CMakeLists.txt" -c "cmake-format.yaml"
	pushd src
		cmake-format -i "CMakeLists.txt" -c "../cmake-format.yaml"
		pushd BaseProject
			cmake-format -i "CMakeLists.txt" -c "../../cmake-format.yaml"
		popd
	popd
popd
REM #################################################
REM # Will Definitely Need An Easier Way To Do This #
REM #################################################