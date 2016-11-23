// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99

probabilistic

// atomic formulae 
// left fork free and right fork free resp.
formula lfree = p2=0..4,6,10;
formula rfree = p20=0..3,5,7;

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

module phil2  = phil1 [p1=p2,  p2=p3,  p20=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p20=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p20=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p20=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p20=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p20=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p20=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10, p20=p8]  endmodule
module phil10 = phil1 [p1=p10, p2=p11, p20=p9]  endmodule
module phil11 = phil1 [p1=p11, p2=p12, p20=p10] endmodule
module phil12 = phil1 [p1=p12, p2=p13, p20=p11] endmodule
module phil13 = phil1 [p1=p13, p2=p14, p20=p12] endmodule
module phil14 = phil1 [p1=p14, p2=p15, p20=p13] endmodule
module phil15 = phil1 [p1=p15, p2=p16, p20=p14] endmodule
module phil16 = phil1 [p1=p16, p2=p17, p20=p15] endmodule
module phil17 = phil1 [p1=p17, p2=p18, p20=p16] endmodule
module phil18 = phil1 [p1=p18, p2=p19, p20=p17] endmodule
module phil19 = phil1 [p1=p19, p2=p20, p20=p18] endmodule
module phil20 = phil1 [p1=p20, p2=p1,  p20=p19] endmodule
