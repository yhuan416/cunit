mkdir windows-build
cd windows-build
cmake -G "Visual Studio 14 2015 Win64" .. || exit \b
cmake --build . --config Release || exit \b

cd CUnit

Release\cunit_test.exe || exit \b
