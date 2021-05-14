declare -a fruits
fruits=(orange apple banana peach strawberry)
echo "this is what u got ${fruits[*]}"
read fruit

if [[ $fruit == ${fruits[0]} ]]; then echo "${fruits[1]} ${fruits[2]} ${fruits[3]} ${fruits[4]}";
elif [[ $fruit == ${fruits[1]} ]]; then echo "${fruits[2]} ${fruits[3]} ${fruits[4]}";
elif [[ $fruit == ${fruits[2]} ]]; then echo "${fruits[3]} ${fruits[4]}";
elif [[ $fruit == ${fruits[3]} ]]; then echo ${fruits[4]};
elif [[ $fruit == ${fruits[4]} ]]; then echo '';
else echo "waterMelon";
fi
echo "*************************************"

# case $fruit in ${fruits[0]}) echo "${fruits[1]} ${fruits[2]} ${fruits[3]} ${fruits[4]}";;
#                 *)
#                 esac