~/binder_bin/bin/binder --root-module lidar --prefix ~/bindings/ --bind unitree_lidar_sdk \
  ./binder.hpp -- -std=c++11 ./include/ -I./lib/x86_64/