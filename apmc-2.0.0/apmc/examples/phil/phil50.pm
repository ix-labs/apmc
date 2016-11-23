// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p50=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p50=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p50=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p50=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p50=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p50=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p50=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p50=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p50=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p50=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p50=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p50=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p50=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p50=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p50=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p50=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p50=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p50=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p50=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p50=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p50=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p50=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p50=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p50=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p50=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p50=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p50=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p50=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p50=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p50=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p50=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p50=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p50=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p50=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p50=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p50=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p50=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p50=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p50=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p50=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p50=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p50=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p50=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p50=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p50=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p50=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p50=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p50=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p50=p48]  endmodule
module phil50 = phil1 [p1=p50, p2=p1,  p50=p49] endmodule
