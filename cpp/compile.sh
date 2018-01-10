
g++  -o inference inference.cpp \
    -I $CAFFE_HOME/include/ \
    -D CPU_ONLY \
    -I $CAFFE_HOME/.build_release/src/ \
    -L $CAFFE_HOME/build/lib/ \
    -lcaffe \
    -lboost_system \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_core \
    -lglog
