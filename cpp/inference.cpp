//An Inference programming
//Author: chencheng
//Date:   20180108

#include<iostream>
#include<string>
#include<caffe/caffe.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>


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


    string model_file;
    string weight_file;
    string label_file;
    string image_file;


    //create Net
    Net<float>* net;
    net  = new Net<float>(model_file, caffe::TEST);
    
    //copy weight
    net -> CopyTrainedLayersFrom(weight_file);

    //get input blob
    Blob<float>* input_blob = net->input_blobs()[0];
    
    int num_channels;
    int num_width;
    int num_height;
    num_channels = input_blob->channels();
    num_width = input_blob->width();
    num_height = input_blob->height();
    
    input_blob->Reshape(1, num_channels, num_width, num_height);
    net->Reshape();

    

    
    float* input_data = input_blob->mutable_cpu_data();
    for(int i = 0; i < num_channels; i++)
    {
    }
    

    //read image file
    cv::Mat img = cv::imread(image_file, -1);
    
    

    //get output blob
    Blob<float>* output_blob = net->output_blobs()[0];
    

    
    
    

    cout << "inference complete!" <<endl;
    return 0; 
}
