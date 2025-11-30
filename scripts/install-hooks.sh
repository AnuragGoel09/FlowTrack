#!/bin/sh
# Usage: ./install-hooks.sh /path/to/your/git/repo
REPO_PATH="$1"
if [ -z "$REPO_PATH" ]; then
  echo "Usage: $0 /path/to/git/repo"
  exit 1
fi

HOOK_DIR="$REPO_PATH/.git/hooks"
if [ ! -d "$HOOK_DIR" ]; then
  echo "Not a git repo: $REPO_PATH"
  exit 1
fi

cp "$(dirname "$0")/git-hook-post-commit" "$HOOK_DIR/post-commit"
chmod +x "$HOOK_DIR/post-commit"
echo "Installed post-commit hook into $HOOK_DIR"
