
.SECONDEXPANSION:

foo: foo.1 bar.1 $$< $$^ $$+
foo: foo.2 bar.2 $$< $$^ $$+

%.1:
	touch $$@
%.2:
	touch $$@
