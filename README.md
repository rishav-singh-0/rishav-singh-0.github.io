# Rishav's Website

Personal website and digital garden built with Hugo.

Content includes notes, guides, and tutorials from hands-on work.

This repo contains pipeline that publishes a private Obsidian vault as a public website using Hugo as the SSG.

## Prerequisites

- hugo
- python
- uv

## Setup

Create a submodule of your actual repo as `vault`
```bash
git submodule command
```

- The notes which has "draft" property will be selected as posts and copied to new location in `hudo_root` directory.
- All the obsidian to hugo format conversion of contents will be done by the python file
- Hugo will convert pre-converted markdown files to html and generate static site
- You will have all the features of `PaperMod` theme of hugo and few additional obsidian features which i have added
    - Graph view (local and global)
    - Callouts

## Run locally

```bash
./bin/start.sh
```
