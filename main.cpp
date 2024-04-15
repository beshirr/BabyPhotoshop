// ======================================== Header ==================================================================
/*
File: CS112_A3_part1_21_20230161_20230109_20230476.cpp
Purpose: manipulating images with some filters.
Authors:
    Zeyad Mohamed Arafat - 20230161   s21   zeyadarafat833@gmail.com
    John Ayman Demian    - 20230109   s21   johnayman03@gmail.com
    Youssef Ahmed Beshir - 20230476   s21   youssefahmedbeshir@gmail.com

Zeyad Mohamed Arafat:
    Gray scale filter.
    Resize filter.

John Ayman Demian:
    Black and White filter.
    Flip filter.
    Darken and Lighten Filter .
    Detect edges Filter .
    Infrared Filter .

Youssef Ahmed Beshir:
    Menu.
    Invert filter.
    Frame filter.
    Rotate filter.
    Blur filter.
    Sunlight filter.
*/
// ============================================================================================================================


# include <bits/stdc++.h>
# include "Image_Class.h"

using namespace std;


string fileName;


void save_image(Image& image){
    while (true){
        try{
            string choice;
            string newFileName;
            cout << "Do you want to save the same file (1) or change the file name (2)?";
            cin >> choice;

            if (choice == "1"){
                image.saveImage(fileName);
                break;
            }

            else if (choice == "2"){
                cout << "Enter the new image name:" << endl;
                cin.clear();
                cin.ignore();
                getline(cin, newFileName);
                image.saveImage(newFileName);
                break;
            }

            else
                cout << "Invalid choice, try again." << endl << endl;


        }

        catch (...){}
    }

    cout << "Image save successfully!" << endl << endl;
}


void load(Image& image){

    while (true){
        cout << "Enter the image name:";
        try{
            cin.clear();
            cin.ignore();
            getline(cin, fileName);
            image.loadNewImage(fileName);
            break;
        }

        catch (...){}
    }

    cout << "New image loaded successfully!" << endl << endl;

}

void grayscale(Image& image){
    // iterate through the image matrix
    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){

            // calculating the average of all the colors(Green, Red, Blue) in each pixel.
            int avg = (image(i, j, 0) + image(i, j, 1) +
                       image(i, j, 2)) / 3;
            // assigning the average to all the colors in each pixel to get a gray scale.
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    save_image(image);
}


void black_and_white(Image& image) {

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            int y;

            if (avg < 127)
                y = 0;
            else
                y = 255;

            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = y;
            }
        }
    }
    save_image(image);
}


void invert(Image& image){
    // Iterate through the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            for (int k = 0; k < 3; ++k) {
                // Colour inversion is achieved by subtracting each RGB colour value from the maximum possible value
                image(i,j,k) = 255 - image(i, j, k);
            }
        }
    }
    save_image(image);
}


void crop_merge(Image& image){

    int counter = 0; // the counter will help in the merging part.
    // getting the  image that the user want to merge and checking the validity.
    string mergeFileName;
    Image mergeImage;
    while (true){
        try{
            cout << "Enter the name of the image you want to merge:" << endl;
            cout << "->";
            cin >> mergeFileName;
            mergeImage.loadNewImage(mergeFileName);
            break;
        }
        catch(...){}
    }

    // if the two images have the same width and height we start merging them directly.
    if ((image.width == mergeImage.width) and (image.height == mergeImage.height)){
        Image mergedImage(image.width, image.height);

        // the merging is done by taking a pixel of each image (one pixel from image 1then one pixel from image2)
        for (int i = 0; i < mergedImage.width; ++i) {
            for (int j = 0; j < mergedImage.height; ++j) {

                if (counter % 2 == 0){
                    mergedImage(i, j, 0) = image(i, j, 0);
                    mergedImage(i, j, 1) = image(i, j, 1);
                    mergedImage(i, j, 2) = image(i, j, 2);
                    counter++;
                }

                else{
                    mergedImage(i, j, 0) = mergeImage(i, j, 0);
                    mergedImage(i, j, 1) = mergeImage(i, j, 1);
                    mergedImage(i, j, 2) = mergeImage(i, j, 2);
                    counter++;
                }
            }
        }
        image = mergedImage;
        save_image(image);
    }

    // if the two images don't have the same width or height, we do the merge and crop a part from the bigger image.
    else{
        Image mergedImage(min(image.width , mergeImage.width), min(image.height , mergeImage.height));

        // same algorithm for merging.
        for (int i = 0; i < mergedImage.width; ++i) {
            for (int j = 0; j < mergedImage.height; ++j) {

                if (counter % 2 == 0){
                    mergedImage(i, j, 0) = image(i, j, 0);
                    mergedImage(i, j, 1) = image(i, j, 1);
                    mergedImage(i, j, 2) = image(i, j, 2);
                    counter++;
                }

                else{
                    mergedImage(i, j, 0) = mergeImage(i, j, 0);
                    mergedImage(i, j, 1) = mergeImage(i, j, 1);
                    mergedImage(i, j, 2) = mergeImage(i, j, 2);
                    counter++;
                }
            }
        }
        image = mergedImage;
        save_image(image);
    }
    cout << "Done!" << endl << endl;
}


