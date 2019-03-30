// Image sample
#include <ivl/image>
#include <ivl/ivl>
#include <ivl/ivlcv>
//#include <ivl/array_2d>
#include <ivl/system>
#include <iostream>


using namespace ivl;
using namespace std;

void image_sample(); // generic image functions
void ip_sample(); // image processing functions
void plot_sample(); // plotting functions


void image_main()
{
    image_sample();
    ip_sample();
    plot_sample();
}

timer t;

#if 1
void image_sample()
{

    array_2d<double> xx(5,5);
    for(size_t i=0; i<25; i++) xx[i]=i;
    for(size_t i=0; i<5; i++)
    {
        array<double> f(xx(ivl::index_array(i), ivl::all()));

        // the same without the explicit constructor
        array<double> f2(xx(i, ivl::all()));

    }

    cout << endl << "BASIC IMAGE OPERATIONS" << endl;
    cout << "--------------------------------------" << endl;

    image<int> a;
    cout << "Default constructor: a="<< a << endl << endl;

    image<double> b(5, 7, 3);
    cout << "Construct using custom initial dimensions: b="<< b << endl << endl;

    image<double> c(5, 7, 3, 1);
    cout << "Construct using custom initial dimensions and value: c="<< c << endl << endl;

    image<uchar> d("img/lena.jpg");
    cout << "Construct by loading from a filename: d=(shown)" << endl << endl;

    try
    {
        image<uchar> e("img/foo.jpg");
    }
    catch(std::exception&)
    {
        cout << "Construct by loading can be used with exception handling" << endl << endl;
    }//TODO: should cout the exception

    IplImage* ipl = cvCreateImage(cvSize(2,2), IPL_DEPTH_8U, 3);
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++)
        {
            CvScalar s;
            //s=cvGet2D(ipl,i,j); // get the (i,j) pixel value
            s.val[0]='r';
            s.val[1]='g';
            s.val[2]='b';
            cvSet2D(ipl,i,j,s);
        }


    image<uchar> f(ipl);
    cvReleaseImage(&ipl);
    cout << "Construct from an existing IplImage: f=(shown)" << endl << endl;

    array_nd<double> nd_f(idx(2,2,1));
    image<double> g(nd_f);
    cout << "Construct from an existing array_nd of the same type: g="<< f << endl << endl;

    a.load("img/maimou.jpg");
    cout << "Load from a file: a=(shown)" << endl << endl;

    a.save("img/maimoux.jpg");
    cout << "Save to a file: img/maimoux.jpg was saved" << endl << endl;

    //a = cast(b);
    cout << "Cast from image<double> b, to image<int>: a="<< endl << endl;
}

void ip_sample()
{
    cout << endl << "IMAGE PROCESSING OPERATIONS" << endl;
    cout << "--------------------------------------" << endl;

    image<uchar> c("img/lena.jpg");
    cout << "original c:(shown" << endl << endl;
    show(c, "");

    //show(d,"sub");
    //d=flipud(d);
    //show(d,"sub");



    cout << "flipud(c)" << endl << endl;
    show(flipud(c), "flipud(c)");

    cout << "fliplr(c)" << endl << endl;
    show(fliplr(c), "fliplr(c)");

    cout << "rotate(c)" << endl << endl;
    show(rotate(c, 15, point<float>(float(c.height()) / 2,
                                    float(c.width()) / 2)), "rotate(c)");

}

void plot_sample()
{

    array<array<double> > a(2, arr._<double>()(1));

//report(cast<array<size_t> >(a).base());
//report(cast<size_t>(a).base());
    //array<array<size_t> > b = (cast<array<size_t> >(a));

    array<array<size_t> > b = (cast<size_t>(a));



    cout << "cast<array<size_t> > : " << b << endl;

    t.tic();

    image<uchar> i(700, 700, 3, 0);

    i.line(point<double>(50, 50), point<double>(120, 100), colors::white<uchar, colors::rgb>());

    i.ellipse(point<double>(150, 150), point<double>(180, 340), 200 / 2, colors::white<uchar, colors::rgb>(), 2.0);

    i.ellipse(point<double>(550, 250), point<double>(480, 340), 200 / 2, colors::white<uchar, colors::rgb>(), 1.0);

    i.fill_ellipse(point<double>(150, 150), point<double>(180, 340), 200 / 2, color<uchar>(arr._<uchar>()(155, 155, 255)), 0.5);

    i.fill_ellipse(point<double>(150, 150), point<double>(180, 340), (200 - 12.5) / 2., color<uchar>(arr._<uchar>()(255, 0, 0)), 0.4);

    i.fill_triangle(point<double>(100, 100), point<double>(100, 50), point<double>(50, 50), colors::white<uchar, colors::rgb>(), 0.5);

    i.fill_quad(point<double>(200, 100), point<double>(220, 100), point<double>(240, 110), point<double>(230, 151));

    i.fill_rect(point<double>(400, 50), point<double>(500, 100));


    i.ellipse(point<double>(300, 550), 100, 50, 3.14 / 4, colors::white<uchar, colors::rgb>(), 2.0);

    i.fill_ellipse(point<double>(300, 550), 70, 50, 3.14 / 4, colors::white<uchar, colors::rgb>());

    //i.fill_ellipse(point<double>(100, 150), point<double>(180, 340), 200 / 2, white<uchar>(), 2.0);
    double dur = t.toc();
    cout << "Time for plotting': " << dur << " ms." << endl;


    show(i, "image");

}

