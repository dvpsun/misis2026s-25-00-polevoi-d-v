set SUFF="vs.clang"
cmake -S . -B ./build.%SUFF% -G "Visual Studio 17 2022" -T ClangCL -DSUFF_BUILD=.%SUFF% -DBUILD_TO_CHECK_TESTS=1
cmake --build ./build.%SUFF% --config Debug -j 15
cmake --build ./build.%SUFF% --config Release -j 15