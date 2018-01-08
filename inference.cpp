//A Inference programming
//Author: chencheng
//Date:   20180108

#include<iostream>
#include<caffe/caffe.hpp>

using namespace std;
using namespace caffe;

//usage: inference model.prototxt model.caffemodel label.txt image.jpg

int main(int argc, char **argv)
{
    if(5 != argc)
    {
        cerr << "Usage: " << argv[0]
              << " deploy.prototxt network.caffemodel"
              << " mean.binaryproto labels.txt img.jpg" << std::endl;
        return 1;
    }


    //create Net
    Net<float>* net;
    
    

    cout << "inference complete!" <<endl;
    return 0; 
}
