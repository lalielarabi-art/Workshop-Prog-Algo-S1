#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>

void green(sil::Image& image)
{
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x,y).r = 0.f;
            image.pixel(x,y).b = 0.f;
        }
    }
}

void blackwhite(sil::Image& image){
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            float gray = (image.pixel(x,y).r + image.pixel(x,y).g + image.pixel(x,y).b) / 3.0f;
            image.pixel(x,y).r = gray;
            image.pixel(x,y).g = gray;
            image.pixel(x,y).b = gray;
        }
    }
}

void blackwhite1(sil::Image& image){
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            float gray = (image.pixel(x,y).r*0.2126f + image.pixel(x,y).g*0.7152f + image.pixel(x,y).b*0.0722f);
            image.pixel(x,y).r = gray;
            image.pixel(x,y).g = gray;
            image.pixel(x,y).b = gray;
        }
    }
}

void mirror(sil::Image& image){
    sil::Image copy = image;
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x,y)=copy.pixel(image.width() - (x+1), y);
        }
    }
}

void neg(sil::Image& image){
    sil::Image copy = image;
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x,y) = 1.0f - copy.pixel(x,y);
        }
    }
}


void switch_channels(sil::Image& image){
    sil::Image copy = image;
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x,y).r =copy.pixel(x,y).g;
            image.pixel(x,y).g =copy.pixel(x,y).r;

        }
    }
}

void degraded(sil::Image& image){
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            float t = static_cast<float>(x) / (image.width() - 1);
            image.pixel(x,y) = {t, t, t};

        }
    }
}

void noisy(sil::Image& image){
    for (int y = 0; y < image.height(); ++y)
    {
        for (int i = 0; i < 100; ++i)
        {
            float pix=random_float(0.0f, image.width()-1);
            float r = random_float(0.0f,1.0f);
            float g = random_float(0.0f,1.0f);
            float b = random_float(0.0f,1.0f);


            image.pixel(pix,y) = {r,g,b};
        }
    }
}

void rotate(sil::Image& image){
    sil::Image new_image{image.height(), image.width()};
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            new_image.pixel(image.height()-1-y,x)=image.pixel(x,y);
           

        }
  }
   image=new_image;
}

void split(sil::Image& image){
    sil::Image copy = image;
    int shift=30;
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            int xr=x-shift;         
            if (xr<0) xr=0;

            int xb=x+shift;
            if (xb>=image.width()) xb=image.width()-1;
   
            image.pixel(x,y).r =copy.pixel(xr,y).r;    
            image.pixel(x,y).g =copy.pixel(x,y).g;
            image.pixel(x,y).b =copy.pixel(xb,y).b;
            
        }
    }
}

void brightness(sil::Image& image){ //éclaircissement avec puissance 1/2
    sil::Image copy = image;
    
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x,y).r =std::sqrt(copy.pixel(x,y).r);    
            image.pixel(x,y).g =std::sqrt(copy.pixel(x,y).g);
            image.pixel(x,y).b =std::sqrt(copy.pixel(x,y).b);   
        }
    }
}

void brightness1(sil::Image& image){ //assombrissement avec puissance 2
    sil::Image copy = image;

    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x,y).r =(copy.pixel(x,y).r)*(copy.pixel(x,y).r);    
            image.pixel(x,y).g =(copy.pixel(x,y).g)*(copy.pixel(x,y).g);
            image.pixel(x,y).b =(copy.pixel(x,y).b)*(copy.pixel(x,y).b);
        }
    }
}

int main()
{
    { 
    sil::Image image{"images/logo.png"};
    green(image);
    image.save("output/green_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    blackwhite(image);
    image.save("output/blackwhite_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    blackwhite1(image);
    image.save("output/blackwhite1_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    mirror(image);
    image.save("output/mirror_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    neg(image);
    image.save("output/neg_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    switch_channels(image);
    image.save("output/switch_channels_logo.png");
    }

    {
    sil::Image image{300,200};
    degraded(image);
    image.save("output/degraded_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    noisy(image);
    image.save("output/noisy_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    rotate(image);
    image.save("output/rotate_logo.png");
    }

    {
    sil::Image image{"images/logo.png"};
    split(image);
    image.save("output/split_logo.png");
    }

    {
    sil::Image image{"images/photo.jpg"};
    brightness(image);
    image.save("output/brightness_photo.jpg");
    }
    
    {
    sil::Image image{"images/photo.jpg"};
    brightness1(image);
    image.save("output/brightness1_photo.jpg");
    }
}