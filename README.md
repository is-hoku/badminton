# badminton
image processing in C++ for badminton robot.   
## preparation
```
# pacman -S opencv
# pacman -S hdf5
```
## build
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
## usage
1. Execute ```get_frames.cpp``` to split video into frames(.png).
2. Execute ```shuttle_point.cpp``` and draw and extract the coordinates of a shuttle to csv file.
```
$ ./shuttle_point [the number of total frames] [interval]
$ ./shuttle_point 4710 10
```

### how to draw and extract
- Left Click : draw point.
- j : previous frame.
- k : next frame.
- h : previous trial.
- l : next trial.
- x : erase(=ignore) a frame.

* When the process of ``shuttle_point.cpp`` is finished, a csv file with the coordinates of a shuttle will be automatically saved.
