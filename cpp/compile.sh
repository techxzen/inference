
g++  -o inference inference.cpp \
    -I $CAFFE_ROOT/include/ \
    -I $CAFFE_ROOT/build/include/ \
    -D CPU_ONLY \
    -L $CAFFE_ROOT/build/lib/ \
    -lcaffe \
    -lboost_system \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_core \
    -lglog
