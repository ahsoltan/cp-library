import subprocess, re, sys

assert(len(sys.argv) == 4)
path = sys.argv[1]
lang = sys.argv[2]
out = sys.argv[3]

if lang == "C++":
  src = subprocess.run(["clang-format", path], stdout=subprocess.PIPE).stdout.decode()
else:
  with open(path) as f:
    src = f.read()
src = re.sub(r'(for|while|if|else|else if)(.*){ (.*;)\s*}', r'\1\2\3', src)

with open(out, "w") as f:
  f.write(f"\\begin{{lstlisting}}[language={lang}]\n{src.rstrip()}\n\\end{{lstlisting}}")
