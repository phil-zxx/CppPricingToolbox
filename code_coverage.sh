#! /bin/sh

if [ -d "linux_build_folder" ]; then
  echo ">>> Deleting old build folder"
  rm -r linux_build_folder
fi

echo ">>> Creating build folder"
mkdir linux_build_folder
cd linux_build_folder

echo ">>> Running CMake"
cmake -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage" -DCMAKE_BUILD_TYPE=Debug ..

echo ">>> Running Make"
make -j 12

echo ">>> Running Unit Tests"
./../build/Debug_x86_64/UnitTests

echo ">>> Running Code Coverage"
lcov -d . -c -o coverage.info
lcov -r coverage.info "/usr*"        -o coverage.info
lcov -r coverage.info "*/external/*" -o coverage.info
genhtml coverage.info -o out --legend --demangle-cpp

echo ">>> Opening Code Coverage HTML"
cd out
explorer.exe index.html
cd ../..
