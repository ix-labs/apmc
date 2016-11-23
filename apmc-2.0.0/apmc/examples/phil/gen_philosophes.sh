#! /bin/sh

if [ $# -ne 1 ] ; then
    echo "Usage: $0 nb_philo"
    exit
fi

file="phil$1.prop"
echo "Generating $file"
echo "true U (" > "$file"
echo "(" >> "$file"
i=1
while [ $i -lt $1 ] ; do
    echo -n "((p$i>0) & (p$i<8)) | " >> "$file"
    i=$(( $i + 1 ))
done
echo "(p$i>0) & (p$i<8)))" >> "$file"
echo "& X ( true U (" >> "$file"
i=1
while [ $i -lt $1 ] ; do
    echo -n "(p$i>7) | " >> "$file"
    i=$(( $i + 1 ))
done
echo "(p$i>7)))" >> "$file"
#echo ")" >> "$file"

file="phil$1.pm"
echo "Generating $file"
echo "// randomized dining philosophers [PZ86]" > "$file"
echo "// dxp/gxn 12/12/99" >> "$file"
echo "probabilistic" >> "$file"
echo "// atomic formulae" >> "$file"
echo "// left fork free and right fork free resp" >> "$file"
echo "formula lfree = p2=0..4,6,10;" >> "$file"
echo "formula rfree = p$1=0..3,5,7;" >> "$file"
echo "module phil1" >> "$file"
echo "	p1: [0..10];" >> "$file"
echo "	// made probabilistic (0.2 stay thinking, 0.8 become hungry)" >> "$file"
echo "	[] p1=0 -> 0.2 : p1'=0 + 0.8 : p1'=1;" >> "$file"
echo "	[] p1=1 -> 0.5 : p1'=2 + 0.5 : p1'=3;" >> "$file"
echo "	[] p1=2 &  lfree -> p1'=4;" >> "$file"
echo "	[] p1=2 & !lfree -> p1'=2;" >> "$file"
echo "	[] p1=3 &  rfree -> p1'=5;" >> "$file"
echo "	[] p1=3 & !rfree -> p1'=3;" >> "$file"
echo "	[] p1=4 &  rfree -> p1'=8;" >> "$file"
echo "	[] p1=4 & !rfree -> p1'=6;" >> "$file"
echo "	[] p1=5 &  lfree -> p1'=8;" >> "$file"
echo "	[] p1=5 & !lfree -> p1'=7;" >> "$file"
echo "	[] p1=6  -> p1'=1;" >> "$file"
echo "	[] p1=7  -> p1'=1;" >> "$file"
echo "	[] p1=8  -> p1'=9;" >> "$file"
echo "	[] p1=9  -> p1'=10;" >> "$file"
echo "	[] p1=10 -> p1'=0;" >> "$file"
echo "endmodule" >> "$file"
echo "// construct further modules through renaming" >> "$file"
i=2
while [ $i -lt $1 ] ; do
    j=$(( $i + 1 ))
    k=$(( $i - 1 ))
    echo "module phil$i  = phil1 [p1=p$i,  p2=p$j,  p$1=p$k]  endmodule" >> "$file"
    i=$(( $i + 1))
done
j=$(( $1 - 1 ))
echo "module phil$1 = phil1 [p1=p$1, p2=p1,  p$1=p$j] endmodule" >> "$file"
echo "Finished !"