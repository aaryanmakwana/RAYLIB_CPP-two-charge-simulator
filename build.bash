rm App && eval cc main.cpp $(pkg-config --libs --cflags raylib) -o App && ./App
