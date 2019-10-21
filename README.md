# SelfDrivingCar

Made for Ubuntu or Raspbian

The following additional packages are required for Raspbian:
```
???
```

To compile the project you need OpenCV:
```
 cd /tmp
 git clone https://github.com/opencv/opencv
 git clone https://github.com/opencv/opencv_contrib
 cd opencv_contrib
 git checkout 3.4.1
 cd ../opencv
 git checkout 3.4.1
 mkdir build
 cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DWITH_TBB=ON -DWITH_V4L=ON -DWITH_QT=OFF -DWITH_GTK=ON -DWITH_OPENGL=ON ..
 make -j3
 sudo make install
 ```
