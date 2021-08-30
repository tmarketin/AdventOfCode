prefix="abcdef"
for (( i = 0; i < 1000000; i++ )); do
  str="$prefix""$i"
  hash=`echo -n "$str" | md5sum -b | awk '{print substr($1,1,5)}'`
  if [ "$hash" == "00000" ]; then
    echo "$i""  ""$hash"
    break
  fi
done