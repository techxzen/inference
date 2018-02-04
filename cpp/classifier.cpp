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

//usage: classifer model.prototxt model.caffemodel label.txt image.jpg

int main(int argc, char **argv)
{
    /*
    if(6 != argc)
    {
        cerr << "Usage: " << argv[0]
              << " deploy.prototxt network.caffemodel"
              << " mean.binaryproto labels.txt img.jpg" << std::endl;
        return 1;
    }
    */
    if(4 != argc)
    {
        cerr << "Usage: " << argv[0]
              << " deploy.prototxt network.caffemodel"
              << " img.jpg" << std::endl;
        return 1;
    }


    string model_file;
    string weight_file;
    string label_file;
    string image_file;

    /* get the argument viriables */
    model_file = argv[1];
    weight_file = argv[2];
    image_file = argv[3];

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
    
    printf("chencheng: the input dim: %d, %d, %d\n",
                                       num_channels, num_width, num_height
                                            );

    input_blob->Reshape(1, num_channels, num_width, num_height);
    net->Reshape();

    

    
    float* input_data = input_blob->mutable_cpu_data();
    

    //read image file
    cv::Mat img = cv::imread(image_file);
    
    /* Convert the input image to the input image format of the network. */
    cv::Mat sample;
    if (img.channels() == 3 && num_channels == 1)
        cv::cvtColor(img, sample, cv::COLOR_BGR2GRAY);
    else if (img.channels() == 4 && num_channels == 1)
        cv::cvtColor(img, sample, cv::COLOR_BGRA2GRAY);
    else if (img.channels() == 4 && num_channels == 3)
        cv::cvtColor(img, sample, cv::COLOR_BGRA2BGR);
    else if (img.channels() == 1 && num_channels == 3)
        cv::cvtColor(img, sample, cv::COLOR_GRAY2BGR);
    else
        sample = img;

    /* image resize */
    cv::Mat sample_resized;
    if(sample.size() != cv::Size(num_width, num_height))
    {
        cv::resize(sample, sample_resized, cv::Size(num_width, num_height));
    }
    else
    {
        sample_resized = sample;
    }


    /* convertTO float */
    cv::Mat sample_float;
    if(num_channels == 3)
    {
        sample_resized.convertTo(sample_float, CV_32FC3);
    }
    else
    {
        sample_resized.convertTo(sample_float, CV_32FC1);
    }

    
    /* normalized */
    //cv::Mat sample_normalized;
    //cv::Mat mean_;
    //cv::substract(sample_float, mean_, sample_normalized);
    

    /* initialze the input blob*/
    printf("chencheng: begin to initialize data\n");
    cv::Mat sample_input;
    sample_input = sample_float;
    
    float value = sample_input.at<float>(0, 0, 0);
    printf("chencheng: end\n");

    for(int row = 0; row < num_width; row++)
    {
        for(int col = 0; col < num_height; col++)
        {
            for(int ch = 0; ch < num_channels; ch++)
            {     
                int offset = ch * num_width * num_height + 
                             row * num_height +
                             col;
                input_data[offset] = sample_input.ptr<float>(row, col)[ch];
            }
        }
    }

    
    /* run the net */
    net->Forward(); 
    

    //get output blob
    Blob<float>* output_blob = net->output_blobs()[0];
    

    float* output_data = output_blob->mutable_cpu_data();
    float maxProb = 0.0f;
    int indexProb = 0;    
    for(int i = 0; i< 1000; i++)
    {
        if( output_data[i] > maxProb )
        {
            maxProb = output_data[i];
            indexProb = i;
        }
    }

    printf("\nmaxProb: %.4f, index: %d\n", maxProb, indexProb);
    
    cout << "inference complete!" <<endl;
    return 0; 
}
