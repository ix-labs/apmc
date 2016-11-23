// randomized dining philosophers [PZ86]
// dxp/gxn 12/12/99
probabilistic
// atomic formulae
// left fork free and right fork free resp
formula lfree = p2=0..4,6,10;
formula rfree = p325=0..3,5,7;
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
module phil2  = phil1 [p1=p2,  p2=p3,  p325=p1]  endmodule
module phil3  = phil1 [p1=p3,  p2=p4,  p325=p2]  endmodule
module phil4  = phil1 [p1=p4,  p2=p5,  p325=p3]  endmodule
module phil5  = phil1 [p1=p5,  p2=p6,  p325=p4]  endmodule
module phil6  = phil1 [p1=p6,  p2=p7,  p325=p5]  endmodule
module phil7  = phil1 [p1=p7,  p2=p8,  p325=p6]  endmodule
module phil8  = phil1 [p1=p8,  p2=p9,  p325=p7]  endmodule
module phil9  = phil1 [p1=p9,  p2=p10,  p325=p8]  endmodule
module phil10  = phil1 [p1=p10,  p2=p11,  p325=p9]  endmodule
module phil11  = phil1 [p1=p11,  p2=p12,  p325=p10]  endmodule
module phil12  = phil1 [p1=p12,  p2=p13,  p325=p11]  endmodule
module phil13  = phil1 [p1=p13,  p2=p14,  p325=p12]  endmodule
module phil14  = phil1 [p1=p14,  p2=p15,  p325=p13]  endmodule
module phil15  = phil1 [p1=p15,  p2=p16,  p325=p14]  endmodule
module phil16  = phil1 [p1=p16,  p2=p17,  p325=p15]  endmodule
module phil17  = phil1 [p1=p17,  p2=p18,  p325=p16]  endmodule
module phil18  = phil1 [p1=p18,  p2=p19,  p325=p17]  endmodule
module phil19  = phil1 [p1=p19,  p2=p20,  p325=p18]  endmodule
module phil20  = phil1 [p1=p20,  p2=p21,  p325=p19]  endmodule
module phil21  = phil1 [p1=p21,  p2=p22,  p325=p20]  endmodule
module phil22  = phil1 [p1=p22,  p2=p23,  p325=p21]  endmodule
module phil23  = phil1 [p1=p23,  p2=p24,  p325=p22]  endmodule
module phil24  = phil1 [p1=p24,  p2=p25,  p325=p23]  endmodule
module phil25  = phil1 [p1=p25,  p2=p26,  p325=p24]  endmodule
module phil26  = phil1 [p1=p26,  p2=p27,  p325=p25]  endmodule
module phil27  = phil1 [p1=p27,  p2=p28,  p325=p26]  endmodule
module phil28  = phil1 [p1=p28,  p2=p29,  p325=p27]  endmodule
module phil29  = phil1 [p1=p29,  p2=p30,  p325=p28]  endmodule
module phil30  = phil1 [p1=p30,  p2=p31,  p325=p29]  endmodule
module phil31  = phil1 [p1=p31,  p2=p32,  p325=p30]  endmodule
module phil32  = phil1 [p1=p32,  p2=p33,  p325=p31]  endmodule
module phil33  = phil1 [p1=p33,  p2=p34,  p325=p32]  endmodule
module phil34  = phil1 [p1=p34,  p2=p35,  p325=p33]  endmodule
module phil35  = phil1 [p1=p35,  p2=p36,  p325=p34]  endmodule
module phil36  = phil1 [p1=p36,  p2=p37,  p325=p35]  endmodule
module phil37  = phil1 [p1=p37,  p2=p38,  p325=p36]  endmodule
module phil38  = phil1 [p1=p38,  p2=p39,  p325=p37]  endmodule
module phil39  = phil1 [p1=p39,  p2=p40,  p325=p38]  endmodule
module phil40  = phil1 [p1=p40,  p2=p41,  p325=p39]  endmodule
module phil41  = phil1 [p1=p41,  p2=p42,  p325=p40]  endmodule
module phil42  = phil1 [p1=p42,  p2=p43,  p325=p41]  endmodule
module phil43  = phil1 [p1=p43,  p2=p44,  p325=p42]  endmodule
module phil44  = phil1 [p1=p44,  p2=p45,  p325=p43]  endmodule
module phil45  = phil1 [p1=p45,  p2=p46,  p325=p44]  endmodule
module phil46  = phil1 [p1=p46,  p2=p47,  p325=p45]  endmodule
module phil47  = phil1 [p1=p47,  p2=p48,  p325=p46]  endmodule
module phil48  = phil1 [p1=p48,  p2=p49,  p325=p47]  endmodule
module phil49  = phil1 [p1=p49,  p2=p50,  p325=p48]  endmodule
module phil50  = phil1 [p1=p50,  p2=p51,  p325=p49]  endmodule
module phil51  = phil1 [p1=p51,  p2=p52,  p325=p50]  endmodule
module phil52  = phil1 [p1=p52,  p2=p53,  p325=p51]  endmodule
module phil53  = phil1 [p1=p53,  p2=p54,  p325=p52]  endmodule
module phil54  = phil1 [p1=p54,  p2=p55,  p325=p53]  endmodule
module phil55  = phil1 [p1=p55,  p2=p56,  p325=p54]  endmodule
module phil56  = phil1 [p1=p56,  p2=p57,  p325=p55]  endmodule
module phil57  = phil1 [p1=p57,  p2=p58,  p325=p56]  endmodule
module phil58  = phil1 [p1=p58,  p2=p59,  p325=p57]  endmodule
module phil59  = phil1 [p1=p59,  p2=p60,  p325=p58]  endmodule
module phil60  = phil1 [p1=p60,  p2=p61,  p325=p59]  endmodule
module phil61  = phil1 [p1=p61,  p2=p62,  p325=p60]  endmodule
module phil62  = phil1 [p1=p62,  p2=p63,  p325=p61]  endmodule
module phil63  = phil1 [p1=p63,  p2=p64,  p325=p62]  endmodule
module phil64  = phil1 [p1=p64,  p2=p65,  p325=p63]  endmodule
module phil65  = phil1 [p1=p65,  p2=p66,  p325=p64]  endmodule
module phil66  = phil1 [p1=p66,  p2=p67,  p325=p65]  endmodule
module phil67  = phil1 [p1=p67,  p2=p68,  p325=p66]  endmodule
module phil68  = phil1 [p1=p68,  p2=p69,  p325=p67]  endmodule
module phil69  = phil1 [p1=p69,  p2=p70,  p325=p68]  endmodule
module phil70  = phil1 [p1=p70,  p2=p71,  p325=p69]  endmodule
module phil71  = phil1 [p1=p71,  p2=p72,  p325=p70]  endmodule
module phil72  = phil1 [p1=p72,  p2=p73,  p325=p71]  endmodule
module phil73  = phil1 [p1=p73,  p2=p74,  p325=p72]  endmodule
module phil74  = phil1 [p1=p74,  p2=p75,  p325=p73]  endmodule
module phil75  = phil1 [p1=p75,  p2=p76,  p325=p74]  endmodule
module phil76  = phil1 [p1=p76,  p2=p77,  p325=p75]  endmodule
module phil77  = phil1 [p1=p77,  p2=p78,  p325=p76]  endmodule
module phil78  = phil1 [p1=p78,  p2=p79,  p325=p77]  endmodule
module phil79  = phil1 [p1=p79,  p2=p80,  p325=p78]  endmodule
module phil80  = phil1 [p1=p80,  p2=p81,  p325=p79]  endmodule
module phil81  = phil1 [p1=p81,  p2=p82,  p325=p80]  endmodule
module phil82  = phil1 [p1=p82,  p2=p83,  p325=p81]  endmodule
module phil83  = phil1 [p1=p83,  p2=p84,  p325=p82]  endmodule
module phil84  = phil1 [p1=p84,  p2=p85,  p325=p83]  endmodule
module phil85  = phil1 [p1=p85,  p2=p86,  p325=p84]  endmodule
module phil86  = phil1 [p1=p86,  p2=p87,  p325=p85]  endmodule
module phil87  = phil1 [p1=p87,  p2=p88,  p325=p86]  endmodule
module phil88  = phil1 [p1=p88,  p2=p89,  p325=p87]  endmodule
module phil89  = phil1 [p1=p89,  p2=p90,  p325=p88]  endmodule
module phil90  = phil1 [p1=p90,  p2=p91,  p325=p89]  endmodule
module phil91  = phil1 [p1=p91,  p2=p92,  p325=p90]  endmodule
module phil92  = phil1 [p1=p92,  p2=p93,  p325=p91]  endmodule
module phil93  = phil1 [p1=p93,  p2=p94,  p325=p92]  endmodule
module phil94  = phil1 [p1=p94,  p2=p95,  p325=p93]  endmodule
module phil95  = phil1 [p1=p95,  p2=p96,  p325=p94]  endmodule
module phil96  = phil1 [p1=p96,  p2=p97,  p325=p95]  endmodule
module phil97  = phil1 [p1=p97,  p2=p98,  p325=p96]  endmodule
module phil98  = phil1 [p1=p98,  p2=p99,  p325=p97]  endmodule
module phil99  = phil1 [p1=p99,  p2=p100,  p325=p98]  endmodule
module phil100  = phil1 [p1=p100,  p2=p101,  p325=p99]  endmodule
module phil101  = phil1 [p1=p101,  p2=p102,  p325=p100]  endmodule
module phil102  = phil1 [p1=p102,  p2=p103,  p325=p101]  endmodule
module phil103  = phil1 [p1=p103,  p2=p104,  p325=p102]  endmodule
module phil104  = phil1 [p1=p104,  p2=p105,  p325=p103]  endmodule
module phil105  = phil1 [p1=p105,  p2=p106,  p325=p104]  endmodule
module phil106  = phil1 [p1=p106,  p2=p107,  p325=p105]  endmodule
module phil107  = phil1 [p1=p107,  p2=p108,  p325=p106]  endmodule
module phil108  = phil1 [p1=p108,  p2=p109,  p325=p107]  endmodule
module phil109  = phil1 [p1=p109,  p2=p110,  p325=p108]  endmodule
module phil110  = phil1 [p1=p110,  p2=p111,  p325=p109]  endmodule
module phil111  = phil1 [p1=p111,  p2=p112,  p325=p110]  endmodule
module phil112  = phil1 [p1=p112,  p2=p113,  p325=p111]  endmodule
module phil113  = phil1 [p1=p113,  p2=p114,  p325=p112]  endmodule
module phil114  = phil1 [p1=p114,  p2=p115,  p325=p113]  endmodule
module phil115  = phil1 [p1=p115,  p2=p116,  p325=p114]  endmodule
module phil116  = phil1 [p1=p116,  p2=p117,  p325=p115]  endmodule
module phil117  = phil1 [p1=p117,  p2=p118,  p325=p116]  endmodule
module phil118  = phil1 [p1=p118,  p2=p119,  p325=p117]  endmodule
module phil119  = phil1 [p1=p119,  p2=p120,  p325=p118]  endmodule
module phil120  = phil1 [p1=p120,  p2=p121,  p325=p119]  endmodule
module phil121  = phil1 [p1=p121,  p2=p122,  p325=p120]  endmodule
module phil122  = phil1 [p1=p122,  p2=p123,  p325=p121]  endmodule
module phil123  = phil1 [p1=p123,  p2=p124,  p325=p122]  endmodule
module phil124  = phil1 [p1=p124,  p2=p125,  p325=p123]  endmodule
module phil125  = phil1 [p1=p125,  p2=p126,  p325=p124]  endmodule
module phil126  = phil1 [p1=p126,  p2=p127,  p325=p125]  endmodule
module phil127  = phil1 [p1=p127,  p2=p128,  p325=p126]  endmodule
module phil128  = phil1 [p1=p128,  p2=p129,  p325=p127]  endmodule
module phil129  = phil1 [p1=p129,  p2=p130,  p325=p128]  endmodule
module phil130  = phil1 [p1=p130,  p2=p131,  p325=p129]  endmodule
module phil131  = phil1 [p1=p131,  p2=p132,  p325=p130]  endmodule
module phil132  = phil1 [p1=p132,  p2=p133,  p325=p131]  endmodule
module phil133  = phil1 [p1=p133,  p2=p134,  p325=p132]  endmodule
module phil134  = phil1 [p1=p134,  p2=p135,  p325=p133]  endmodule
module phil135  = phil1 [p1=p135,  p2=p136,  p325=p134]  endmodule
module phil136  = phil1 [p1=p136,  p2=p137,  p325=p135]  endmodule
module phil137  = phil1 [p1=p137,  p2=p138,  p325=p136]  endmodule
module phil138  = phil1 [p1=p138,  p2=p139,  p325=p137]  endmodule
module phil139  = phil1 [p1=p139,  p2=p140,  p325=p138]  endmodule
module phil140  = phil1 [p1=p140,  p2=p141,  p325=p139]  endmodule
module phil141  = phil1 [p1=p141,  p2=p142,  p325=p140]  endmodule
module phil142  = phil1 [p1=p142,  p2=p143,  p325=p141]  endmodule
module phil143  = phil1 [p1=p143,  p2=p144,  p325=p142]  endmodule
module phil144  = phil1 [p1=p144,  p2=p145,  p325=p143]  endmodule
module phil145  = phil1 [p1=p145,  p2=p146,  p325=p144]  endmodule
module phil146  = phil1 [p1=p146,  p2=p147,  p325=p145]  endmodule
module phil147  = phil1 [p1=p147,  p2=p148,  p325=p146]  endmodule
module phil148  = phil1 [p1=p148,  p2=p149,  p325=p147]  endmodule
module phil149  = phil1 [p1=p149,  p2=p150,  p325=p148]  endmodule
module phil150  = phil1 [p1=p150,  p2=p151,  p325=p149]  endmodule
module phil151  = phil1 [p1=p151,  p2=p152,  p325=p150]  endmodule
module phil152  = phil1 [p1=p152,  p2=p153,  p325=p151]  endmodule
module phil153  = phil1 [p1=p153,  p2=p154,  p325=p152]  endmodule
module phil154  = phil1 [p1=p154,  p2=p155,  p325=p153]  endmodule
module phil155  = phil1 [p1=p155,  p2=p156,  p325=p154]  endmodule
module phil156  = phil1 [p1=p156,  p2=p157,  p325=p155]  endmodule
module phil157  = phil1 [p1=p157,  p2=p158,  p325=p156]  endmodule
module phil158  = phil1 [p1=p158,  p2=p159,  p325=p157]  endmodule
module phil159  = phil1 [p1=p159,  p2=p160,  p325=p158]  endmodule
module phil160  = phil1 [p1=p160,  p2=p161,  p325=p159]  endmodule
module phil161  = phil1 [p1=p161,  p2=p162,  p325=p160]  endmodule
module phil162  = phil1 [p1=p162,  p2=p163,  p325=p161]  endmodule
module phil163  = phil1 [p1=p163,  p2=p164,  p325=p162]  endmodule
module phil164  = phil1 [p1=p164,  p2=p165,  p325=p163]  endmodule
module phil165  = phil1 [p1=p165,  p2=p166,  p325=p164]  endmodule
module phil166  = phil1 [p1=p166,  p2=p167,  p325=p165]  endmodule
module phil167  = phil1 [p1=p167,  p2=p168,  p325=p166]  endmodule
module phil168  = phil1 [p1=p168,  p2=p169,  p325=p167]  endmodule
module phil169  = phil1 [p1=p169,  p2=p170,  p325=p168]  endmodule
module phil170  = phil1 [p1=p170,  p2=p171,  p325=p169]  endmodule
module phil171  = phil1 [p1=p171,  p2=p172,  p325=p170]  endmodule
module phil172  = phil1 [p1=p172,  p2=p173,  p325=p171]  endmodule
module phil173  = phil1 [p1=p173,  p2=p174,  p325=p172]  endmodule
module phil174  = phil1 [p1=p174,  p2=p175,  p325=p173]  endmodule
module phil175  = phil1 [p1=p175,  p2=p176,  p325=p174]  endmodule
module phil176  = phil1 [p1=p176,  p2=p177,  p325=p175]  endmodule
module phil177  = phil1 [p1=p177,  p2=p178,  p325=p176]  endmodule
module phil178  = phil1 [p1=p178,  p2=p179,  p325=p177]  endmodule
module phil179  = phil1 [p1=p179,  p2=p180,  p325=p178]  endmodule
module phil180  = phil1 [p1=p180,  p2=p181,  p325=p179]  endmodule
module phil181  = phil1 [p1=p181,  p2=p182,  p325=p180]  endmodule
module phil182  = phil1 [p1=p182,  p2=p183,  p325=p181]  endmodule
module phil183  = phil1 [p1=p183,  p2=p184,  p325=p182]  endmodule
module phil184  = phil1 [p1=p184,  p2=p185,  p325=p183]  endmodule
module phil185  = phil1 [p1=p185,  p2=p186,  p325=p184]  endmodule
module phil186  = phil1 [p1=p186,  p2=p187,  p325=p185]  endmodule
module phil187  = phil1 [p1=p187,  p2=p188,  p325=p186]  endmodule
module phil188  = phil1 [p1=p188,  p2=p189,  p325=p187]  endmodule
module phil189  = phil1 [p1=p189,  p2=p190,  p325=p188]  endmodule
module phil190  = phil1 [p1=p190,  p2=p191,  p325=p189]  endmodule
module phil191  = phil1 [p1=p191,  p2=p192,  p325=p190]  endmodule
module phil192  = phil1 [p1=p192,  p2=p193,  p325=p191]  endmodule
module phil193  = phil1 [p1=p193,  p2=p194,  p325=p192]  endmodule
module phil194  = phil1 [p1=p194,  p2=p195,  p325=p193]  endmodule
module phil195  = phil1 [p1=p195,  p2=p196,  p325=p194]  endmodule
module phil196  = phil1 [p1=p196,  p2=p197,  p325=p195]  endmodule
module phil197  = phil1 [p1=p197,  p2=p198,  p325=p196]  endmodule
module phil198  = phil1 [p1=p198,  p2=p199,  p325=p197]  endmodule
module phil199  = phil1 [p1=p199,  p2=p200,  p325=p198]  endmodule
module phil200  = phil1 [p1=p200,  p2=p201,  p325=p199]  endmodule
module phil201  = phil1 [p1=p201,  p2=p202,  p325=p200]  endmodule
module phil202  = phil1 [p1=p202,  p2=p203,  p325=p201]  endmodule
module phil203  = phil1 [p1=p203,  p2=p204,  p325=p202]  endmodule
module phil204  = phil1 [p1=p204,  p2=p205,  p325=p203]  endmodule
module phil205  = phil1 [p1=p205,  p2=p206,  p325=p204]  endmodule
module phil206  = phil1 [p1=p206,  p2=p207,  p325=p205]  endmodule
module phil207  = phil1 [p1=p207,  p2=p208,  p325=p206]  endmodule
module phil208  = phil1 [p1=p208,  p2=p209,  p325=p207]  endmodule
module phil209  = phil1 [p1=p209,  p2=p210,  p325=p208]  endmodule
module phil210  = phil1 [p1=p210,  p2=p211,  p325=p209]  endmodule
module phil211  = phil1 [p1=p211,  p2=p212,  p325=p210]  endmodule
module phil212  = phil1 [p1=p212,  p2=p213,  p325=p211]  endmodule
module phil213  = phil1 [p1=p213,  p2=p214,  p325=p212]  endmodule
module phil214  = phil1 [p1=p214,  p2=p215,  p325=p213]  endmodule
module phil215  = phil1 [p1=p215,  p2=p216,  p325=p214]  endmodule
module phil216  = phil1 [p1=p216,  p2=p217,  p325=p215]  endmodule
module phil217  = phil1 [p1=p217,  p2=p218,  p325=p216]  endmodule
module phil218  = phil1 [p1=p218,  p2=p219,  p325=p217]  endmodule
module phil219  = phil1 [p1=p219,  p2=p220,  p325=p218]  endmodule
module phil220  = phil1 [p1=p220,  p2=p221,  p325=p219]  endmodule
module phil221  = phil1 [p1=p221,  p2=p222,  p325=p220]  endmodule
module phil222  = phil1 [p1=p222,  p2=p223,  p325=p221]  endmodule
module phil223  = phil1 [p1=p223,  p2=p224,  p325=p222]  endmodule
module phil224  = phil1 [p1=p224,  p2=p225,  p325=p223]  endmodule
module phil225  = phil1 [p1=p225,  p2=p226,  p325=p224]  endmodule
module phil226  = phil1 [p1=p226,  p2=p227,  p325=p225]  endmodule
module phil227  = phil1 [p1=p227,  p2=p228,  p325=p226]  endmodule
module phil228  = phil1 [p1=p228,  p2=p229,  p325=p227]  endmodule
module phil229  = phil1 [p1=p229,  p2=p230,  p325=p228]  endmodule
module phil230  = phil1 [p1=p230,  p2=p231,  p325=p229]  endmodule
module phil231  = phil1 [p1=p231,  p2=p232,  p325=p230]  endmodule
module phil232  = phil1 [p1=p232,  p2=p233,  p325=p231]  endmodule
module phil233  = phil1 [p1=p233,  p2=p234,  p325=p232]  endmodule
module phil234  = phil1 [p1=p234,  p2=p235,  p325=p233]  endmodule
module phil235  = phil1 [p1=p235,  p2=p236,  p325=p234]  endmodule
module phil236  = phil1 [p1=p236,  p2=p237,  p325=p235]  endmodule
module phil237  = phil1 [p1=p237,  p2=p238,  p325=p236]  endmodule
module phil238  = phil1 [p1=p238,  p2=p239,  p325=p237]  endmodule
module phil239  = phil1 [p1=p239,  p2=p240,  p325=p238]  endmodule
module phil240  = phil1 [p1=p240,  p2=p241,  p325=p239]  endmodule
module phil241  = phil1 [p1=p241,  p2=p242,  p325=p240]  endmodule
module phil242  = phil1 [p1=p242,  p2=p243,  p325=p241]  endmodule
module phil243  = phil1 [p1=p243,  p2=p244,  p325=p242]  endmodule
module phil244  = phil1 [p1=p244,  p2=p245,  p325=p243]  endmodule
module phil245  = phil1 [p1=p245,  p2=p246,  p325=p244]  endmodule
module phil246  = phil1 [p1=p246,  p2=p247,  p325=p245]  endmodule
module phil247  = phil1 [p1=p247,  p2=p248,  p325=p246]  endmodule
module phil248  = phil1 [p1=p248,  p2=p249,  p325=p247]  endmodule
module phil249  = phil1 [p1=p249,  p2=p250,  p325=p248]  endmodule
module phil250  = phil1 [p1=p250,  p2=p251,  p325=p249]  endmodule
module phil251  = phil1 [p1=p251,  p2=p252,  p325=p250]  endmodule
module phil252  = phil1 [p1=p252,  p2=p253,  p325=p251]  endmodule
module phil253  = phil1 [p1=p253,  p2=p254,  p325=p252]  endmodule
module phil254  = phil1 [p1=p254,  p2=p255,  p325=p253]  endmodule
module phil255  = phil1 [p1=p255,  p2=p256,  p325=p254]  endmodule
module phil256  = phil1 [p1=p256,  p2=p257,  p325=p255]  endmodule
module phil257  = phil1 [p1=p257,  p2=p258,  p325=p256]  endmodule
module phil258  = phil1 [p1=p258,  p2=p259,  p325=p257]  endmodule
module phil259  = phil1 [p1=p259,  p2=p260,  p325=p258]  endmodule
module phil260  = phil1 [p1=p260,  p2=p261,  p325=p259]  endmodule
module phil261  = phil1 [p1=p261,  p2=p262,  p325=p260]  endmodule
module phil262  = phil1 [p1=p262,  p2=p263,  p325=p261]  endmodule
module phil263  = phil1 [p1=p263,  p2=p264,  p325=p262]  endmodule
module phil264  = phil1 [p1=p264,  p2=p265,  p325=p263]  endmodule
module phil265  = phil1 [p1=p265,  p2=p266,  p325=p264]  endmodule
module phil266  = phil1 [p1=p266,  p2=p267,  p325=p265]  endmodule
module phil267  = phil1 [p1=p267,  p2=p268,  p325=p266]  endmodule
module phil268  = phil1 [p1=p268,  p2=p269,  p325=p267]  endmodule
module phil269  = phil1 [p1=p269,  p2=p270,  p325=p268]  endmodule
module phil270  = phil1 [p1=p270,  p2=p271,  p325=p269]  endmodule
module phil271  = phil1 [p1=p271,  p2=p272,  p325=p270]  endmodule
module phil272  = phil1 [p1=p272,  p2=p273,  p325=p271]  endmodule
module phil273  = phil1 [p1=p273,  p2=p274,  p325=p272]  endmodule
module phil274  = phil1 [p1=p274,  p2=p275,  p325=p273]  endmodule
module phil275  = phil1 [p1=p275,  p2=p276,  p325=p274]  endmodule
module phil276  = phil1 [p1=p276,  p2=p277,  p325=p275]  endmodule
module phil277  = phil1 [p1=p277,  p2=p278,  p325=p276]  endmodule
module phil278  = phil1 [p1=p278,  p2=p279,  p325=p277]  endmodule
module phil279  = phil1 [p1=p279,  p2=p280,  p325=p278]  endmodule
module phil280  = phil1 [p1=p280,  p2=p281,  p325=p279]  endmodule
module phil281  = phil1 [p1=p281,  p2=p282,  p325=p280]  endmodule
module phil282  = phil1 [p1=p282,  p2=p283,  p325=p281]  endmodule
module phil283  = phil1 [p1=p283,  p2=p284,  p325=p282]  endmodule
module phil284  = phil1 [p1=p284,  p2=p285,  p325=p283]  endmodule
module phil285  = phil1 [p1=p285,  p2=p286,  p325=p284]  endmodule
module phil286  = phil1 [p1=p286,  p2=p287,  p325=p285]  endmodule
module phil287  = phil1 [p1=p287,  p2=p288,  p325=p286]  endmodule
module phil288  = phil1 [p1=p288,  p2=p289,  p325=p287]  endmodule
module phil289  = phil1 [p1=p289,  p2=p290,  p325=p288]  endmodule
module phil290  = phil1 [p1=p290,  p2=p291,  p325=p289]  endmodule
module phil291  = phil1 [p1=p291,  p2=p292,  p325=p290]  endmodule
module phil292  = phil1 [p1=p292,  p2=p293,  p325=p291]  endmodule
module phil293  = phil1 [p1=p293,  p2=p294,  p325=p292]  endmodule
module phil294  = phil1 [p1=p294,  p2=p295,  p325=p293]  endmodule
module phil295  = phil1 [p1=p295,  p2=p296,  p325=p294]  endmodule
module phil296  = phil1 [p1=p296,  p2=p297,  p325=p295]  endmodule
module phil297  = phil1 [p1=p297,  p2=p298,  p325=p296]  endmodule
module phil298  = phil1 [p1=p298,  p2=p299,  p325=p297]  endmodule
module phil299  = phil1 [p1=p299,  p2=p300,  p325=p298]  endmodule
module phil300  = phil1 [p1=p300,  p2=p301,  p325=p299]  endmodule
module phil301  = phil1 [p1=p301,  p2=p302,  p325=p300]  endmodule
module phil302  = phil1 [p1=p302,  p2=p303,  p325=p301]  endmodule
module phil303  = phil1 [p1=p303,  p2=p304,  p325=p302]  endmodule
module phil304  = phil1 [p1=p304,  p2=p305,  p325=p303]  endmodule
module phil305  = phil1 [p1=p305,  p2=p306,  p325=p304]  endmodule
module phil306  = phil1 [p1=p306,  p2=p307,  p325=p305]  endmodule
module phil307  = phil1 [p1=p307,  p2=p308,  p325=p306]  endmodule
module phil308  = phil1 [p1=p308,  p2=p309,  p325=p307]  endmodule
module phil309  = phil1 [p1=p309,  p2=p310,  p325=p308]  endmodule
module phil310  = phil1 [p1=p310,  p2=p311,  p325=p309]  endmodule
module phil311  = phil1 [p1=p311,  p2=p312,  p325=p310]  endmodule
module phil312  = phil1 [p1=p312,  p2=p313,  p325=p311]  endmodule
module phil313  = phil1 [p1=p313,  p2=p314,  p325=p312]  endmodule
module phil314  = phil1 [p1=p314,  p2=p315,  p325=p313]  endmodule
module phil315  = phil1 [p1=p315,  p2=p316,  p325=p314]  endmodule
module phil316  = phil1 [p1=p316,  p2=p317,  p325=p315]  endmodule
module phil317  = phil1 [p1=p317,  p2=p318,  p325=p316]  endmodule
module phil318  = phil1 [p1=p318,  p2=p319,  p325=p317]  endmodule
module phil319  = phil1 [p1=p319,  p2=p320,  p325=p318]  endmodule
module phil320  = phil1 [p1=p320,  p2=p321,  p325=p319]  endmodule
module phil321  = phil1 [p1=p321,  p2=p322,  p325=p320]  endmodule
module phil322  = phil1 [p1=p322,  p2=p323,  p325=p321]  endmodule
module phil323  = phil1 [p1=p323,  p2=p324,  p325=p322]  endmodule
module phil324  = phil1 [p1=p324,  p2=p325,  p325=p323]  endmodule
module phil325 = phil1 [p1=p325, p2=p1,  p325=p324] endmodule
