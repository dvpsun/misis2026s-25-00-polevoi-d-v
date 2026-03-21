set PATH="C:\Programs\ninja";%PATH%
set SUFF="ninja.clang"
@rem  -DCMAKE_BUILD_TYPE=Release
cmake -S . -B ./build.%SUFF% -G "Ninja" -DSUFF_BUILD=.%SUFF% -DPython_FIND_VIRTUALENV=ONLY  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TO_CHECK_TESTS=1
cmake --build ./build.%SUFF% -j 15

@rem  

uv run run-clang-tidy.py -config-file .clang-tidy -export-fixes clang-tidy.fixes -p ./build.%SUFF% -quiet  > clang-tidy.log 