# Introduction

Here lies some of my favourite books, important enough for some VCS. They are managed by [git lfs](https://git-lfs.com/) since most of the books sizes exceed 100mb.

To get started or add a new book:

1. Ensure you have `git lfs` installed on your system. This is not the same as basic `git`!

2. Navigate to the directory youd like to track with `git lfs`, then run:
```bash
    git lfs track "*.pdf"
    git lfs track ".epub"
```

3. Now use normal git to track the files:
```bash
    git add .gitattributes
    git add books/
    git commit -m "Add the books"
    git push origin main
```
