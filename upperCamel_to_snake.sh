# Back when I didn't know norminette allows enum to have UpperCamelCase

echo "UpperCamel_TO_UPPER_SNAKE:"
echo "$@" | sed 's/\([a-z]\)\([A-Z]\)/\1_\2/g' | tr '[:lower:]' '[:upper:]'
