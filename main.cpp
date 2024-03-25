# include <bits/stdc++.h>
# include <cmath>
# include "Image_Class.h"

using namespace std;


bool input_validity(){};


void save(){};


void load(){};


void grey_scale(Image image){

    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){

            int avg = (image(i, j, 0) + image(i, j, 1) +
                       image(i, j, 2)) / 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }

    }

    string newFileName;
    cout << "please enter the filtered image name: ";
    cin >> newFileName;
    image.saveImage(newFileName);
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


void merger(Image image){

    int counter = 0;
    string mergeFileName;
    cout << "please enter the name of the image you want to merge: ";
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
        cout << "please enter the filtered image name: ";
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


};


void flip(Image image){
    string choice;
    cout << "Please select:\n1 - Horizontal flip\n2 - Vertical flip\nEnter your choice: ";
    cin >> choice;

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



void rotate(Image image){

};


void darken_lighten(){};


void crop(){};


void frame(){};


void detect_edges(){};


void resize(){};


void blur(){};



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
            cout << "2- Rotate" << endl;
            cout << "3- Gray_Scale" << endl;
            cout << "4- Black and white" << endl;
            cout << "5- Flip" << endl;


            char filter;
            cin >> filter;

            switch(filter){

                case '1':
                    invert(image);
                    break;

                case '2':
                    rotate(image);
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
