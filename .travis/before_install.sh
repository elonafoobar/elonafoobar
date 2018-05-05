#!/bin/bash

export CXX="g++-4.8" CC="gcc-4.8" BOOST_TOOLSET=gcc
export DOWNLOAD_ROOT="$HOME/download"; if [ ! -d "$DOWNLOAD_ROOT" ]; then mkdir -p "$DOWNLOAD_ROOT"; fi
export BOOST_DOWNLOAD_URL="https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz"
export BOOST_ROOT="$TRAVIS_BUILD_DIR/../boost"
export CMAKE_MODULE_PATH="$CMAKE_MODULE_PATH;$BOOST_ROOT"
if [ ! -f "$DOWNLOAD_ROOT/boost_1_66_0.tar.gz" ]; then wget --no-verbose --output-document="$DOWNLOAD_ROOT/boost_1_66_0.tar.gz" "$BOOST_DOWNLOAD_URL"; fi
if [ ! -d "$BOOST_ROOT" ]; then mkdir -p "$BOOST_ROOT" && tar xzf "$DOWNLOAD_ROOT/boost_1_66_0.tar.gz" --strip-components=1 -C "$BOOST_ROOT"; fi
if [ ! -f "$BOOST_ROOT/b2" ]; then cd "$BOOST_ROOT"; ./bootstrap.sh --with-toolset="$BOOST_TOOLSET" --with-libraries=system,filesystem,locale,iostreams; fi
