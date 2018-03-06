#! /bin/sh
python inference.py ../../models/VGG_ILSVRC_16_layers_deploy.prototxt \
                    ../../models/VGG_ILSVRC_16_layers.caffemodel \
                    ../image/cat.jpg
