for i in *.rb; do
    ruby $i > $i.sh
    source $i.sh
    rm -f $i.sh
done
