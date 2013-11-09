#!/usr/bin/env python
import os
import subprocess

make_cmd = 'cmake -DCMAKE_BUILD_TYPE=debug -DCMAKE_INSTALL_PREFIX=../ ../'
subprocess.Popen(make_cmd,shell=True).wait()
