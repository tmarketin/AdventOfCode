infile="day16.dat"
declare -A data
data[children]=3
data[cats]=7
data[samoyeds]=2
data[pomeranians]=3
data[akitas]=0
data[vizslas]=0
data[goldfish]=5
data[trees]=3
data[cars]=2
data[perfumes]=1
while read line
do
  Suenum=`echo "$line" | awk '{print $2}' | sed 's/://g'`
  cat1=`echo "$line" | awk '{print $3}' | sed 's/://g'`
  cat1val=`echo "$line" | awk '{print $4}' | sed 's/,//'`
  cat2=`echo "$line" | awk '{print $5}' | sed 's/://g'`
  cat2val=`echo "$line" | awk '{print $6}' | sed 's/,//g'`
  cat3=`echo "$line" | awk '{print $7}' | sed 's/://g'`
  cat3val=`echo "$line" | awk '{print $NF}'`
  cat1res=0
  if [ "$cat1" == "cats" -o "$cat1" == "trees" ]; then
    if [ "$cat1val" -gt ${data[$cat1]} ]; then
      cat1res=1
    fi
  elif [ "$cat1" == "pomeranians" -o "$cat1" == "goldfish" ]; then
    if [ "$cat1val" -lt ${data[$cat1]} ]; then
      cat1res=1
    fi
  else
    if [ "$cat1val" -eq ${data[$cat1]} ]; then
      cat1res=1
    fi
  fi
  cat2res=0
  if [ "$cat2" == "cats" -o "$cat2" == "trees" ]; then
    if [ "$cat2val" -gt ${data[$cat2]} ]; then
      cat2res=1
    fi
  elif [ "$cat2" == "pomeranians" -o "$cat2" == "goldfish" ]; then
    if [ "$cat2val" -lt ${data[$cat2]} ]; then
      cat2res=1
    fi
  else
    if [ "$cat2val" -eq ${data[$cat2]} ]; then
      cat2res=1
    fi
  fi
  cat3res=0
  if [ "$cat3" == "cats" -o "$cat3" == "trees" ]; then
    if [ "$cat3val" -gt ${data[$cat3]} ]; then
      cat3res=1
    fi
  elif [ "$cat3" == "pomeranians" -o "$cat3" == "goldfish" ]; then
    if [ "$cat3val" -lt ${data[$cat3]} ]; then
      cat3res=1
    fi
  else
    if [ "$cat3val" -eq ${data[$cat3]} ]; then
      cat3res=1
    fi
  fi
  if [ $cat1res -eq 1 -a $cat2res -eq 1 -a $cat3res -eq 1 ]; then
    echo "$Suenum"
  fi
done < "$infile"