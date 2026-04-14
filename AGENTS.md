# Digital Garden - Hugo Site with PaperMod Theme

## Overview

This is **Rishav's Digital Garden** — a personal knowledge base / blog built with Hugo, using the PaperMod theme as a base, with significant custom overlays. Content is authored in an Obsidian vault and synced to Hugo via a Python build pipeline.

- **URL:** https://blog.rishavs.in/
- **Hugo Theme:** PaperMod (hugo_root/themes/PaperMod/)
- **Content Source:** Obsidian vault (vault/)
- **Build Pipeline:** `bin/start.sh` -> Python (`bin/script.py`) -> Hugo

---

## Base Theme: PaperMod

PaperMod provides:
- Responsive design with light/dark mode (CSS variable–driven, toggled via `data-theme` attribute on root)
- Single post, list, archive, search, and taxonomy layouts
- Social icons, share buttons, reading time, breadcrumbs, TOC
- OpenGraph, Twitter Cards, JSON-LD schema for SEO
- Client-side search (Fuse.js)
- 50+ i18n language files
- Code syntax highlighting (Chroma)

**Key CSS Variables** (used throughout the overlay):
`--primary`, `--secondary`, `--tertiary`, `--content`, `--entry`, `--border`, `--radius`, `--gap`, `--theme`, `--code-block-bg`, `--code-bg`

**Theme switching:** PaperMod uses `[data-theme="dark"]` on `:root`. Light mode is the default (no attribute). Custom overrides use `:root` for light and `:root[data-theme="dark"]` for dark.

---

## Custom Overlay Structure

### Layouts (hugo_root/layouts/)

| File | Purpose |
|------|---------|
| `index.html` | Custom homepage: hero, featured grid, topic chips, recent articles |
| `_default/single.html` | Post page with local graph + Giscus comments |
| `_default/list.html` | List pages with page-hero header + local graph partial |
| `_default/graph.html` | Full knowledge graph visualization page |
| `_default/terms.html` | Taxonomy terms page |
| `_default/archives.html` | Chronological post archive |
| `_default/search.html` | PaperMod search page |
| `_default/_markup/render-codeblock-mermaid.html` | Mermaid diagram rendering |
| `_default/_markup/render-blockquote-alert.html` | Callout/alert boxes (15+ types) with foldable details |
| `_default/_markup/render-link.html` | Obsidian-style `[[wikilink]]` → Hugo link resolver |
| `shortcodes/toy-network.html` | Interactive network visualization (vis-network.js) |

### Partials (hugo_root/layouts/partials/)

| File | Purpose |
|------|---------|
| `local-graph.html` | D3.js force-directed graph showing current page + 2-depth neighbors |
| `full-graph.html` | Full knowledge graph with search, settings panel, force sliders |
| `header.html` | Custom header override (theme toggle, nav) |
| `callout-icons.html` | SVG icons for callout types (note, tip, warning, danger, etc.) |
| `giscus.html` | GitHub Discussions comment system integration |
| `extend_head.html` | Mermaid.js CDN loader |

### CSS (hugo_root/assets/css/extended/)

| File | Purpose |
|------|---------|
| `theme-override.css` | **Primary custom CSS**: dual-theme system (Coffee Light + Tokyo Night Dark), heading colors/spacing, cover image constraints, graph theming, Chroma code syntax colors |
| `home.css` | Homepage styling: hero, featured grid, topic chips, recent articles |
| `callouts.css` | Callout/alert styling with color schemes per type, foldable details |
| `page-hero.css` | Centered heading + subtitle + divider for list/taxonomy pages |
| `tags-bubbles.css` | Tag/taxonomy bubble styling |
| `archive.css` | Archive page layout styling |

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

## Theming System

### Dual Theme: Coffee Light + Tokyo Night Dark

The site ships with two fully customized themes defined in `theme-override.css`:

**Coffee Light (default / light mode):**
- Inspired by the **Primary** Obsidian theme (Cecilia May) — warm, nostalgic, yellowing magazine pages
- Background: `#f5f0e8` (warm cream), cards: `#ede7db`, text: `#4a3728` (dark brown)
- Accent: `#9b4d3a` (warm red) for links, hover → `#c0563e`
- Heading colors: warm earthy rainbow — red `#8a3324`, amber `#8a6d2b`, olive `#4a7c3f`, teal `#2d6e6e`, navy `#2d5a8a`, plum `#6b3a6b`
- Code syntax: earthy tones matching the light palette

**Tokyo Night Dark (`data-theme="dark"`):**
- Background: `#1a1b26`, cards: `#24283b`, text: `#a9b1d6`
- Accent: `#7aa2f7` (blue), hover → `#7dcfff` (cyan)
- Heading colors: rainbow — red `#ff757f`, yellow `#e0af68`, green `#9ece6a`, cyan `#7dcfff`, blue `#7aa2f7`, magenta `#bb9af7`
- Code syntax: full Tokyo Night color mapping

### Heading Spacing

Custom heading margins for `.post-content h1`–`h6` (PaperMod's reset.css zeroes all heading margins; `.md-content` defines margins but `.post-content` used by posts does not):
- h1: `2.0em` top, h2: `1.8em`, h3: `1.5em`, h4: `1.3em`, h5: `1.2em`, h6: `1.1em`

### Cover Image Constraints

- List page: `max-height: 250px; object-fit: cover`
- Single page: `max-height: 360px; object-fit: cover`

---

## Custom Features Added Over PaperMod

1. **Knowledge Graph Visualization** — Two D3.js implementations:
   - Local graph (per-post, 2-depth neighbor view)
   - Full graph (global, with search/filter, settings panel, force sliders, color-by-folder)
2. **Obsidian Vault Integration** — Python pipeline (`bin/script.py`) converts Obsidian markdown to Hugo content, resolving wikilinks, extracting tags, generating graph data
3. **Callout System** — 15+ callout types (note, info, tip, warning, danger, bug, example, quote, etc.) rendered from blockquote syntax with foldable details support
4. **Mermaid Diagrams** — Code fence `mermaid` blocks auto-rendered via CDN
5. **Giscus Comments** — GitHub Discussions–based commenting on posts
6. **Interactive Network Shortcode** — vis-network.js for embedding node/edge visualizations
7. **Custom Homepage** — Hero section, featured articles grid, topic chips, recent articles list
8. **Smart Link Resolution** — Obsidian `[[wikilink#section]]` → correct Hugo URLs
9. **Dual Theme System** — Coffee Light (Primary-inspired warm) + Tokyo Night Dark with full Chroma syntax highlighting for both

---

## Configuration Highlights (hugo_root/hugo.toml)

```toml
baseURL = 'https://blog.rishavs.in/'
title = "Rishav's Digital Garden"
theme = 'PaperMod'
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

[outputs]
home = ["HTML", "RSS", "JSON"]

[markup.goldmark.renderer]
unsafe = true
```

---

## Build & Deployment Pipeline

1. **bin/script.py** — Obsidian vault → Hugo content:
   - Processes all `vault/**/*.md` files
   - Converts Obsidian wikilinks to Hugo links
   - Copies images to `hugo_root/static/images/`
   - Generates `hugo_root/static/data/graph.json`
   - Respects draft/production filtering

2. **bin/start.sh** — Local development server startup

3. **Content Flow:** `vault/` → `bin/script.py` → `hugo_root/content/posts/` → Hugo build → `hugo_root/public/`

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
