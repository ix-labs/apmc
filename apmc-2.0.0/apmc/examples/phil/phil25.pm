// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p25=0..3,5,7;
module phil1
	p1: [0..10];
	// made probabilistic (0.2 stay thinking, 0.8 become hungry)
	[] p1=0 -> 0.2 : p1'=0 + 0.8 : p1'=1;
	[] p1=1 -> 0.5 : p1'=2 + 0.5 : p1'=3;
	[] p1=2 &  lfree -> p1'=4;
	[] p1=2 & !lfree -> p1'=2;
	[] p1=3 &  rfree -> p1'=5;
	[] p1=3 & !rfree -> p1'=3;
	[] p1=4 &  rfree -> p1'=8;
	[] p1=4 & !rfree -> p1'=6;
	[] p1=5 &  lfree -> p1'=8;
	[] p1=5 & !lfree -> p1'=7;
	[] p1=6  -> p1'=1;
	[] p1=7  -> p1'=1;
	[] p1=8  -> p1'=9;
	[] p1=9  -> p1'=10;
	[] p1=10 -> p1'=0;
endmodule
// construct further modules through renaming
module phil2  = phil1 [p1=p2,  p2=p3,  p25=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p25=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p25=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p25=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p25=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p25=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p25=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p25=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p25=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p25=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p25=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p25=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p25=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p25=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p25=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p25=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p25=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p25=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p25=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p25=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p25=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p25=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p25=p23]  endmodule
module phil25 = phil1 [p1=p25, p2=p1,  p25=p24] endmodule