void resize_merge(Image& image){

    int counter = 0; // the counter will help in the merging part.
    // getting the  image that the user want to merge and checking the validity.
    string mergeFileName;
    Image mergeImage;
    while (true){
        try{
            cout << "Enter the name of the image you want to merge:" << endl;
            cout << "->";
            cin >> mergeFileName;
            mergeImage.loadNewImage(mergeFileName);
            break;
        }

        catch(...){}
    }


    // if the two images have the same width and height we start merging without resizing them.
    if ((image.width == mergeImage.width) and (image.height == mergeImage.height)){
        Image mergedImage(image.width, image.height);

        // the merging is done by taking a pixel of each image (one pixel from image 1then one pixel from image2)
        // this is done with the help of the counter.
        for (int i = 0; i < mergedImage.width; ++i) {
            for (int j = 0; j < mergedImage.height; ++j) {

                if (counter % 2 == 0){
                    mergedImage(i, j, 0) = image(i, j, 0);
                    mergedImage(i, j, 1) = image(i, j, 1);
                    mergedImage(i, j, 2) = image(i, j, 2);
                    counter++;
                }

                else{
                    mergedImage(i, j, 0) = mergeImage(i, j, 0);
                    mergedImage(i, j, 1) = mergeImage(i, j, 1);
                    mergedImage(i, j, 2) = mergeImage(i, j, 2);
                    counter++;
                }
            }
        }
        image = mergedImage;
    }

        // if both images don't have the same width or height, then we resize them first before merging.
    else{
        Image mergedImage(max(image.width , mergeImage.width), max(image.height , mergeImage.height));

        // resizing the first image.
        // we will use the same algorithm as in the resizing function.
        Image resizedImage_1(max(image.width, mergeImage.width), max(image.height , mergeImage.height));
        double widthRatio = static_cast<double>(image.width) / max(image.width , mergeImage.width);
        double heightRatio = static_cast<double>(image.height) / max(image.height , mergeImage.height);
        for (int i = 0; i < max(image.width , mergeImage.width); ++i) {
            for (int j = 0; j < max(image.height , mergeImage.height); ++j) {
                resizedImage_1(i, j, 0) = image(floor(i * widthRatio), floor(j * heightRatio), 0);
                resizedImage_1(i, j, 1) = image(floor(i * widthRatio), floor(j * heightRatio), 1);
                resizedImage_1(i, j, 2) = image(floor(i * widthRatio), floor(j * heightRatio), 2);
            }
        }

        // resizing the second image.
        Image resizedImage_2(max(image.width, mergeImage.width), max(image.height , mergeImage.height));
        widthRatio = static_cast<double>(mergeImage.width) / max(image.width , mergeImage.width);
        heightRatio = static_cast<double>(mergeImage.height) / max(image.height , mergeImage.height);
        for (int i = 0; i < max(image.width , mergeImage.width); ++i) {
            for (int j = 0; j < max(image.height , mergeImage.height); ++j) {
                resizedImage_2(i, j, 0) = mergeImage(floor(i * widthRatio), floor(j * heightRatio), 0);
                resizedImage_2(i, j, 1) = mergeImage(floor(i * widthRatio), floor(j * heightRatio), 1);
                resizedImage_2(i, j, 2) = mergeImage(floor(i * widthRatio), floor(j * heightRatio), 2);
            }
        }

        // then after resizing both images we do the merging.
        for (int i = 0; i < mergedImage.width; ++i) {
            for (int j = 0; j < mergedImage.height; ++j) {

                if (counter % 2 == 0){
                    mergedImage(i, j, 0) = resizedImage_1(i, j, 0);
                    mergedImage(i, j, 1) = resizedImage_1(i, j, 1);
                    mergedImage(i, j, 2) = resizedImage_1(i, j, 2);
                    counter++;
                }

                else{
                    mergedImage(i, j, 0) = resizedImage_2(i, j, 0);
                    mergedImage(i, j, 1) = resizedImage_2(i, j, 1);
                    mergedImage(i, j, 2) = resizedImage_2(i, j, 2);
                    counter++;
                }
            }
        }
        image = mergedImage;
    }
    save_image(image);
}


