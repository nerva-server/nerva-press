#!/bin/bash

mkdir -p bin

src=$(find src/ -type f | grep -E "[.]c(xx|pp)$")

g++ $src -I./include -o bin/nerva-press
