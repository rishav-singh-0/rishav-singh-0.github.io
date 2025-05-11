import os
import re
import shutil
from pathlib import Path

try:
    import frontmatter
except ImportError:
    raise ImportError("Missing required module 'frontmatter'. Install it via pip: pip install python-frontmatter")

# Define paths
VAULT_DIR = Path("vault")
HUGO_ROOT = Path("hugo_root")
CONTENT_DIR = HUGO_ROOT / "content/posts"
STATIC_IMG_DIR = HUGO_ROOT / "static/images"
IMG_EXTENSIONS = {".jpg", ".jpeg", ".png", ".webp", ".gif"}


def slugify(text):
    return re.sub(r'[\s_]+', '-', text.strip().lower())


def convert_links(text):
    # Convert Obsidian image embeds: ![[image.png]] -> ![image](./image.png)
    text = re.sub(r'!\[\[([^\]]+?)\]\]', lambda m: f"![{Path(m.group(1)).stem}](./{Path(m.group(1)).name})", text)

    # Convert Obsidian links with alias: [[Note|Text]] -> [Text](../note/index.md)
    text = re.sub(r'\[\[([^|\]#]+)\|([^\]]+)\]\]', lambda m: f"[{m.group(2)}](../" + slugify(m.group(1)) + "/index.md)", text)

    # Convert Obsidian section links: [[Note#Section]] -> [Note - Section](../note/index.md#section)
    text = re.sub(r'\[\[([^\]#]+)#([^\]]+)\]\]', lambda m: f"[{m.group(1)} - {m.group(2)}](../" + slugify(m.group(1)) + "/index.md#" + slugify(m.group(2)) + ")", text)

    # Convert simple Obsidian links: [[Note]] -> [Note](../note/index.md)
    text = re.sub(r'\[\[([^\]]+?)\]\]', lambda m: f"[{m.group(1)}](../" + slugify(m.group(1)) + "/index.md)", text)

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


def process_note(original_file):
    try:
        with open(original_file, 'r', encoding='utf-8') as f:
            post = frontmatter.load(f)
    except Exception as e:
        print(f"Failed to read frontmatter from {original_file}: {e}")
        return

    post.content = convert_links(post.content)

    if 'related' in post and isinstance(post['related'], list):
        post['related'] = process_related(post['related'])

    slug = slugify(original_file.stem)
    target_dir = CONTENT_DIR / slug
    target_dir.mkdir(parents=True, exist_ok=True)
    target_file = target_dir / "index.md"

    try:
        with open(target_file, 'w', encoding='utf-8') as f:
            f.write(frontmatter.dumps(post))
        print(f"Copied note: {original_file.relative_to(VAULT_DIR)}")
    except Exception as e:
        print(f"Failed to write file {target_file}: {e}")


def copy_images():
    STATIC_IMG_DIR.mkdir(parents=True, exist_ok=True)
    for root, _, files in os.walk(VAULT_DIR):
        for file in files:
            if Path(file).suffix.lower() in IMG_EXTENSIONS:
                src = Path(root) / file
                dst = STATIC_IMG_DIR / file
                try:
                    if not dst.exists():
                        shutil.copy2(src, dst)
                        print(f"Copied image: {file}")
                except Exception as e:
                    print(f"Failed to copy image {file}: {e}")


def main():
    for md_file in VAULT_DIR.rglob("*.md"):
        process_note(md_file)

    copy_images()


if __name__ == "__main__":
    main()
