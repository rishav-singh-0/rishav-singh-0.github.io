#!/bin/sh -x

rm -rf hugo_root/public/ hugo_root/static/images hugo_root/content/posts
uv run ./bin/script.py && hugo server -s hugo_root --environment production --disableFastRender --ignoreCache
