function printall ()
{
	for localarg in "$@"
	do
		echo "arg: $localarg"
	done
}

# $@ seems to be a smarter version of $* inside quote,
# $* is just expanding the content like variable
# Whereas $@ will partition like argv[?]
printall "$@"
printall "$*"
# No difference without quote
printall $@
printall $*

# Doesn't make any difference when not pass as argv or range based loop
# echo "$@"
# echo "$*"
# Doesn't make any difference outside of quote either, of course
# echo $@
# echo $*
