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

**Theme switching:** PaperMod uses `[data-theme="dark"]` on `:root`. Custom overrides define the light palette in `:root` and the dark palette in `:root[data-theme="dark"]`.

---

## Custom Overlay Structure

### Layouts (hugo_root/layouts/)

| File | Purpose |
|------|---------|
| `home.html` | Custom homepage: hero, featured grid, topic chips, recent articles |
| `list.html` | List and taxonomy term pages with page-hero header + local graph |
| `graph.html` | Full knowledge graph visualization page |
| `taxonomy.html` | Taxonomy terms page |
| `archives.html` | Article archive with title, tag, and year filters |
| `search.html` | Redirects `/search/` to the archive, with a no-JavaScript fallback |
| `_markup/render-codeblock-mermaid.html` | Mermaid diagram rendering |
| `_markup/render-blockquote-alert.html` | Callout/alert boxes (15+ types) with foldable details |

Post pages use PaperMod's `layouts/single.html`. The overlay adds the local graph and Giscus through the hooks below; it does not copy the post template. Wikilinks are converted by `bin/script.py` before Hugo renders them.

### Partials (hugo_root/layouts/_partials/)

| File | Purpose |
|------|---------|
| `extend_post_content.html` | D3 local graph showing the current page + 2-depth neighbors; PaperMod post-content hook also called by `list.html` |
| `full-graph.html` | Full knowledge graph with search, settings panel, force sliders |
| `header.html` | Custom header override (theme toggle, nav) |
| `callout-icons.html` | SVG icons for callout types (note, tip, warning, danger, etc.) |
| `comments.html` | Giscus integration through PaperMod's comments hook; follows the site's theme |
| `extend_head.html` | Loads Mermaid.js from its CDN when the page contains a Mermaid code block |

### CSS (hugo_root/assets/css/extended/)

| File | Purpose |
|------|---------|
| `theme-override.css` | **Primary custom CSS**: dual-theme system (Coffee Light + Tokyo Night Dark), heading colors/spacing, cover image constraints, graph theming, Chroma code syntax colors |
| `graph.css` | Full graph explorer layout, controls, responsive styles, and colors |
| `home.css` | Homepage styling: hero, featured grid, topic chips, recent articles |
| `callouts.css` | Callout/alert styling with color schemes per type, foldable details |
| `page-hero.css` | Centered heading + subtitle + divider for list/taxonomy pages |
| `tags-bubbles.css` | Tag/taxonomy bubble styling |
| `archive.css` | Archive page layout styling |

Custom JavaScript stays inline in the homepage, archive, and graph/comment templates. The graph partials load D3.js v7 from its CDN.

### Static Data (hugo_root/static/data/)

| File | Purpose |
|------|---------|
| `graph.json` | Auto-generated node/edge data for graph visualizations |

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

Post content uses both `post-content` and PaperMod's `md-content` classes. Custom heading margins for `.post-content h1`–`h6` preserve the garden's spacing over PaperMod's defaults:
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
6. **Custom Homepage** — Hero section, featured articles grid, topic chips, recent articles list
7. **Smart Link Resolution** — Obsidian `[[wikilink#section]]` → correct Hugo URLs
8. **Dual Theme System** — Coffee Light (Primary-inspired warm) + Tokyo Night Dark with full Chroma syntax highlighting for both

---

## Configuration Highlights (hugo_root/hugo.toml)

```toml
baseURL = 'https://blog.rishavs.in/'
title = "Rishav's Digital Garden"
theme = 'PaperMod'
googleAnalytics = "G-NPJY8ZT1P0"

[params]
comments = true
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

[markup.highlight]
noClasses = false
```

---

## Build & Deployment Pipeline

1. **bin/script.py** — Obsidian vault → Hugo content:
   - Processes all `vault/**/*.md` files
   - Converts Obsidian wikilinks to Hugo links
   - Copies images to `hugo_root/static/images/`
   - Generates `hugo_root/static/data/graph.json`
   - Respects draft/production filtering

2. **bin/start.sh** — Removes generated `hugo_root/public/`, `hugo_root/static/images/`, and `hugo_root/content/posts/`, then rebuilds the content and starts Hugo in production mode. Only notes explicitly marked `draft: false` are exported in this mode.

3. **Deployment:** `.github/workflows/main.yml` checks out submodules at their recorded revisions, then updates only `vault` from its remote. PaperMod remains pinned to the reviewed submodule commit. The workflow builds with Hugo 0.147.2 and `--gc --minify`.

4. **Content Flow:** `vault/` → `bin/script.py` → `hugo_root/content/posts/` → Hugo build → `hugo_root/public/`

### Maintenance

- Prefer PaperMod's extension hooks and keep related custom behavior in the existing files.
- Validate theme changes with the deployment Hugo version. Keep `languageCode` until the deployment Hugo version supports `locale`; Hugo 0.147.2 ignores a `locale`-only setting.
- Compare representative local/live pages visually and functionally, including mobile portrait/landscape, zoom, scrolling, and relevant controls. Exclude the three generated paths removed by `bin/start.sh` from file comparisons.

---

## Content Pages

| Page | Layout | Purpose |
|------|--------|---------|
| `content/graph.md` | `graph` | Full knowledge graph explorer |
| `content/search.md` | `search` | Redirect to archive search; retain the existing frontmatter layout name |
| `content/archives.md` | `archives` | Article archive with title, tag, and year filters |
| `content/posts/` | auto-generated | Blog posts from Obsidian vault |

---

## Tag Rules

Tags containing `/` represent a **hierarchy** and must be split into multiple separate tags:

- A tag like `Platform/Buildroot` produces **2 tags**: `Platform` and `Buildroot`. The combined `Platform/Buildroot` is **never** treated as a single tag.
- If an article has tags `Platform/Buildroot` and `Platform/FileSystem`, the resulting individual tags are: `Platform`, `Buildroot`, `FileSystem`.
- The `/` denotes that the right-hand side is a subcategory of the left-hand side (e.g., `Buildroot` is a subcategory of `Platform`), but each part is also a standalone tag usable independently.
- Tag-specific pages (taxonomy term pages, tag listings) must reflect these split tags — each individual tag (`Platform`, `Buildroot`, `FileSystem`) should have its own page listing all articles that belong to it.
- Never render or link `Platform/Buildroot` as a single combined tag in the UI or in Hugo taxonomy configuration.

---

## Key Technology Stack

- **Static Site Generator:** Hugo
- **Theme:** PaperMod
- **Graph Visualization:** D3.js v7
- **Diagrams:** Mermaid.js (CDN)
- **Comments:** Giscus (GitHub Discussions)
- **Search:** Custom client-side archive filters. The retained `search` layout also causes PaperMod to include its Fuse.js bundle on the redirect page.
- **Content Authoring:** Obsidian
- **Build Pipeline:** Python (frontmatter, json, shutil)
- **Analytics:** Google Analytics 4 through PaperMod's call to Hugo's built-in analytics partial in production; no custom analytics override is needed.
