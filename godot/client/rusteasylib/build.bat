@echo off

echo Building RustEasylib Release...

cargo build --release

echo Copying Release DLL...

if not exist "bin" mkdir "bin"

copy /Y "target\release\rusteasylib.dll" "bin\rusteasylib_release.dll"

echo Building RustEasylib Release...

cargo build

echo Copying Debug DLL...

copy /Y "target\debug\rusteasylib.dll" "bin\rusteasylib_debug.dll"

echo Build Complete!
