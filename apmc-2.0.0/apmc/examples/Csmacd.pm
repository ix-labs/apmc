dtmc

//Protocole Csma-cd

//constantes de temps

const lambda=780;  //longueur d'un message
const sigma=24;  //temps de propagation d'un message
const tempsmax=1400;
const timeMax=1023;
 
//nondeterministic

module Channel

//etats

c1 : [0..2] init 0;
c2 : [0..2] init 0;

//0 rien n'est envoyé
//1 un message est correctement envoyé
//2 le message est perdu

//Un seul message est envoyé
//Le sender a attendu sigma unites de temps avant de lancer ca.

[send1] (c1=0) & (c2=0) ->  c1'=1 ;
[send2] (c2=0) & (c1=0) ->  c2'=1 ;

//On envoie un message mais le canal est occupé

[send1] (c1=0) & (c2>0) ->  (c1'=2) ;
[send2] (c2=0) & (c1>0) ->  (c2'=2) ;

//On verifie que notre message est passe
[verify1] (c1=1) & (c2=2) -> (c1'=2) ;
[verify2] (c1=2) & (c2=1) -> (c2'=2) ;
[verify1] (c1=1) & (c2=0) -> (c1'=1) ;
[verify2] (c1=0) & (c2=1) -> (c2'=1) ;

//Un message se termine

[finish1] (c1>0) -> (c1'=0) ;
[finish2] (c2>0) -> (c2'=0) ;

endmodule

//Le canal est occupé
formula busy = (c1>0) | (c2>0) ;
//le canal est libre
formula free = (c1=0) & (c2=0) ;
//le canal est brouillé
formula garbled =  (c1=2) | (c2=2) ;
//Un module pour modéliser le temps discret qui se synchronisera avec les actions labellisées time

module temps

t : [0..tempsmax] init 0;

[time] t<tempsmax -> t'=t+1;

endmodule

module Sender1

//horloges du sender1

h1 : [0..lambda] init 0;

//temps aléatoire d'attente

alea1 : [0..timeMax] init 0;

//Nombres de collisions du sender1

col1 : [0..10] init 0;

//états du sender1

s1 : [0..9] init 0;

//0: Initialisation
//1: envie d'envoyer un message
//2: Envoi du message période d'attente 1
//3: Envoi du message période d'attente 2
//4: test au bout de 2sigma
//5: Envoi du message, sur qu'il passera
//6: Collision détectée
//7: Calcul du temps aléatoire
//8: Message envoyé correctement

//variables servant à faire le calcul du temps d'attente aléatoire

nbc1 : [0..10] init 0;

calcul1 : [0..1] init 0;

n1 : [0..1] init 0;
n2 : [0..1] init 0;
n3 : [0..1] init 0;
n4 : [0..1] init 0;
n5 : [0..1] init 0;
n6 : [0..1] init 0;
n7 : [0..1] init 0;
n8 : [0..1] init 0;
n9 : [0..1] init 0;
n10 : [0..1] init 0;

[time] (s1=0) -> 0.5 : (s1'=1) + 0.5 : (s1'=0); //passage à l'état critique, message à envoyer
//[time] (s1=0) -> (s1'=1);      

[time] (s1=1) & busy & (h1=0)  -> (s1'=1); // on attend que le canal soit libre

[] (s1=1) & free & (h1=0) -> (s1'=2) & (h1'=sigma); //On passe à l'envoi du message

//[time] (s1=0) -> (s1'=0);
[time] (s1=7) & (alea1>0) -> (alea1'=alea1-1) ; //le temps passe
[time] (s1=2) & (h1>0) -> (h1'=h1-1) ; //le temps passe
[time] (s1=3) & (h1>0) -> (h1'=h1-1) ; //le temps passe
[time] (s1=5) & (h1>0) -> (h1'=h1-1) ; //le temps passe
[time] (s1=6) & (h1>0) -> (h1'=h1-1) ; //le temps passe
[time] (s1=9) & (h1>0) -> (h1'=h1-1) ; //le temps passe


[send1] (s1=2) & (h1=0) & free -> (s1'=3) & (h1'=sigma);  //Au bout de sigma le message est envoyé

[send1] (s1=2) & (h1=0) & busy -> (s1'=6) & (h1'=sigma) & (col1'=min(10,col1+1)) & (calcul1'=1);  //Il y a eu collision

[verify1] (s1=3) & (h1=0) -> (s1'=4); // On va vérifier au bout de 2sigma

[] (s1=4) & !garbled -> (s1'=5) & (h1'=lambda-sigma); //le message passera

[finish1] (s1=5) & (h1=0) -> (s1'=8); //le temps passe le message est passé

[] (s1=8) -> (s1'=0) & (col1'=0); //retour à l'état d'origine

[] (s1=4) & garbled -> (s1'=6) & (h1'=sigma) & (col1'=min(10,col1+1)) & (calcul1'=1); //il y a eu collision

//Calcul du temps aléatoire a faire ici

[](s1=6) & (calcul1=1) & (nbc1=0) & (h1=0) -> (nbc1'=col1);

[](s1=6) & (nbc1=10) -> 0.5 : (n10'=0) & (nbc1'=nbc1-1) + 0.5 : (n10'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=9 -> 1/2 : (n9'=0) & (nbc1'=nbc1-1) + 1/2 : (n9'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=8 -> 1/2 : (n8'=0) & (nbc1'=nbc1-1) + 1/2 : (n8'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=7 -> 1/2 : (n7'=0) & (nbc1'=nbc1-1) + 1/2 : (n7'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=6 -> 0.5 : (n6'=0) & (nbc1'=nbc1-1) + 0.5 : (n6'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=5 -> 0.5 : (n5'=0) & (nbc1'=nbc1-1) + 0.5 : (n5'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=4 -> 0.5 : (n4'=0) & (nbc1'=nbc1-1) + 0.5 : (n4'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=3 -> 0.5 : (n3'=0) & (nbc1'=nbc1-1) + 0.5 : (n3'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=2 -> 0.5 : (n2'=0) & (nbc1'=nbc1-1) + 0.5 : (n2'=1) & (nbc1'=nbc1-1);
[]s1=6 & nbc1=1 -> 0.5 : (n1'=0) & (nbc1'=nbc1-1) & (calcul1'=0) + 0.5 : (n1'=1) & (nbc1'=nbc1-1) & (calcul1'=0);

[](s1=6) & (nbc1=0) & (calcul1=0) -> (alea1'=n1+2*n2+4*n3+8*n4+16*n5+32*n6+64*n7+128*n8+256*n9+512*n10) & (n1'=0) & (n2'=0) & (n3'=0) & (n4'=0) & (n5'=0) & (n6'=0) & (s1'=9) & (h1'=1) & (n7'=0) & (n8'=0) & (n9'=0) & (n10'=0); 

[finish1] (s1=9) & (h1=0) -> (s1'=7);

[] (s1=7) & (alea1=0) -> (s1'=1); 
//le canal se vide, on retourne en attente mais avec un temps aleatoire

endmodule

module 

Sender2=Sender1 [h1=h2,alea1=alea2,col1=col2,s1=s2,nbc1=nbc2,calcul1=calcul2,n1=m1,n2=m2,n3=m3,n4=m4,n5=m5,n6=m6,n7=m7,n8=m8,n9=m9,n10=m10,finish1=finish2,send1=send2,verify1=verify2,time=time]

endmodule
