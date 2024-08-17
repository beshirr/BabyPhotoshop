#ifndef BABYPHOTOSHOP_FILTERS_H
#define BABYPHOTOSHOP_FILTERS_H

#include "Image_Class.h"

class filters {
public:
    static void grayscale(Image& image){
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
    }


    static void black_and_white(Image& image){
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
    }


    static void purple(Image& image){
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
    }


    static void infrared(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // set the red 255 and invert green and blue
                image(i,j,0) = 255;
                image(i,j,1) = 255 - image(i,j,1) ;
                image(i,j,2) = 255 - image(i,j,2) ;

            }

        }
    }


    static void sunlight(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                int redTent = 40, greenTent = 30, blueTent = 30;

                while (image(i, j, 0) + redTent > 255) redTent --;
                image(i, j, 0) += redTent;

                while (image(i, j, 1) + greenTent > 255) greenTent --;
                image(i, j, 1) += greenTent;

                while (image(i, j, 2) - blueTent < 0) blueTent --;
                image(i, j, 2) -= blueTent;
            }
        }
    }
};

#endif

