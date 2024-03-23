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

    string menu;

    while (true){
        // Program Menu
        cout << "Welcome to BabyPhotoshop" << endl << endl;
        cout << "1- Load an image (1)" << endl;
        cout << "2- exit (-1)" << endl << endl;

        cin >> menu;


        if (menu == "-1"){
            break;
        }

        else if (menu == "1"){

        }

        else
            cout << "Invalid Choice." << endl << endl;

    }

    return 0;
}