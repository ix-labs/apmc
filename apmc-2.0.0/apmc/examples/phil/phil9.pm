// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99

probabilistic

// atomic formulae 
// left fork free and right fork free resp.
formula lfree = p2=0..4,6,10;
formula rfree = p9=0..3,5,7;

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

module phil2 = phil1 [p1=p2, p2=p3, p9=p1] endmodule
module phil3 = phil1 [p1=p3, p2=p4, p9=p2] endmodule
module phil4 = phil1 [p1=p4, p2=p5, p9=p3] endmodule
module phil5 = phil1 [p1=p5, p2=p6, p9=p4] endmodule
module phil6 = phil1 [p1=p6, p2=p7, p9=p5] endmodule
module phil7 = phil1 [p1=p7, p2=p8, p9=p6] endmodule
module phil8 = phil1 [p1=p8, p2=p9, p9=p7] endmodule
module phil9 = phil1 [p1=p9, p2=p1, p9=p8] endmodule
