建置流程

sudo apt update
sudo apt install libcurl4-openssl-dev


mkdir build && cd build
cmake -DBUILD_DEMOS=OFF -DBUILD_TESTS=OFF -DDOWNLOAD_CERTS=OFF ..
make mqtt_mutual -j$(nproc)

Test with AWS IoT Core

curl -X POST https://xxxxxxxx.execute-api.ap-northeast-2.amazonaws.com/default/led -H "Content-Type: application/json" -d '{"state":"ON"}' // ON or OFF
