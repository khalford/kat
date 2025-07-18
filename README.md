# kat
A command line utility tool that combines features of common linux commands such as: cat, grep and wc.
> **NOTE:** This is a learning and development project and is not intended to be used or actively maintained.

Written in C++ this tool is designed to provide simple file viewing without needing to pipe your output to many different commands.

**Example:**
```shell
# Finding all lines in a file with the phrase "yellow banana" and their line number

# With linux commands
cat sample.txt | grep -i "yellow banana" | wc -l

# With kat
kat sample.txt -c -f="yellow banana"
```

