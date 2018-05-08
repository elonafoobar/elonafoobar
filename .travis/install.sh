#!/bin/bash
set -e

# Boost 1.66
ccache -V && ccache --show-stats && ccache --zero-stats
echo "using gcc : : ccache $CXX : <cflags>-std=c11 <cxxflags>-std=c++11 ;" > ~/user-config.jam
echo "using clang : : ccache $CXX : <cflags>-std=c11 <cxxflags>-std=c++11 ;" >> ~/user-config.jam
export BOOST_TOOLSET=gcc
cd "$BOOST_ROOT" && ./b2 toolset="$BOOST_TOOLSET" threading=multi --prefix="$BOOST_ROOT" -d0 install
export CMAKE_ARGS="$CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=/usr"


cd "$DOWNLOAD_ROOT"
export SDL2DIR=/usr

# SDL2
if [ ! -f "$DOWNLOAD_ROOT/SDL2-2.0.8" ]; then
    curl -L https://www.libsdl.org/release/SDL2-2.0.8.tar.gz | tar xz
fi
pushd SDL2-2.0.8
    ./configure --prefix=$SDL2DIR
    make
    sudo make install
popd

# SDL2_mixer
if [ ! -f "$DOWNLOAD_ROOT/SDL2_mixer-2.0.2" ]; then
    curl -L https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.2.tar.gz | tar xz
fi
pushd SDL2_mixer-2.0.2
    ./configure --prefix=$SDL2DIR
    make
    sudo make install
popd

# SDL2_ttf
if [ ! -f "$DOWNLOAD_ROOT/SDL2_ttf-2.0.14" ]; then
    curl -L https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz | tar xz
fi
pushd SDL2_ttf-2.0.14
    ./configure --prefix=$SDL2DIR
    make
    sudo make install
popd

# SDL2_image
if [ ! -f "$DOWNLOAD_ROOT/SDL2_image-2.0.3" ]; then
    curl -L https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz | tar xz
fi
pushd SDL2_image-2.0.3
    ./configure --prefix=$SDL2DIR
    make
    sudo make install
popd