void flip(Image& image){
    // make user select any flip
    string choice;
    // check validation of input
    while (true){
        cout << "Please select:\n1- Horizontal flip \n2- Vertical flip \nEnter your choice:";
        cin >> choice;

        if (choice == "1"){
            choice = "1";
            break;
        }

        else if (choice == "2"){
            choice = "2";
            break;

        }

        else{
            cout << endl << "Invalid choice!" << endl;
            continue;
        }

    }

    // Horizontal flip
    if (choice == "1") {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // here we replace first pixel with last one from width and continue others
                for (int k = 0; k < 3; ++k) {
                    swap(image(i, j, k), image(image.width - i - 1, j, k));
                }
            }
        }
    }

        // Vertical flip
    else if (choice == "2") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // here we replace first pixel with last one from height and continue others
                    swap(image(i, j, k), image(i, image.height - j - 1, k));
                }
            }
        }
    }

    save_image(image);
}


void rotate(Image& image){
    int newHeight, newWidth;

    string degree;

    while (true){
        cout << "(90, 180, 270)?" << endl;
        cout << "->";
        cin >> degree;

        if (degree == "90"){

            // New image dimensions
            newHeight = image.width;
            newWidth = image.height;

            Image newImage(newWidth, newHeight);

            // Transposing the image matrix 90 degrees
            for (int i = 0 ; i < newWidth ; ++i){
                for (int j = 0 ; j < newHeight ; ++j){

                    for (int k = 0; k < 3 ; ++k){
                        newImage(i, j, k) = image(j, newWidth - i - 1, k);
                    }

                }
            }
            image = newImage;
            break;
        }

        else if (degree == "180"){

            Image newImage(image.width, image.height);

            // Transposing the image matrix 180 degree
            for (int i = 0; i < image.width; ++i){
                for (int j = 0; j < image.height; ++j){

                    for (int k = 0; k < 3; ++k){
                        newImage(i, j, k) = image(i, (image.height) - j - 1, k);
                    }
                }
            }
            image = newImage;
            break;
        }

        else if (degree == "270"){

            // New image dimensions
            newHeight = image.width;
            newWidth = image.height;

            Image newImage(newWidth, newHeight);

            // Transposing the image matrix 270 degree
            for (int i = 0 ; i < newWidth ; ++i){
                for (int j = 0 ; j < newHeight ; ++j){

                    for (int k = 0; k < 3 ; ++k){
                        newImage(i, j , k) = image(j, i , k);
                    }

                }
            }
            image = newImage;
            break;
        }

        else
            cout << "Invalid degree." << endl;
    }
    save_image(image);
}


