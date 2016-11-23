// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p100=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p100=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p100=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p100=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p100=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p100=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p100=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p100=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p100=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p100=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p100=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p100=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p100=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p100=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p100=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p100=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p100=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p100=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p100=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p100=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p100=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p100=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p100=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p100=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p100=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p100=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p100=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p100=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p100=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p100=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p100=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p100=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p100=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p100=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p100=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p100=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p100=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p100=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p100=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p100=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p100=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p100=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p100=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p100=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p100=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p100=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p100=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p100=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p100=p48]  endmodule
module phil50  = phil1 [p1=p50,  p2=p51,  p100=p49]  endmodule
module phil51  = phil1 [p1=p51,  p2=p52,  p100=p50]  endmodule
module phil52  = phil1 [p1=p52,  p2=p53,  p100=p51]  endmodule
module phil53  = phil1 [p1=p53,  p2=p54,  p100=p52]  endmodule
module phil54  = phil1 [p1=p54,  p2=p55,  p100=p53]  endmodule
module phil55  = phil1 [p1=p55,  p2=p56,  p100=p54]  endmodule
module phil56  = phil1 [p1=p56,  p2=p57,  p100=p55]  endmodule
module phil57  = phil1 [p1=p57,  p2=p58,  p100=p56]  endmodule
module phil58  = phil1 [p1=p58,  p2=p59,  p100=p57]  endmodule
module phil59  = phil1 [p1=p59,  p2=p60,  p100=p58]  endmodule
module phil60  = phil1 [p1=p60,  p2=p61,  p100=p59]  endmodule
module phil61  = phil1 [p1=p61,  p2=p62,  p100=p60]  endmodule
module phil62  = phil1 [p1=p62,  p2=p63,  p100=p61]  endmodule
module phil63  = phil1 [p1=p63,  p2=p64,  p100=p62]  endmodule
module phil64  = phil1 [p1=p64,  p2=p65,  p100=p63]  endmodule
module phil65  = phil1 [p1=p65,  p2=p66,  p100=p64]  endmodule
module phil66  = phil1 [p1=p66,  p2=p67,  p100=p65]  endmodule
module phil67  = phil1 [p1=p67,  p2=p68,  p100=p66]  endmodule
module phil68  = phil1 [p1=p68,  p2=p69,  p100=p67]  endmodule
module phil69  = phil1 [p1=p69,  p2=p70,  p100=p68]  endmodule
module phil70  = phil1 [p1=p70,  p2=p71,  p100=p69]  endmodule
module phil71  = phil1 [p1=p71,  p2=p72,  p100=p70]  endmodule
module phil72  = phil1 [p1=p72,  p2=p73,  p100=p71]  endmodule
module phil73  = phil1 [p1=p73,  p2=p74,  p100=p72]  endmodule
module phil74  = phil1 [p1=p74,  p2=p75,  p100=p73]  endmodule
module phil75  = phil1 [p1=p75,  p2=p76,  p100=p74]  endmodule
module phil76  = phil1 [p1=p76,  p2=p77,  p100=p75]  endmodule
module phil77  = phil1 [p1=p77,  p2=p78,  p100=p76]  endmodule
module phil78  = phil1 [p1=p78,  p2=p79,  p100=p77]  endmodule
module phil79  = phil1 [p1=p79,  p2=p80,  p100=p78]  endmodule
module phil80  = phil1 [p1=p80,  p2=p81,  p100=p79]  endmodule
module phil81  = phil1 [p1=p81,  p2=p82,  p100=p80]  endmodule
module phil82  = phil1 [p1=p82,  p2=p83,  p100=p81]  endmodule
module phil83  = phil1 [p1=p83,  p2=p84,  p100=p82]  endmodule
module phil84  = phil1 [p1=p84,  p2=p85,  p100=p83]  endmodule
module phil85  = phil1 [p1=p85,  p2=p86,  p100=p84]  endmodule
module phil86  = phil1 [p1=p86,  p2=p87,  p100=p85]  endmodule
module phil87  = phil1 [p1=p87,  p2=p88,  p100=p86]  endmodule
module phil88  = phil1 [p1=p88,  p2=p89,  p100=p87]  endmodule
module phil89  = phil1 [p1=p89,  p2=p90,  p100=p88]  endmodule
module phil90  = phil1 [p1=p90,  p2=p91,  p100=p89]  endmodule
module phil91  = phil1 [p1=p91,  p2=p92,  p100=p90]  endmodule
module phil92  = phil1 [p1=p92,  p2=p93,  p100=p91]  endmodule
module phil93  = phil1 [p1=p93,  p2=p94,  p100=p92]  endmodule
module phil94  = phil1 [p1=p94,  p2=p95,  p100=p93]  endmodule
module phil95  = phil1 [p1=p95,  p2=p96,  p100=p94]  endmodule
module phil96  = phil1 [p1=p96,  p2=p97,  p100=p95]  endmodule
module phil97  = phil1 [p1=p97,  p2=p98,  p100=p96]  endmodule
module phil98  = phil1 [p1=p98,  p2=p99,  p100=p97]  endmodule
module phil99  = phil1 [p1=p99,  p2=p100,  p100=p98]  endmodule
module phil100 = phil1 [p1=p100, p2=p1,  p100=p99] endmodule
