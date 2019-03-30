#!/bin/bash
cmake -DMODE=COMPILE -DCOMPILER_ID=GNU -DPACKAGE=$1 -P ../cmakeconfig_install/cmake-config.cmake