void darken_lighten(Image& image) {

    // make user select darken or lighten
    string choice;

    // check validation of input
    while (true){
        cout << "Please select:\n1- Lighten filter \n2- Darken filter\nEnter your choice:";
        cin >> choice;

        if (choice == "1"){
            choice = "1";
            break;
        }

        else if (choice == "2"){
            choice = "2";
            break;

        }

        else{
            cout << endl << "Invalid choice!" <<endl;
            continue;
        }

    }
    // Apply lighter filter
    if (choice == "1"){
        // Iterate through each pixel of the image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Make the image lighter by 50% by + 0.5 of light
                    float new_Value = image(i, j, k) * 1.5;
                    // make pixel value in range [0, 255]
                    image(i, j, k) = static_cast<unsigned char>(min(max(new_Value, 0.0f), 255.0f));
                }
            }
        }

    }

        //Apply darker filter
    else if (choice== "2" ){
        // Iterate through each pixel of the image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Make the image lighter by 50% by - 0.5 of lights
                    float new_Value = image(i, j, k) * 0.5;
                    // make pixel value in range [0, 255]
                    image(i, j, k) = static_cast<unsigned char>(min(max(new_Value, 0.0f), 255.0f));
                }
            }
        }

    }

    save_image(image);
}


void crop(Image& image){

    int x, y, h, w;
    cout << "enter the index of the starting point(ex: 600 500): ";
    // getting the index of the starting point and checking the validity.
    cin >> x >> y;
    while (true) {
        if (cin.fail()) {
            cout << "please use a valid index!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> x >> y;
        }
        else if ((x > image.width) or (y > image.height)){
            cout << "this index seems too big for the image!" << endl;
            cout << "enter the index of the starting point(ex: 600 500): ";
            cin >> x >> y;
        }
        else {
            break;
        }
    }
    cout << "enter the size of the cropped image(ex: 600 900): ";
    // getting the width and height (size) of the cropped image and checking the validity.
    cin >> w >> h;
    while (true) {
        if (cin.fail()) {
            cout << "please use a valid size!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> x >> y;
        }
        else if ((w + x > image.width) or (h + y > image.height)) {
            cout << "this size seems too high for the image you are trying to crop!" << endl;
            cout << "enter the size of the cropped image(ex: 600 900): ";
            cin >> w >> h;
        }
        else {
            break;
        }
    }
    // create empty image for the cropped part.
    Image croppedImage(w, h);
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            // fill each pixel in the cropped image with the colors from the original one to show the cropped part.
            croppedImage(i, j, 0) = image(i+x, j+y, 0);
            croppedImage(i, j, 1) = image(i+x, j+y, 1);
            croppedImage(i, j, 2) = image(i+x, j+y, 2);
        }
    }
    image = croppedImage;
    save_image(image);
}


void simple_frame(Image &image, int red, int green, int blue, int frameSize) {

    int currentFrameSize = frameSize;

    // Frame boundaries
    int x = image.width - 1;
    int y = image.height - 1;

    // Up and Down frame
    while (frameSize--) {
        for (int i = 0; i < image.width; ++i) {
            // Up
            image(i, frameSize, 0) = red;
            image(i, frameSize, 1) = green;
            image(i, frameSize, 2) = blue;

            // Down
            image(i, y - frameSize, 0) = red;
            image(i, y - frameSize, 1) = green;
            image(i, y - frameSize, 2) = blue;
        }
    }


    // Right and left frame
    while (currentFrameSize--) {
        for (int i = 0; i < image.height; ++i) {
            // Right
            image(currentFrameSize, i, 0) = red;
            image(currentFrameSize, i, 1) = green;
            image(currentFrameSize, i, 2) = blue;

            // Left
            image(x - currentFrameSize, i, 0) = red;
            image(x - currentFrameSize, i, 1) = green;
            image(x - currentFrameSize, i, 2) = blue;
        }
    }

}


