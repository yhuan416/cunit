mkdir windows-build
cd windows-build
cmake -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config Release

cd CUnit

Sources\Release\cunit_test.exe
