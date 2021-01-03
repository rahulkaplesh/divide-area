# Project To Build a Area Divison Logic as node module and demo it using Cesium

Aim is to build a node module and insclude in the frontend simulator ( which just simulates the area selection logic )

Currently Done : 

1. Started building the simulator frontend which will be used to test my node module. Here is a simple angular app built with angular cesium which will serve as application interacting with the node module.
2. Started building the node module which will wrap the c++ api ( I plan to provide a docker based build environment which can be loaded in vs code )
    I have started building the environment , which just pulls in the cgal library and includes it using cmake to build a node module . I have also provided a way to debug the parts of cpp module right out of the box. Look in the folder divide-area-module. As I build it i will provide more info.

# Contribution

If you want to help out you can reach out to me at rahulkaplesh@gmail.com