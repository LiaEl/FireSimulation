# Cover note

## Build & run instructions

To build the solution , you can just invoke `./build.sh`. Alternatively, you
can do the same steps manually:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 5
```

To run the solution, invoke:

```sh
./build/FireSimulation
```

## Used materials

1) Main propagation algorithm        https://github.com/filipedeschamps/doom-fire-algorithm/
2) Image conversion Qt <=> OpenCV    https://github.com/dbzhang800/QtOpenCV/
3) Gaussian blur                     https://www.opencv-srf.com/2018/03/gaussian-blur.html