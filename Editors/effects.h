#ifndef BABYPHOTOSHOP_EFFECTS_H
#define BABYPHOTOSHOP_EFFECTS_H

#include "Headers/Image_Class.h"

using namespace std;

class effects {
public:
    static void invert(Image& image){
        // Iterate through the image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                for (int k = 0; k < 3; ++k) {
                    // Colour inversion is achieved by subtracting each RGB colour value from the maximum possible value
                    image(i,j,k) = 255 - image(i, j, k);
                }
            }
        }
    }


    static void detect_edges(Image& image){
        // Detect edges in the image using Sobel operator
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
    }


    static void blur(Image& image){

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
    }


    static void oil_painting(Image& image){
        Image oilImage(image.width, image.height);
        for (int i = 10; i < image.width - 10; i += 20){
            for (int j = 10; j < image.height - 10; j += 20){
                int bin_31_875 = 0, maxR1 = 0, maxG1=0, maxB1 =0;
                int bin_63_75 = 0, maxR2 = 0, maxG2=0, maxB2 =0;
                int bin_95_625 = 0, maxR3 = 0, maxG3=0, maxB3 =0;
                int bin_127_5 = 0, maxR4 = 0, maxG4=0, maxB4 =0;
                int bin_159_375 = 0, maxR5 = 0, maxG5=0, maxB5 =0;
                int bin_191_25 = 0, maxR6 = 0, maxG6=0, maxB6 =0;
                int bin_223_125 = 0, maxR7 = 0, maxG7=0, maxB7 =0;
                int bin_255 = 0, maxR8 = 0, maxG8=0, maxB8 =0;
                for (int x = i-10; x < i+11; x++){
                    for (int y = j-10; y < j+11; y++){
                        double currentIntensity;
                        currentIntensity = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3.0;
                        if (currentIntensity >= 223.125){
                            bin_255++;
                            maxR8 += image(x, y, 0);
                            maxG8 += image(x, y, 1);
                            maxB8 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 191.25){
                            bin_223_125++;
                            maxR7 += image(x, y, 0);
                            maxG7 += image(x, y, 1);
                            maxB7 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 159.375){
                            bin_191_25++;
                            maxR6 += image(x, y, 0);
                            maxG6 += image(x, y, 1);
                            maxB6 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 127.5){
                            bin_159_375++;
                            maxR5 += image(x, y, 0);
                            maxG5 += image(x, y, 1);
                            maxB5 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 95.625){
                            bin_127_5++;
                            maxR4 += image(x, y, 0);
                            maxG4 += image(x, y, 1);
                            maxB4 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 63.75){
                            bin_95_625++;
                            maxR3 += image(x, y, 0);
                            maxG3 += image(x, y, 1);
                            maxB3 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 31.875){
                            bin_63_75++;
                            maxR2 += image(x, y, 0);
                            maxG2 += image(x, y, 1);
                            maxB2 += image(x, y, 2);
                        }
                        else if (currentIntensity >= 0){
                            bin_31_875++;
                            maxR1 += image(x, y, 0);
                            maxG1 += image(x, y, 1);
                            maxB1 += image(x, y, 2);
                        }
                    }
                }

                for (int x = i-10; x < i+11; x++){
                    for (int y = j-10; y < j+11; y++){
                        double currentIntensity;
                        currentIntensity = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3.0;
                        if (currentIntensity >= 223.125){
                            image(x, y, 0) = maxR8 / bin_255;
                            image(x, y, 1) = maxG8 / bin_255;
                            image(x, y, 2) = maxB8 / bin_255;
                        }
                        else if (currentIntensity >= 191.25){
                            image(x, y, 0) = maxR7 / bin_223_125;
                            image(x, y, 1) = maxG7 / bin_223_125;
                            image(x, y, 2) = maxB7 / bin_223_125;
                        }
                        else if (currentIntensity >= 159.375){
                            image(x, y, 0) = maxR6 / bin_191_25;
                            image(x, y, 1) = maxG6 / bin_191_25;
                            image(x, y, 2) = maxB6 / bin_191_25;
                        }
                        else if (currentIntensity >= 127.5){
                            image(x, y, 0) = maxR5 / bin_159_375;
                            image(x, y, 1) = maxG5 / bin_159_375;
                            image(x, y, 2) = maxB5 / bin_159_375;
                        }
                        else if (currentIntensity >= 95.625){
                            image(x, y, 0) = maxR4 / bin_127_5;
                            image(x, y, 1) = maxG4 / bin_127_5;
                            image(x, y, 2) = maxB4 / bin_127_5;
                        }
                        else if (currentIntensity >= 63.75){
                            image(x, y, 0) = maxR3 / bin_95_625;
                            image(x, y, 1) = maxG3 / bin_95_625;
                            image(x, y, 2) = maxB3 / bin_95_625;
                        }
                        else if (currentIntensity >= 31.875){
                            image(x, y, 0) = maxR2 / bin_63_75;
                            image(x, y, 1) = maxG2 / bin_63_75;
                            image(x, y, 2) = maxB2 / bin_63_75;
                        }
                        else if (currentIntensity >= 0){
                            image(x, y, 0) = maxR1 / bin_31_875;
                            image(x, y, 1) = maxG1 / bin_31_875;
                            image(x, y, 2) = maxB1 / bin_31_875;
                        }
                    }
                }


            }
        }
        cout << "Done!" << endl;
    }


    static void old_TV(Image& image){
        int counter = 0;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                if (j % 10 != 0){
                    if (counter % 3 == 2){
                        image(i, j, 0) = 0;
                        image(i, j, 1) = 0;
                        image(i, j, 2) = 0;
                        counter++;
                    }
                    else{
                        image(i, j, 0) = image(i, j, 0);
                        image(i, j, 1) = image(i, j, 1);
                        image(i, j, 2) = image(i, j, 2);
                        counter++;
                    }
                }
            }
        }

        cout << "Done!" << endl;
    }
};


#endif
