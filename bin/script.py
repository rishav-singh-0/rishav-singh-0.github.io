import json
import os
import re
import shutil
from pathlib import Path
import urllib.parse

try:
    import frontmatter
except ImportError:
    raise ImportError("Missing required module 'frontmatter'. Install it via pip: pip install python-frontmatter")

# Define paths
VAULT_DIR = Path("vault")
HUGO_ROOT = Path("hugo_root")
CONTENT_DIR = HUGO_ROOT / "content/posts"
STATIC_IMG_DIR = HUGO_ROOT / "static/images"
GRAPH_DATA_FILE = HUGO_ROOT / "static/data/graph.json"
IMG_EXTENSIONS = {".jpg", ".jpeg", ".png", ".webp", ".gif"}

# Global state for graph
nodes = []
edges = []


def slugify(text):
    text = text.strip().lower()
    # replace spaces and underscores with dashes
    text = re.sub(r'[\s_]+', '-', text)
    # remove any character that is not a letter, a number, a dash, or a slash
    text = re.sub(r'[^\w/-]', '', text)
    return text


def convert_links(text, current_note_title=None):
    # Convert Obsidian image embeds: ![[image.png]]
    text = re.sub(r'!\[\[([^\]]+?)\]\]', lambda m: f'{{{{< figure src="/images/{Path(m.group(1)).name}" alt="{Path(m.group(1)).stem}" >}}}}', text)

    # Fix markdown image paths: ![alt](assets/image.jpg)
    text = re.sub(
        r'!\[(.*?)\]\((?:\.?/)?assets/([^\)]+)\)',
        lambda m: f'{{{{< figure src="/images/{m.group(2)}" alt="{m.group(1)}" >}}}}',
        text
    )

    # Unified Obsidian link conversion
    def replace_link(match):
        full_match = match.group(1)
        parts = full_match.split('|')
        link_part = parts[0]
        alias_part = parts[1] if len(parts) > 1 else ''

        link_parts = link_part.split('#')
        path = link_parts[0]
        section = link_parts[1] if len(link_parts) > 1 else ''

        # Determine the display text
        file_name = Path(path).name
        if file_name.endswith('.md'):
            file_name = file_name[:-3]

        display_text = alias_part or (f"{file_name}#{section}" if section else file_name)
        ref_path = slugify(file_name)
        
        # For the graph, record the edge
        if current_note_title:
            edges.append({"source": current_note_title, "target": file_name})

        hugo_link = f'../{ref_path}/'
        if section:
            hugo_link += f'#{slugify(section)}'

        return f'[{display_text}]({hugo_link})'

    text = re.sub(r'\[\[([^\]]+?)\]\]', replace_link, text)
    return text


def process_related(related_list):
    new_related = []
    for entry in related_list:
        match = re.match(r'\[\[([^\]]+)\]\]', entry.strip())
        if match:
            slug = slugify(match.group(1))
            new_related.append(f"/{slug}/")
        else:
            new_related.append(entry)
    return new_related


def process_cover_image(cover_value):
    if not cover_value or isinstance(cover_value, dict):
        return cover_value
    
    cover_str = str(cover_value).strip()
    match = re.match(r'\[\[(.*?)\]\]', cover_str)
    if match:
        cover_str = match.group(1)
    
    filename = Path(cover_str).name
    return {"image": f"images/{filename}", "relative": False}


def process_note(original_file):
    try:
        with open(original_file, 'r', encoding='utf-8') as f:
            post = frontmatter.load(f)
    except Exception as e:
        print(f"Failed to read {original_file}: {e}")
        return
    
    title = original_file.stem.strip()
    # Get the relative path for folder-based grouping
    relative_path = str(original_file.parent.relative_to(VAULT_DIR))
    if relative_path == ".":
        relative_path = "root"

    post['title'] = title
    slug = slugify(title)
    url = f"/posts/{slug}/"

    # Add to graph nodes with path info
    nodes.append({
        "id": title, 
        "title": title, 
        "url": url, 
        "type": "page",
        "path": relative_path
    })

    # Record tags
    if 'tags' in post and isinstance(post['tags'], list):
        for tag in post['tags']:
            tag_id = f"tag:{tag}"
            nodes.append({
                "id": tag_id,
                "title": tag,
                "url": f"/tags/{slugify(tag)}/",
                "type": "tag"
            })
            edges.append({"source": title, "target": tag_id})

    post.content = convert_links(post.content, current_note_title=title)

    if 'related' in post and isinstance(post['related'], list):
        post['related'] = process_related(post['related'])
    
    if 'cover' in post:
        post['cover'] = process_cover_image(post['cover'])

    target_dir = CONTENT_DIR / slug
    target_dir.mkdir(parents=True, exist_ok=True)
    target_file = target_dir / "index.md"

    try:
        with open(target_file, 'w', encoding='utf-8') as f:
            f.write(frontmatter.dumps(post))
        print(f"Copied note: {original_file.relative_to(VAULT_DIR)}")
    except Exception as e:
        print(f"Failed to write {target_file}: {e}")


def copy_images():
    STATIC_IMG_DIR.mkdir(parents=True, exist_ok=True)
    for root, _, files in os.walk(VAULT_DIR):
        for file in files:
            if Path(file).suffix.lower() in IMG_EXTENSIONS:
                src = Path(root) / file
                dst = STATIC_IMG_DIR / file
                if not dst.exists():
                    try:
                        shutil.copy2(src, dst)
                        print(f"Copied image: {file}")
                    except Exception as e:
                        print(f"Failed to copy {file}: {e}")


def write_graph():
    # Deduplicate nodes
    unique_nodes = {node['id']: node for node in nodes}
    
    # Filter and deduplicate edges
    valid_edges = []
    seen_edges = set()
    for edge in edges:
        if edge['source'] in unique_nodes and edge['target'] in unique_nodes:
            edge_key = tuple(sorted([edge['source'], edge['target']]))
            if edge_key not in seen_edges:
                valid_edges.append({"source": edge_key[0], "target": edge_key[1]})
                seen_edges.add(edge_key)

    graph_data = {"nodes": list(unique_nodes.values()), "edges": valid_edges}
    
    GRAPH_DATA_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(GRAPH_DATA_FILE, 'w', encoding='utf-8') as f:
        json.dump(graph_data, f, indent=2)
    print(f"Wrote graph data to {GRAPH_DATA_FILE}")


def main():
    global nodes, edges
    nodes, edges = [], []

    # Clean content dir for a fresh start
    if CONTENT_DIR.exists():
        shutil.rmtree(CONTENT_DIR)
    CONTENT_DIR.mkdir(parents=True, exist_ok=True)

    for md_file in VAULT_DIR.rglob("*.md"):
        if ".obsidian" in str(md_file) or ".git" in str(md_file):
            continue
        process_note(md_file)

    copy_images()
    write_graph()


if __name__ == "__main__":
    main()
