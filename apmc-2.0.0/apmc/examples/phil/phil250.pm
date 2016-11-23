// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p250=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p250=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p250=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p250=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p250=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p250=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p250=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p250=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p250=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p250=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p250=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p250=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p250=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p250=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p250=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p250=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p250=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p250=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p250=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p250=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p250=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p250=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p250=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p250=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p250=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p250=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p250=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p250=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p250=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p250=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p250=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p250=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p250=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p250=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p250=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p250=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p250=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p250=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p250=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p250=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p250=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p250=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p250=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p250=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p250=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p250=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p250=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p250=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p250=p48]  endmodule
module phil50  = phil1 [p1=p50,  p2=p51,  p250=p49]  endmodule
module phil51  = phil1 [p1=p51,  p2=p52,  p250=p50]  endmodule
module phil52  = phil1 [p1=p52,  p2=p53,  p250=p51]  endmodule
module phil53  = phil1 [p1=p53,  p2=p54,  p250=p52]  endmodule
module phil54  = phil1 [p1=p54,  p2=p55,  p250=p53]  endmodule
module phil55  = phil1 [p1=p55,  p2=p56,  p250=p54]  endmodule
module phil56  = phil1 [p1=p56,  p2=p57,  p250=p55]  endmodule
module phil57  = phil1 [p1=p57,  p2=p58,  p250=p56]  endmodule
module phil58  = phil1 [p1=p58,  p2=p59,  p250=p57]  endmodule
module phil59  = phil1 [p1=p59,  p2=p60,  p250=p58]  endmodule
module phil60  = phil1 [p1=p60,  p2=p61,  p250=p59]  endmodule
module phil61  = phil1 [p1=p61,  p2=p62,  p250=p60]  endmodule
module phil62  = phil1 [p1=p62,  p2=p63,  p250=p61]  endmodule
module phil63  = phil1 [p1=p63,  p2=p64,  p250=p62]  endmodule
module phil64  = phil1 [p1=p64,  p2=p65,  p250=p63]  endmodule
module phil65  = phil1 [p1=p65,  p2=p66,  p250=p64]  endmodule
module phil66  = phil1 [p1=p66,  p2=p67,  p250=p65]  endmodule
module phil67  = phil1 [p1=p67,  p2=p68,  p250=p66]  endmodule
module phil68  = phil1 [p1=p68,  p2=p69,  p250=p67]  endmodule
module phil69  = phil1 [p1=p69,  p2=p70,  p250=p68]  endmodule
module phil70  = phil1 [p1=p70,  p2=p71,  p250=p69]  endmodule
module phil71  = phil1 [p1=p71,  p2=p72,  p250=p70]  endmodule
module phil72  = phil1 [p1=p72,  p2=p73,  p250=p71]  endmodule
module phil73  = phil1 [p1=p73,  p2=p74,  p250=p72]  endmodule
module phil74  = phil1 [p1=p74,  p2=p75,  p250=p73]  endmodule
module phil75  = phil1 [p1=p75,  p2=p76,  p250=p74]  endmodule
module phil76  = phil1 [p1=p76,  p2=p77,  p250=p75]  endmodule
module phil77  = phil1 [p1=p77,  p2=p78,  p250=p76]  endmodule
module phil78  = phil1 [p1=p78,  p2=p79,  p250=p77]  endmodule
module phil79  = phil1 [p1=p79,  p2=p80,  p250=p78]  endmodule
module phil80  = phil1 [p1=p80,  p2=p81,  p250=p79]  endmodule
module phil81  = phil1 [p1=p81,  p2=p82,  p250=p80]  endmodule
module phil82  = phil1 [p1=p82,  p2=p83,  p250=p81]  endmodule
module phil83  = phil1 [p1=p83,  p2=p84,  p250=p82]  endmodule
module phil84  = phil1 [p1=p84,  p2=p85,  p250=p83]  endmodule
module phil85  = phil1 [p1=p85,  p2=p86,  p250=p84]  endmodule
module phil86  = phil1 [p1=p86,  p2=p87,  p250=p85]  endmodule
module phil87  = phil1 [p1=p87,  p2=p88,  p250=p86]  endmodule
module phil88  = phil1 [p1=p88,  p2=p89,  p250=p87]  endmodule
module phil89  = phil1 [p1=p89,  p2=p90,  p250=p88]  endmodule
module phil90  = phil1 [p1=p90,  p2=p91,  p250=p89]  endmodule
module phil91  = phil1 [p1=p91,  p2=p92,  p250=p90]  endmodule
module phil92  = phil1 [p1=p92,  p2=p93,  p250=p91]  endmodule
module phil93  = phil1 [p1=p93,  p2=p94,  p250=p92]  endmodule
module phil94  = phil1 [p1=p94,  p2=p95,  p250=p93]  endmodule
module phil95  = phil1 [p1=p95,  p2=p96,  p250=p94]  endmodule
module phil96  = phil1 [p1=p96,  p2=p97,  p250=p95]  endmodule
module phil97  = phil1 [p1=p97,  p2=p98,  p250=p96]  endmodule
module phil98  = phil1 [p1=p98,  p2=p99,  p250=p97]  endmodule
module phil99  = phil1 [p1=p99,  p2=p100,  p250=p98]  endmodule
module phil100  = phil1 [p1=p100,  p2=p101,  p250=p99]  endmodule
module phil101  = phil1 [p1=p101,  p2=p102,  p250=p100]  endmodule
module phil102  = phil1 [p1=p102,  p2=p103,  p250=p101]  endmodule
module phil103  = phil1 [p1=p103,  p2=p104,  p250=p102]  endmodule
module phil104  = phil1 [p1=p104,  p2=p105,  p250=p103]  endmodule
module phil105  = phil1 [p1=p105,  p2=p106,  p250=p104]  endmodule
module phil106  = phil1 [p1=p106,  p2=p107,  p250=p105]  endmodule
module phil107  = phil1 [p1=p107,  p2=p108,  p250=p106]  endmodule
module phil108  = phil1 [p1=p108,  p2=p109,  p250=p107]  endmodule
module phil109  = phil1 [p1=p109,  p2=p110,  p250=p108]  endmodule
module phil110  = phil1 [p1=p110,  p2=p111,  p250=p109]  endmodule
module phil111  = phil1 [p1=p111,  p2=p112,  p250=p110]  endmodule
module phil112  = phil1 [p1=p112,  p2=p113,  p250=p111]  endmodule
module phil113  = phil1 [p1=p113,  p2=p114,  p250=p112]  endmodule
module phil114  = phil1 [p1=p114,  p2=p115,  p250=p113]  endmodule
module phil115  = phil1 [p1=p115,  p2=p116,  p250=p114]  endmodule
module phil116  = phil1 [p1=p116,  p2=p117,  p250=p115]  endmodule
module phil117  = phil1 [p1=p117,  p2=p118,  p250=p116]  endmodule
module phil118  = phil1 [p1=p118,  p2=p119,  p250=p117]  endmodule
module phil119  = phil1 [p1=p119,  p2=p120,  p250=p118]  endmodule
module phil120  = phil1 [p1=p120,  p2=p121,  p250=p119]  endmodule
module phil121  = phil1 [p1=p121,  p2=p122,  p250=p120]  endmodule
module phil122  = phil1 [p1=p122,  p2=p123,  p250=p121]  endmodule
module phil123  = phil1 [p1=p123,  p2=p124,  p250=p122]  endmodule
module phil124  = phil1 [p1=p124,  p2=p125,  p250=p123]  endmodule
module phil125  = phil1 [p1=p125,  p2=p126,  p250=p124]  endmodule
module phil126  = phil1 [p1=p126,  p2=p127,  p250=p125]  endmodule
module phil127  = phil1 [p1=p127,  p2=p128,  p250=p126]  endmodule
module phil128  = phil1 [p1=p128,  p2=p129,  p250=p127]  endmodule
module phil129  = phil1 [p1=p129,  p2=p130,  p250=p128]  endmodule
module phil130  = phil1 [p1=p130,  p2=p131,  p250=p129]  endmodule
module phil131  = phil1 [p1=p131,  p2=p132,  p250=p130]  endmodule
module phil132  = phil1 [p1=p132,  p2=p133,  p250=p131]  endmodule
module phil133  = phil1 [p1=p133,  p2=p134,  p250=p132]  endmodule
module phil134  = phil1 [p1=p134,  p2=p135,  p250=p133]  endmodule
module phil135  = phil1 [p1=p135,  p2=p136,  p250=p134]  endmodule
module phil136  = phil1 [p1=p136,  p2=p137,  p250=p135]  endmodule
module phil137  = phil1 [p1=p137,  p2=p138,  p250=p136]  endmodule
module phil138  = phil1 [p1=p138,  p2=p139,  p250=p137]  endmodule
module phil139  = phil1 [p1=p139,  p2=p140,  p250=p138]  endmodule
module phil140  = phil1 [p1=p140,  p2=p141,  p250=p139]  endmodule
module phil141  = phil1 [p1=p141,  p2=p142,  p250=p140]  endmodule
module phil142  = phil1 [p1=p142,  p2=p143,  p250=p141]  endmodule
module phil143  = phil1 [p1=p143,  p2=p144,  p250=p142]  endmodule
module phil144  = phil1 [p1=p144,  p2=p145,  p250=p143]  endmodule
module phil145  = phil1 [p1=p145,  p2=p146,  p250=p144]  endmodule
module phil146  = phil1 [p1=p146,  p2=p147,  p250=p145]  endmodule
module phil147  = phil1 [p1=p147,  p2=p148,  p250=p146]  endmodule
module phil148  = phil1 [p1=p148,  p2=p149,  p250=p147]  endmodule
module phil149  = phil1 [p1=p149,  p2=p150,  p250=p148]  endmodule
module phil150  = phil1 [p1=p150,  p2=p151,  p250=p149]  endmodule
module phil151  = phil1 [p1=p151,  p2=p152,  p250=p150]  endmodule
module phil152  = phil1 [p1=p152,  p2=p153,  p250=p151]  endmodule
module phil153  = phil1 [p1=p153,  p2=p154,  p250=p152]  endmodule
module phil154  = phil1 [p1=p154,  p2=p155,  p250=p153]  endmodule
module phil155  = phil1 [p1=p155,  p2=p156,  p250=p154]  endmodule
module phil156  = phil1 [p1=p156,  p2=p157,  p250=p155]  endmodule
module phil157  = phil1 [p1=p157,  p2=p158,  p250=p156]  endmodule
module phil158  = phil1 [p1=p158,  p2=p159,  p250=p157]  endmodule
module phil159  = phil1 [p1=p159,  p2=p160,  p250=p158]  endmodule
module phil160  = phil1 [p1=p160,  p2=p161,  p250=p159]  endmodule
module phil161  = phil1 [p1=p161,  p2=p162,  p250=p160]  endmodule
module phil162  = phil1 [p1=p162,  p2=p163,  p250=p161]  endmodule
module phil163  = phil1 [p1=p163,  p2=p164,  p250=p162]  endmodule
module phil164  = phil1 [p1=p164,  p2=p165,  p250=p163]  endmodule
module phil165  = phil1 [p1=p165,  p2=p166,  p250=p164]  endmodule
module phil166  = phil1 [p1=p166,  p2=p167,  p250=p165]  endmodule
module phil167  = phil1 [p1=p167,  p2=p168,  p250=p166]  endmodule
module phil168  = phil1 [p1=p168,  p2=p169,  p250=p167]  endmodule
module phil169  = phil1 [p1=p169,  p2=p170,  p250=p168]  endmodule
module phil170  = phil1 [p1=p170,  p2=p171,  p250=p169]  endmodule
module phil171  = phil1 [p1=p171,  p2=p172,  p250=p170]  endmodule
module phil172  = phil1 [p1=p172,  p2=p173,  p250=p171]  endmodule
module phil173  = phil1 [p1=p173,  p2=p174,  p250=p172]  endmodule
module phil174  = phil1 [p1=p174,  p2=p175,  p250=p173]  endmodule
module phil175  = phil1 [p1=p175,  p2=p176,  p250=p174]  endmodule
module phil176  = phil1 [p1=p176,  p2=p177,  p250=p175]  endmodule
module phil177  = phil1 [p1=p177,  p2=p178,  p250=p176]  endmodule
module phil178  = phil1 [p1=p178,  p2=p179,  p250=p177]  endmodule
module phil179  = phil1 [p1=p179,  p2=p180,  p250=p178]  endmodule
module phil180  = phil1 [p1=p180,  p2=p181,  p250=p179]  endmodule
module phil181  = phil1 [p1=p181,  p2=p182,  p250=p180]  endmodule
module phil182  = phil1 [p1=p182,  p2=p183,  p250=p181]  endmodule
module phil183  = phil1 [p1=p183,  p2=p184,  p250=p182]  endmodule
module phil184  = phil1 [p1=p184,  p2=p185,  p250=p183]  endmodule
module phil185  = phil1 [p1=p185,  p2=p186,  p250=p184]  endmodule
module phil186  = phil1 [p1=p186,  p2=p187,  p250=p185]  endmodule
module phil187  = phil1 [p1=p187,  p2=p188,  p250=p186]  endmodule
module phil188  = phil1 [p1=p188,  p2=p189,  p250=p187]  endmodule
module phil189  = phil1 [p1=p189,  p2=p190,  p250=p188]  endmodule
module phil190  = phil1 [p1=p190,  p2=p191,  p250=p189]  endmodule
module phil191  = phil1 [p1=p191,  p2=p192,  p250=p190]  endmodule
module phil192  = phil1 [p1=p192,  p2=p193,  p250=p191]  endmodule
module phil193  = phil1 [p1=p193,  p2=p194,  p250=p192]  endmodule
module phil194  = phil1 [p1=p194,  p2=p195,  p250=p193]  endmodule
module phil195  = phil1 [p1=p195,  p2=p196,  p250=p194]  endmodule
module phil196  = phil1 [p1=p196,  p2=p197,  p250=p195]  endmodule
module phil197  = phil1 [p1=p197,  p2=p198,  p250=p196]  endmodule
module phil198  = phil1 [p1=p198,  p2=p199,  p250=p197]  endmodule
module phil199  = phil1 [p1=p199,  p2=p200,  p250=p198]  endmodule
module phil200  = phil1 [p1=p200,  p2=p201,  p250=p199]  endmodule
module phil201  = phil1 [p1=p201,  p2=p202,  p250=p200]  endmodule
module phil202  = phil1 [p1=p202,  p2=p203,  p250=p201]  endmodule
module phil203  = phil1 [p1=p203,  p2=p204,  p250=p202]  endmodule
module phil204  = phil1 [p1=p204,  p2=p205,  p250=p203]  endmodule
module phil205  = phil1 [p1=p205,  p2=p206,  p250=p204]  endmodule
module phil206  = phil1 [p1=p206,  p2=p207,  p250=p205]  endmodule
module phil207  = phil1 [p1=p207,  p2=p208,  p250=p206]  endmodule
module phil208  = phil1 [p1=p208,  p2=p209,  p250=p207]  endmodule
module phil209  = phil1 [p1=p209,  p2=p210,  p250=p208]  endmodule
module phil210  = phil1 [p1=p210,  p2=p211,  p250=p209]  endmodule
module phil211  = phil1 [p1=p211,  p2=p212,  p250=p210]  endmodule
module phil212  = phil1 [p1=p212,  p2=p213,  p250=p211]  endmodule
module phil213  = phil1 [p1=p213,  p2=p214,  p250=p212]  endmodule
module phil214  = phil1 [p1=p214,  p2=p215,  p250=p213]  endmodule
module phil215  = phil1 [p1=p215,  p2=p216,  p250=p214]  endmodule
module phil216  = phil1 [p1=p216,  p2=p217,  p250=p215]  endmodule
module phil217  = phil1 [p1=p217,  p2=p218,  p250=p216]  endmodule
module phil218  = phil1 [p1=p218,  p2=p219,  p250=p217]  endmodule
module phil219  = phil1 [p1=p219,  p2=p220,  p250=p218]  endmodule
module phil220  = phil1 [p1=p220,  p2=p221,  p250=p219]  endmodule
module phil221  = phil1 [p1=p221,  p2=p222,  p250=p220]  endmodule
module phil222  = phil1 [p1=p222,  p2=p223,  p250=p221]  endmodule
module phil223  = phil1 [p1=p223,  p2=p224,  p250=p222]  endmodule
module phil224  = phil1 [p1=p224,  p2=p225,  p250=p223]  endmodule
module phil225  = phil1 [p1=p225,  p2=p226,  p250=p224]  endmodule
module phil226  = phil1 [p1=p226,  p2=p227,  p250=p225]  endmodule
module phil227  = phil1 [p1=p227,  p2=p228,  p250=p226]  endmodule
module phil228  = phil1 [p1=p228,  p2=p229,  p250=p227]  endmodule
module phil229  = phil1 [p1=p229,  p2=p230,  p250=p228]  endmodule
module phil230  = phil1 [p1=p230,  p2=p231,  p250=p229]  endmodule
module phil231  = phil1 [p1=p231,  p2=p232,  p250=p230]  endmodule
module phil232  = phil1 [p1=p232,  p2=p233,  p250=p231]  endmodule
module phil233  = phil1 [p1=p233,  p2=p234,  p250=p232]  endmodule
module phil234  = phil1 [p1=p234,  p2=p235,  p250=p233]  endmodule
module phil235  = phil1 [p1=p235,  p2=p236,  p250=p234]  endmodule
module phil236  = phil1 [p1=p236,  p2=p237,  p250=p235]  endmodule
module phil237  = phil1 [p1=p237,  p2=p238,  p250=p236]  endmodule
module phil238  = phil1 [p1=p238,  p2=p239,  p250=p237]  endmodule
module phil239  = phil1 [p1=p239,  p2=p240,  p250=p238]  endmodule
module phil240  = phil1 [p1=p240,  p2=p241,  p250=p239]  endmodule
module phil241  = phil1 [p1=p241,  p2=p242,  p250=p240]  endmodule
module phil242  = phil1 [p1=p242,  p2=p243,  p250=p241]  endmodule
module phil243  = phil1 [p1=p243,  p2=p244,  p250=p242]  endmodule
module phil244  = phil1 [p1=p244,  p2=p245,  p250=p243]  endmodule
module phil245  = phil1 [p1=p245,  p2=p246,  p250=p244]  endmodule
module phil246  = phil1 [p1=p246,  p2=p247,  p250=p245]  endmodule
module phil247  = phil1 [p1=p247,  p2=p248,  p250=p246]  endmodule
module phil248  = phil1 [p1=p248,  p2=p249,  p250=p247]  endmodule
module phil249  = phil1 [p1=p249,  p2=p250,  p250=p248]  endmodule
module phil250 = phil1 [p1=p250, p2=p1,  p250=p249] endmodule
