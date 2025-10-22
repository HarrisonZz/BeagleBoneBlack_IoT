建置流程

sudo apt update
sudo apt install libcurl4-openssl-dev


mkdir build && cd build
cmake -DBUILD_DEMOS=OFF -DBUILD_TESTS=OFF -DDOWNLOAD_CERTS=OFF ..
make mqtt_mutual -j$(nproc)