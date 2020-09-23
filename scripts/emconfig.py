#!/usr/bin/env python3
 
import os

if not os.path.exists("build/debug-emscripten"):
  os.makedirs("build/debug-emscripten")
os.chdir("build/debug-emscripten")
os.system("emcmake cmake ../..")
