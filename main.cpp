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

Youssef Ahmed Beshir:
    Menu.
    Invert filter.
*/
// ============================================================================================================================


# include <bits/stdc++.h>
# include "Image_Class.h"


using namespace std;


void grey_scale(Image image){

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
    // saving the image.
    string newFileName;
    while(true){

        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            image.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        }

        catch(...){}
    }

}


void black_and_white(Image pic) {

    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < pic.height; ++j) {

            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += pic(i, j, k);
            }
            avg /= 3;
            int y;

            if (avg < 127)
                y = 0;
            else
                y = 255;

            for (int k = 0; k < 3; ++k) {
                pic(i, j, k) = y;
            }
        }
    }

    string newFileName;
    while(true){

        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            pic.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        }

        catch(...){}
    }

}


void invert(Image image){

    // Iterate through the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            for (int k = 0; k < 3; ++k) {
                // Colour inversion is achieved by subtracting each RGB colour value from the maximum possible value
                image(i,j,k) = 255 - image(i, j, k);
            }
        }
    }

    string newFileName;
    while (true){
        // File existence and valid extension handling
        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            image.saveImage(newFileName);
            break;
        }

        catch(...){}
    }
    cout << "Done!" << endl << endl;
}


void crop_merge(Image image){

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

        // then save the merged image and check the validity.
        string newFileName;
        while(true){

            try{
                cout << "Please enter the new image name:";
                cin >> newFileName;
                mergedImage.saveImage(newFileName);
                counter = 0;
                cout << "Done!" << endl << endl;
                break;
            }

            catch(...){}
        }

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

        // then we save the merged image and check the validity.
        string newFileName;
        while(true){

            try{
                cout << "Please enter the new image name:";
                cin >> newFileName;
                mergedImage.saveImage(newFileName);
                cout << "Done!" << endl << endl;
                break;
            }

            catch(...){}
        }

    }
}


void resize_merge(Image image){

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

        // then we save the merged image and check the validity.
        string newFileName;
        while(true){

            try{
                cout << "Please enter the new image name:";
                cin >> newFileName;
                mergedImage.saveImage(newFileName);
                counter = 0;
                cout << "Done!" << endl << endl;
                break;
            }

            catch(...){}
        }

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

        // saving the merged image and checking the validity.
        string newFileName;
        while(true){

            try{
                cout << "Please enter the new image name:";
                cin >> newFileName;
                mergedImage.saveImage(newFileName);
                counter = 0;
                cout << "Done!" << endl << endl;
                break;
            }

            catch(...){}
        }

    }
}


void flip(Image image){

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

    // make user select name to photo and save it
    string newFileName;
    while(true){

        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            image.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        }

        catch(...){}
    }

}


void rotate(Image image){
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

            // Saving the image
            while(true){
                string newFileName;

                try{
                    cout << "Please enter the new image name:";
                    cin >> newFileName;
                    newImage.saveImage(newFileName);
                    break;
                }

                catch(...){}
            }

            cout << "Done!" << endl << endl;
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

            // Saving the image
            while(true){

                string newFileName;
                try{
                    cout << "Please enter the new image name:";
                    cin >> newFileName;
                    newImage.saveImage(newFileName);
                    break;
                }

                catch(...){}
            }
            cout << "Done!" << endl << endl;
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

            // Saving the image
            while(true){
                string newFileName;
                try{
                    cout << "Please enter the new image name:";
                    cin >> newFileName;
                    newImage.saveImage(newFileName);
                    break;
                }

                catch(...){}
            }
            cout << "Done!" << endl << endl;
            break;
        }

        else cout << "Invalid degree." << endl;
    }



}


void darken_lighten(Image image) {

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

    // make user select name to photo and save it
    string newFileName;
    while(true){

        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            image.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        }

        catch(...){}
    }
}


void crop(Image image){

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
    // saving the cropped image.
    string newFileName;
    while (true){
        // File existence and valid extension handling
        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            croppedImage.saveImage(newFileName);
            break;
        }

        catch(...){}
    }
    cout << "Done!" << endl << endl;
}


