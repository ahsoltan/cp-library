SOURCES := icpc.cpp data/treap.cpp data/ordered_set.cpp flow/dinic.cpp flow/matching.cpp flow/mcmf.cpp graph/ctree.cpp graph/scc.cpp string/strings.cpp

pdf: ps
	ps2pdf lib.ps lib.pdf

ps:
	a2ps $(SOURCES) -2 --file-align=virtual --define=user.name="Adam Soltan" --prologue=color -o lib.ps

.PHONY: clean
clean:
	trash lib.ps lib.pdf
