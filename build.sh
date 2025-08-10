#!/bin/bash
src=$(find src/ -type f | grep -E "[.]c(xx|pp)$")

g++ $src -I./include
