// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p170=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p170=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p170=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p170=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p170=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p170=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p170=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p170=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p170=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p170=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p170=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p170=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p170=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p170=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p170=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p170=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p170=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p170=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p170=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p170=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p170=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p170=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p170=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p170=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p170=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p170=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p170=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p170=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p170=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p170=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p170=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p170=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p170=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p170=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p170=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p170=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p170=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p170=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p170=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p170=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p170=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p170=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p170=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p170=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p170=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p170=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p170=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p170=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p170=p48]  endmodule
module phil50  = phil1 [p1=p50,  p2=p51,  p170=p49]  endmodule
module phil51  = phil1 [p1=p51,  p2=p52,  p170=p50]  endmodule
module phil52  = phil1 [p1=p52,  p2=p53,  p170=p51]  endmodule
module phil53  = phil1 [p1=p53,  p2=p54,  p170=p52]  endmodule
module phil54  = phil1 [p1=p54,  p2=p55,  p170=p53]  endmodule
module phil55  = phil1 [p1=p55,  p2=p56,  p170=p54]  endmodule
module phil56  = phil1 [p1=p56,  p2=p57,  p170=p55]  endmodule
module phil57  = phil1 [p1=p57,  p2=p58,  p170=p56]  endmodule
module phil58  = phil1 [p1=p58,  p2=p59,  p170=p57]  endmodule
module phil59  = phil1 [p1=p59,  p2=p60,  p170=p58]  endmodule
module phil60  = phil1 [p1=p60,  p2=p61,  p170=p59]  endmodule
module phil61  = phil1 [p1=p61,  p2=p62,  p170=p60]  endmodule
module phil62  = phil1 [p1=p62,  p2=p63,  p170=p61]  endmodule
module phil63  = phil1 [p1=p63,  p2=p64,  p170=p62]  endmodule
module phil64  = phil1 [p1=p64,  p2=p65,  p170=p63]  endmodule
module phil65  = phil1 [p1=p65,  p2=p66,  p170=p64]  endmodule
module phil66  = phil1 [p1=p66,  p2=p67,  p170=p65]  endmodule
module phil67  = phil1 [p1=p67,  p2=p68,  p170=p66]  endmodule
module phil68  = phil1 [p1=p68,  p2=p69,  p170=p67]  endmodule
module phil69  = phil1 [p1=p69,  p2=p70,  p170=p68]  endmodule
module phil70  = phil1 [p1=p70,  p2=p71,  p170=p69]  endmodule
module phil71  = phil1 [p1=p71,  p2=p72,  p170=p70]  endmodule
module phil72  = phil1 [p1=p72,  p2=p73,  p170=p71]  endmodule
module phil73  = phil1 [p1=p73,  p2=p74,  p170=p72]  endmodule
module phil74  = phil1 [p1=p74,  p2=p75,  p170=p73]  endmodule
module phil75  = phil1 [p1=p75,  p2=p76,  p170=p74]  endmodule
module phil76  = phil1 [p1=p76,  p2=p77,  p170=p75]  endmodule
module phil77  = phil1 [p1=p77,  p2=p78,  p170=p76]  endmodule
module phil78  = phil1 [p1=p78,  p2=p79,  p170=p77]  endmodule
module phil79  = phil1 [p1=p79,  p2=p80,  p170=p78]  endmodule
module phil80  = phil1 [p1=p80,  p2=p81,  p170=p79]  endmodule
module phil81  = phil1 [p1=p81,  p2=p82,  p170=p80]  endmodule
module phil82  = phil1 [p1=p82,  p2=p83,  p170=p81]  endmodule
module phil83  = phil1 [p1=p83,  p2=p84,  p170=p82]  endmodule
module phil84  = phil1 [p1=p84,  p2=p85,  p170=p83]  endmodule
module phil85  = phil1 [p1=p85,  p2=p86,  p170=p84]  endmodule
module phil86  = phil1 [p1=p86,  p2=p87,  p170=p85]  endmodule
module phil87  = phil1 [p1=p87,  p2=p88,  p170=p86]  endmodule
module phil88  = phil1 [p1=p88,  p2=p89,  p170=p87]  endmodule
module phil89  = phil1 [p1=p89,  p2=p90,  p170=p88]  endmodule
module phil90  = phil1 [p1=p90,  p2=p91,  p170=p89]  endmodule
module phil91  = phil1 [p1=p91,  p2=p92,  p170=p90]  endmodule
module phil92  = phil1 [p1=p92,  p2=p93,  p170=p91]  endmodule
module phil93  = phil1 [p1=p93,  p2=p94,  p170=p92]  endmodule
module phil94  = phil1 [p1=p94,  p2=p95,  p170=p93]  endmodule
module phil95  = phil1 [p1=p95,  p2=p96,  p170=p94]  endmodule
module phil96  = phil1 [p1=p96,  p2=p97,  p170=p95]  endmodule
module phil97  = phil1 [p1=p97,  p2=p98,  p170=p96]  endmodule
module phil98  = phil1 [p1=p98,  p2=p99,  p170=p97]  endmodule
module phil99  = phil1 [p1=p99,  p2=p100,  p170=p98]  endmodule
module phil100  = phil1 [p1=p100,  p2=p101,  p170=p99]  endmodule
module phil101  = phil1 [p1=p101,  p2=p102,  p170=p100]  endmodule
module phil102  = phil1 [p1=p102,  p2=p103,  p170=p101]  endmodule
module phil103  = phil1 [p1=p103,  p2=p104,  p170=p102]  endmodule
module phil104  = phil1 [p1=p104,  p2=p105,  p170=p103]  endmodule
module phil105  = phil1 [p1=p105,  p2=p106,  p170=p104]  endmodule
module phil106  = phil1 [p1=p106,  p2=p107,  p170=p105]  endmodule
module phil107  = phil1 [p1=p107,  p2=p108,  p170=p106]  endmodule
module phil108  = phil1 [p1=p108,  p2=p109,  p170=p107]  endmodule
module phil109  = phil1 [p1=p109,  p2=p110,  p170=p108]  endmodule
module phil110  = phil1 [p1=p110,  p2=p111,  p170=p109]  endmodule
module phil111  = phil1 [p1=p111,  p2=p112,  p170=p110]  endmodule
module phil112  = phil1 [p1=p112,  p2=p113,  p170=p111]  endmodule
module phil113  = phil1 [p1=p113,  p2=p114,  p170=p112]  endmodule
module phil114  = phil1 [p1=p114,  p2=p115,  p170=p113]  endmodule
module phil115  = phil1 [p1=p115,  p2=p116,  p170=p114]  endmodule
module phil116  = phil1 [p1=p116,  p2=p117,  p170=p115]  endmodule
module phil117  = phil1 [p1=p117,  p2=p118,  p170=p116]  endmodule
module phil118  = phil1 [p1=p118,  p2=p119,  p170=p117]  endmodule
module phil119  = phil1 [p1=p119,  p2=p120,  p170=p118]  endmodule
module phil120  = phil1 [p1=p120,  p2=p121,  p170=p119]  endmodule
module phil121  = phil1 [p1=p121,  p2=p122,  p170=p120]  endmodule
module phil122  = phil1 [p1=p122,  p2=p123,  p170=p121]  endmodule
module phil123  = phil1 [p1=p123,  p2=p124,  p170=p122]  endmodule
module phil124  = phil1 [p1=p124,  p2=p125,  p170=p123]  endmodule
module phil125  = phil1 [p1=p125,  p2=p126,  p170=p124]  endmodule
module phil126  = phil1 [p1=p126,  p2=p127,  p170=p125]  endmodule
module phil127  = phil1 [p1=p127,  p2=p128,  p170=p126]  endmodule
module phil128  = phil1 [p1=p128,  p2=p129,  p170=p127]  endmodule
module phil129  = phil1 [p1=p129,  p2=p130,  p170=p128]  endmodule
module phil130  = phil1 [p1=p130,  p2=p131,  p170=p129]  endmodule
module phil131  = phil1 [p1=p131,  p2=p132,  p170=p130]  endmodule
module phil132  = phil1 [p1=p132,  p2=p133,  p170=p131]  endmodule
module phil133  = phil1 [p1=p133,  p2=p134,  p170=p132]  endmodule
module phil134  = phil1 [p1=p134,  p2=p135,  p170=p133]  endmodule
module phil135  = phil1 [p1=p135,  p2=p136,  p170=p134]  endmodule
module phil136  = phil1 [p1=p136,  p2=p137,  p170=p135]  endmodule
module phil137  = phil1 [p1=p137,  p2=p138,  p170=p136]  endmodule
module phil138  = phil1 [p1=p138,  p2=p139,  p170=p137]  endmodule
module phil139  = phil1 [p1=p139,  p2=p140,  p170=p138]  endmodule
module phil140  = phil1 [p1=p140,  p2=p141,  p170=p139]  endmodule
module phil141  = phil1 [p1=p141,  p2=p142,  p170=p140]  endmodule
module phil142  = phil1 [p1=p142,  p2=p143,  p170=p141]  endmodule
module phil143  = phil1 [p1=p143,  p2=p144,  p170=p142]  endmodule
module phil144  = phil1 [p1=p144,  p2=p145,  p170=p143]  endmodule
module phil145  = phil1 [p1=p145,  p2=p146,  p170=p144]  endmodule
module phil146  = phil1 [p1=p146,  p2=p147,  p170=p145]  endmodule
module phil147  = phil1 [p1=p147,  p2=p148,  p170=p146]  endmodule
module phil148  = phil1 [p1=p148,  p2=p149,  p170=p147]  endmodule
module phil149  = phil1 [p1=p149,  p2=p150,  p170=p148]  endmodule
module phil150  = phil1 [p1=p150,  p2=p151,  p170=p149]  endmodule
module phil151  = phil1 [p1=p151,  p2=p152,  p170=p150]  endmodule
module phil152  = phil1 [p1=p152,  p2=p153,  p170=p151]  endmodule
module phil153  = phil1 [p1=p153,  p2=p154,  p170=p152]  endmodule
module phil154  = phil1 [p1=p154,  p2=p155,  p170=p153]  endmodule
module phil155  = phil1 [p1=p155,  p2=p156,  p170=p154]  endmodule
module phil156  = phil1 [p1=p156,  p2=p157,  p170=p155]  endmodule
module phil157  = phil1 [p1=p157,  p2=p158,  p170=p156]  endmodule
module phil158  = phil1 [p1=p158,  p2=p159,  p170=p157]  endmodule
module phil159  = phil1 [p1=p159,  p2=p160,  p170=p158]  endmodule
module phil160  = phil1 [p1=p160,  p2=p161,  p170=p159]  endmodule
module phil161  = phil1 [p1=p161,  p2=p162,  p170=p160]  endmodule
module phil162  = phil1 [p1=p162,  p2=p163,  p170=p161]  endmodule
module phil163  = phil1 [p1=p163,  p2=p164,  p170=p162]  endmodule
module phil164  = phil1 [p1=p164,  p2=p165,  p170=p163]  endmodule
module phil165  = phil1 [p1=p165,  p2=p166,  p170=p164]  endmodule
module phil166  = phil1 [p1=p166,  p2=p167,  p170=p165]  endmodule
module phil167  = phil1 [p1=p167,  p2=p168,  p170=p166]  endmodule
module phil168  = phil1 [p1=p168,  p2=p169,  p170=p167]  endmodule
module phil169  = phil1 [p1=p169,  p2=p170,  p170=p168]  endmodule
module phil170 = phil1 [p1=p170, p2=p1,  p170=p169] endmodule
