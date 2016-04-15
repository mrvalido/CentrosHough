//
//#include<iostream>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/highgui/highgui.hpp>
//
//using namespace std;
//using namespace cv;
//
//
///*float filterGaussian(valarray<unsigned char> im, int x, int y, int dimX){
//	return (   (im[(y-1)*dimX + (x-1)]) + 2*(im[(y-1)*dimX + (x)]) +   (im[(y-1)*dimX + (x+1)]) +
//			 2*(im[(y)*dimX + (x-1)]) + 4*(im[(y)*dimX + (x)]) + 2*(im[(y)*dimX + (x+1)]) +
//			   (im[(y+1)*dimX + (x-1)]) + 2*(im[(y+1)*dimX + (x)]) +   (im[(y+1)*dimX + (x+1)])
//		   )/16;
//}
//}*/
//
//int dd()
//{
//
//      Mat src, dst;
//      float sum;
//
//      /// Load an image
//      src = imread("salt.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//
//      if( !src.data )
//      { return -1; }
//
//      // define the kernel
//      float Kernel[3][3] = {
//                            {1/9.0, 1/9.0, 1/9.0},
//                            {1/9.0, 1/9.0, 1/9.0},
//                            {1/9.0, 1/9.0, 1/9.0}
//                           };
//         dst = src.clone();
//
//
//        for(int y = 0; y < src.rows; y++)
//            for(int x = 0; x < src.cols; x++)
//                dst.at<uchar>(y,x) = 0.0;
// valarray<double> median_filter(ImageValInt val,float Kernel[][]);
//        //convolution operation
//        for(int y = 1; y < src.rows - 1; y++){
//            for(int x = 1; x < src.cols - 1; x++){
//                sum = 0.0;
//                for(int k = -1; k <= 1;k++){
//                    for(int j = -1; j <=1; j++){
//                        sum = sum + Kernel[j+1][k+1]*src.at<uchar>(y - j, x - k);
//                    }
//                }
//                dst.at<uchar>(y,x) = sum;
//            }
//        }
//
//        namedWindow("final");
//        imshow("final", dst);
//
//        namedWindow("initial");
//        imshow("initial", src);
//
//      waitKey();
//
//
//    return 0;
//}

//
//#include<iostream>
//#include<cmath>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/highgui/highgui.hpp>
//
//using namespace std;
//using namespace cv;
//
//
//// Computes the x component of the gradient vector
//// at a given point in a image.
//// returns gradient in the x direction
//int xGradient(Mat image, int x, int y)
//{
//    return image.at<uchar>(y-1, x-1) +
//                2*image.at<uchar>(y, x-1) +
//                 image.at<uchar>(y+1, x-1) -
//                  image.at<uchar>(y-1, x+1) -
//                   2*image.at<uchar>(y, x+1) -
//                    image.at<uchar>(y+1, x+1);
//}
//
//// Computes the y component of the gradient vector
//// at a given point in a image
//// returns gradient in the y direction
//
//double yGradient(const valarray<double> image, int x, int y)
//{

 // tmp[ind(y,x)] = sum;
//    return image.at<uchar>(y-1, x-1) +
//                2*image.at<uchar>(y-1, x) +
//                 image.at<uchar>(y-1, x+1) -
//                  image.at<uchar>(y+1, x-1) -
//                   2*image.at<uchar>(y+1, x) -
//                    image.at<uchar>(y+1, x+1);
//}
//
//int main()
//{
//
//      Mat src, dst;
//      int gx, gy, sum;
//
//      // Load an image
//      src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//      dst = src.clone();
//      if( !src.data )
//      { return -1; }
//
//
//        for(int y = 0; y < src.rows; y++)
//            for(int x = 0; x < src.cols; x++)
//                dst.at<uchar>(y,x) = 0.0;
//
//        for(int y = 1; y < src.rows - 1; y++){
//            for(int x = 1; x < src.cols - 1; x++){
//                gx = xGradient(src, x, y);
//                gy = yGradient(src, x, y);
//                sum = abs(gx) + abs(gy);
//                sum = sum > 255 ? 255:sum;
//                sum = sum < 0 ? 0 : sum;
//                dst.at<uchar>(y,x) = sum;
//            }
//        }
//
//        namedWindow("final");
//        imshow("final", dst);
//
//        namedWindow("initial");
//        imshow("initial", src);
//
//      waitKey();
//
//
//    return 0;
//}

