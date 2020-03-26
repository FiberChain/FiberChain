# Create build dirs
mkdir build
mkdir out
cd build
# Build
cmake -DCMAKE_BUILD_TYPE=$BUILD_CONF ..
make -j$(nproc) all
# Copy binaries
cp ./programs/futurepiad/futurepiad ../out
cp ./programs/cli_wallet/cli_wallet ../out
cp ./programs/js_operation_serializer/js_operation_serializer ../out
