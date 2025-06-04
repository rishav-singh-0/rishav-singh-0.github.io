#!/bin/bash -ex

# omh - https://github.com/ukautz/obsidian-meets-hugo

./bin/oe --recursive \
 --obsidian-root vault \
 --hugo-root hugo_root \
 --sub-path posts \
 --publish-field draft \
 --time-zone Asia/Kolkata
#  --include-tag Platform \

echo "Done!"
