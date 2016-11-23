// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p150=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p150=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p150=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p150=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p150=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p150=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p150=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p150=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p150=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p150=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p150=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p150=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p150=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p150=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p150=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p150=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p150=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p150=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p150=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p150=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p150=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p150=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p150=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p150=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p150=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p150=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p150=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p150=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p150=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p150=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p150=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p150=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p150=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p150=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p150=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p150=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p150=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p150=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p150=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p150=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p150=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p150=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p150=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p150=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p150=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p150=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p150=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p150=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p150=p48]  endmodule
module phil50  = phil1 [p1=p50,  p2=p51,  p150=p49]  endmodule
module phil51  = phil1 [p1=p51,  p2=p52,  p150=p50]  endmodule
module phil52  = phil1 [p1=p52,  p2=p53,  p150=p51]  endmodule
module phil53  = phil1 [p1=p53,  p2=p54,  p150=p52]  endmodule
module phil54  = phil1 [p1=p54,  p2=p55,  p150=p53]  endmodule
module phil55  = phil1 [p1=p55,  p2=p56,  p150=p54]  endmodule
module phil56  = phil1 [p1=p56,  p2=p57,  p150=p55]  endmodule
module phil57  = phil1 [p1=p57,  p2=p58,  p150=p56]  endmodule
module phil58  = phil1 [p1=p58,  p2=p59,  p150=p57]  endmodule
module phil59  = phil1 [p1=p59,  p2=p60,  p150=p58]  endmodule
module phil60  = phil1 [p1=p60,  p2=p61,  p150=p59]  endmodule
module phil61  = phil1 [p1=p61,  p2=p62,  p150=p60]  endmodule
module phil62  = phil1 [p1=p62,  p2=p63,  p150=p61]  endmodule
module phil63  = phil1 [p1=p63,  p2=p64,  p150=p62]  endmodule
module phil64  = phil1 [p1=p64,  p2=p65,  p150=p63]  endmodule
module phil65  = phil1 [p1=p65,  p2=p66,  p150=p64]  endmodule
module phil66  = phil1 [p1=p66,  p2=p67,  p150=p65]  endmodule
module phil67  = phil1 [p1=p67,  p2=p68,  p150=p66]  endmodule
module phil68  = phil1 [p1=p68,  p2=p69,  p150=p67]  endmodule
module phil69  = phil1 [p1=p69,  p2=p70,  p150=p68]  endmodule
module phil70  = phil1 [p1=p70,  p2=p71,  p150=p69]  endmodule
module phil71  = phil1 [p1=p71,  p2=p72,  p150=p70]  endmodule
module phil72  = phil1 [p1=p72,  p2=p73,  p150=p71]  endmodule
module phil73  = phil1 [p1=p73,  p2=p74,  p150=p72]  endmodule
module phil74  = phil1 [p1=p74,  p2=p75,  p150=p73]  endmodule
module phil75  = phil1 [p1=p75,  p2=p76,  p150=p74]  endmodule
module phil76  = phil1 [p1=p76,  p2=p77,  p150=p75]  endmodule
module phil77  = phil1 [p1=p77,  p2=p78,  p150=p76]  endmodule
module phil78  = phil1 [p1=p78,  p2=p79,  p150=p77]  endmodule
module phil79  = phil1 [p1=p79,  p2=p80,  p150=p78]  endmodule
module phil80  = phil1 [p1=p80,  p2=p81,  p150=p79]  endmodule
module phil81  = phil1 [p1=p81,  p2=p82,  p150=p80]  endmodule
module phil82  = phil1 [p1=p82,  p2=p83,  p150=p81]  endmodule
module phil83  = phil1 [p1=p83,  p2=p84,  p150=p82]  endmodule
module phil84  = phil1 [p1=p84,  p2=p85,  p150=p83]  endmodule
module phil85  = phil1 [p1=p85,  p2=p86,  p150=p84]  endmodule
module phil86  = phil1 [p1=p86,  p2=p87,  p150=p85]  endmodule
module phil87  = phil1 [p1=p87,  p2=p88,  p150=p86]  endmodule
module phil88  = phil1 [p1=p88,  p2=p89,  p150=p87]  endmodule
module phil89  = phil1 [p1=p89,  p2=p90,  p150=p88]  endmodule
module phil90  = phil1 [p1=p90,  p2=p91,  p150=p89]  endmodule
module phil91  = phil1 [p1=p91,  p2=p92,  p150=p90]  endmodule
module phil92  = phil1 [p1=p92,  p2=p93,  p150=p91]  endmodule
module phil93  = phil1 [p1=p93,  p2=p94,  p150=p92]  endmodule
module phil94  = phil1 [p1=p94,  p2=p95,  p150=p93]  endmodule
module phil95  = phil1 [p1=p95,  p2=p96,  p150=p94]  endmodule
module phil96  = phil1 [p1=p96,  p2=p97,  p150=p95]  endmodule
module phil97  = phil1 [p1=p97,  p2=p98,  p150=p96]  endmodule
module phil98  = phil1 [p1=p98,  p2=p99,  p150=p97]  endmodule
module phil99  = phil1 [p1=p99,  p2=p100,  p150=p98]  endmodule
module phil100  = phil1 [p1=p100,  p2=p101,  p150=p99]  endmodule
module phil101  = phil1 [p1=p101,  p2=p102,  p150=p100]  endmodule
module phil102  = phil1 [p1=p102,  p2=p103,  p150=p101]  endmodule
module phil103  = phil1 [p1=p103,  p2=p104,  p150=p102]  endmodule
module phil104  = phil1 [p1=p104,  p2=p105,  p150=p103]  endmodule
module phil105  = phil1 [p1=p105,  p2=p106,  p150=p104]  endmodule
module phil106  = phil1 [p1=p106,  p2=p107,  p150=p105]  endmodule
module phil107  = phil1 [p1=p107,  p2=p108,  p150=p106]  endmodule
module phil108  = phil1 [p1=p108,  p2=p109,  p150=p107]  endmodule
module phil109  = phil1 [p1=p109,  p2=p110,  p150=p108]  endmodule
module phil110  = phil1 [p1=p110,  p2=p111,  p150=p109]  endmodule
module phil111  = phil1 [p1=p111,  p2=p112,  p150=p110]  endmodule
module phil112  = phil1 [p1=p112,  p2=p113,  p150=p111]  endmodule
module phil113  = phil1 [p1=p113,  p2=p114,  p150=p112]  endmodule
module phil114  = phil1 [p1=p114,  p2=p115,  p150=p113]  endmodule
module phil115  = phil1 [p1=p115,  p2=p116,  p150=p114]  endmodule
module phil116  = phil1 [p1=p116,  p2=p117,  p150=p115]  endmodule
module phil117  = phil1 [p1=p117,  p2=p118,  p150=p116]  endmodule
module phil118  = phil1 [p1=p118,  p2=p119,  p150=p117]  endmodule
module phil119  = phil1 [p1=p119,  p2=p120,  p150=p118]  endmodule
module phil120  = phil1 [p1=p120,  p2=p121,  p150=p119]  endmodule
module phil121  = phil1 [p1=p121,  p2=p122,  p150=p120]  endmodule
module phil122  = phil1 [p1=p122,  p2=p123,  p150=p121]  endmodule
module phil123  = phil1 [p1=p123,  p2=p124,  p150=p122]  endmodule
module phil124  = phil1 [p1=p124,  p2=p125,  p150=p123]  endmodule
module phil125  = phil1 [p1=p125,  p2=p126,  p150=p124]  endmodule
module phil126  = phil1 [p1=p126,  p2=p127,  p150=p125]  endmodule
module phil127  = phil1 [p1=p127,  p2=p128,  p150=p126]  endmodule
module phil128  = phil1 [p1=p128,  p2=p129,  p150=p127]  endmodule
module phil129  = phil1 [p1=p129,  p2=p130,  p150=p128]  endmodule
module phil130  = phil1 [p1=p130,  p2=p131,  p150=p129]  endmodule
module phil131  = phil1 [p1=p131,  p2=p132,  p150=p130]  endmodule
module phil132  = phil1 [p1=p132,  p2=p133,  p150=p131]  endmodule
module phil133  = phil1 [p1=p133,  p2=p134,  p150=p132]  endmodule
module phil134  = phil1 [p1=p134,  p2=p135,  p150=p133]  endmodule
module phil135  = phil1 [p1=p135,  p2=p136,  p150=p134]  endmodule
module phil136  = phil1 [p1=p136,  p2=p137,  p150=p135]  endmodule
module phil137  = phil1 [p1=p137,  p2=p138,  p150=p136]  endmodule
module phil138  = phil1 [p1=p138,  p2=p139,  p150=p137]  endmodule
module phil139  = phil1 [p1=p139,  p2=p140,  p150=p138]  endmodule
module phil140  = phil1 [p1=p140,  p2=p141,  p150=p139]  endmodule
module phil141  = phil1 [p1=p141,  p2=p142,  p150=p140]  endmodule
module phil142  = phil1 [p1=p142,  p2=p143,  p150=p141]  endmodule
module phil143  = phil1 [p1=p143,  p2=p144,  p150=p142]  endmodule
module phil144  = phil1 [p1=p144,  p2=p145,  p150=p143]  endmodule
module phil145  = phil1 [p1=p145,  p2=p146,  p150=p144]  endmodule
module phil146  = phil1 [p1=p146,  p2=p147,  p150=p145]  endmodule
module phil147  = phil1 [p1=p147,  p2=p148,  p150=p146]  endmodule
module phil148  = phil1 [p1=p148,  p2=p149,  p150=p147]  endmodule
module phil149  = phil1 [p1=p149,  p2=p150,  p150=p148]  endmodule
module phil150 = phil1 [p1=p150, p2=p1,  p150=p149] endmodule
