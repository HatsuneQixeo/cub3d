#!/bin/bash
# Compile flags
cc="gcc"
extra="-Wextra"
error="-Werror"
cflags="-Wall $extra $error -g"
unused="-Wno-unused"
unused_set="$unused-parameter $unused-function $unused-variable"
san="-fsanitize=address -D SAN=1"

# Files
src="$1"
libft="libft.a -Iinclude"
exlib="experiment/exlib/exlib.a -Iexperiment/exlib/include"
prg="$(basename ${src//.c/.miku})"
compile=true

function esh_echo()
{
	echo "exp: $@"
}

function esh_errorexit()
{
	esh_echo "$@" >&2
	exit 1
}

function removeflag()
{
	local	flag="$1"
	
	if [[ "$cflags" =~ "$flag" ]]
	then
		cflags="${cflags//"$flag"/}"
		return 0
	else
		return 1
	fi
}

function addflag()
{
	local	flag="$1"
	
	if ! [[ "$cflags" =~ "$flag" ]]
	then
		cflags+=" $flag"
		return 0
	else
		return 1
	fi
}

if [ $# -eq 0 ]
then
	esh_errorexit 'Please provide a source file with main for testing'
elif ! [ -e "$src" ]
then
	esh_errorexit "File not found: $src"
elif [ -d "$src" ]
then
	esh_errorexit "Is a directory: $src"
elif [[ "$src" != *".c" ]]
then
	esh_errorexit "Not a C Source file: $src"
fi

messages=()
for arg in "${@:2}"
do
	case "$arg" in
	'nocom')
		esh_echo 'Skipped compilation'
		compile=false
		break
	;;
	"san")
		addflag "$san" && messages+=('Sanitizer: ON')
	;;
	'noextra')
		removeflag "$extra" && messages+=("Excluding $extra flag")
	;;
	'noerror')
		removeflag "$error" && messages+=("Excluding $error flag")
	;;
	'nounused')
		addflag "$unused_set" && messages+=("Including $unused_set flag")
	;;
	'noopti')
		addflag "-O0" && messages+=('No optimisation')
	;;
	*)
		esh_echo "Unknown flag: $arg"
		<< EOF cat
Available flag are:
	nocom:		Skip compilation
	san:		Compile with $san
	noextra:	Compile without $extra
	noerror:	Compile without $error
	nounused:	Compile with $unused_set
	noopti:		Compile with optimisation off
EOF
		exit 1
	;;
	esac
done

if [ $compile != false ]
then
	compile="$cc $cflags $src $libft $exlib -o $prg"
	for msg in "${messages[@]}"
	do
		echo "$msg"
	done
	make $([[ "$cflags" =~ "$san" ]] && echo "SAN=1")&& make -C experiment/exlib &&
	esh_echo $compile &&
	$compile &&
	esh_echo "Compiled: $(basename $prg)"
fi

[ $? -ne 0 ] && exit 1

"./$prg"

# BUG: make is executed in the current working directory, where the bash script is ran
# so it could be running another make if not executed it's own directory