#if 1

int main()
{
    image_main();
}

#else

// define 3 images of unsinged 8-bit per channel (uchar)
image<uchar> img;
image<uchar> maimou;
image<uchar> spiti;

void img_load_sample()
{
    double dur;
    // load from files
    try
    {
        // start the timers
        t.tic();
        img.load("img/lena.jpg");
        dur = t.toc();
        cout << "Time for loading image 'img/lena.jpg': " << dur << " ms." << endl;
        t.tic();
        maimou.load("img/maimou.jpg");
        dur = t.toc();
        cout << "Time for loading image 'img/maimou.jpg': " << dur << " ms." << endl;
        t.tic();
        spiti.load("img/spiti.bmp");
        dur = t.toc();
        cout << "Time for loading image 'img/spiti.bmp': " << dur << " ms." << endl;
    }
    catch(ivl::exception&)
    {
        // in case loading one of the files fails
        cout << "Loading image failed. please make sure the sample files exist" << endl;
        exit(1);
    }
}

void img_flip_sample()
{
    double dur;
    // vertical and horizontal flipping of img
    cout << "vertical and horizontal flipping..." << endl;
    image<uchar> img1;
    image<uchar> img2;
    image<uchar> img3;
    image<uchar> img4;
    t.tic();
    img1 = flipud(img);
    dur = t.toc();
    cout << "Time for flipud: " << dur << "ms." << endl;
    t.tic();
    img2 = fliplr(img);
    dur = t.toc();
    cout << "Time for fliplr: " << dur << "ms." << endl;
    t.tic();
    img3 = rotate (img, 15, point<float>(img.height() / 2.0f, img.width() / 2.0f));
    dur = t.toc();
    cout << "Time for rotate(img, 15): " << dur << "ms." << endl;
    t.tic();
    img4 = rotate(img, -15, point<float> (0, 0), 1.0, cubic, inverse_map);
    dur = t.toc();
    cout << "Time for rotate(img, 15) with cubic interpolation and inverse map warp: " << dur << "ms." << endl;

    show(img, "original",
         img1, "flipud",
         img2, "fliplr",
         img3, "rotate by 15 degrees ccw around image center",
         img4, "rotate by 15 degrees cw around (0, 0), inverse map warp");
    // quickview: displays img, img1 and img2 into two separate windows
}

void img_grayscale_sample()
{
    double dur;
    // grayscale 3 channels => 1
    cout << "grayscale..." << endl;
    image<uchar> gray;
    t.tic();
    gray = grayscale(img);
    dur = t.toc();
    cout << "Time for grayscale: " << dur << "ms." << endl;

    // setting and retrieving color values with pixelcolor and color class
    cout << "setting and retrieving color values..." << endl;

    // we use a color<uchar> value
    // the color class is generic, for any k-channel color.
    color<uchar> color0 = img.col(50, 50);
    color<uchar, 3> colorrgb = img.col(50, 50);

    // we get a color value from the image
    cout << "the color value at position (50, 50) in RGB form is ("
         << int(colorrgb.r) << ", " << int(colorrgb.g) << ", "
         << int(colorrgb.b) << ")" << endl;

    // we set a color value to the image using a C array
    uchar newcol[] = {255, 255, 255};
    img.col(50, 50) = newcol;
    //cout << "the new color value at position (50, 50) of the image is " <<
    //	(array<int> out = cast<int>(array<uchar> (color<uchar> (img.col(50, 50))))) << endl;
    // we convert the color to array<int> so that it is not printed in ascii

    // we set a color value to the image using a color<char>
    img.col(50, 50) = color0;
    //cout << "the color value at position (50, 50) has been set back to " <<
    //	array<int>(color<uchar> (img.col(50, 50))) << endl;

    // we get a 1-channel color value from the image the same way as 3-channel
    color0 = gray.col(50, 50);
    cout << "the gray value at position (50, 50) of the grayscale image is " <<
         int(color0.val()) << endl;

    // display the images, original and grayscale
    show(img, "original", gray, "grayscale");
}

void img_resize_sample()
{
    // resizing image
    double dur;
    cout << "resizing..." << endl;
    image<uchar> img1;
    image<uchar> img2;
    t.tic();
    img1 = resample(img, 200, 100);
    dur = t.toc();
    cout << "Time for resize (200, 100): " << dur << "ms." << endl;
    t.tic();
    img2 = resample(img, 800, 600);
    dur = t.toc();
    cout << "Time for resize (800, 600): " << dur << "ms." << endl;

    show(img, "original",
         img1, "resized (200, 100)",
         img2, "resized (800, 600)");
}

