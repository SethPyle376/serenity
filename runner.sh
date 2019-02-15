rm -rf build || true
cmake -H. -Bbuild -G "Visual Studio 15 2017 Win64"
cmake --build build
cp sdl/lib/x64/SDL2.dll build/Debug/SDL2.dll