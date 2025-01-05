#ifndef BABYPHOTOSHOP_ADJUSTMENTS_H
#define BABYPHOTOSHOP_ADJUSTMENTS_H

#include "Headers/Image_Class.h"
#include <string>

using namespace std;

class adjustments {
public:
    static void darken_lighten(Image& image){
        string choice;

        while (true){
            cout << "Please select:\n1- Lighten filter \n2- Darken filter\nEnter your choice:";
            cin >> choice;

            // lighten
            if (choice == "1"){
                // Iterate through each pixel of the image
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            // Make the image lighter by 50% by + 0.5 of light
                            auto new_Value = static_cast<float>(image(i, j, k) * 1.5);
                            // make pixel value in range [0, 255]
                            image(i, j, k) = static_cast<unsigned char>(min(max(new_Value, 0.0f), 255.0f));
                        }
                    }
                }
                break;
            }

            // Darken
            if (choice == "2"){
                // Iterate through each pixel of the image
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            // Make the image lighter by 50% by - 0.5 of lights
                            auto new_Value = static_cast<float>(image(i, j, k) * 0.5);
                            // make pixel value in range [0, 255]
                            image(i, j, k) = static_cast<unsigned char>(min(max(new_Value, 0.0f), 255.0f));
                        }
                    }
                }
                break;
            }

            cout << endl << "Invalid choice!" <<endl;
        }
    }


    static void crop_merge(Image& image){

        // the counter will help in the merging part.
        int counter = 0;
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
            catch(...){// Handled in Image_Class.h
            }
        }

        // if the two images have the same width and height we start merging them directly.
        if ((image.width == mergeImage.width) and (image.height == mergeImage.height)){
            Image mergedImage(image.width, image.height);

            // the merging is done by taking a pixel of each image (one pixel from an image then one pixel from the other one)
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

            // if the two images don't have the same width or height, we do the merge and crop a part from the bigger image.
        else{
            Image mergedImage(min(image.width , mergeImage.width), min(image.height , mergeImage.height));

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
        cout << "Done!" << endl << endl;
    }


    static void resize_merge(Image& image){
        // the counter will help in the merging part.
        int counter = 0;
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

            catch(...){ // Handled in Image_Class.h
            }
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

            // if both images don't have the same width or height, then we'll first resize them before merging.
        else{
            Image mergedImage(max(image.width , mergeImage.width), max(image.height , mergeImage.height));

            // resizing the first image.
            // using the same algorithm as in the resizing function.
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
    }


    static void flip(Image& image){
        string choice;
        while (true){
            cout << "Please select:\n1- Horizontal flip \n2- Vertical flip \nEnter your choice:";
            cin >> choice;

            // Horizontal flip
            if (choice == "1"){
                for (int i = 0; i < image.width / 2; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            swap(image(i, j, k), image(image.width - i - 1, j, k));
                        }
                    }
                }
                break;
            }
                // Vertical flip
            else if (choice == "2"){
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height / 2; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            swap(image(i, j, k), image(i, image.height - j - 1, k));
                        }
                    }
                }
                break;

            }

            else{
                cout << endl << "Invalid choice!" << endl;
            }
        }
    }


    static void rotate(Image& image){
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
    }


    static void crop(Image& image){
        int x, y, h, w;
        cout << "Enter the index of the starting point(ex: 600 500): ";
        cin >> x >> y;

        while (true) {
            if (cin.fail()) {
                cout << "Please use a valid index!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> x >> y;
            }
            else if ((x > image.width) or (y > image.height)){
                cout << "This index seems too big for the image!" << endl;
                cout << "Enter the index of the starting point(ex: 600 500): ";
                cin >> x >> y;
            }
            else {
                break;
            }
        }

        cout << "Enter the size of the cropped image(ex: 600 900): ";
        cin >> w >> h;

        while (true) {
            if (cin.fail()) {
                cout << "Please use a valid size!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> x >> y;
            }
            else if ((w + x > image.width) or (h + y > image.height)) {
                cout << "This size seems too high for the image you are trying to crop!" << endl;
                cout << "Enter the size of the cropped image(ex: 600 900): ";
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
    }


    static void simple_frame(Image& image, int red, int green, int blue, int frameSize){

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


    static void fancy_frame(Image& image, int red, int green, int blue, int frameSize, bool isWhite){
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


    static void frame(Image& image){

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

                if (color == "2") {
                    red = 255;
                    green = 255;
                    blue = 255;
                    isWhite = true;
                    break;
                }

                if (color == "3") {
                    red = 176;
                    green = 91;
                    blue = 71;
                    break;
                }

                if (color == "4") {
                    red = 102;
                    green = 179;
                    blue = 80;
                    break;
                }

                if (color == "5") {
                    red = 65;
                    green = 105;
                    blue = 225;
                    break;
                }

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

            if (option == "F" || option == "f") {
                fancy_frame(image, red, green, blue, frameSize, isWhite);
                break;
            }


            cout << "Invalid option, try again" << endl;
        }
    }


    static void resize(Image& image){

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
    }
};
#endif