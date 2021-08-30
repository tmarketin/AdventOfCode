awk 'BEGIN {ttot = 2503} {printf("%s %d %d %d\n",$1,$4,$7,$14); v = $4; tv = $7; tr = $14; s = 0; for(i = 1; i <= ttot; i++) {if(i % (tv+tr) > 0 && i % (tv+tr) <= tv) s = s + v;} print s}' day14.dat
