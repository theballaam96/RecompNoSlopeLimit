#!/usr/bin/env bash
set -e
echo "Creating ./bin directory..."
mkdir -p ./bin

python to_dds.py

make

echo "Running RecompModTool..."
./RecompModTool ./mod.toml ./bin

echo "Zipping output file into ./bin..."
zip -j ./bin/no_slope_limit.zip ./bin/no_slope_limit.nrm

echo "Complete"