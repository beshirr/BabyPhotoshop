# BabyPhotoshop: A Simple Image Editor
BabyPhotoshop is a lightweight image editor designed for basic photo manipulation tasks using image processing algorithms.
## Features
* Open and Save images in JPG, PNG, BMP formats.
* Apply basic image adjustments like brightness.
* Implement simple image filters (grayscale, blur, oil panting, etc.) (check the .cpp file to see all filters).
* Resize images.
* Crop images.
* Rotate images.
* Merge two images -> (you can either merge by resizing the image or croping it).
## Special Filters and adjustments 
### 1. Blur:
   #### Box Blur:
   The Box Blur algorithm is a simple and efficient image processing technique used to reduce image noise and create a blurring effect. It works by averaging the color values of a pixel with its surrounding neighbors, you can control the kernal size to increase or reduce the blur effect.<br />
   
![1_PwfAjy2PrWUHyg7g22KbtQ](https://github.com/beshirr/BabyPhotoshop/assets/154796903/117108a7-9e03-4c35-9a90-abc8b9626fcb)
![images](https://github.com/beshirr/BabyPhotoshop/assets/154796903/381cf743-9d7d-4b12-ba05-fd099263a20c)
   #### Box Blur Optimization:
   Box BLur algorithm takes a long runtime to apply. 
   Fortunately, we can optimise it by applying it in two independent passes: <br />
* First pass: Average along rows, considering the neighborhood for each pixel within a row (Add these values to a temporary image).
* Second pass: Average along columns, considering the neighborhood for  each pixel within a column (using the blurred row values from the first pass).
### 2. Detect Edges:
   ### Sobel operator:
   The Sobel operator is a popular edge detection algorithm used in image processing to identify locations in an image where there's a significant change in intensity (brightness) of pixels. It estimates the gradient of the image intensity function, which often corresponds to edges.'
   <br />
   ![download](https://github.com/beshirr/BabyPhotoshop/assets/154796903/3bf6e8cf-c78d-48e9-95ca-2df1b73b6874)
### 3. Oil Painting:
## How to run the code: 
1. Clone this repository.
2. Make sure you have the images in the same directory as the project files.
3. If you are using CLion (or any other IDE that uses CMAke files), images should be in the cmake-build-debug directory.
## Authors:
* Youssef Ahmed Beshir:
   * Email: youssefahmedbeshir@gmail.com
   * GitHub: https://github.com/beshirr
* Zeyad Mohamed Arafat:
   * Email: zeyadarafat833@gmail.com
   * GitHub: https://github.com/ZeyadArafat
* John Ayman: 
   * Email: johnayman03@gmail.com
   * GitHub: https://github.com/Johnayman1
## Disclaimer: 
BabyPhotoshop is a college assignment and a work in progress and may contain bugs or limitations.
