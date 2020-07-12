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
./../build/Debug_x86_64/UnitTests -tc=*Algebra*

echo ">>> Running Code Coverage"
lcov -d . -c -o coverage.info --rc lcov_branch_coverage=1
lcov -r coverage.info "/usr*"        -o coverage.info --rc lcov_branch_coverage=1
lcov -r coverage.info "*/external/*" -o coverage.info --rc lcov_branch_coverage=1
genhtml coverage.info -o out --legend --rc genhtml_branch_coverage=1

echo ">>> Opening Code Coverage HTML"
cd out
explorer.exe index.html
cd ../..