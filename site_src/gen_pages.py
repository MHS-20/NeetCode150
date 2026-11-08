"""Builds the site's pages from the repository at `mkdocs build` time.

Markdown files keep their repository paths, so relative links between them
keep working. Every problem folder gets a page with its README (if any) and
one tab per solution file. SUMMARY.md defines the navigation.
"""
import re
from pathlib import Path

import mkdocs_gen_files

ROOT = Path(__file__).resolve().parent.parent
LANGS = {  # folder or extension -> (tab label, highlight.js language)
    "c": ("C", "c"), "cpp": ("C++", "cpp"), "go": ("Go", "go"), "java": ("Java", "java"),
    "javascript": ("JavaScript", "javascript"), "js": ("JavaScript", "javascript"),
    "python": ("Python", "python"), "py": ("Python", "python"),
    "rust": ("Rust", "rust"), "rs": ("Rust", "rust"), "sql": ("SQL", "sql"),
}
CODE_EXT = {".c", ".h", ".cpp", ".hpp", ".go", ".java", ".js", ".py", ".rs", ".sql"}
nav = []


def fix_dir_links(text, src):
    """Points links to folders at the folder's README, or its first page if it has none."""
    def repl(m):
        target = (src.parent / m.group(1)).resolve()
        if not target.is_dir():
            return m.group(0)
        page = target / "README.md"
        if not page.exists():
            pages = sorted(target.glob("*.md"), key=lambda p: leading_number(p.name))
            if not pages:
                return m.group(0)
            page = pages[0]
        return f"]({m.group(1).rstrip('/')}/{page.name})"
    return re.sub(r"\]\(([^)#:]+/)\)", repl, text)


def write(path, text):
    with mkdocs_gen_files.open(path, "w") as f:
        f.write(text)


def title_of(md):
    for line in md.read_text().splitlines():
        if line.startswith("# "):
            return line[2:].strip()
    return md.stem


def leading_number(name):
    m = re.match(r"\d+", name)
    return (int(m.group()) if m else 10**9, name)


def pretty(folder):
    words = re.sub(r"^\d+_", "", folder).replace("_", " ")
    words = words[:1].upper() + words[1:]
    return re.sub(r"\bSql\b", "SQL", words)


def code_files(problem):
    """(tab label, language, file) for every source file in the folder or its language subfolders."""
    found = []
    for f in sorted(problem.rglob("*")):
        if f.suffix not in CODE_EXT or "__pycache__" in f.parts:
            continue
        sub = f.relative_to(problem).parts
        lang = LANGS.get(sub[0]) if len(sub) > 1 else None
        label, hl = lang or LANGS.get(f.suffix[1:], (f.suffix[1:], f.suffix[1:]))
        found.append((label, hl, f))
    counts = {}
    for lbl, _, _ in found:
        counts[lbl] = counts.get(lbl, 0) + 1
    return [((f"{lbl}: {f.name}" if counts[lbl] > 1 else lbl), hl, f) for lbl, hl, f in found]


def problem_page(problem, heading):
    readme = problem / "README.md"
    text = fix_dir_links(readme.read_text(), readme).rstrip() + "\n\n" if readme.exists() else f"# {heading}\n\n"
    files = code_files(problem)
    if files:
        text += "## Solutions\n\n" if readme.exists() else ""
        for label, hl, f in files:
            code = f.read_text().rstrip("\n")
            fence = "~~~~" if "~~~" in code else "~~~"
            body = "\n".join("    " + line if line else "" for line in code.split("\n"))
            text += f'=== "{label}"\n\n    {fence}{hl}\n{body}\n    {fence}\n\n'
    path = f"{problem.relative_to(ROOT)}/README.md"
    write(path, text)
    return path


def copy_md(rel):
    write(rel, fix_dir_links((ROOT / rel).read_text(), ROOT / rel))


# home
write("index.md", fix_dir_links((ROOT / "README.md").read_text(), ROOT / "README.md"))
nav.append("* [Home](index.md)")

# lessons
nav.append("* Lessons")
for folder in sorted((ROOT / "00_docs").iterdir()):
    if not folder.is_dir():
        continue
    nav.append(f"    * {pretty(folder.name)}")
    for md in sorted(folder.glob("*.md"), key=lambda p: leading_number(p.name)):
        rel = str(md.relative_to(ROOT))
        copy_md(rel)
        nav.append(f"        * [{title_of(md)}]({rel})")

# LeetCode problems by topic
nav.append("* Problems")
for topic in sorted(p for p in ROOT.iterdir() if p.is_dir() and re.match(r"(0[1-9]|1[0-8])_", p.name)):
    nav.append(f"    * {pretty(topic.name)}")
    for problem in sorted((p for p in topic.iterdir() if p.is_dir()), key=lambda p: leading_number(p.name)):
        num = leading_number(problem.name)[0]
        heading = f"{num}. {pretty(problem.name)}"
        nav.append(f"        * [{heading}]({problem_page(problem, heading)})")

# SQL problems
copy_md("19_sql/README.md")
nav.append("* SQL problems")
nav.append("    * [Overview](19_sql/README.md)")
for problem in sorted((p for p in (ROOT / "19_sql").iterdir() if p.is_dir()), key=lambda p: leading_number(p.name)):
    nav.append(f"    * [{title_of(problem / 'README.md')}]({problem_page(problem, problem.name)})")

# practical exercises
nav.append("* Practical")
copy_md("20_practical/README.md")
nav.append("    * [Overview](20_practical/README.md)")
for group in sorted(p for p in (ROOT / "20_practical").iterdir() if p.is_dir()):
    nav.append(f"    * {pretty(group.name)}")
    if (group / "README.md").exists():
        copy_md(str((group / "README.md").relative_to(ROOT)))
        nav.append(f"        * [Overview]({(group / 'README.md').relative_to(ROOT)})")
    for ex in sorted(p for p in group.iterdir() if p.is_dir()):
        nav.append(f"        * [{title_of(ex / 'README.md')}]({problem_page(ex, ex.name)})")

# HackerRank
nav.append("* HackerRank")
copy_md("hackerrank/README.md")
nav.append("    * [Overview](hackerrank/README.md)")
for problem in sorted(p for p in (ROOT / "hackerrank").iterdir() if p.is_dir()):
    nav.append(f"    * [{title_of(problem / 'README.md')}]({problem_page(problem, problem.name)})")

write("SUMMARY.md", "\n".join(nav) + "\n")
