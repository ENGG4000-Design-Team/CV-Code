# CV-Code
A repository to hold all computer vision related code for the BBST.

## Installing OpenCV on Raspberry Pi
Below is a basic, to-the-point list of commands for compiling and installing OpenCV on a Raspberry Pi. This was tested on a Raspberry Pi 4 Model B.
1. ```sudo apt update```
2. ```sudo apt upgrade```
3. ```sudo apt install cmake build-essential pkg-config git```
4. ```sudo apt install libjpeg-dev libtiff-dev libjasper-dev libpng-dev libwebp-dev libopenexr-dev```
5. ```sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libdc1394-22-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev```
6. ```sudo apt install libgtk-3-dev libqt5gui5 libqt5webkit5 libqt5test5 python3-pyqt5```
7. ```sudo apt install libatlas-base-dev liblapacke-dev gfortran```
8. ```sudo apt install libhdf5-dev libhdf5-103```
9. ```sudo apt install python3-dev python3-pip python3-numpy```

The next step requires temporarily increasing the swap size of the OS on the Raspberry Pi. This can and will be reverted once we are done compiling OpenCV.
10. ```sudo nano /etc/dphys-swapfile```
11. In this file, replace the line ```CONF_SWAPSIZE=100``` with ```CONF_SWAPSIZE=3072``` When done, save the file by pressing CTRL+X followed by Y then ENTER.
12. ```sudo systemctl restart dphys-swapfile```

Next we must clone the OpenCV code repositories. This may take a while based on your internet connections.
13. ```git clone https://github.com/opencv/opencv.git```
14. ```git clone https://github.com/opencv/opencv_contrib.git```
15. ```mkdir ~/opencv/build```
16. ```cd ~/opencv/build```

Configure the makefile.
17. ```cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D CMAKE_SHARED_LINKER_FLAGS=-latomic \
    -D OPENCV_PYTHON_INSTALL_PATH=lib/python3.9/dist-packages \
    -D BUILD_EXAMPLES=OFF ..```

Next we compile OpenCV. If the compilation process fails, try running without -j$(nproc). This process can take upwards of an hour.
18. ```make -j$(nproc)```
Once compilation has completed, install OpenCV with this command.
19. ```sudo make install```
20. ```sudo ldconfig```
Once we are finished, revert changes made to the OS swap size.
21. ```sudo nano /etc/dphys-swapfile```
22. In this file, replace the line ```CONF_SWAPSIZE=3072``` with ```CONF_SWAPSIZE=100``` When done, save the file by pressing CTRL+X followed by Y then ENTER.
23. ```sudo systemctl restart dphys-swapfile```

## Testing OpenCV Installation
To test your OpenCV installation, attempt to import OpenCV in a python script.
```python3```
```import cv2```
```cv2.__version__```
If everything was correctly installed, you will see the installed OpenCV version printed to your terminal.

Author: Ethan Garnier
