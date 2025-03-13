# VINE (Vim Notes Explorer)

A vim-motions tui tool for navigating and managing notes for classes, written in C.

Navigation uses a vim-like control scheme (hjkl for movement)

## UI Layout

2 screens

1. List of courses
2. List of documents

You select a course and it takes you to it's list of documents.

Keeps track of the current "working" document

Can move the working document to the archive (e.g., moving to a new unit in a course)

Can open archived and current note documents in glow or vim

## TODO

- [ ] Learn how to read the files in a directory
- [ ] Create a makefile
- [ ] Creating a tui from scratch
- [ ] Learn how to read a config file
- [ ] Create a config file
