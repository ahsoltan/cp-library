import subprocess, re

tex = ""

def code_block(title, src, desc, lang):
  res = f"{{\\large {title}}}\n"
  for key, val in desc.items():
    res += f"{{\\par\\noindent\\footnotesize{{\\textbf{{{key}:}} {val}\\par}}}}\n"
  res += "\\smallskip\n\\hrule\n"
  res += f"\\begin{{lstlisting}}[language={lang}]\n{src}\n\\end{{lstlisting}}"
  return res

def code_file(title, path, desc, lang):
  if lang == "C++":
    src = subprocess.run(["clang-format", path], stdout=subprocess.PIPE).stdout.decode()
  else:
    with open(path) as f:
      src = f.read()
  src = re.sub(r'(for|while|if|else|else if)(.*){ (.*;)\s*}', r'\1\2\3', src)
  return code_block(title, src.rstrip(), desc, lang)

def section(title):
  global tex
  tex += f"\\section{{{title}}}\n"

def subsection(title, src):
  global tex
  tex += f"\\subsection{{{title}}}\n{src}\n"

def file(title, path, desc = {}, lang = "C++"):
  global tex
  tex += code_file(title, path, desc, lang) + "\n"

section("Struktury danych")
file("Drzewo falkowe", "../data/wavelet.cpp", desc={
  "Opis": r'Obsługuje zapytania typu \textit{podaj k-ty najmniejszy na przedziale} itp.~na statycznej tablicy. Jeżeli zapytań jest dużo lub pamięć jest ciasna warto przeskalować liczby. Niszczy tablicę.',
  "Czas": r'$\mathcal{O}(\log A)$'
})

with open("temp.tex") as f:
  print(f.read().replace("%0%", tex))
