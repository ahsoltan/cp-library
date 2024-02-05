import subprocess, re, sys

path = sys.argv[1]
lang = sys.argv[2]

if lang == "C++":
  src = subprocess.run(["clang-format", path], stdout=subprocess.PIPE).stdout.decode()
else:
  with open(path) as f:
    src = f.read()
src = re.sub(r'(for|while|if|else|else if)(.*){ (.*;)\s*}', r'\1\2\3', src)

print(f"\\begin{{lstlisting}}[language={lang}]\n{src.rstrip()}\n\\end{{lstlisting}}")
