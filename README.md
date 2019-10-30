# SelfDrivingCar

## Made for Ubuntu or Raspbian

#### The following additional packages are required for OpenCV for Raspbian:
```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install build-essential cmake pkg-config
sudo apt-get install libjpeg-dev libtiff5-dev libjasper-dev libpng-dev

sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev

sudo apt-get install libfontconfig1-dev libcairo2-dev
sudo apt-get install libgdk-pixbuf2.0-dev libpango1.0-dev
sudo apt-get install libgtk2.0-dev libgtk-3-dev

sudo apt-get install libatlas-base-dev gfortran

sudo apt-get install libhdf5-dev libhdf5-serial-dev libhdf5-103
sudo apt-get install libqtgui4 libqtwebkit4 libqt4-test python3-pyqt5

sudo apt-get install python3-dev
```

#### To compile the project you need OpenCV:

Get the source from the website:
```
https://opencv.org/releases/            

::OpenCV – 3.4.5 ==> Soures::
```
Make a directory and put the zip file in there:
```
cd; mkdir OpenCV; cd OpenCV
```

Unzip the file:
```
unzip opencv-3.4.5.zip
```

Compile OpenCV:
```
cd opencv-3.4.5/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DWITH_TBB=ON -DWITH_V4L=ON -DWITH_QT=OFF -DWITH_GTK=ON -DWITH_OPENGL=ON ..
make -j3
sudo make install
```
 
#### Compile the project:
Make a directory:
```
cd; mkdir SelfDrivingCar; cd SelfDrivingCar
```

Clone and compile the project
```
git clone https://github.com/ThijsLuttikhuis/SelfDrivingCar.git
cd SelfDrivingCar
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=DEBUG ..
make
```

#### Run the script:
```
./SelfDrivingCar
```



