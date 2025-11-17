#!/bin/bash
g++ hyprlight.cpp -o hyprlight $(pkg-config --cflags --libs gtk+-3.0)

