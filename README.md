# raspicam damon

This is a simple server application for the the Raspberry Pi camera module to stream images over the network.

## Prerequisites

* CMake version 3.0 or later
* [RaspiCam](https://github.com/cedricve/raspicam): A C++ wrapper library for the Raspberry Pi camera module.
Simply clone that repository to your raspberry pi and follow the installation instructions. The non-OpenCV version is sufficient for this project.
* `Boost.ASIO` and `Boost.Log`  
  Packages provided by Raspbian work well here. You can install them with `apt-get install libboost-system-dev libboost-log-dev` or the complete package `libboost-all-dev`.

## Build & run

### CMake build

```
mkdir build
cd build
cmake ..
make
```

### Executing the application

```
./raspicam-daemon
```

## Related projects

- raspicam-control-qt

## Future plans

* Add RaspiCam project as git submodule
* Add description and scripts to install application as a service
* Add interface to receive configuration settings


## Authors

* [sebblonline](https://github.com/sebblonline)
