#!/bin/bash

echo Requesting the image-sample test-data from the svn repository...
mkdir -p img
svn co https://svn.image.ntua.gr/repos/smag/lib/branches/test-data/image-sample/img img