void frame(Image image){

    while (true){
        // Setting the RGB for each color
        int red, green, blue;

        string color;
        while(1){
            cout << "Choose a color:" << endl;
            cout << "1- Black" << endl;
            cout << "2- White" << endl;
            cout << "3- Red" << endl;
            cout << "4- Green" << endl;
            cout << "5- Blue" << endl;
            cin >> color;

            if (color == "1"){
                red = 0;
                green = 0;
                blue = 0;
                break;
            }

            else if (color == "2"){
                red = 255;
                green = 255;
                blue = 255;
                break;
            }

            else if (color == "3"){
                red = 176;
                green = 91;
                blue = 71;
                break;
            }

            else if (color == "4"){
                red = 102;
                green = 179;
                blue = 80;
                break;
            }

            else if (color == "5"){
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

        if (option == "S" || option == "s"){

            // Frame size
            unsigned int frameSize = ((image.width * image.height)
            / (image.width + image.height)) * 0.05;

            // Frame boundries
            int x = image.width - 1;
            int y = image.height - 1;

            // Up and Down frame
            while(frameSize--){
                for(int i = 0; i < image.width; ++i){
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

            // Updating the value since it became zero due to the while loop
            frameSize = ((image.width * image.height)
            / (image.width + image.height)) * 0.05;

            // Right and left frame
            while(frameSize--){
                for (int i = 0; i < image.height; ++i){
                    // Right
                    image(frameSize, i, 0) = red;
                    image(frameSize, i, 1) = green;
                    image(frameSize, i, 2) = blue;

                    // Left
                    image(x - frameSize, i, 0) = red;
                    image(x - frameSize, i, 1) = green;
                    image(x - frameSize, i, 2) = blue;
                }
            }


            while(true){

                string newFileName;

                try{
                    cout << "Please enter the new image name:";
                    cin >> newFileName;
                    image.saveImage(newFileName);
                    break;
                }

                catch(...){}
            }

            cout << "Done!" << endl << endl;
            break;
        }

        else if (option == "F" || option == "f"){

            break;
        }

        else
            cout << "Invalid option, try again" << endl;
    }

}



// Function to detect edges in the image using Sobel operator
void detect_edges(Image image) {
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

    // Saving the resulting image
    string newFileName;
    while (true) {
        try {
            cout << "Please enter the new image name:";
            cin >> newFileName;
            resultImage.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        } catch (...) {
        }
    }
}



void resize(Image image){

    // getting the dimensions of the resized image from the user.
    int width_, height_;
    cout << "Enter the dimensions of the new image:";
    while(!(cin >> width_) or !(cin >> height_)){
        cin.clear();
        cin.ignore();
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

    // saving the image.
    string newFileName;
    while(true){

        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            resizedImage.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        }

        catch(...){}
    }

}


void blur(Image image){}


void purple(Image image) {

    Image purpleImage(image.width, image.height);
    double redRatio, greenRatio, blueRatio;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            redRatio = image(i, j, 0) / 255.0;
            purpleImage(i, j, 0) = min((int)(128  * redRatio * 1.5), 255);
            greenRatio = image(i, j, 1) / 255.0;
            purpleImage(i, j, 1) = min((int)(50 * greenRatio * 1.5), 255);
            blueRatio = image(i, j, 2) / 255.0;
            purpleImage(i, j, 2) = min((int)(128 * blueRatio * 1.5), 255);
        }
    }

    // then we save the merged image and check the validity.
    string newFileName;
    while(true){

        try{
            cout << "Please enter the new image name:";
            cin >> newFileName;
            purpleImage.saveImage(newFileName);
            cout << "Done!" << endl << endl;
            break;
        }

        catch(...){}
    }
}

void infrared(Image image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i,j,0) = 255;
            image(i,j,1) = 255 - image(i,j,1) ;
            image(i,j,2) = 255 - image(i,j,2) ;

            }

        }
    string newFileName;
    while(true){
    try{
    cout << "Please enter the new image name:";
    cin >> newFileName;
    image.saveImage(newFileName);
    cout << "Done!" << endl << endl;
    break;
    }

    catch(...){}
    }

}



int main(){

    cout << "Welcome to BabyPhotoshop" << endl << endl;
    string menu;
    string mergeType;

    Image image;

    while (true){

        // Program Menu
        cout << "1- Load an image (1)" << endl;
        cout << "2- exit (-1)" << endl;
        cout << "->";

        cin >> menu;
        cout << endl;

        if (menu == "-1"){
            cout << "Goodbye!" << endl;
            break;
        }

        else if (menu == "1"){
            string fileName;

            while (true){
                try{
                    cout << "Enter the image name:" << endl;
                    cout << "->";
                    cin >> fileName;

                    image.loadNewImage(fileName);

                    break;
                }

                catch(...){}

            }

            cout << endl;
            cout << "Choose a filter: " << endl;
            cout << "1- Invert" << endl;
            cout << "2- Resize" << endl;
            cout << "3- Gray Scale" << endl;
            cout << "4- Black and white" << endl;
            cout << "5- Flip" << endl;
            cout << "6- Merge" << endl;
            cout << "7- Crop" << endl;
            cout << "8- Purple" << endl;
            cout << "9- Rotate" << endl;
            cout << "10- Frame" << endl;
            cout << "11- Darken / Lighten" << endl;
            cout << "12- Blur" << endl;
            cout << "13- Detect edges" << endl;
            cout << "14- infrared" << endl;

            string filter;
            cin >> filter;

            if (filter == "1")
                invert(image);
            else if (filter == "2")
                resize(image);
            else if (filter == "3")
                grey_scale(image);
            else if (filter == "4")
                black_and_white(image);
            else if (filter == "5")
                flip(image);
            else if (filter == "6"){
                cout << "choose the type of merging:" << endl;
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
                        cout << "please choose a valid option" << endl;
                        cin >> mergeType;
                    }
                }
            }
            else if (filter == "7")
                crop(image);
            else if (filter == "8")
                purple(image);
            else if (filter == "9")
                rotate(image);
            else if (filter == "10")
                frame(image);
            else if (filter == "11")
                darken_lighten(image);
            else if (filter == "12")
                blur(image);
            else if (filter == "13")
                detect_edges(image);
            else if (filter== "14")
                infrared(image);
            else
                cout << "Invalid choice, try again" << endl << endl;
        }

        else
            cout << "Invalid Choice." << endl << endl;
    }
    return 0;
}
