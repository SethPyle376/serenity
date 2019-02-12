rm -rf build || true
cmake -H. -Bbuild
cmake --build build
