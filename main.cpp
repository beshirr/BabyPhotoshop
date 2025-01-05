/**
@Purpose: Photo Editor
@Authors:
    Zeyad Mohamed Arafat - zeyadarafat833@gmail.com
    John Ayman Demian    - johnayman03@gmail.com
    Youssef Ahmed Beshir - youssefahmedbeshir@gmail.com
@GitHub: https://github.com/beshirr/BabyPhotoshop
*/


#include "Editors/filters.h"
#include "Editors/effects.h"
#include "Editors/adjustments.h"

using namespace std;


string file;

void save_image(Image& image){
    while (true){
        try{
            string choice;
            string newFileName;
            cout << "Do you want to save the same file (1) or change the file name (2)?";
            cin >> choice;

            if (choice == "1"){
                image.saveImage(file);
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

    cout << "Image saved successfully!" << endl << endl;
}

void load(Image& image){

    while (true){
        cout << "Enter the image name:";
        try{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, file);
            image.loadNewImage(file);
            break;
        }

        catch (...){}
    }

    cout << "New image loaded successfully!" << endl << endl;

}


int main(){
    cout << "Welcome to babyPhotoshop" << endl << endl;

    Image image;
    // Loading the image for the first time
    while (true){
        cout << "Enter the image name:";
        try{
            getline(cin, file);
            image.loadNewImage(file);
            break;
        }
        catch (...){// Handled in Image_Class
        }
    }
    cout << "New image loaded successfully!" << endl << endl;

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
        cout << "18- Oil painting" << endl;
        cout << "19- Old TV" << endl;
        cout << "23- Exit" << endl;
        cout << "->";
        cin >> menu;

        if (menu == "23"){

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
                            "(2) Save current then load new image\n"
                            "->";
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
            if (saved){
                cout << "Image is already saved!" << endl;
            }
            else{
                save_image(image);
                saved = true;
            }
        }

        else if (menu == "3"){
            filters::grayscale(image);
        }
        else if (menu == "4"){
            filters::black_and_white(image);
        }
        else if (menu == "5"){
            effects::invert(image);
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
                    adjustments::resize_merge(image);
                    break;
                }
                else if (mergeType == "2") {
                    adjustments::crop_merge(image);
                    break;
                }
                else {
                    cout << "Please choose a valid option" << endl;
                    cin >> mergeType;
                }
            }
        }
        else if (menu == "7"){
            adjustments::flip(image);
        }
        else if (menu == "8"){
            adjustments::rotate(image);
        }
        else if (menu == "9"){
            adjustments::darken_lighten(image);
        }
        else if (menu == "10"){
            adjustments::crop(image);
        }
        else if (menu == "11"){
            adjustments::frame(image);
        }
        else if (menu == "12"){
            effects::detect_edges(image);
        }
        else if (menu == "13"){
            adjustments::resize(image);
        }
        else if (menu == "14"){
            effects::blur(image);
        }
        else if (menu == "15"){
            filters::sunlight(image);
        }
        else if (menu == "16"){
            filters::purple(image);
        }
        else if (menu == "17"){
            filters::infrared(image);
        }
        else if (menu == "18"){
            effects::oil_painting(image);
        }
        else if (menu == "19"){
            effects::old_TV(image);
        }

        else
            cout << "Invalid choice, Try again." << endl << endl;
    }
    return 0;
}
