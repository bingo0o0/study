GIT_SUB_CMD="clone init"

_foo()
{
	COMPREPLY=();
	local cur=${COMP_WORDS[$COMP_CWORD]};
	local cmd=${COMP_WORDS[$COMP_CWORD-1]};
	
#	echo -e "\e[33m$cmd\e[m"
	case $cmd in
	'foo')
		COMPREPLY=( $(compgen -W "${GIT_SUB_CMD}" -- $cur) );;
	'*')
		;;
	esac
	return 0;
}

complete -F _foo foo
