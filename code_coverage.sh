#! /bin/sh

if [ -d "linux_build_folder" ]; then
  echo "\n>>> Deleting old build folder"
  rm -r linux_build_folder
fi

echo "\n>>> Creating build folder"
mkdir linux_build_folder
cd linux_build_folder

echo "\n>>> Running CMake"
cmake -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage" -DCMAKE_BUILD_TYPE=Debug ..

echo "\n>>> Running Make"
make -j 8

echo "\n>>> Running Unit Tests"
./../build/Debug_x86_64/UnitTests

echo "\n>>> Running Code Coverage"
lcov -d . -c -o coverage.info                                      # parse coverage data
lcov -r coverage.info "/usr*"        -o coverage.info
lcov -r coverage.info "*/external/*" -o coverage.info
genhtml coverage.info -o out

echo "\n>>> Opening Code Coverage HTML"
cd out
explorer.exe index.html
