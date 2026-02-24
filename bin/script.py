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
IMG_EXTENSIONS = {".jpg", ".jpeg", ".png", ".webp", ".gif"}


def slugify(text):
    text = text.strip().lower()
    # replace spaces and underscores with dashes
    text = re.sub(r'[\s_]+', '-', text)
    # remove any character that is not a letter, a number, or a dash
    text = re.sub(r'[^\w-]', '', text)
    return text


def convert_links(text):
    # Convert Obsidian image embeds: ![[image.png]] -> {{< figure src="/images/image.png" alt="image" >}}
    text = re.sub(r'!\[\[([^\]]+?)\]\]', lambda m: f'{{{{< figure src="/images/{Path(m.group(1)).name}" alt="{Path(m.group(1)).stem}" >}}}}', text)

    # Fix markdown image paths like ![alt](assets/image.jpg) -> {{< figure src="/images/image.jpg" alt="alt" >}}
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
        if alias_part:
            display_text = alias_part
        elif section:
            display_text = f"{Path(path).name}#{section}"
        else:
            display_text = Path(path).name

        path_parts = path.split('/')
        file_name = path_parts[-1]
        
        ref_path = slugify(file_name)
        
        # Use relative links instead of ref
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


def process_note(original_file):
    try:
        with open(original_file, 'r', encoding='utf-8') as f:
            post = frontmatter.load(f)
    except Exception as e:
        print(f"Failed to read frontmatter from {original_file}: {e}")
        return
    
    if 'draft' not in post:
        return

    # Inject title from filename (without extension)
    post['title'] = original_file.stem.strip()

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
