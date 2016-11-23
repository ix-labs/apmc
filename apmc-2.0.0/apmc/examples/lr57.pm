probabilistic

const n=7;
const n_1=6;
const n_2=5;
const n_3=4;
formula can1 = !((c2=n) | (c3=n) | ((c2=n_1) & (c3=n_1)) | (c4=n) | ((c2=n_1) & (c4=n_1)) | ((c3=n_1) & (c4=n_1)) | ((c2=n_2) & (c3=n_2) & (c4=n_2)) | (c5=n) | ((c2=n_1) & (c5=n_1)) | ((c3=n_1) & (c5=n_1)) | ((c2=n_2) & (c3=n_2) & (c5=n_2)) | ((c4=n_1) & (c5=n_1)) | ((c2=n_2) & (c4=n_2) & (c5=n_2)) | ((c3=n_2) & (c4=n_2) & (c5=n_2)) | ((c2=n_3) & (c3=n_3) & (c4=n_3) & (c5=n_3)));
formula can2 = !((c1=n) | (c3=n) | ((c1=n_1) & (c3=n_1)) | (c4=n) | ((c1=n_1) & (c4=n_1)) | ((c3=n_1) & (c4=n_1)) | ((c1=n_2) & (c3=n_2) & (c4=n_2)) | (c5=n) | ((c1=n_1) & (c5=n_1)) | ((c3=n_1) & (c5=n_1)) | ((c1=n_2) & (c3=n_2) & (c5=n_2)) | ((c4=n_1) & (c5=n_1)) | ((c1=n_2) & (c4=n_2) & (c5=n_2)) | ((c3=n_2) & (c4=n_2) & (c5=n_2)) | ((c1=n_3) & (c3=n_3) & (c4=n_3) & (c5=n_3)));
formula can3 = !((c1=n) | (c2=n) | ((c1=n_1) & (c2=n_1)) | (c4=n) | ((c1=n_1) & (c4=n_1)) | ((c2=n_1) & (c4=n_1)) | ((c1=n_2) & (c2=n_2) & (c4=n_2)) | (c5=n) | ((c1=n_1) & (c5=n_1)) | ((c2=n_1) & (c5=n_1)) | ((c1=n_2) & (c2=n_2) & (c5=n_2)) | ((c4=n_1) & (c5=n_1)) | ((c1=n_2) & (c4=n_2) & (c5=n_2)) | ((c2=n_2) & (c4=n_2) & (c5=n_2)) | ((c1=n_3) & (c2=n_3) & (c4=n_3) & (c5=n_3)));
formula can4 = !((c1=n) | (c2=n) | ((c1=n_1) & (c2=n_1)) | (c3=n) | ((c1=n_1) & (c3=n_1)) | ((c2=n_1) & (c3=n_1)) | ((c1=n_2) & (c2=n_2) & (c3=n_2)) | (c5=n) | ((c1=n_1) & (c5=n_1)) | ((c2=n_1) & (c5=n_1)) | ((c1=n_2) & (c2=n_2) & (c5=n_2)) | ((c3=n_1) & (c5=n_1)) | ((c1=n_2) & (c3=n_2) & (c5=n_2)) | ((c2=n_2) & (c3=n_2) & (c5=n_2)) | ((c1=n_3) & (c2=n_3) & (c3=n_3) & (c5=n_3)));
formula can5 = !((c1=n) | (c2=n) | ((c1=n_1) & (c2=n_1)) | (c3=n) | ((c1=n_1) & (c3=n_1)) | ((c2=n_1) & (c3=n_1)) | ((c1=n_2) & (c2=n_2) & (c3=n_2)) | (c4=n) | ((c1=n_1) & (c4=n_1)) | ((c2=n_1) & (c4=n_1)) | ((c1=n_2) & (c2=n_2) & (c4=n_2)) | ((c3=n_1) & (c4=n_1)) | ((c1=n_2) & (c3=n_2) & (c4=n_2)) | ((c2=n_2) & (c3=n_2) & (c4=n_2)) | ((c1=n_3) & (c2=n_3) & (c3=n_3) & (c4=n_3)));
formula count1 = (p1!=13) & (p1!=0);
formula ncount1 = (p1=13) | (p1=0);
formula count2 = (p2!=13) & (p2!=0);
formula ncount2 = (p2=13) | (p2=0);
formula count3 = (p3!=13) & (p3!=0);
formula ncount3 = (p3=13) | (p3=0);
formula count4 = (p4!=13) & (p4!=0);
formula ncount4 = (p4=13) | (p4=0);
formula count5 = (p5!=13) & (p5!=0);
formula ncount5 = (p5=13) | (p5=0);

module counter