void img_wrappers_sample()
{
    // opencv wrappers
    cout << "open-cv wrapped algorithms..." << endl;
    double dur;
    image<uchar> gray;
    image<uchar> img1;
    image<float> img2;
    image<int> img3;
    image<uchar> img4;
    image<uchar> img5;
    image<float> img6;
    image<float> img7;
    image<float> img8;
    image<float> img9;
    // image derivative algorithms
    cout << "image derivative algorithms..." << endl;
    t.tic();
    img1 = sobel(img, 2, 1, 3);
    dur = t.toc();
    cout << "Time for sobel(img, 2, 1, 3): " << dur << "ms." << endl;
    t.tic();

    img2 = laplace(rval(cast<float>(img))); // to float
    img2 /= float(255);
    dur = t.toc();
    cout << "Time for laplace 8u->32f and float conversion: " << dur << "ms." << endl;
    t.tic();
    img3 = cast<int>(laplace(rval(cast<float>(img)))); // to int
    dur = t.toc();
    cout << "Time for laplace 8u->16s: " << dur << "ms." << endl;
    /*
    img4 = edges(img, 50, 200) edges canny algorithm fails... */
    show(img, "original",
         img1, "sobel(img, 2, 1, 3)");

    show(
        img2, "laplace 8u->32f");

    show(
        img3, "laplace 8u->16s");

    // pyramid (gaussian) double size and half size algorithms
    cout << "pyramid (gaussian) double size and half size algorithms..." << endl;
    t.tic();
    img4 = pyramid_up(img);
    dur = t.toc();
    cout << "Time for pyramid_up: " << dur << "ms." << endl;
    t.tic();
    img5 = pyramid_down(img);
    dur = t.toc();
    cout << "Time for pyramid_down: " << dur << "ms." << endl;
    show(img, "original",
         img4, "pyramid up",
         img5, "pyramind down");

    // various corner detection algorithms
    cout << "various corner detection algorithms..." << endl;
    gray = grayscale(img);
    // use the grayscale image
    t.tic();
    img6 = cast<float>(pre_corner_detect(gray));
    img6 *= float(255.0);
    dur = t.toc();
    cout << "Time for pre_corner_detect: " << dur << "ms." << endl;
    t.tic();
    img7 = corner_eigenvals(rval(cast<float>(gray)), 3);
    dur = t.toc();
    cout << "Time for corner_eigenvals(gray, 3): " << dur << "ms." << endl;
    t.tic();
    img8 = corner_min_eigenval(rval(cast<float>(gray)), 3);
    img8 *= float(255.0);
    dur = t.toc();
    cout << "Time for corner_min_eigenval(gray, 3): " << dur << "ms." << endl;
    t.tic();
    img9 = corner_harris(rval(cast<float>(gray)), 3);
    img9 *= float(255.0);
    dur = t.toc();
    cout << "Time for corner_harris(gray, 3): " << dur << "ms." << endl;
    /*
    corner_detect(float(255)*image<float>(gray)) fails ... */
    show(image<float>(img), "original",
         img6, "pre_corner_detect",
         img7, "corner_eigenvals(gray, 3)",
         img8, "corner_min_eigenval(gray, 3)",
         img9, "corner_harris(gray, 3)");

    // various blur algorithms
    cout << "various blur algorithms..." << endl;
    img2 = cast<float>(img);
    // using the float image
    t.tic();
    img6 = blur_no_scale(img2);
    dur = t.toc();
    cout << "Time for blur_no_scale: " << dur << "ms." << endl;
    t.tic();
    img7 = blur(img2, 9);
    dur = t.toc();
    cout << "Time for blur(img, 9): " << dur << "ms." << endl;
    t.tic();
    img8 = gaussian_blur(img2, 9);
    dur = t.toc();
    cout << "Time for gaussian_blur(img, 9): " << dur << "ms." << endl;
    t.tic();
    img4 = median_blur(img, 9);
    dur = t.toc();
    cout << "Time for median_blur(img, 9): " << dur << "ms." << endl;
    t.tic();
    img5 = bilateral_blur(img, 9);
    dur = t.toc();
    cout << "Time for bilateral_blur(img, 9): " << dur << "ms." << endl;
    t.tic();
    show(img6, "blur_no_scale",
         img7, "blur(img, 9)",
         img8, "gaussian_blur(img, 9)",
         image<float>(img4), "median_blur(img, 9)",
         image<float>(img5), "bilateral_blur(img, 9)");
}

int main()
{
    // Constructor and usage examples...
    image<uchar> a;
    // construct an empty image
    image<uchar> b(50, 30, 3);
    // construct a 3-channel 50 (width) x 30 (height) image
    b(10, 5, 1);

    // get channel 1, from row 10 and column 5
    // image derives from ivl::array_nd and can be treated as such.

    cout << "----- ivl::image sample -----" << endl;
    img_load_sample();
    img_flip_sample();
    img_grayscale_sample();
    img_resize_sample();
    img_wrappers_sample();
    cout << "image sample complete." << endl;
    return 0;
}

#endif
#endif
