@echo on
cd windows-build
cd Examples\CI\Release

cicd-pass-plain || exit /b
cicd-pass-setupfuncs || exit /b

echo cicd-pass-plain-Results.xml
type cicd-pass-plain-Results.xml

echo ----

echo cicd-pass-setupfuncs-Results.xml
type cicd-pass-setupfuncs-Results.xml

echo ----

python -m junit2htmlreport --summary-matrix cicd-pass-plain-Results.xml cicd-pass-setupfuncs-Results.xml

