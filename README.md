# mini-vga-driver
A small VGA driver that runs in an emulated environment, for x86_64 

## Building

```bash
cmake -B .build -S . && cmake --build .build
```

## Running 

```bash
cmake --build .build --target run
```
