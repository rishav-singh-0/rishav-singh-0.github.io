#!/bin/sh -x

export HUGO_ENVIRONMENT=production

rm -rf hugo_root/public/ hugo_root/static/images hugo_root/content/posts
uv run ./bin/script.py && hugo server -s hugo_root --environment $HUGO_ENVIRONMENT --disableFastRender --ignoreCache
