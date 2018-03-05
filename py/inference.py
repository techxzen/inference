# @file  : inference.py
# @author: chencheng
# @date  : 20180305

import sys
import caffe
import cv2

def main():
    model_name = sys.argv[1]
    weight_name= sys.argv[2]
    image_name = sys.argv[3]

    net = caffe.Net(model_name, weight_name, caffe.TEST)

    print('\n--------- net created ---------')
    
    img_cv      = cv2.imread(image_name)
    img_resized = cv2.resize(img_cv, (224, 224))
    img         = img_resized.transpose((2, 0, 1))

    net.blobs['data'].data[...] = img
    
    net.forward()

    out = net.blobs['prob'].data
    
    out1000 = enumerate(out[0])
 
    sortedOut = sorted(out1000, key=lambda item:item[1], reverse=True)
    print('biggest 5: ')
    print(sortedOut[0:5])


if __name__ == "__main__":
    main()
