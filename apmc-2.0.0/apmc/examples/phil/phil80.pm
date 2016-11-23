// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p80=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p80=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p80=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p80=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p80=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p80=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p80=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p80=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p80=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p80=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p80=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p80=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p80=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p80=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p80=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p80=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p80=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p80=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p80=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p80=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p80=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p80=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p80=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p80=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p80=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p80=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p80=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p80=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p80=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p80=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p80=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p80=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p80=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p80=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p80=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p80=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p80=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p80=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p80=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p80=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p80=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p80=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p80=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p80=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p80=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p80=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p80=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p80=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p80=p48]  endmodule
module phil50  = phil1 [p1=p50,  p2=p51,  p80=p49]  endmodule
module phil51  = phil1 [p1=p51,  p2=p52,  p80=p50]  endmodule
module phil52  = phil1 [p1=p52,  p2=p53,  p80=p51]  endmodule
module phil53  = phil1 [p1=p53,  p2=p54,  p80=p52]  endmodule
module phil54  = phil1 [p1=p54,  p2=p55,  p80=p53]  endmodule
module phil55  = phil1 [p1=p55,  p2=p56,  p80=p54]  endmodule
module phil56  = phil1 [p1=p56,  p2=p57,  p80=p55]  endmodule
module phil57  = phil1 [p1=p57,  p2=p58,  p80=p56]  endmodule
module phil58  = phil1 [p1=p58,  p2=p59,  p80=p57]  endmodule
module phil59  = phil1 [p1=p59,  p2=p60,  p80=p58]  endmodule
module phil60  = phil1 [p1=p60,  p2=p61,  p80=p59]  endmodule
module phil61  = phil1 [p1=p61,  p2=p62,  p80=p60]  endmodule
module phil62  = phil1 [p1=p62,  p2=p63,  p80=p61]  endmodule
module phil63  = phil1 [p1=p63,  p2=p64,  p80=p62]  endmodule
module phil64  = phil1 [p1=p64,  p2=p65,  p80=p63]  endmodule
module phil65  = phil1 [p1=p65,  p2=p66,  p80=p64]  endmodule
module phil66  = phil1 [p1=p66,  p2=p67,  p80=p65]  endmodule
module phil67  = phil1 [p1=p67,  p2=p68,  p80=p66]  endmodule
module phil68  = phil1 [p1=p68,  p2=p69,  p80=p67]  endmodule
module phil69  = phil1 [p1=p69,  p2=p70,  p80=p68]  endmodule
module phil70  = phil1 [p1=p70,  p2=p71,  p80=p69]  endmodule
module phil71  = phil1 [p1=p71,  p2=p72,  p80=p70]  endmodule
module phil72  = phil1 [p1=p72,  p2=p73,  p80=p71]  endmodule
module phil73  = phil1 [p1=p73,  p2=p74,  p80=p72]  endmodule
module phil74  = phil1 [p1=p74,  p2=p75,  p80=p73]  endmodule
module phil75  = phil1 [p1=p75,  p2=p76,  p80=p74]  endmodule
module phil76  = phil1 [p1=p76,  p2=p77,  p80=p75]  endmodule
module phil77  = phil1 [p1=p77,  p2=p78,  p80=p76]  endmodule
module phil78  = phil1 [p1=p78,  p2=p79,  p80=p77]  endmodule
module phil79  = phil1 [p1=p79,  p2=p80,  p80=p78]  endmodule
module phil80 = phil1 [p1=p80, p2=p1,  p80=p79] endmodule
