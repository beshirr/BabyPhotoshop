# include <bits/stdc++.h>
# include <cmath>
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
    while (true){
        try{
            cout << "please enter the filtered image name: ";
            cin >> newFileName;
            image.saveImage(newFileName);
            break;
        }
        catch (...){

        }
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
    cout << "Please enter the filtered image name: ";
    cin >> newFileName;
    pic.saveImage(newFileName);
    cout << "Done well" << endl;
}


void invert(Image image){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            for (int k = 0; k < 3; ++k) {
                image(i,j,k) = 255 - image(i, j, k);
            }
        }
    }

    string newFileName;
    cout << "please enter the filtered image name: ";
    cin >> newFileName;
    image.saveImage(newFileName);
}


void merger(Image image){ // not complete.

    int counter = 0;
    string mergeFileName;
    cout << "please enter the name of the image you want to merge:";
    cin >> mergeFileName;

    Image mergeImage(mergeFileName);

    if ((image.width == mergeImage.width) and (image.height == mergeImage.height)){
        Image mergedImage(image.width, image.height);

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

        string newFileName;
        cout << "please enter the filtered image name:";
        cin >> newFileName;
        mergedImage.saveImage(newFileName);
        counter = 0;
    }

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

        string newFileName;
        cout << "please enter the filtered image name: ";
        cin >> newFileName;
        mergedImage.saveImage(newFileName);
        counter = 0;
    }
}


void flip(Image image){
    string choice;
    while (true){
        cout << "Please select:\n1 - Horizontal flip \n2 - Vertical flip \nEnter your choice: ";
        cin >> choice;
        if (choice == "1"){
            choice = "1";
            break;
        }else if (choice == "2"){
            choice = "2";
            break;

        } else{
            cout << endl <<"Invalid choice !"<<endl;
            continue;
        }

    }

    if (choice == "1") {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    swap(image(i, j, k), image(image.width - i - 1, j, k));
                }
            }
        }
    }
    else if (choice == "2") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    swap(image(i, j, k), image(i, image.height - j - 1, k));
                }
            }
        }
    }

    string newFileName;
    cout << "Please enter the filtered image name: ";
    cin >> newFileName;
    image.saveImage(newFileName);
}




void rotate(){}


void darken_lighten(Image image) {
    string choice;
    while (true){
        cout << "Please select:\n1 - Lighten filter \n2 - Darken filter\nEnter your choice: ";
        cin >> choice;
        if (choice == "1"){
            choice = "1";
            break;
        }else if (choice == "2"){
            choice = "2";
            break;

        } else{
            cout << endl <<"Invalid choice !"<<endl;
            continue;
        }

    }

    if (choice == "1"){
        // Iterate through each pixel of the image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Make the image lighter by 50%
                    float newPixelValue = image(i, j, k) * 1.5;
                    // Clamp pixel value to range [0, 255]
                    image(i, j, k) = static_cast<unsigned char>(min(max(newPixelValue, 0.0f), 255.0f));
                }
            }
        }

    } else if (choice== "2" ){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Make the image lighter by 50%
                    float newPixelValue = image(i, j, k) * 0.5;
                    // Clamp pixel value to range [0, 255]
                    image(i, j, k) = static_cast<unsigned char>(min(max(newPixelValue, 0.0f), 255.0f));
                }
            }
        }

    }
    // Save the modified image
    string newFileName;
    cout << "Please enter the filtered image name: ";
    cin >> newFileName;
    image.saveImage(newFileName);
    cout << "Done well" << endl;
}


void crop(){}


void frame(){}


void detect_edges(){}


void resize(Image image){

    // getting the dimensions of the resized image from the user.
    int width_, height_;
    cout << "enter the dimensions of the new image: ";
    while(!(cin >> width_) or !(cin >> height_)){
        cin.clear();
        cin.ignore();
        cout << "please enter a valid width or height (a positive integer.)" << endl;
    }
    // create a new image with the dimensions we got from the user.
    Image resizedImage(width_, height_);
    // calculating the ratio between the width and height of the original image and the resized one.
    double widthRatio = static_cast<double>(image.width) / resizedImage.width;
    double heightRatio = static_cast<double>(image.height) / resizedImage.height;
    // iterate through the resized image and assigning the colors of the original image to the resized one using the ratio we calculated earlier.
    for (int i = 0; i < resizedImage.width; ++i) {
        for (int j = 0; j < resizedImage.height; ++j) {
            resizedImage(i, j, 0) = image(floor(i * widthRatio), floor(j * heightRatio), 0);
            resizedImage(i, j, 1) = image(floor(i * widthRatio), floor(j * heightRatio), 1);
            resizedImage(i, j, 2) = image(floor(i * widthRatio), floor(j * heightRatio), 2);
        }
    }
    // saving the image.
    string newFileName;
    while (true){
        try{
            cout << "please enter the filtered image name: ";
            cin >> newFileName;
            resizedImage.saveImage(newFileName);
            break;
        }
        catch (...){

        }
    }

}


void blur(){}



int main(){

    cout << "Welcome to BabyPhotoshop" << endl << endl;
    string menu;

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
                    cout << "Enter the image name" << endl;
                    cout << "->";
                    cin >> fileName;

                    image.loadNewImage(fileName);

                    break;

                }
                catch (...){

                }
            }

            cout << endl;
            cout << "Choose a filter: " << endl;
            cout << "1- Invert" << endl;
            cout << "2- Resize" << endl;
            cout << "3- Gray Scale" << endl;
            cout << "4- Black and white" << endl;
            cout << "5- Flip" << endl;


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


                default:
                    cout << "Invalid choice, try again." << endl << endl;
            }

        }

        else
            cout << "Invalid Choice." << endl << endl;

    }

    return 0;
}