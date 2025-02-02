echo "Building..."
gcc TopoRun.c map_.c p_to_local.c priority_.c init_data.c queue.c -o test
if %ERRORLEVEL% EQU 0 (
    echo "Build successful!"
    echo "Running..."
    ./test
    echo "Done!"
) else (
    echo "Build failed!"
)