void fancy_frame (Image &image, int red, int green, int blue, int frameSize, bool isWhite){
    int color;
    if (isWhite){
        color = 0;
    }
    else
        color = 255;

    frameSize = (((image.width * image.height) /
                  (image.width + image.height)) * 0.07);

    simple_frame(image, color, color, color, frameSize);

    frameSize = (((image.width * image.height) /
                  (image.width + image.height)) * 0.06);

    simple_frame(image, red, green, blue, frameSize);

    frameSize = (((image.width * image.height) /
                  (image.width + image.height)) * 0.04);

    simple_frame(image, color, color, color, frameSize);

    frameSize = (((image.width * image.height) /
                  (image.width + image.height)) * 0.03);

    simple_frame(image, red, green, blue, frameSize);
}


void frame(Image &image) {

    bool isWhite = false;

    while (true) {
        // Setting the RGB for each color
        int red, green, blue;

        string color;
        while (true) {
            cout << "Choose a color:" << endl;
            cout << "1- Black" << endl;
            cout << "2- White" << endl;
            cout << "3- Red" << endl;
            cout << "4- Green" << endl;
            cout << "5- Blue" << endl;
            cin >> color;

            if (color == "1") {
                red = 0;
                green = 0;
                blue = 0;
                break;
            }
            else if (color == "2") {
                red = 255;
                green = 255;
                blue = 255;
                isWhite = true;
                break;
            }
            else if (color == "3") {
                red = 176;
                green = 91;
                blue = 71;
                break;
            }
            else if (color == "4") {
                red = 102;
                green = 179;
                blue = 80;
                break;
            }
            else if (color == "5") {
                red = 65;
                green = 105;
                blue = 225;
                break;
            }
            else
                cout << "Invalid option, try again" << endl << endl;
        }

        string option;
        cout << "Simple (S/s) or Fancy (F/f) frame?";
        cin >> option;

        int frameSize = ((image.width * image.height)
                         / (image.width + image.height)) * 0.05;

        if (option == "S" || option == "s") {
            simple_frame(image, red, green, blue, frameSize);
            break;
        }

        else if (option == "F" || option == "f") {
            fancy_frame(image, red, green, blue, frameSize, isWhite);
            break;
        }

        else
            cout << "Invalid option, try again" << endl;
    }
    save_image(image);
}


void detect_edges(Image &image) {
    // Function to detect edges in the image using Sobel operator
    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){

            // calculating the average of all the colors(Green, Red, Blue) in each pixel.
            int avg = (image(i, j, 0) + image(i, j, 1) +
                       image(i, j, 2)) / 3;
            // assigning the average to all the colors in each pixel to get a gray scale.
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }

    }
    // Create an image to store the result
    Image resultImage(image.width, image.height);

    // Iterate over each pixel of the image, excluding the border
    for (int i = 1; i < image.height - 1; i++) {
        for (int j = 1; j < image.width - 1; j++) {
            for (int k = 0; k < image.channels; ++k) {
                int valuex = 0, valuey = 0; // Reset valuex and valuey for each pixel

                // Compute valuex
                valuex += image(i - 1, j - 1, k) * -1;
                valuex += image(i - 1, j, k) * 0;
                valuex += image(i - 1, j + 1, k) * 1;
                valuex += image(i, j - 1, k) * -2;
                valuex += image(i, j, k) * 0;
                valuex += image(i, j + 1, k) * 2;
                valuex += image(i + 1, j - 1, k) * -1;
                valuex += image(i + 1, j, k) * 0;
                valuex += image(i + 1, j + 1, k) * 1;

                // Compute valuey
                valuey += image(i - 1, j - 1, k) * 1;
                valuey += image(i - 1, j, k) * 2;
                valuey += image(i - 1, j + 1, k) * 1;
                valuey += image(i, j - 1, k) * 0;
                valuey += image(i, j, k) * 0;
                valuey += image(i, j + 1, k) * 0;
                valuey += image(i + 1, j - 1, k) * -1;
                valuey += image(i + 1, j, k) * -2;
                valuey += image(i + 1, j + 1, k) * -1;

                // Compute edge magnitude
                double edgeMagnitude = sqrt(valuex * valuex + valuey * valuey);

                // Assign the edge magnitude to the corresponding pixel of the result image
                resultImage(i, j, k) = (edgeMagnitude > 100 ? 0 : 255);
            }
        }
    }

    image = resultImage;
    save_image(image);
}


