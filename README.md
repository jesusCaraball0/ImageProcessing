# Image Editor
## Description
Preset Image editor that creates, stores, and manipulates .tga images using C++. It reads the images as binary files and manipulates them according to presest operations such as overlaying 2 images, greyscaling, decomposing into red, blue, or green components, or "multiplying" their pixels. The output images are then written out using binary IOS and saved in the /output folder. 
## Install Instructions
There are no external dependencies required, so the project can be ran locally with an IDE or Makefile. However, it expect images to be in an /input folder and have names as depicted in the ifstream lines. It also expects an /output folder to write out results. 
