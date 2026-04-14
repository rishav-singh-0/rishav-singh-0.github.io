# Digital Garden - Hugo Site with PaperMod Theme

## Overview

This is **Rishav's Digital Garden** — a personal knowledge base / blog built with Hugo, using the PaperMod theme as a base, with significant custom overlays. Content is authored in an Obsidian vault and synced to Hugo via a Python build pipeline.

- **URL:** https://blog.rishavs.in/
- **Hugo Theme:** PaperMod (hugo_root/themes/PaperMod/)
- **Content Source:** Obsidian vault (vault/)
- **Build Pipeline:** `` -> Python (main.py) -> Hugo

---

## Base Theme: PaperMod

PaperMod provides:
- Responsive design with light/dark mode (CSS variable–driven)
- Single post, list, archive, search, and taxonomy layouts
- Social icons, share buttons, reading time, breadcrumbs, TOC
- OpenGraph, Twitter Cards, JSON-LD schema for SEO
- Client-side search (Fuse.js)
- 50+ i18n language files
- Code syntax highlighting (Chroma)

**Key CSS Variables** (used throughout the overlay):
`--primary`, `--secondary`, `--tertiary`, `--content`, `--entry`, `--border`, `--radius`, `--gap`, `--theme`

---

## Custom Overlay Structure

### Layouts (hugo_root/layouts/)

| File | Purpose |
|------|---------|
| `index.html` | Custom homepage: hero, featured grid, topic chips, recent articles |
| `_default/single.html` | Post page with local graph + Giscus comments |
| `_default/list.html` | List pages with local graph partial |
| `_default/graph.html` | Full knowledge graph visualization page |
| `_default/_markup/render-codeblock-mermaid.html` | Mermaid diagram rendering |
| `_default/_markup/render-blockquote-alert.html` | Callout/alert boxes (15+ types) with foldable details |
| `_default/_markup/render-link.html` | Obsidian-style `[[wikilink]]` → Hugo link resolver |
| `shortcodes/toy-network.html` | Interactive network visualization (vis-network.js) |

### Partials (hugo_root/layouts/partials/)

| File | Purpose |
|------|---------|
| `local-graph.html` | D3.js force-directed graph showing current page + 2-depth neighbors |
| `full-graph.html` | Full knowledge graph with search, settings panel, force sliders |
| `callout-icons.html` | SVG icons for callout types (note, tip, warning, danger, etc.) |
| `giscus.html` | GitHub Discussions comment system integration |
| `extend_head.html` | Mermaid.js CDN loader |

### CSS (hugo_root/assets/css/extended/)

| File | Purpose |
|------|---------|
| `home.css` | Homepage styling: hero, featured grid, topic chips, recent articles |
| `callouts.css` | Callout/alert styling with color schemes per type, foldable details |

### JavaScript (hugo_root/static/js/)

| File | Purpose |
|------|---------|
| `toy-network.js` | vis-network.js integration for network shortcode |
| `vis-network.min.js` | Bundled vis-network library |

### Static Data (hugo_root/static/data/)

| File | Purpose |
|------|---------|
| `graph.json` | Auto-generated node/edge data for graph visualizations |
| `toy-network/nodes.json` | Network demo node data |
| `toy-network/edges.json` | Network demo edge data |

---

## Custom Features Added Over PaperMod

1. **Knowledge Graph Visualization** — Two D3.js implementations:
   - Local graph (per-post, 2-depth neighbor view)
   - Full graph (global, with search/filter, settings panel, force sliders, color-by-folder)
2. **Obsidian Vault Integration** — Python pipeline (main.py) converts Obsidian markdown to Hugo content, resolving wikilinks, extracting tags, generating graph data
3. **Callout System** — 15+ callout types (note, info, tip, warning, danger, bug, example, quote, etc.) rendered from blockquote syntax with foldable details support
4. **Mermaid Diagrams** — Code fence `mermaid` blocks auto-rendered via CDN
5. **Giscus Comments** — GitHub Discussions–based commenting on posts
6. **Interactive Network Shortcode** — vis-network.js for embedding node/edge visualizations
7. **Custom Homepage** — Hero section, featured articles grid, topic chips, recent articles list
8. **Smart Link Resolution** — Obsidian `[[wikilink#section]]` → correct Hugo URLs

---

## Configuration Highlights (hugo_root/hugo.toml)

```toml
title = "Rishav's Digital Garden"
theme = "PaperMod"
googleAnalytics = "G-NPJY8ZT1P0"

[params]
featuredLimit = 4
recentLimit = 6
selectedTags = ["Programming", "Embedded", "Linux", "Personal"]
ShowReadingTime = true
ShowPostNavLinks = true
ShowCodeCopyButtons = true

[params.homeInfoParams]
Title = "Welcome to My Digital Garden"
# Subtitle: Developer / Tinkerer

[outputs]
home = ["HTML", "RSS", "JSON"]

[markup.goldmark.renderer]
unsafe = true
```

---

## Build & Deployment Pipeline

1. **main.py** — Obsidian vault → Hugo content:
   - Processes all `vault/**/*.md` files
   - Converts Obsidian wikilinks to Hugo links
   - Copies images to `hugo_root/static/images/`
   - Generates `hugo_root/static/data/graph.json`
   - Respects draft/production filtering

2. **bin/start.sh** — Local development server startup

3. **Content Flow:** `vault/` → `main.py` → `hugo_root/content/posts/` → Hugo build → `hugo_root/public/`

---

## Content Pages

| Page | Layout | Purpose |
|------|--------|---------|
| `content/graph.md` | `graph` | Full knowledge graph explorer |
| `content/toy-network.md` | default | Network visualization demo |
| `content/search.md` | `search` | PaperMod built-in search |
| `content/archives.md` | `archives` | Chronological post archive |
| `content/posts/` | auto-generated | Blog posts from Obsidian vault |

---

## Key Technology Stack

- **Static Site Generator:** Hugo
- **Theme:** PaperMod
- **Graph Visualization:** D3.js v7
- **Network Visualization:** vis-network.js
- **Diagrams:** Mermaid.js (CDN)
- **Comments:** Giscus (GitHub Discussions)
- **Search:** Fuse.js (client-side)
- **Content Authoring:** Obsidian
- **Build Pipeline:** Python (frontmatter, json, shutil)
- **Analytics:** Google Tag Manager
