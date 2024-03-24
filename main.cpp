# include <bits/stdc++.h>
# include "Image_Class.h"

using namespace std;


bool input_validity(){};


void save(){};


void load(){};


void grey_scale(){};


void black_and_white(){};


void invert(){};


void merge(){};


void flip(){};


void rotate(){};


void darken_lighten(){};


void crop(){};


void frame(){};


void detect_edges(){};


void resize(){};


void blur(){};



int main(){

    cout << "Welcome to BabyPhotoshop" << endl << endl;
    string menu;

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

            cout << "Enter the image name" << endl;
            cout << "->";
            cin >> fileName;

            Image image(fileName);

            cout << "Choose a filter: " << endl;
            cout << "1- Invert" << endl;
            cout << "2- Rotate" << endl;


            char filter;
            cin >> filter;

            switch(filter){

                case '1':
                    invert();
                    break;

                case '2':
                    rotate();
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