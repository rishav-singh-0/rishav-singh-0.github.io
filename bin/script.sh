#!/bin/bash

# omh - https://github.com/ukautz/obsidian-meets-hugo

./bin/omh.linux-amd64 --recursive \
 --obsidian-root vault \
 --hugo-root hugo_root \
 --sub-path posts \
 --time-zone Asia/Kolkata
#  --include-tag Platform \

echo "Done!"