void resize(Image& image){

    // getting the dimensions of the resized image from the user.
    int width_, height_;
    cout << "Enter the dimensions of the new image:";
    while(!(cin >> width_) or !(cin >> height_)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid width or height (a positive integer.)" << endl;
    }
    // create a new image with the dimensions we got from the user.
    Image resizedImage(width_, height_);

    // calculating the ratio between the width and height of the original image and the resized one.
    double widthRatio = static_cast<double>(image.width) / resizedImage.width;
    double heightRatio = static_cast<double>(image.height) / resizedImage.height;
    // iterate through the resized image and assigning the colors of the original image to the resized one
    //using the ratio we calculated earlier.
    for (int i = 0; i < resizedImage.width; ++i) {
        for (int j = 0; j < resizedImage.height; ++j) {
            resizedImage(i, j, 0) = image(floor(i * widthRatio), floor(j * heightRatio), 0);
            resizedImage(i, j, 1) = image(floor(i * widthRatio), floor(j * heightRatio), 1);
            resizedImage(i, j, 2) = image(floor(i * widthRatio), floor(j * heightRatio), 2);
        }
    }

    image = resizedImage;
    save_image(image);
}


void blur(Image& image){

    int rad  = 9;
    int width = image.width;
    int height = image.height;

    // Final image
    Image blurred(width, height);

    // Temporary image for horizontal blur
    Image temp(width, height);

    // Dividing the box blur operation into two separate operations
    // (one for the horizontal and the other one for the vertical)
    // this technique helps to reduce the time needed to perform the box blur algorithm.


    // 1- Horizontal blur
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            // Reset color values after each iteration
            int red = 0, green = 0, blue = 0;

            for (int x = -rad; x <= rad; ++x) {
                int ix = max(0, j + x);
                if (ix < width) {
                    red += image(ix, i, 0);
                    green += image(ix, i, 1);
                    blue += image(ix, i, 2);
                }
            }
            int divisor = rad * 2 + 1;
            // Calculate the average
            temp(j, i, 0) = red / divisor;
            temp(j, i, 1) = green / divisor;
            temp(j, i, 2) = blue / divisor;
        }
    }

    // 2- Vertical blur  using the temporary image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {

            int red = 0, green = 0, blue = 0;

            for (int y = -rad; y <= rad; ++y) {
                int iy = max(0, j + y);
                if (iy < height) {
                    red += temp(i, iy, 0);
                    green += temp(i, iy, 1);
                    blue += temp(i, iy, 2);
                }
            }
            int divisor = rad * 2 + 1;
            blurred(i, j, 0) = red / divisor;
            blurred(i, j, 1) = green / divisor;
            blurred(i, j, 2) = blue / divisor;
        }
    }

    image = blurred;
    save_image(image);
}


void purple(Image& image) {

    // the purple shade we are using in this filter is (R:200, G:160, B:255).
    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){
            double redRatio, greenRatio, blueRatio;
            // calculate the ratio for the red channel to use it in the color assigning.
            redRatio = image(i, j, 0) / 255.0;
            // using the ratio and the prestated shade to assign the color to the red channel.
            // same goes for the rest of the channels.
            image(i, j, 0) = (int)(redRatio * 200);
            greenRatio = image(i, j, 1) / 255.0;
            image(i, j, 1) = (int)(greenRatio * 160);
            blueRatio = image(i, j, 2) / 255.0;
            image(i, j, 2) = (int)(blueRatio * 255);
        }

    }
    save_image(image);
}


void infrared(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // set the red 255 and invert green and blue
            image(i,j,0) = 255;
            image(i,j,1) = 255 - image(i,j,1) ;
            image(i,j,2) = 255 - image(i,j,2) ;

        }

    }
    save_image(image);
}


void sunlight(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int redTent = 40, greenTent = 30, blueTent = 30;

            while (image(i, j, 0) + redTent > 255) redTent --;
            image(i, j, 0) += redTent;
            redTent = 40;

            while (image(i, j, 1) + greenTent > 255) greenTent --;
            image(i, j, 1) += greenTent;
            greenTent = 30;

            while (image(i, j, 2) - blueTent < 0) blueTent --;
            image(i, j, 2) -= blueTent;
            blueTent = 30;
        }
    }
    save_image(image);
}





