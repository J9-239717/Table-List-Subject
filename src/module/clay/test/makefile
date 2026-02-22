linux:
	gcc test.c -o r -I../raylib-5.5_linux_amd64/include/ -L../raylib-5.5_linux_amd64/lib/ -Wl,-rpath,../raylib-5.5_linux_amd64/lib -lraylib -lm -lGL -lpthread -ldl -lrt -lX11

windows:
	gcc test.c -o r.exe -I../raylib-5.5_win64_mingw-w64/include/ -L../raylib-5.5_win64_mingw-w64/lib/ -Wl,-rpath,../raylib-5.5_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lwinmm