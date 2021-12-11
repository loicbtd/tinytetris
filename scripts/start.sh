rm -rf build
mkdir build
cd build
conan install .. --profile=default
cmake .. -G "Kate - Unix Makefiles"
cmake --build . --config Release
cd ..
# ./build/bin/app