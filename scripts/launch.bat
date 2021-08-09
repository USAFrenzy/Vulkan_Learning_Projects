@echo off
REM ##########################################
REM #     devenv needs to be set on PATH     #
REM ##########################################
pushd ..
call devenv.exe "build/Vulkan Learning Projects.sln"
popd