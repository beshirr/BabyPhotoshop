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


void save(){}


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


void rotate(){}


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


void frame(){}


void detect_edges(){}


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


void blur(){}


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

            char filter;
            cin >> filter;

            switch(filter){

                case '1':
                    invert(image);
                    break;

                case '2':
                    resize(image);
                    break;

                case '3':
                    grey_scale(image);
                    break;

                case '4':
                    black_and_white(image);
                    break;

                case '5':
                    flip(image);
                    break;

                case '6':
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
                    break;

                case '7':
                    crop(image);
                    break;

                case '8':
                    purple(image);
                    break;
                    
                default:
                    cout << "Invalid choice, try again." << endl << endl;
            }

        }

        else
            cout << "Invalid Choice." << endl << endl;
    }
    return 0;
}
