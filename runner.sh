rm -rf build || true
cmake -H. -Bbuild
cmake --build build
cp sdl/lib/x64/SDL2.dll build/Debug/SDL2.dll
