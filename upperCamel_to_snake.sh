# Back when I didn't know norminette allows enum to have upper camel case

echo "UPPER_CAMEL_TO_SNAKE:"
echo "$@" | sed 's/\([a-z]\)\([A-Z]\)/\1_\2/g' | tr '[:lower:]' '[:upper:]'
