@title High Dynamic Range

print "1) normal"
shoot

set_aflock 1
get_av96 p
get_sv96 s
get_tv96 t

print "2) bright"
set_tv96_direct t-192
set_sv96 s
set_av96 p
shoot 

print "3) dark"
set_tv96_direct t+192
set_sv96 s
set_av96 p
shoot
		
set_aflock 0
print "...done"
