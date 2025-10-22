建置流程

mkdir build && cd build
cmake -DBUILD_DEMOS=OFF -DBUILD_TESTS=OFF -DDOWNLOAD_CERTS=OFF ..
make -j$(nproc)