int main(){
    cout << "Welcome to babyPhotoshop" << endl << endl;

    Image image;
    load(image);
    bool saved = false;

    while (true){
        string menu;
        cout << "1- Load new image" << endl;
        cout << "2- Save current image" << endl;
        cout << "3- Grayscale Conversion" << endl;
        cout << "4- Black and White" << endl;
        cout << "5- Invert image" << endl;
        cout << "6- Merge images" << endl;
        cout << "7- Flip image" << endl;
        cout << "8- Rotate image" << endl;
        cout << "9- Darken and Lighten image" << endl;
        cout << "10- Crop image" << endl;
        cout << "11- Frame" << endl;
        cout << "12- Detect image Edges" << endl;
        cout << "13- Resizing image" << endl;
        cout << "14- Blur image" << endl;
        cout << "15- Sunlight" << endl;
        cout << "16- Purple filter" << endl;
        cout << "17- Infrared filter" << endl;
        cout << "18- Exit" << endl;
        cout << "->";

        cin >> menu;

        if (menu == "18"){

            if (saved){
                cout << "GoodBye!" << endl;
                break;
            }

            else{
                cout << "You have unsaved changes if you exit you are going to lose progress\n"
                        "are you sure you want to exit?\n"
                        "(1) Exit without saving \n"
                        "(2) Save then exit\n"
                        "->";

                string option;
                cin >> option;

                if (option == "1"){
                    cout << "GoodBye!" << endl << endl;
                    break;
                }

                else if (option == "2"){
                    save_image(image);
                    cout << "GoodBye!" << endl << endl;
                    break;
                }

                else
                    cout << "Invalid option, try again" << endl << endl;
            }
        }

        else if (menu == "1"){
            if (saved){
                load(image);
                saved = false;
            }
            else{
                while (true){
                    cout << "You have unsaved changes if you loaded a new image you are going to lose progress \n"
                            "make sure you save changes before loading a new image \n"
                            "(1) Load new image and discard changes\n"
                            "(2) Save current then load new image";
                    string option;
                    cin >> option;
                    if (option == "1") {
                        load(image);
                        saved = false;
                        break;
                    }
                    else if (option == "2"){
                        save_image(image);
                        load(image);
                        saved = false;
                        break;
                    }
                    else
                        cout << "Invalid choice, try again" << endl << endl;
                }
            }
        }

        else if (menu == "2"){
            save_image(image);
            saved = true;
        }

        else if (menu == "3"){
            grayscale(image);
        }
        else if (menu == "4"){
            black_and_white(image);
        }
        else if (menu == "5"){
            invert(image);
        }
        else if (menu == "6"){
            string mergeType;
            cout << "Choose the type of merging:" << endl;
            cout << "1- merge by resize" << endl;
            cout << "2- merge by crop" << endl;
            cout << "->";
            cin >> mergeType;
            while (true) {
                if (mergeType == "1") {
                    resize_merge(image);
                    break;
                }
                else if (mergeType == "2") {
                    crop_merge(image);
                    break;
                }
                else {
                    cout << "Please choose a valid option" << endl;
                    cin >> mergeType;
                }
            }
        }
        else if (menu == "7"){
            flip(image);
        }
        else if (menu == "8"){
            rotate(image);
        }
        else if (menu == "9"){
            darken_lighten(image);
        }
        else if (menu == "10"){
            crop(image);
        }
        else if (menu == "11"){
            frame(image);
        }
        else if (menu == "12"){
            detect_edges(image);
        }
        else if (menu == "13"){
            resize(image);
        }
        else if (menu == "14"){
            blur(image);
        }
        else if (menu == "15"){
            sunlight(image);
        }
        else if (menu == "16"){
            purple(image);
        }
        else if (menu == "17"){
            infrared(image);
        }

        else
            cout << "Invalid choice, Try again." << endl << endl;
    }
    return 0;
}