c1 : [0..n];
c2 : [0..n];
c3 : [0..n];
c4 : [0..n];
c5 : [0..n];
	[s1] can1  & ncount2  & ncount3  & ncount4  & ncount5  -> (c1'=0);
	[s1] can1  & count2  & ncount3  & ncount4  & ncount5  -> (c1'=0) & (c2'=c2+1);
	[s1] can1  & ncount2  & count3  & ncount4  & ncount5  -> (c1'=0) & (c3'=c3+1);
	[s1] can1  & count2  & count3  & ncount4  & ncount5  -> (c1'=0) & (c2'=c2+1) & (c3'=c3+1);
	[s1] can1  & ncount2  & ncount3  & count4  & ncount5  -> (c1'=0) & (c4'=c4+1);
	[s1] can1  & count2  & ncount3  & count4  & ncount5  -> (c1'=0) & (c2'=c2+1) & (c4'=c4+1);
	[s1] can1  & ncount2  & count3  & count4  & ncount5  -> (c1'=0) & (c3'=c3+1) & (c4'=c4+1);
	[s1] can1  & count2  & count3  & count4  & ncount5  -> (c1'=0) & (c2'=c2+1) & (c3'=c3+1) & (c4'=c4+1);
	[s1] can1  & ncount2  & ncount3  & ncount4  & count5  -> (c1'=0) & (c5'=c5+1);
	[s1] can1  & count2  & ncount3  & ncount4  & count5  -> (c1'=0) & (c2'=c2+1) & (c5'=c5+1);
	[s1] can1  & ncount2  & count3  & ncount4  & count5  -> (c1'=0) & (c3'=c3+1) & (c5'=c5+1);
	[s1] can1  & count2  & count3  & ncount4  & count5  -> (c1'=0) & (c2'=c2+1) & (c3'=c3+1) & (c5'=c5+1);
	[s1] can1  & ncount2  & ncount3  & count4  & count5  -> (c1'=0) & (c4'=c4+1) & (c5'=c5+1);
	[s1] can1  & count2  & ncount3  & count4  & count5  -> (c1'=0) & (c2'=c2+1) & (c4'=c4+1) & (c5'=c5+1);
	[s1] can1  & ncount2  & count3  & count4  & count5  -> (c1'=0) & (c3'=c3+1) & (c4'=c4+1) & (c5'=c5+1);
	[s1] can1  & count2  & count3  & count4  & count5  -> (c1'=0) & (c2'=c2+1) & (c3'=c3+1) & (c4'=c4+1) & (c5'=c5+1);
	[s2] can2  & ncount1  & ncount3  & ncount4  & ncount5  -> (c2'=0);
	[s2] can2  & count1  & ncount3  & ncount4  & ncount5  -> (c2'=0) & (c1'=c1+1);
	[s2] can2  & ncount1  & count3  & ncount4  & ncount5  -> (c2'=0) & (c3'=c3+1);
	[s2] can2  & count1  & count3  & ncount4  & ncount5  -> (c2'=0) & (c1'=c1+1) & (c3'=c3+1);
	[s2] can2  & ncount1  & ncount3  & count4  & ncount5  -> (c2'=0) & (c4'=c4+1);
	[s2] can2  & count1  & ncount3  & count4  & ncount5  -> (c2'=0) & (c1'=c1+1) & (c4'=c4+1);
	[s2] can2  & ncount1  & count3  & count4  & ncount5  -> (c2'=0) & (c3'=c3+1) & (c4'=c4+1);
	[s2] can2  & count1  & count3  & count4  & ncount5  -> (c2'=0) & (c1'=c1+1) & (c3'=c3+1) & (c4'=c4+1);
	[s2] can2  & ncount1  & ncount3  & ncount4  & count5  -> (c2'=0) & (c5'=c5+1);
	[s2] can2  & count1  & ncount3  & ncount4  & count5  -> (c2'=0) & (c1'=c1+1) & (c5'=c5+1);
	[s2] can2  & ncount1  & count3  & ncount4  & count5  -> (c2'=0) & (c3'=c3+1) & (c5'=c5+1);
	[s2] can2  & count1  & count3  & ncount4  & count5  -> (c2'=0) & (c1'=c1+1) & (c3'=c3+1) & (c5'=c5+1);
	[s2] can2  & ncount1  & ncount3  & count4  & count5  -> (c2'=0) & (c4'=c4+1) & (c5'=c5+1);
	[s2] can2  & count1  & ncount3  & count4  & count5  -> (c2'=0) & (c1'=c1+1) & (c4'=c4+1) & (c5'=c5+1);
	[s2] can2  & ncount1  & count3  & count4  & count5  -> (c2'=0) & (c3'=c3+1) & (c4'=c4+1) & (c5'=c5+1);
	[s2] can2  & count1  & count3  & count4  & count5  -> (c2'=0) & (c1'=c1+1) & (c3'=c3+1) & (c4'=c4+1) & (c5'=c5+1);
	[s3] can3  & ncount1  & ncount2  & ncount4  & ncount5  -> (c3'=0);
	[s3] can3  & count1  & ncount2  & ncount4  & ncount5  -> (c3'=0) & (c1'=c1+1);
	[s3] can3  & ncount1  & count2  & ncount4  & ncount5  -> (c3'=0) & (c2'=c2+1);
	[s3] can3  & count1  & count2  & ncount4  & ncount5  -> (c3'=0) & (c1'=c1+1) & (c2'=c2+1);
	[s3] can3  & ncount1  & ncount2  & count4  & ncount5  -> (c3'=0) & (c4'=c4+1);
	[s3] can3  & count1  & ncount2  & count4  & ncount5  -> (c3'=0) & (c1'=c1+1) & (c4'=c4+1);
	[s3] can3  & ncount1  & count2  & count4  & ncount5  -> (c3'=0) & (c2'=c2+1) & (c4'=c4+1);
	[s3] can3  & count1  & count2  & count4  & ncount5  -> (c3'=0) & (c1'=c1+1) & (c2'=c2+1) & (c4'=c4+1);
	[s3] can3  & ncount1  & ncount2  & ncount4  & count5  -> (c3'=0) & (c5'=c5+1);
	[s3] can3  & count1  & ncount2  & ncount4  & count5  -> (c3'=0) & (c1'=c1+1) & (c5'=c5+1);
	[s3] can3  & ncount1  & count2  & ncount4  & count5  -> (c3'=0) & (c2'=c2+1) & (c5'=c5+1);
	[s3] can3  & count1  & count2  & ncount4  & count5  -> (c3'=0) & (c1'=c1+1) & (c2'=c2+1) & (c5'=c5+1);
	[s3] can3  & ncount1  & ncount2  & count4  & count5  -> (c3'=0) & (c4'=c4+1) & (c5'=c5+1);
	[s3] can3  & count1  & ncount2  & count4  & count5  -> (c3'=0) & (c1'=c1+1) & (c4'=c4+1) & (c5'=c5+1);
	[s3] can3  & ncount1  & count2  & count4  & count5  -> (c3'=0) & (c2'=c2+1) & (c4'=c4+1) & (c5'=c5+1);
	[s3] can3  & count1  & count2  & count4  & count5  -> (c3'=0) & (c1'=c1+1) & (c2'=c2+1) & (c4'=c4+1) & (c5'=c5+1);
	[s4] can4  & ncount1  & ncount2  & ncount3  & ncount5  -> (c4'=0);
	[s4] can4  & count1  & ncount2  & ncount3  & ncount5  -> (c4'=0) & (c1'=c1+1);
	[s4] can4  & ncount1  & count2  & ncount3  & ncount5  -> (c4'=0) & (c2'=c2+1);
	[s4] can4  & count1  & count2  & ncount3  & ncount5  -> (c4'=0) & (c1'=c1+1) & (c2'=c2+1);
	[s4] can4  & ncount1  & ncount2  & count3  & ncount5  -> (c4'=0) & (c3'=c3+1);
	[s4] can4  & count1  & ncount2  & count3  & ncount5  -> (c4'=0) & (c1'=c1+1) & (c3'=c3+1);
	[s4] can4  & ncount1  & count2  & count3  & ncount5  -> (c4'=0) & (c2'=c2+1) & (c3'=c3+1);
	[s4] can4  & count1  & count2  & count3  & ncount5  -> (c4'=0) & (c1'=c1+1) & (c2'=c2+1) & (c3'=c3+1);
	[s4] can4  & ncount1  & ncount2  & ncount3  & count5  -> (c4'=0) & (c5'=c5+1);
	[s4] can4  & count1  & ncount2  & ncount3  & count5  -> (c4'=0) & (c1'=c1+1) & (c5'=c5+1);
	[s4] can4  & ncount1  & count2  & ncount3  & count5  -> (c4'=0) & (c2'=c2+1) & (c5'=c5+1);
	[s4] can4  & count1  & count2  & ncount3  & count5  -> (c4'=0) & (c1'=c1+1) & (c2'=c2+1) & (c5'=c5+1);
	[s4] can4  & ncount1  & ncount2  & count3  & count5  -> (c4'=0) & (c3'=c3+1) & (c5'=c5+1);
	[s4] can4  & count1  & ncount2  & count3  & count5  -> (c4'=0) & (c1'=c1+1) & (c3'=c3+1) & (c5'=c5+1);
	[s4] can4  & ncount1  & count2  & count3  & count5  -> (c4'=0) & (c2'=c2+1) & (c3'=c3+1) & (c5'=c5+1);
	[s4] can4  & count1  & count2  & count3  & count5  -> (c4'=0) & (c1'=c1+1) & (c2'=c2+1) & (c3'=c3+1) & (c5'=c5+1);
	[s5] can5  & ncount1  & ncount2  & ncount3  & ncount4  -> (c5'=0);
	[s5] can5  & count1  & ncount2  & ncount3  & ncount4  -> (c5'=0) & (c1'=c1+1);
	[s5] can5  & ncount1  & count2  & ncount3  & ncount4  -> (c5'=0) & (c2'=c2+1);
	[s5] can5  & count1  & count2  & ncount3  & ncount4  -> (c5'=0) & (c1'=c1+1) & (c2'=c2+1);
	[s5] can5  & ncount1  & ncount2  & count3  & ncount4  -> (c5'=0) & (c3'=c3+1);
	[s5] can5  & count1  & ncount2  & count3  & ncount4  -> (c5'=0) & (c1'=c1+1) & (c3'=c3+1);
	[s5] can5  & ncount1  & count2  & count3  & ncount4  -> (c5'=0) & (c2'=c2+1) & (c3'=c3+1);
	[s5] can5  & count1  & count2  & count3  & ncount4  -> (c5'=0) & (c1'=c1+1) & (c2'=c2+1) & (c3'=c3+1);
	[s5] can5  & ncount1  & ncount2  & ncount3  & count4  -> (c5'=0) & (c4'=c4+1);
	[s5] can5  & count1  & ncount2  & ncount3  & count4  -> (c5'=0) & (c1'=c1+1) & (c4'=c4+1);
	[s5] can5  & ncount1  & count2  & ncount3  & count4  -> (c5'=0) & (c2'=c2+1) & (c4'=c4+1);
	[s5] can5  & count1  & count2  & ncount3  & count4  -> (c5'=0) & (c1'=c1+1) & (c2'=c2+1) & (c4'=c4+1);
	[s5] can5  & ncount1  & ncount2  & count3  & count4  -> (c5'=0) & (c3'=c3+1) & (c4'=c4+1);
	[s5] can5  & count1  & ncount2  & count3  & count4  -> (c5'=0) & (c1'=c1+1) & (c3'=c3+1) & (c4'=c4+1);
	[s5] can5  & ncount1  & count2  & count3  & count4  -> (c5'=0) & (c2'=c2+1) & (c3'=c3+1) & (c4'=c4+1);
	[s5] can5  & count1  & count2  & count3  & count4  -> (c5'=0) & (c1'=c1+1) & (c2'=c2+1) & (c3'=c3+1) & (c4'=c4+1);

endmodule

formula lfree = (p2=0..4,6,11,13);
formula rfree = (p5=0..3,5,7,12,13);


module phil1

p1 : [0..13];
[s1] (p1=0) -> 0.2 : (p1'=0) + 0.8 : (p1'=1);
[s1] (p1=1) -> 0.5 : (p1'=2) + 0.5 : (p1'=3);
[s1] (p1=2) &  lfree -> (p1'=4);
[s1] (p1=2) & !lfree -> (p1'=2);
[s1] (p1=3) &  rfree -> (p1'=5);
[s1] (p1=3) & !rfree -> (p1'=3);
[s1] (p1=4) &  rfree -> (p1'=8);
[s1] (p1=4) & !rfree -> (p1'=6);
[s1] (p1=5) &  lfree -> (p1'=8);
[s1] (p1=5) & !lfree -> (p1'=7);
[s1] (p1=6)  -> (p1'=1);
[s1] (p1=7)  -> (p1'=1);
[s1] (p1=8)  -> (p1'=9);
[s1] (p1=9)  -> (p1'=10);
[s1] (p1=10) ->  0.5 : (p1'=11) + 0.5: (p1'=12);
[s1] (p1=11) -> (p1'=13);
[s1] (p1=12) -> (p1'=13);
[s1] (p1=13) ->  0.5 : (p1'=0) + 0.5 : (p1'=13);

endmodule

module phil2=phil1 [p1=p2, p2=p3, p3=p4, p4=p5, s1=s2] endmodule
module phil3=phil1 [p1=p3, p2=p4, p3=p5, p4=p1, s1=s3] endmodule
module phil4=phil1 [p1=p4, p2=p5, p3=p1, p4=p2, s1=s4] endmodule
module phil5=phil1 [p1=p5, p2=p1, p3=p2, p4=p3, s1=s5] endmodule
