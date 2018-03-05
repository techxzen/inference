# @file  : inference.py
# @author: chencheng
# @date  : 20180305

import sys
import caffe

def main():
    model_name = sys.argv[1]
    weight_name= sys.argv[2]
    image_name = sys.argv[3]

    net = caffe.Net(model_name, weight_name, caffe.TEST)
    
    img_cv      = cv2.imread(image_name)
    img_resized = cv2.resize(img_cv, (224, 224))
    img         = img_resized.transpose((2, 0, 1))

    net.blobs['data'].data[...] = img
    
    net.forward()

    out = net.blobs['prob'].data

    sortedOut = sorted(out.tolist(), reverse=True)

    print(sortedOut[0])



if __name__ == "__main__":
    main()
