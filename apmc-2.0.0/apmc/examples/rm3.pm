// mutual exclusion [PZ82]
// dxp/gxn 19/12/99

probabilistic

// atomic formula
// none in low, high, tie
    formula none_lht = ((p2!=4) & (p2!=5) & (p2!=6) & (p2!=7) & (p2!=8) & (p2!=9) & (p2!=10) & (p2!=11) & (p2!=12) & (p2!=13) & (p3!=4) & (p3!=5) & (p3!=6) & (p3!=7) & (p3!=8) & (p3!=9) & (p3!=10) & (p3!=11) & (p3!=12) & (p3!=13));
// some in admit
formula some_a = ((p2=14) | (p2=15) | (p3=14) | (p3=15));
// some in high, admit
formula some_ha = ((p2=4) | (p2=5) | (p2=10) | (p2=11) | (p2 =12) | (p2=13) | (p2=14) | (p2=15) | (p3=4) | (p3=5) |(p3=10) | (p3=11) | (p3 =12) | (p3=13) | (p3=14) | (p3=15));
// none in high, tie, admit
formula none_hta = (((p2=0) | (p2=1) | (p2=2) | (p2=3) | (p2=7) | (p2=8)) & ((p3=0) | (p3=1) | (p3=2) | (p3=3) | (p3=7) | (p3=8)))  ;
// none in enter
formula none_e = ((p2!=2) & (p2!=3) & (p3!=2) & (p3!=3));
formula none_lht_or_some_a = (((p2!=4) & (p2!=5) & (p2!=6) & (p2!=7) & (p2!=8) & (p2!=9) & (p2!=10) & (p2!=11) & (p2!=12) & (p2!=13) & (p3!=4) & (p3!=5) & (p3!=6) & (p3!=7) & (p3!=8) & (p3!=9) & (p3!=10) & (p3!=11) & (p3!=12) & (p3!=13)) | ((p2=14) | (p2=15) | (p3=14) | (p3=15)));

module process1

p1: [0..15];
p2: [0..15];
p3: [0..15];
	
	[] p1=0 -> 0.5 : (p1'=0) + 0.5 : (p1'=1);
	[] p1=1 -> p1'=2;
	[] p1=2 & none_lht_or_some_a -> p1'=3;
	[] p1=2 & !none_lht_or_some_a -> p1'=2;
	[] p1=3 -> 0.5 : (p1'=4) + 0.5 : (p1'=7);
	[] p1=4 & some_ha -> p1'=5;
	[] p1=4 & !some_ha -> p1'=10;
	[] p1=5 -> p1'=6;
	[] p1=6 & some_ha -> p1'=6;
	[] p1=6 & !some_ha -> p1'=9;
	[] p1=7 & none_hta -> p1'=8;
	[] p1=7 & !none_hta -> p1'=7;
	[] p1=8 -> p1'=9;
	[] p1=9 -> 0.5 : p1'=4 + 0.5 : p1'=7;
	[] p1=10 -> p1'=11;
	[] p1=11 & none_lht -> p1'=13;
	[] p1=11 & !none_lht -> p1'=12;
	[] p1=12 -> p1'=0;
	[] p1=13 -> p1'=14;
	[] p1=14 & none_e -> p1'=15;
	[] p1=14 & !none_e -> p1'=14;
	[] p1=15 -> p1'=0;
	
endmodule

// construct further modules through renaming

module process2 = process1 [p1=p2, p2=p1] endmodule module process3 = process1 [p1=p3, p3=p1] endmodule 
